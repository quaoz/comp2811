#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "data.hpp"
#include "csv.hpp"

using namespace std;

WaterQualityRecord::WaterQualityRecord(const string& label, const string& dt, const string& def, const string& notation, double result, const string& unitLabel, const string& materialType, bool compliant, const string& purpose):
    samplingPointLabel, sampleDateTime, determinandDefinition, determinandNotation, result, determinandUnitLabel, sampledMaterialType,  isComplianceSample, purposeLabel


/* ostream& operator<<(ostream& out, const Quake& quake)
{
  return out << "Location: " << quake.getLocation()
             << "\nDateTime: " << quake.getLatitude() << " deg"
             << "\nLongitude: " << quake.getLongitude() << " deg"
             << "\nDepth: " << quake.getDepth() << " km"
             << "\nMagnitude: " << quake.getMagnitude() << endl;
}



std::string location;          // sample.samplingPoint.label
        std::string dateTime;              // sample.sampleDateTime
        std::string pollutant;       // determinand.definition
        std::string pollutantId;         // determinand.notation
        double result;                           // result
        std::string resultUnit;        // determinand.unit.label
        std::string materialType;         // sample.sampledMaterialType.label
        bool compliant;                 // sample.isComplianceSample
        std::string purpose;     */
/* std::string samplingPointLabel;
        std::string sampleDateTime;
        std::string determinandDefinition;
        std::string determinandNotation;
        double result;
        std::string determinandUnitLabel;
        std::string sampledMaterialType;
        bool isComplianceSample;
        std::string purposeLabel
{
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row: reader) {
    WaterQualityRecord WATERQUALITYRECORD{
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
    data.push_back(WATERQUALITYRECORD);
    }
} */