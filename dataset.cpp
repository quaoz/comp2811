#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"

using namespace std;

void WaterQualityDataSet::loadData(const string& filename)
{
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row: reader) {
    WaterQualityDataSet WATERQUALITYDATASET{
        row["sample.samplingPoint.label"].get<>(),
        row["sample.sampleDateTime"].get<>(),
        row["determinand.definition"].get<>(),
        row["determinand.notation"].get<>(),
        row["result"].get<bool>(),
        row["determinand.unit.label"].get<>(),
        row["sample.sampledMaterialType.label"].get<>(),
        row["sample.isComplianceSample"].get<double>(),
        row["sample.purpose.label"].get<>()
    };
    data.push_back(WATERQUALITYDATASET);
    }
}