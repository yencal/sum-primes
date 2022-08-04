#pragma once
#include "sum_primes_mpi.h"

void distributeWork(int_t& startIndex, int_t& endIndex, int N);
void parseCommandLineArgs(int argc, char* argv[], int& N);
