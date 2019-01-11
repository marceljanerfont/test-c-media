cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(main VERSION 0.1.0 LANGUAGES CXX)
add_compile_options(-std=c++11)
 
file (TO_CMAKE_PATH  $ENV{APIS_PATH_VS2017}  APIS_PATH )
include_directories(include)
add_subdirectory(src)
