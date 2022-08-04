#include "utilities.h"
#include "mpi.h"
#include <math.h>
#include <stdio.h>
#include <string>

void distributeWork(int_t& startIndex, int_t& endIndex, int N)
{
    int numRanks, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Redefining N to include 0 to N
    int_t auxN = (int_t)(N + 1);

    // Distribute work to ranks as [startIndex, endIndex).
    startIndex = rank * auxN / numRanks;
    endIndex = (rank + 1) * auxN / numRanks;

    // Check that all numbers to use for sieving are contained in rank 0
    if (rank == 0)
    {
        int_t sieveLimit = (int_t)floor(sqrt(N));
        if (endIndex <= sieveLimit)
        {
            printf("\nToo many processes used."
                   " Please use number of processes < %ld for N = %d\n",
                   auxN / sieveLimit, N);
            MPI_Abort(MPI_COMM_WORLD, EXIT_FAILURE);
        }
    }

/*
    for (int i = 0; i < numRanks; i++)
    {
        if (rank == i)
        {
            printf("Process %d is working on [%ld,%ld)\n", rank, startIndex, endIndex);
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
*/
}

void parseCommandLineArgs(int argc, char* argv[], int& N)
{
    std::string opt;
    int i = 1;
    while (i < argc && argv[i][0] == '-')
    {
        opt = std::string(argv[i]);

        if (opt == "-N")
            N = atoi(argv[++i]);

        ++i;
    }
}
