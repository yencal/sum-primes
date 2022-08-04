cmake_minimum_required(VERSION 3.8)

set(This SumPrimes)

project(${This} C CXX)

find_package(MPI REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include_directories(sum_primes_serial)
add_subdirectory(sum_primes_serial)

include_directories(sum_primes_MPI)
add_subdirectory(sum_primes_MPI)

if (TEST)
  add_subdirectory(googletest)
endif(TEST)
