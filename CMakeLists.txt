# Minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Project's name
project(EnvSetup CXX)

# Current C++ standard, since 23 is not yet supported
set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/external) 
if(APPLE)
    link_directories(${PROJECT_SOURCE_DIR}/lib/mac) 
else()
    link_directories(${PROJECT_SOURCE_DIR}/lib) 
endif()

# Add executable
add_executable(${PROJECT_NAME} src/Main.cpp)

# Link the jsoncpp library
target_link_libraries(${PROJECT_NAME} jsoncpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
