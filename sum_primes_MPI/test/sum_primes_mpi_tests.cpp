#include "mpi.h"
#include "sum_primes_mpi.h"
#include "sum_primes_serial.h"
#include "utilities.h"
#include <gtest/gtest.h>
#include <stdio.h>

TEST(SumPrimesTestsMPI, NEqualsNMinToNMax)
{
    int numRanks, rank;
    MPI_Comm_size(MPI_COMM_WORLD, &numRanks);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int_t NMin = (numRanks * numRanks) + (numRanks - 1);

    int_t NMax = NMin + 1000;

    for (int_t N = NMin; N < NMax; N++)
    {
        MPI_Barrier(MPI_COMM_WORLD);

        int_t startIndex, endIndex;
        distributeWork(startIndex, endIndex, (int)N);

        EXPECT_EQ(sumPrimesSieveOfEratosthenes(N), sumPrimesSieveOfEratosthenesMPI(startIndex, endIndex, N))
            << "faild at rank " << rank << " N=" << N;
    }
}

int main(int argc, char* argv[])
{
    int result = 0;

    testing::InitGoogleTest(&argc, argv);

    MPI_Init(&argc, &argv);

    result = RUN_ALL_TESTS();

    MPI_Finalize();

    return result;
}
