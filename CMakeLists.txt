PROJECT(RK4_TEST)

cmake_minimum_required(VERSION 2.6)

# Compilation options
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -std=c++11")

# OPTINS for MPI
option(WITH_MPI "Enable MPI processing" OFF)
if(WITH_MPI)
    MESSAGE(STATUS "MPI mode")
    add_definitions(-DWITH_MPI)
endif()


# includes and sources
INCLUDE_DIRECTORIES(${RK4_TEST_SOURCE_DIR}/rk4_lib ${RK4_TEST_SOURCE_DIR}/IO ${RK4_TEST_SOURCE_DIR}/MPI_communications)
FILE(GLOB rk4_CXX "${RK4_TEST_SOURCE_DIR}/rk4_lib/*.cpp")
FILE(GLOB rk4IO_CXX "${RK4_TEST_SOURCE_DIR}/IO/*.cpp")
FILE(GLOB rk4MPI_CXX "${RK4_TEST_SOURCE_DIR}/MPI_communications/*.cpp")

# rk4Lib library
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
ADD_LIBRARY(rk4 SHARED  ${rk4_CXX})

# Binary
ADD_EXECUTABLE(rk4Launcher rk4_launcher.cpp ${rk4IO_CXX} ${rk4MPI_CXX})
TARGET_LINK_LIBRARIES(rk4Launcher rk4)
