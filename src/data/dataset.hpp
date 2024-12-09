#pragma once

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

 private:
  std::vector<Sample> data;
  std::set<std::string> locations;
  std::set<std::string> pollutants;
  void checkDataExists() const;
};
