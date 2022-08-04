#include "sum_primes_mpi.h"
#include "mpi.h"
#include <vector>

int_t sumPrimesSieveOfEratosthenesMPI(int_t startIndex, int_t endIndex, int_t N)
{
    /*
      This function sums primes from 2 to N by first using
      sieve of Eratosthenes to find the primes from 2 to N.
      Time: O(N*log(log(N))) + O(N)
      Space: O(N)
    */

    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Note that std::vector<bool> is used to save space. Check out
    // https://en.cppreference.com/w/cpp/container/vector_bool
    std::vector<bool> primeArray(endIndex - startIndex, true);

    // Set 0 and 1 as non-prime
    if (rank == 0)
    {
        primeArray[0] = false;
        primeArray[1] = false;
    }

    int_t i = 0;
    int_t firstMultiple;
    while (i * i <= N)
    {
        // Rank 0 finds the next i and broadcast to the other ranks
        if (rank == 0)
        {
            while (primeArray[i] == false)
            {
                i++;
            }
        }

        MPI_Bcast(&i, 1, MPI_UNSIGNED_LONG, 0, MPI_COMM_WORLD);

        // Find first multiple index in rank
        // Note: rank 0 has to start from i*i
        if (i * i > startIndex)
        {
            firstMultiple = i * i - startIndex;
        }
        else
        {
            if (startIndex % i == 0)
            {
                firstMultiple = 0;
            }
            else
            {
                firstMultiple = i - (startIndex % i);
            }
        }

        // All ranks perform sieve
        for (int_t j = firstMultiple; j < endIndex - startIndex; j += i)
        {
            primeArray[j] = false;
        }

        // increament i
        i++;
    }

    // Sum all prime numbers
    int_t localSum = 0;
    for (int_t i = 0; i < endIndex - startIndex; i++)
    {
        if (primeArray[i])
        {
            localSum += (i + startIndex);
        }
    }

    // Allreduce localSum into globalSum
    int_t globalSum = 0;
    MPI_Allreduce(&localSum, &globalSum, 1, MPI_UNSIGNED_LONG, MPI_SUM, MPI_COMM_WORLD);

    return globalSum;
}
