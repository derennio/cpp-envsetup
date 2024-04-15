# Minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(EnvSetup)

# Current C++ standard, since 23 is not yet supported
set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include) 
link_directories(${PROJECT_SOURCE_DIR}/lib) 

# Find the jsoncpp library
#find_package(jsoncpp REQUIRED)

# Add executable
add_executable(${PROJECT_NAME} src/Main.cpp)

# Link the jsoncpp library
#target_link_libraries(${PROJECT_NAME} jsoncpp_lib)
target_link_libraries(${PROJECT_NAME} jsoncpp)
