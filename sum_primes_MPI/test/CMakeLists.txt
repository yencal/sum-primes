cmake_minimum_required(VERSION 3.8)

set(This SumPrimesMPITests)

set(Sources
    sum_primes_mpi_tests.cpp
)

add_executable(${This} ${Sources})

link_directories(${CMAKE_BINARY_DIR}/sum_primes_serial)

target_link_libraries(${This} PUBLIC
    gtest_main
    SumPrimesSerial
    SumPrimesMPI
    MPI::MPI_CXX
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
