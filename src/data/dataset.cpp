#include "dataset.hpp"

#include <QDateTime>
#include <QWidget>
#include <algorithm>
#include <map>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <vector>

#include "csv.hpp"
#include "sample.hpp"

using namespace std;

void QuakeDataset::loadData(const string& filename) {
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

  map<string, vector<Sample>, greater<string>> dateSampleMap;
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
    locations.insert(sample.getSamplingPoint().getLabel());
    pollutants.insert(sample.getDeterminand().getLabel());
  }

  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "main body: " << ms_double.count() << "ms\n";

  /* Data sorting:
   *
   * ordered map mapping each dateTime to a vector of samples constructed
   * dateTimes extracted from hashmap keys, appended to priority queue
   * pq drained, for each value corresponding vector from hashmap added to data
   *
   */

  t1 = high_resolution_clock::now();

  // drain priority queue
  data.reserve(dateSampleMap.size());
  for (const auto& entry : dateSampleMap) {
    data.insert(data.end(), entry.second.begin(), entry.second.end());
  }

  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "pq drain: " << ms_double.count() << "ms\n";

  t1 = high_resolution_clock::now();
  locationsMap.reserve(dateSampleMap.size());
  pollutantsMap.reserve(dateSampleMap.size());
  for (const auto& sample : data) {
    locationsMap[sample.getSamplingPoint().getLabel()].push_back(sample);
    pollutantsMap[sample.getDeterminand().getLabel()].push_back(sample);
  }
  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "map const: " << ms_double.count() << "ms\n";
}

struct sampleCmp {
  bool operator()(const Sample& a, const Sample& b) const {
    return a.getSampleDateTime() > b.getSampleDateTime();
  }
};

std::vector<Sample> QuakeDataset::getLocationSamples(
  const std::string& location) const {
  auto it = locationsMap.find(location);
  if (it != locationsMap.end()) {
    return it->second;
  } else {
    return {};
  }
}

// TODO: inefficient merge strategy
std::vector<Sample> QuakeDataset::getLocationSamples(
  const std::set<std::string>& locations) const {
  vector<Sample> samples = {};

  for (const auto& location : locations) {
    auto current = getLocationSamples(location);
    vector<Sample> temp;
    set_union(samples.begin(), samples.end(), current.begin(), current.end(),
              back_inserter(temp), sampleCmp());
    samples.swap(temp);
  }

  return samples;
}

std::vector<Sample> QuakeDataset::getPollutantSamples(
  const std::string& pollutant) const {
  auto it = pollutantsMap.find(pollutant);
  if (it != pollutantsMap.end()) {
    return it->second;
  } else {
    return {};
  }
}

std::vector<Sample> QuakeDataset::getPollutantSamples(
  const std::set<std::string>& pollutants) const {
  vector<Sample> samples = {};

  for (const auto& pollutant : pollutants) {
    auto current = getPollutantSamples(pollutant);
    vector<Sample> temp;
    set_union(samples.begin(), samples.end(), current.begin(), current.end(),
              back_inserter(temp), sampleCmp());
    samples.swap(temp);
  }

  return samples;
}

void QuakeDataset::checkDataExists() const {
  if (size() == 0) { throw std::runtime_error("Dataset is empty!"); }
}
