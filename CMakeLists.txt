cmake_minimum_required(VERSION 3.16)
project(FileNameEditor VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "/nfs/homes/bgoron/Qt/6.9.0/gcc_64")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_SOURCE_DIR}/include
)

file(GLOB_RECURSE HEADER_FILES
    "${CMAKE_SOURCE_DIR}/include/*.hpp"
)

set(SOURCES
    main.cpp
    source/controller/FileRenamerController.cpp
    source/view/MainWindow.cpp
)

set(RESOURCE_FILES
    ${CMAKE_SOURCE_DIR}/resources/resources.qrc
)

qt6_add_resources(QT_RESOURCES ${RESOURCE_FILES})

add_executable(FileRenamer
    ${SOURCES}
    ${HEADER_FILES}
    ${QT_RESOURCES}
)

target_link_libraries(FileRenamer PRIVATE Qt6::Widgets)
