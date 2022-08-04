#include "sum_primes_serial.h"
#include <assert.h>
#include <cstring>
#include <stdio.h>
#include <string>

/*

  This program sums all primes from 2 to N, where N is
  input from command line;

  Example to sum primes from 2 to 1000,
  Run as: ./exec -N 1000

*/

int N;

void parseCommandLineArgs(int argc, char* argv[]);

int main(int argc, char* argv[])
{

    // Read N from command line arguments
    parseCommandLineArgs(argc, argv);
    assert(N > 0 && "Please specify N as an integer greater than 0.");

    // Sum primes from 2 to N and print result
    printf("Using sumPrimesNaive sum of primes from 2 to %d = %ld\n", N, sumPrimesNaive((int_t)N));
    printf("Using sumPrimesSieveOfEratosthenes sum of primes from 2 to %d = %ld\n", N,
           sumPrimesSieveOfEratosthenes((int_t)N));
    return 0;
}

void parseCommandLineArgs(int argc, char* argv[])
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
