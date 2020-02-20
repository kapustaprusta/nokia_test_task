#include <iostream>
#include "time.h"
#include <fstream>

#include "utils/utils.h"

int main() {
//    clock_t tStart = clock();
//    // some actions
//    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    auto number = uint64_t(0x5f);
    auto [min_number, max_number] = utils::GetMinMaxNumbers(number);

    std::cout << "min: " <<  std::hex << min_number << " max: " << std::hex << max_number;

    return 0;
}
