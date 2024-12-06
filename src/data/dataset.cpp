#include "dataset.hpp"

#include <algorithm>
#include <numeric>
#include <stdexcept>
#include <unordered_map>
#include <vector>

#include "csv.hpp"
#include "sample.hpp"

using namespace std;

void QuakeDataset::loadData(const string& filename) {
  csv::CSVReader reader(filename);

  data.clear();

  unordered_map<string, vector<Sample>> dateSampleMap;
  for (const auto& row : reader) {
    SamplingPoint samplingPoint{
      row["sample.samplingPoint"].get<string>(),
      row["sample.samplingPoint.notation"].get<string>(),
      row["sample.samplingPoint.label"].get<string>(),
      row["sample.samplingPoint.easting"].get<int>(),
      row["sample.samplingPoint.northing"].get<int>(),
    };

    Determinand determinand{
      row["determinand.label"].get<string>(),
      row["determinand.definition"].get<string>(),
      row["determinand.notation"].get<int>(),
      row["determinand.unit.label"].get<string>(),
    };

    Sample sample{
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

  /* Data sorting:
   *
   * samples appended to vector containing samples with same dateTime
   * iterate over dateTimes and construct ordered list
   * iterate over list of dateTimes and append corresponding vector to dataset
   *
   * as there are many samples for each dateTime it is more efficent to group
   * them by dateTime and then sort the vector of dateTimes
   *
   */

  // TODO: maybe more efficient to construct vector of keys and then sort
  //       to avoid expensive insertions
  int count = 0;
  vector<string> keys;
  for (auto& value : dateSampleMap) {
    int left = 0;
    int right = count;

    if (count <= 1) {
      if (count == 0 || keys[0].compare(value.first) < 0) {
        keys.push_back(value.first);
      } else {
        keys.insert(keys.begin(), value.first);
      }
    } else {
      while (left < right) {
        int mid = left + (right - left) / 2;
        if (keys[mid].compare(value.first) < 0) {
          left = mid + 1;
        } else {
          right = mid;
        }
      }
      keys.insert(keys.begin() + left, value.first);
    }

    count++;
  }

  for (auto& key : keys) {
    data.insert(data.end(), dateSampleMap[key].begin(),
                dateSampleMap[key].end());
  }
}

void QuakeDataset::checkDataExists() const {
  if (size() == 0) { throw std::runtime_error("Dataset is empty!"); }
}
