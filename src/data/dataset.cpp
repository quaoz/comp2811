#include "dataset.hpp"

#include <QDateTime>
#include <QFuture>
#include <QFutureSynchronizer>
#include <QWidget>
#include <QtConcurrent/QtConcurrent>
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <vector>

#include "csv.hpp"
#include "sample.hpp"

using namespace std;

void WaterQalDataset::loadData(const string& filename) {
  csv::CSVReader reader(filename);

  data.clear();
  locationsMap.clear();
  pollutantsMap.clear();
  locations.clear();
  pollutants.clear();

  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  auto t1 = high_resolution_clock::now();

  map<string, vector<Sample>> dateSampleMap;
  for (const auto& row : reader) {
    SamplingPoint const samplingPoint{
      row["sample.samplingPoint"].get<string>(),
      row["sample.samplingPoint.notation"].get<string>(),
      row["sample.samplingPoint.label"].get<string>(),
      row["sample.samplingPoint.easting"].get<int>(),
      row["sample.samplingPoint.northing"].get<int>(),
    };

    Determinand const determinand{
      row["determinand.label"].get<string>(),
      row["determinand.definition"].get<string>(),
      row["determinand.notation"].get<int>(),
      row["determinand.unit.label"].get<string>(),
    };

    Sample const sample{
      row["@id"].get<string>(),
      samplingPoint,
      row["sample.sampleDateTime"].get<string>(),
      determinand,
      row["resultQualifier.notation"].get<string>(),
      row["result"].get<double>(),
      row["codedResultInterpretation.interpretation"].get<string>(),
      row["sample.sampledMaterialType.label"].get<string>(),
      row["sample.isComplianceSample"].get<string>(),
      row["sample.purpose.label"].get<string>(),
    };

    dateSampleMap[sample.getSampleDateTime()].push_back(sample);
  }

  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "main body: " << ms_double.count() << "ms\n";

  /* Data sorting:
   *
   * As many pages require the ability to filter by location and pollutant type
   * it is more efficient to construct several hash map on data load to avoid
   * having to filter the full dataset ever time it is necessary to filter by
   * location or pollutant. Additionally it is necessary for the charts that the
   * data is ordered from earliest to latest so the entier data set and all
   * vectors constructed from it are ordered from earliest date to latest date.
   *
   * data          : vec of samples ordered from earliest date to latest date
   *
   * pollutants    : ordered set of all pollutants
   * locations     : ordered set of all locations
   *
   * pollutantsMap : map of pollutant to a vec of samples
   * locationsMap  : map of location to a vec of samples
   *
   */

  QFutureSynchronizer<void> synchronizer;

  t1 = high_resolution_clock::now();

  synchronizer.addFuture(QtConcurrent::run([this, dateSampleMap]() {
    data.reserve(dateSampleMap.size());
    for (const auto& entry : dateSampleMap) {
      data.insert(data.end(), entry.second.begin(), entry.second.end());
    }
  }));

  synchronizer.addFuture(QtConcurrent::run([this, dateSampleMap]() {
    pollutantsMap.reserve(dateSampleMap.size());

    for (const auto& entry : dateSampleMap) {
      for (const auto& sample : entry.second) {
        pollutants.insert(sample.getDeterminand().getLabel());
        pollutantsMap[sample.getDeterminand().getLabel()].push_back(sample);
      }
    }
  }));

  synchronizer.addFuture(QtConcurrent::run([this, dateSampleMap]() {
    locationsMap.reserve(dateSampleMap.size());

    for (const auto& entry : dateSampleMap) {
      for (const auto& sample : entry.second) {
        locations.insert(sample.getSamplingPoint().getLabel());
        locationsMap[sample.getSamplingPoint().getLabel()].push_back(sample);
      }
    }
  }));

  synchronizer.waitForFinished();

  minDate = data.at(0).getSampleDateTime();
  maxDate = data.at(data.size() - 1).getSampleDateTime();
  startDate = minDate;
  endDate = maxDate;

  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "processing: " << ms_double.count() << "ms\n";
}

struct sampleCmp {
  bool operator()(const Sample& a, const Sample& b) const {
    return a.getSampleDateTime() > b.getSampleDateTime();
  }

  bool operator()(const Sample& sample, const std::string& date) const {
    return sample.getSampleDateTime() < date;
  }

  bool operator()(const std::string& date, const Sample& sample) const {
    return date < sample.getSampleDateTime();
  }
};

std::vector<Sample> WaterQalDataset::getLocationSamples(
  const std::string& location) const {
  auto it = locationsMap.find(location);
  if (it != locationsMap.end()) {
    return this->mask(it->second);
  } else {
    return {};
  }
}

std::vector<Sample> WaterQalDataset::getPollutantSamples(
  const std::string& pollutant) const {
  auto it = pollutantsMap.find(pollutant);
  if (it != pollutantsMap.end()) {
    return this->mask(it->second);
  } else {
    return {};
  }
}

std::vector<Sample> WaterQalDataset::getLocationSamples(
  const std::set<std::string>& locations) const {
  std::vector<Sample> samples;

  for (const auto& location : locations) {
    auto current = getLocationSamples(location);
    std::vector<Sample> temp;

    set_union(samples.begin(), samples.end(), current.begin(), current.end(),
              back_inserter(temp), sampleCmp());
    samples.swap(temp);
  }

  return this->mask(samples);
}

std::vector<Sample> WaterQalDataset::getPollutantSamples(
  const std::set<std::string>& pollutants) const {
  vector<Sample> samples;

  for (const auto& pollutant : pollutants) {
    auto current = getPollutantSamples(pollutant);
    vector<Sample> temp;

    set_union(samples.begin(), samples.end(), current.begin(), current.end(),
              back_inserter(temp), sampleCmp());
    samples.swap(temp);
  }

  return this->mask(samples);
}

void WaterQalDataset::setDataMask(const std::string& startDate,
                                  const std::string& endDate) {
  this->startDate = startDate;
  this->endDate = endDate;
  emit dataChanged();
}

void WaterQalDataset::resetDataMask() {
  this->startDate = minDate;
  this->endDate = maxDate;
  emit dataChanged();
}

std::vector<Sample> WaterQalDataset::mask(std::vector<Sample> samples) const {
  if (samples.empty()) { return samples; }

  std::vector<Sample> maskedSamples = {};

  // find bounds
  auto lower =
    std::lower_bound(samples.begin(), samples.end(), startDate, sampleCmp());
  auto upper = std::upper_bound(lower, samples.end(), endDate, sampleCmp());

  maskedSamples.insert(maskedSamples.end(), lower, upper);
  return maskedSamples;
}

void WaterQalDataset::checkDataExists() const {
  if (size() == 0) { throw std::runtime_error("Dataset is empty!"); }
}
