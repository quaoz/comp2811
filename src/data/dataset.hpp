#pragma once

#include <QObject>
#include <set>
#include <unordered_map>
#include <vector>

#include "sample.hpp"

/**
 * The dataset of water quality samples
 */
class WaterQalDataset : public QObject {
  Q_OBJECT

 public:
  /**
   * Default constructor
   */
  WaterQalDataset() {}

  /**
   * Constructor that loads the data from a CSV file
   *
   * @param filename The filename of the CSV file to load
   */
  WaterQalDataset(const std::string& filename) { loadData(filename); }

  /**
   * Loads the data from a CSV file
   *
   * @param filename The filename of the CSV file to load
   */
  void loadData(const std::string&);

  /**
   * Sets the data mask to only include samples within the date range
   *
   * @param startDate The start date of the mask
   * @param endDate   The end date of the mask
   */
  void setDataMask(const std::string& startDate, const std::string& endDate);

  /**
   * Resets the data mask to include all samples
   */
  void resetDataMask();

  /**
   * Returns the number of samples in the dataset
   *
   * @return The number of samples in the dataset
   */
  int size() const { return data.size(); }

  /**
   * Returns the sample at the given index
   *
   * @param index The index of the sample to return
   * @return      The sample at the given index
   */
  Sample at(int index) const { return data.at(index); }

  /**
   * Returns all locations in the dataset
   *
   * @return A set of all locations in the dataset
   */
  std::set<std::string> getLocations() const { return locations; }

  /**
   * Returns all pollutants in the dataset
   *
   * @return A set of all pollutants in the dataset
   */
  std::set<std::string> getPollutants() const { return pollutants; }

  /**
   * Returns all samples for a location
   *
   * @param locations The location to return samples for
   * @return          An ordered vector of samples for the given location
   */
  std::vector<Sample> getLocationSamples(const std::string& location) const;

  /**
   * Returns all samples for a set of locations
   *
   * @param locations The set of locations to return samples for
   * @return          An ordered vector of samples for the given locations
   */
  std::vector<Sample> getLocationSamples(
    const std::set<std::string>& locations) const;

  /**
   * Returns all samples for a location
   *
   * @param locations The location to return samples for
   * @return          An ordered vector of samples for the given location
   */
  std::vector<Sample> getPollutantSamples(const std::string& pollutant) const;

  /**
   * Returns all samples for a set of pollutants
   *
   * @param pollutants The set of pollutants to return samples for
   * @return           An ordered vector of samples for the given pollutants
   */
  std::vector<Sample> getPollutantSamples(
    const std::set<std::string>& pollutants) const;

  /**
   * Returns all samples
   *
   * @return An ordered vector of all samples
   */
  std::vector<Sample> getSamples() const { return mask(data); };

 signals:
  /**
   * Signal emitted when the data mask has changed
   */
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

  /**
   * Checks that the data exists
   */
  void checkDataExists() const;

  /**
   * Masks the samples to only include those within the date range
   *
   * @param samples The samples to mask
   * @return        The masked samples
   */
  std::vector<Sample> mask(std::vector<Sample> samples) const;
};
