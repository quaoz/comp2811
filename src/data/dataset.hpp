#pragma once

#include <set>
#include <vector>
#include <unordered_map>

#include "sample.hpp"

class WaterQalDataset {
 public:
  WaterQalDataset() {}
  WaterQalDataset(const std::string& filename) { loadData(filename); }

  void loadData(const std::string&);

  int size() const { return data.size(); }
  Sample operator[](int index) const { return data.at(index); }

  std::set<std::string> getLocations() const { return locations; }
  std::set<std::string> getPollutants() const { return pollutants; }

  std::vector<Sample> getLocationSamples(const std::string& location) const;
  std::vector<Sample> getLocationSamples(
    const std::set<std::string>& locations) const;

  std::vector<Sample> getPollutantSamples(const std::string& pollutant) const;
  std::vector<Sample> getPollutantSamples(
    const std::set<std::string>& pollutants) const;

 private:
  std::vector<Sample> data;
  std::set<std::string> locations;
  std::set<std::string> pollutants;
  std::unordered_map<std::string, std::vector<Sample>> locationsMap;
  std::unordered_map<std::string, std::vector<Sample>> pollutantsMap;
  void checkDataExists() const;
};
