cmake_minimum_required(VERSION 2.6)

project (Mini8BVM)

#CORE FILES
file(GLOB
     source_files
     ./src/*.cpp
)
include_directories(${CMAKE_SOURCE_DIR}/include)

#Global Parameter
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Build sequence
add_executable(Mini8BVM ${source_files})