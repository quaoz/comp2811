// COMP2811 Coursework 1 sample solution: QuakeDataset class

#pragma once

#include <vector>

#include "sample.hpp"

class QuakeDataset {
 public:
  QuakeDataset() {}
  QuakeDataset(const std::string& filename) { loadData(filename); }
  void loadData(const std::string&);
  int size() const { return data.size(); }
  Sample operator[](int index) const { return data.at(index); }

 private:
  std::vector<Sample> data;
  void checkDataExists() const;
};
