PROJECT(MOPSI_Project)

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${d}/CMake")


add_executable(MOPSI_Project main.cpp functions.cpp fftw3.h)
