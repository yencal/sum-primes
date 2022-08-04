#include "sum_primes_mpi.h"
#include "utilities.h"
#include <assert.h>
#include <cstring>
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

/*

This program uses MPI to sum all primes from 2 to N, where N is
input from command line. Sieve of Eratosthenes is used to identify
all primes in the range.

Example to sum primes from 2 to 1000,
Run as: mpirun --bind-to core -n ${numProcesses} ./${exec} -N 1000

*/

int main(int argc, char* argv[])
{
    int N;
    int numRanks, rank;
    int_t startIndex, endIndex;
    int_t sumPrimes;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Read N from command line arguments
    parseCommandLineArgs(argc, argv, N);

    // Check that N > 0
    if (N < 1 && rank == 0)
    {
        printf("Please specify N as an integer greater than 0.\n");
        MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
    }

    // Each MPI rank gets chunk of work to do
    distributeWork(startIndex, endIndex, N);

    // Get the sum of primes from 2 to N
    double totalTime = -MPI_Wtime();
    sumPrimes = sumPrimesSieveOfEratosthenesMPI(startIndex, endIndex, N);
    totalTime += MPI_Wtime();

    // Print result of sum of primes from 2 to N
    if (rank == 0)
    {
        printf("Using MPI sumPrimesSieveOfEratosthenes sum of primes from 2 to %ld = %ld\n", (int_t)N, sumPrimes);
        printf("Total time: %12.8f\n", totalTime);
    }

    MPI_Finalize();

    return 0;
}
