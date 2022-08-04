cmake_minimum_required(VERSION 3.8)

set(This SumPrimesSerialTests)

set(Sources
    sum_primes_serial_tests.cpp
)

add_executable(${This} ${Sources})

target_link_libraries(${This} PUBLIC
    gtest_main
    SumPrimesSerial
)

add_test(
    NAME ${This}
    COMMAND ${This}
)
