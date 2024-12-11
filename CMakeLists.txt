cmake_minimum_required(VERSION 3.16)

project(
  cwk2
  VERSION 1.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS_DEBUG "-Og")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts LinguistTools)

set(TS_FILES quaketool_en.ts quaketool_fr.ts)

qt_standard_project_setup()

qt_add_executable(
  waterqaltool
  src/main.cpp
  src/window.cpp
  src/data/dataset.cpp
  src/pages/pops.cpp
  src/pages/litter.cpp
  src/pages/pollutants.cpp
  src/pages/compliance.cpp
  src/pages/fluorinated.cpp
  src/pages/dashboard.cpp
  src/pages/card.cpp
  src/pages/timeseries.cpp)

qt_add_translations(waterqaltool TS_FILES quaketool_fr.ts quaketool_en.ts)

target_link_libraries(waterqaltool PRIVATE Qt6::Widgets Qt6::Charts)

set_target_properties(waterqaltool PROPERTIES WIN32_EXECUTABLE ON MACOSX_BUNDLE
                                                                  OFF)

install(TARGETS waterqaltool DESTINATION bin)
