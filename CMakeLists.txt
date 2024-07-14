cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(chat++ VERSION 1.0.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the nlohmann_json package
find_package(nlohmann_json 3.2.0 REQUIRED)

# Find the Boost package
find_package(Boost 1.65 REQUIRED COMPONENTS system)

# Include directories
include_directories(include)
include_directories(${Boost_INCLUDE_DIRS})
include_directories(${nlohmann_json_INCLUDE_DIRS})

# Add the executable
add_executable(chat++
    src/main.cpp
    src/client.cpp
    src/server.cpp
    src/message.cpp
    src/helper.cpp
)

# Add a test executable
file(GLOB TEST_SOURCES tests/*.cpp)
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
endforeach()

# Link the libraries
target_link_libraries(chat++ ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)