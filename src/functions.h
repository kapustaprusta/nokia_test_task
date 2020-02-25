#pragma once

#include <map>
#include <list>
#include <queue>
#include <tuple>
#include <vector>
#include <istream>
#include <algorithm>

#include "defs/defs.h"

namespace functions {

    void CalcPrimeNumbers(std::vector<uint64_t> &primes, size_t n);

    std::map<uint32_t, uint32_t> CountWordsNumber(std::istream& text_stream);

    void SieveList(defs::List* list, int deleted_node_number = 5);

    template <typename T>
    inline std::tuple<T, T> GetMinMaxNumbers(const T number) {
        T min_number = 0;
        T max_number = 0;
        T bit_shift = 0;
        T bit_size = sizeof(number) * 8;

        for (T i = 0; i < bit_size; i++) {
            if (number >> i & T(0x01)) {
                min_number |= T(0x01) << bit_shift;
                max_number |= T(0x01) << (bit_size - 1 - bit_shift);

                bit_shift++;
            }
        }

        return std::make_tuple(min_number, max_number);
    }

    std::list<std::list<defs::TreeNode*>> CalcTreeDepth(defs::TreeNode* node);

} // functions
