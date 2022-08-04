#include "../sum_primes_serial.h"
#include <gtest/gtest.h>

TEST(SumPrimesTests, NEquals0ToNMax)
{
    int_t NMax = 1000;
    for (int_t N = 0; N < NMax; N++)
    {
        EXPECT_EQ(sumPrimesNaive(N), sumPrimesSieveOfEratosthenes(N)) << "N=" << N;
    }
}

int main(int argc, char* argv[])
{
    int result = 0;
    testing::InitGoogleTest(&argc, argv);
    result = RUN_ALL_TESTS();
    return result;
}
