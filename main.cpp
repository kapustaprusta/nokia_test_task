#include <iostream>
#include "time.h"

#include "functions/functions.h"

int main() {
    auto primes = std::vector<int>();

    clock_t tStart = clock();
    functions::CalcPrimeNumbers(1000000, primes);
    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);


    std::cout << primes.size() << '\n';

//    for (const auto& prime : primes)
//    {
//        std::cout << prime << " ";
//    }

    return 0;
}
