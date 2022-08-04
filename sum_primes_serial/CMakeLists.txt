cmake_minimum_required(VERSION 3.8)

set(This SumPrimesSerial)

project(${This} C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(Headers
    sum_primes_serial.h
)

set(Sources
    sum_primes_serial.cpp
    main.cpp
)

add_executable(${This}Exec ${Sources} ${Headers})

#-----------------------------------------------
# Testing stuff
#-----------------------------------------------
if (TEST)
  add_subdirectory(test)

  add_library(${This} STATIC ${Sources} ${Headers})
endif(TEST)
