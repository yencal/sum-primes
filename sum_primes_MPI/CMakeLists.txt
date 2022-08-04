cmake_minimum_required(VERSION 3.8)

set(This SumPrimesMPI)

project(${This} C CXX)

find_package(MPI REQUIRED)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(Headers
    sum_primes_mpi.h
    utilities.h
)

set(Sources
    sum_primes_mpi.cpp
    utilities.cpp
    main.cpp
)

add_executable(${This}Exec ${Sources} ${Headers})
target_link_libraries(${This}Exec MPI::MPI_CXX)

#-----------------------------------------------
# Testing stuff
#-----------------------------------------------
if (TEST)
  add_subdirectory(test)

  add_library(${This} STATIC ${Sources} ${Headers})
  target_link_libraries(${This} MPI::MPI_CXX)
endif(TEST)
