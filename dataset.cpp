// COMP2811 Coursework 1 sample solution: QuakeDataset class

#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"
#include "sample.hpp"

using namespace std;


void QuakeDataset::loadData(const string& filename)
{
  csv::CSVReader reader(filename);

  data.clear();

  for (const auto& row: reader) {
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
    data.push_back(sample);
  }
}

void QuakeDataset::checkDataExists() const
{
  if (size() == 0) {
    throw std::runtime_error("Dataset is empty!");
  }
}
