#pragma oncce

#include <iostream>
#include <string>

class WaterQualityRecord {
    public:
    // Attributes

    // Constructor
    waterQualityRecord(const std:string&, const std:string&, const std:string&, const std:string&, double, const std:string&, const std:string&, bool, const std:string&);

    std::string getLocation() const { return location; }
    std::string getDateTime() const { return dateTime; }
    std::string getPollutant() const { return pollutant; }
    std::string getPollutantId() const { return pollutantId; }
    double getResult() const { return result; }
    std::string getResultUnit() const { return resultUnit; }
    std::string getMaterialType() const { return materialType; }
    bool getCompliant() const { return compliant; }
    std::string getPurpose() const { return purpose; }


/*     st
    WaterQualityRecord(
        const std::string& spLabel, const std::string& sampleDateTime, const std::string& dDefinition,
        const std::string& dNotation, double result, const std::string& dUnitLabel,
        const std::string& smType, bool isCompliance, const std::string& purpose)
        : samplingPointLabel(spLabel), sampleDateTime(sampleDateTime), determinandDefinition(dDefinition),
          determinandNotation(dNotation), result(result), determinandUnitLabel(dUnitLabel),
          sampledMaterialType(smType), isComplianceSample(isCompliance), purposeLabel(purpose) {} */

    private:
        std::string location;          // sample.samplingPoint.label
        std::string dateTime;              // sample.sampleDateTime
        std::string pollutant;       // determinand.definition
        std::string pollutantId;         // determinand.notation
        double result;                           // result
        std::string resultUnit;        // determinand.unit.label
        std::string materialType;         // sample.sampledMaterialType.label
        bool compliant;                 // sample.isComplianceSample
        std::string purpose;                // sample.purpose.label

    // // Display record details
    // void display() const {
    //     std::cout << "Sampling Point Label: " << samplingPointLabel << "\n"
    //               << "Sample Date Time: " << sampleDateTime << "\n"
    //               << "Determinant Definition: " << determinandDefinition << "\n"
    //               << "Determinant Notation: " << determinandNotation << "\n"
    //               << "Result: " << result << " " << determinandUnitLabel << "\n"
    //               << "Sampled Material Type: " << sampledMaterialType << "\n"
    //               << "Compliance Sample: " << (isComplianceSample ? "Yes" : "No") << "\n"
    //               << "Purpose: " << purposeLabel << "\n"
    //               << std::endl;
    // }
};

std::ostream& operator << (std::ostream&, const WaterQualityRecord&);

	
