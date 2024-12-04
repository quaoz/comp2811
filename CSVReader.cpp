#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

class RowData {
public:
    std::string col1;
    std::string col2;
    std::string col3;

    RowData(const std::string &c1, const std::string &c2, const std::string &c3)
        : col1(c1), col2(c2), col3(c3) {}
};

class CSVReader {
public:
    static std::vector<RowData> readCSV(const std::string &filePath) {
        std::vector<RowData> data;
        std::ifstream file(filePath);

        if (!file.is_open()) {
            throw std::runtime_error("Could not open CSV file");
        }

        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::string col1, col2, col3;

            if (std::getline(ss, col1, ',') &&
                std::getline(ss, col2, ',') &&
                std::getline(ss, col3, ',')) {
                data.emplace_back(col1, col2, col3);
            }
        }
        file.close();
        return data;
    }
};