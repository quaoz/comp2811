cmake_minimum_required(VERSION 3.16)

project(cwk2 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Charts)
qt_standard_project_setup()

qt_add_executable(quaketool
    src/main.cpp
    src/window.cpp
    src/data/dataset.cpp
    src/data/model.cpp
    src/pages/table.cpp
    src/pages/pops.cpp
    src/pages/litter.cpp
    src/pages/pollutants.cpp
    src/pages/compliance.cpp
    src/pages/flourinated.cpp
)

target_link_libraries(quaketool PRIVATE Qt6::Widgets Qt6::Charts)

set_target_properties(quaketool PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE OFF
)

install(TARGETS quaketool DESTINATION bin)
