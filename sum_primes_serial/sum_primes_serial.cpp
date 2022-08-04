#include "sum_primes_serial.h"
#include <vector>

bool primalityCheck(int_t num)
{
    /*
      This function checks whether a number is prime or not.
      Time: O(sqrt(num))
      Space: O(1)
    */

    if (num == 0 || num == 1)
    {
        return false;
    }

    for (int_t i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }

    return true;
}

int_t sumPrimesNaive(int_t N)
{
    /*
      This function sums primes from 2 to N by checking if
      a number is prime or not using primalityCheck function.
      Time: O(N*sqrt(N))
      Space: O(1)
    */

    int_t sum = 0;

    for (int_t i = 0; i <= N; i++)
    {
        if (primalityCheck(i))
        {
            sum += i;
        }
    }

    return sum;
}

int_t sumPrimesSieveOfEratosthenes(int_t N)
{
    /*
      This function sums primes from 2 to N by first using
      sieve of Eratosthenes to find the primes from 2 to N.
      Time: O(N*log(log(N))) + O(N)
      Space: O(N)
    */

    // Note that std::vector<bool> is used to save space. Check out
    // https://en.cppreference.com/w/cpp/container/vector_bool

    // All numbers are set to prime initially.
    std::vector<bool> primeArray(N + 1, true);  // +1 to account for [0,N]

    // Set 0 and 1 as non-prime
    primeArray[0] = false;
    primeArray[1] = false;

    // Perform sieve of Eratosthenes
    for (int_t i = 0; i * i <= N; i++)
    {
        if (primeArray[i])
        {
            for (int_t j = i * i; j <= N; j += i)
            {
                primeArray[j] = false;
            }
        }
    }

    // Sum all prime numbers
    int_t sum = 0;
    for (int_t i = 0; i <= N; i++)
    {
        if (primeArray[i])
        {
            sum += i;
        }
    }

    return sum;
}
