# sum-primes

## Description
This code sums up the prime numbers from 2 to _N_ in serial or parallel (using MPI).

The design process of the project is as follows:
* A serial version was implemented in `sum_primes_serial`.
* In the serial version, a naive method was implemented which uses the Trial division method. Trial division method has a time complexity of O(N*sqrt(N)) and uses auxiliary space of O(1).
* A better algorithm know as sieve of Eratosthenes was implemented which has a time complexity of O(N*log(log(N))) + O(N) and uses auxiliary space of O(N).
* Googletest was used to test the Trial division method and sieve of Eratosthenes serial implementationss.
* To implement the MPI version `sum_primes_MPI`, the sieve of Eratosthenes algorithm was selected for its superior time complexity. 
* Googletest was used to test the `sum_primes_MPI` against the `sum_primes_serial`.
* CMake build system was used.


## Basic build and usage
After cloning the project use the following commands to build it.
```
cd sum-primes
mkdir build
cmake -S . -B build
cmake --build build
```
This builds the executables `SumPrimesSerialExec` and `SumPrimesMPIExec` in `/build/sum_primes_serial` and `/build/sum_primes_MPI`, respectively.

The program accepts command line arguments. Run the program as follows:
* For the serial version, to sum prime numbers from 2 to 1000 run as:
```
./build/sum_primes_serial/SumPrimesSerialExec -N 10000

output:
Using sumPrimesNaive sum of primes from 2 to 1000 = 76127 
Using sumPrimesSieveOfEratosthenes sum of primes from 2 to 1000 = 76127
```

* For the MPI version, to sum prime numbers from 2 to 1000 using 4 processes run as:
```
mpirun -n 4 ./build/sum_primes_MPI/SumPrimesMPIExec -N 10000

output:
Using MPI sumPrimesSieveOfEratosthenes sum of primes from 2 to 1000 = 76127
Total time:   0.00215840
```



## Test build and testing
After cloning the project use the following commands to build the test.
```
cd sum-primes
mkdir build
cmake -DTEST=1 -S . -B build
cmake --build build
```
This builds the test executables `SumPrimesSerialTests` and `SumPrimesMPITests` in `/build/sum_primes_serial/test` and `/build/sum_primes_MPI/test`, respectively.

Note that the tests does not accept command line arguments because the test cases are predefined.
Check the test out in the `test` directory of `sum_primes_serial` and `sum_primes_MPI`, respectively. Other tests can be added accordingly.

* Run the test for the serial version as:
```
./build/sum_primes_serial/test/SumPrimesSerialTests
```

* Run the test for the MPI version as:
```
mpirun -n 4 ./build/sum_primes_MPI/test/SumPrimesMPITests
```