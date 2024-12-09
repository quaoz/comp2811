#include "dataset.hpp"

#include <QDateTime>
#include <QWidget>
#include <algorithm>
#include <numeric>
#include <queue>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "csv.hpp"
#include "sample.hpp"

using namespace std;

void QuakeDataset::loadData(const string& filename) {
  csv::CSVReader reader(filename);

  data.clear();

  using std::chrono::duration;
  using std::chrono::duration_cast;
  using std::chrono::high_resolution_clock;
  using std::chrono::milliseconds;

  auto t1 = high_resolution_clock::now();

  unordered_map<string, vector<Sample>> dateSampleMap;
  dateSampleMap.reserve(50000);
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

    dateSampleMap[sample.getSampleDateTime()].push_back(std::move(sample));
    locations.insert(sample.getSamplingPoint().getLabel());
    pollutants.insert(sample.getDeterminand().getLabel());
  }

  auto t2 = high_resolution_clock::now();
  duration<double, std::milli> ms_double = t2 - t1;
  std::cout << "main body: " << ms_double.count() << "ms\n";

  /* Data sorting:
   *
   * hashmap mapping each dateTime to a vector of samples constructed
   * dateTimes extracted from hashmap keys, appended to priority queue
   * pq drained, for each value corresponding vector from hashmap added to data
   *
   */

  t1 = high_resolution_clock::now();

  // construct priority queue of dates
  priority_queue<string, vector<string>, greater<string>> dates;
  for (const auto& entry : dateSampleMap) { dates.push(entry.first); }

  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "pq construct: " << ms_double.count() << "ms\n";

  t1 = high_resolution_clock::now();

  // drain priority queue
  data.reserve(dateSampleMap.size());
  for (; !dates.empty(); dates.pop()) {
    string const date = dates.top();
    auto& samples = dateSampleMap[date];
    data.insert(data.end(), std::make_move_iterator(samples.begin()),
                std::make_move_iterator(samples.end()));
  }

  t2 = high_resolution_clock::now();
  ms_double = t2 - t1;
  std::cout << "pq drain: " << ms_double.count() << "ms\n";
}

void QuakeDataset::checkDataExists() const {
  if (size() == 0) { throw std::runtime_error("Dataset is empty!"); }
}
