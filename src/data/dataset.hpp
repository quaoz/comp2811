#pragma once

#include <QObject>
#include <set>
#include <unordered_map>
#include <vector>

#include "sample.hpp"

class WaterQalDataset : public QObject {
  Q_OBJECT

 public:
  WaterQalDataset() {}
  WaterQalDataset(const std::string& filename) { loadData(filename); }

  void loadData(const std::string&);
  void setDataMask(const std::string& startDate, const std::string& endDate);
  void resetDataMask();

  int size() const { return data.size(); }
  Sample at(int index) const { return data.at(index); }

  std::set<std::string> getLocations() const { return locations; }
  std::set<std::string> getPollutants() const { return pollutants; }

  std::vector<Sample> getLocationSamples(const std::string& location) const;
  std::vector<Sample> getLocationSamples(
    const std::set<std::string>& locations) const;

  std::vector<Sample> getPollutantSamples(const std::string& pollutant) const;
  std::vector<Sample> getPollutantSamples(
    const std::set<std::string>& pollutants) const;

  std::vector<Sample> getSamples() const { return mask(data); };

 signals:
  void dataChanged();

 private:
  std::vector<Sample> data;
  std::set<std::string> locations;
  std::set<std::string> pollutants;
  std::unordered_map<std::string, std::vector<Sample>> locationsMap;
  std::unordered_map<std::string, std::vector<Sample>> pollutantsMap;

  std::string startDate;
  std::string endDate;
  std::string minDate;
  std::string maxDate;

  void checkDataExists() const;
  std::vector<Sample> mask(std::vector<Sample> samples) const;
};
