#pragma once

#include <stdbool.h>

#include <string>

class SamplingPoint {
 public:
  SamplingPoint(const std::string &id, const std::string &notation, const std::string &label, int easting, int northing)
    : id(id), notation(notation), label(label), easting(easting), northing(northing){};
  std::string getID() const { return id; };
  std::string getNotation() const { return notation; };
  std::string getLabel() const { return label; };
  int getEasting() const { return easting; };
  int getNorthing() const { return northing; };

 private:
  std::string id;        // sample.samplingPoint
  std::string notation;  // sample.samplingPoint.notation
  std::string label;     // sample.samplingPoint.label
  int easting;           // sample.samplingPoint.easting
  int northing;          // sample.samplingPoint.northing
};

class Determinand {
 public:
  Determinand(const std::string &label, const std::string &definition,
              int notation, const std::string &unitlabel)
    : label(label),
      definition(definition),
      notation(notation),
      unitLabel(unitlabel){};
  std::string getLabel() const { return label; };
  std::string getDefinition() const { return definition; };
  int getNotation() const { return notation; };
  std::string getUnitLabel() const { return unitLabel; };

 private:
  std::string label;       // determinand.label
  std::string definition;  // determinand.definition
  int notation;            // determinand.notation
  std::string unitLabel;   // determinand.unit.label
};

class Sample {
 public:
  Sample(const std::string &id, const SamplingPoint &samplingPoint,
         const std::string &sampleDateTime, const Determinand &determinand,
         const std::string &resultQualifier, const double result,
         const std::string &resultInterpretation,
         const std::string &sampledMaterialType, const std::string &compliant,
         const std::string &purpose)
    : id(id),
      samplingPoint(samplingPoint),
      sampleDateTime(sampleDateTime),
      determinand(determinand),
      resultQualifier(resultQualifier),
      result(result),
      resultInterpretation(resultInterpretation),
      sampledMaterialType(sampledMaterialType),
      compliant(compliant),
      purpose(purpose){};
  std::string getID() const { return id; };
  SamplingPoint getSamplingPoint() const { return samplingPoint; };
  std::string getSampleDateTime() const { return sampleDateTime; };
  Determinand getDeterminand() const { return determinand; };
  std::string getResultQualifier() const { return resultQualifier; };
  double getResult() const { return result; };
  std::string getResultInterpretation() const { return resultInterpretation; };
  std::string getSampledMaterialType() const { return sampledMaterialType; };
  std::string isComplianceSample() const { return compliant; }; // TODO: should be bool
  std::string getPurpose() const { return purpose; };

 private:
  std::string id;                    // @id
  SamplingPoint samplingPoint;       // sample.samplingPoint.*
  std::string sampleDateTime;        // sample.sampleDateTime
  Determinand determinand;           // determinand.*
  std::string resultQualifier;       // resultQualifier.notation
  double result;                     // result
  std::string resultInterpretation;  // codedResultInterpretation.interpretation
  std::string sampledMaterialType;   // sample.sampledMaterialType.label
  std::string compliant;             // sample.isComplianceSample
  std::string purpose;               // sample.purpose.label
};
