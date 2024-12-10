#pragma once

#include <map>
#include <set>
#include <vector>

#include "sample.hpp"

class QuakeDataset {
 public:
  QuakeDataset() {}
  QuakeDataset(const std::string& filename) { loadData(filename); }
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
  std::map<std::string, std::vector<Sample>, std::greater<std::string>>
    locationsMap;
  std::map<std::string, std::vector<Sample>, std::greater<std::string>>
    pollutantsMap;
  void checkDataExists() const;
};
