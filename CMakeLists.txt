cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(AVEngineerTest VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14) 
include(cmake/virtualfolders.cmake)


#Organize projects into virtual folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)
include_directories(${CMAKE_SOURCE_DIR})
set (APIS_PATH  $ENV{APIS_PATH_VS2017})
 include(cmake/libs/ffmpeg.cmake)

include_directories(include)
add_subdirectory(src)
