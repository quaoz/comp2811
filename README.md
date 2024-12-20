# COMP2811 Coursework 3 (Group 26)

## Group Member
Full Names and Student IDs:
-Yuan He Pang id: 201905231
-Matthew Alwan id: 201730832
-Zijian Ni id: 201753248
-Adil Aabideen id: 201706416
-Catherine Weightman id: 201699989

## Waterqaltool

## Project Overview

Waterqaltool is a desktop application designed to visualize and manage the environmental water quality data of UK. The tool allows users to filter, explore, and analyze datasets using intuitive tables, charts, and summary dashboards. It supports multilingual translations to cater to a diverse user base.

## Features
 1. Data Visualization
 • View water quality data in a tabular format.
 • Summary dashboard for compliance and non-compliance samples.
 2. Filtering
 • Filter data by:
 • Location
 • Pollutant
 • Compliance level (Compliant, Non-Compliant, etc.)
 3. Multilingual Support
 • Supports dynamic translations into multiple languages (e.g., English, French).
 • Automatically detects the system’s locale or allows manual language selection.
 4. Chart Visualization
 • Visualize pollutant trends using line and bar charts.
 • Litter distribution via pie charts.
 5. User-Friendly Interface
 • Clear and simple layout with interactive elements for seamless data exploration.

Setup and Installation Requirements
 • Operating System: macOS, Windows, FEPS Red Hat system or Linux VM
 • Qt Version: Qt 6.8 or higher installed
 • Compiler: C++17 compatible compiler (e.g., GCC, MSVC, Clang)

Steps
 1. Clone the Repository

```sh
git clone https://github.com/quaoz/comp2811.git
cd comp2811
```

 2. Build the Application
 • Create a build directory:

```sh
mkdir build && cd build
```

 • Configure the build with CMake:

```sh
cmake ..
```

 • Build the application:

```sh
make waterqaltool
```

(or just `make` by itself)


 3. Run the Application with

```
./waterqaltool
```

## Dependencies

Required Libraries
 1. Qt Components:
 • Widgets
 • Charts
 • Linguist Tools
 2. Compiler and Build Tools:
 • CMake (minimum version 3.16)
 • GCC/Clang
 3. Additional Dependencies:
 • Ensure required libraries are available for CSV parsing (e.g., csv.hpp).

## File Structure

```
.
├── CMakeLists.txt
├── README.md
├── data
│   └── Y-2024.csv
├── src
│   ├── data
│   │   ├── csv.hpp
│   │   ├── dataset.cpp
│   │   ├── dataset.hpp
│   │   └── sample.hpp
│   ├── main.cpp
│   ├── pages
│   │   ├── card.cpp
│   │   ├── card.hpp
│   │   ├── compliance.cpp
│   │   ├── compliance.hpp
│   │   ├── dashboard.cpp
│   │   ├── dashboard.hpp
│   │   ├── fluorinated.cpp
│   │   ├── fluorinated.hpp
│   │   ├── litter.cpp
│   │   ├── litter.hpp
│   │   ├── pollutants.cpp
│   │   ├── pollutants.hpp
│   │   ├── pops.cpp
│   │   ├── pops.hpp
│   │   ├── timeseries.cpp
│   │   └── timeseries.hpp
│   ├── window.cpp
│   └── window.hpp
├── waterqaltool_en.qm      # Compiled English translations
├── waterqaltool_en.ts      # English translations
├── waterqaltool_fr.qm      # Compiled French translations
└── waterqaltool_fr.ts      # French translations
```

## Known Issues
 1. Translation Updates: If new user-visible strings are added, .ts files must be updated and recompiled.
 2. Red Hat Compatibility: Ensure the application runs on the FEPS Red Hat system. Certain Qt dependencies may require additional configuration.
 3. Large Datasets: Performance may degrade when loading extremely large CSV files.
