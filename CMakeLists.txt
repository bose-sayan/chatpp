cmake_minimum_required(VERSION 3.10)

# Set the project name and version
project(chat++ VERSION 1.0.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
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
add_executable(chat++ src/main.cpp)

# Link the libraries
target_link_libraries(chat++ ${Boost_LIBRARIES} nlohmann_json::nlohmann_json)