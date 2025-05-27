cmake_minimum_required(VERSION 3.16)
project(FileNameEditor VERSION 1.0 LANGUAGES CXX)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable automatic Qt6 handling (moc, uic, rcc)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Export compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include project headers for compiler and automoc
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

# Collect source and header files
file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

set(SOURCES
    main.cpp
    source/model/FileModel.cpp
    source/controller/FileRenamerController.cpp
    source/view/MainWindow.cpp
)

# Define Qt resource files
set(RESOURCE_FILES
    ${CMAKE_SOURCE_DIR}/resources/resources.qrc
)

# Generate Qt resource code
qt6_add_resources(QT_RESOURCES ${RESOURCE_FILES})

# Create executable with sources, headers, and resources
add_executable(FileRenamer
    ${SOURCES}
    ${HEADER_FILES}
    ${QT_RESOURCES}
)

# Link Qt6 Widgets
target_link_libraries(FileRenamer PRIVATE Qt6::Widgets)
