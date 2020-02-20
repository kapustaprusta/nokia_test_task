#pragma once

#include <map>
#include <tuple>
#include <vector>
#include <istream>

namespace utils
{
    void CalcPrimeNumbers(size_t n, std::vector<int>& primes)
    {
        if (n == 0)
        {
            return;
        }

        std::vector<bool> tmp_primes;
        tmp_primes.resize(10*n+1, true);
        tmp_primes[0] = tmp_primes[1] = false;

        size_t prev_bound = 0;
        while (true)
        {
            for (size_t i = 2; i*i <= tmp_primes.size(); i++)
            {
                if (tmp_primes[i])
                {
                    size_t start_pos = 0;
                    if (prev_bound == 0)
                    {
                        start_pos = i*i;
                    }
                    else
                    {
                        start_pos = (prev_bound/i)*i;
                    }

                    for(size_t j = start_pos; j <= tmp_primes.size(); j+= i)
                    {
                        tmp_primes[j] = false;
                    }
                }
            }

            for(size_t i = prev_bound; i < tmp_primes.size(); i++)
            {
                if (tmp_primes[i])
                {
                    primes.push_back(i);
                }

                if (primes.size() == n)
                {
                    return;
                }
            }

            prev_bound = tmp_primes.size();
            tmp_primes.resize(2*tmp_primes.size()+1, true);
        }
    }

    std::map<int, int> CountWordsNumber(std::istream& text_stream)
    {
        std::map<int, int> words_map;
        if (text_stream.good())
        {
            while(!text_stream.eof())
            {
                std::string curr_word;
                text_stream >> curr_word;
                words_map[curr_word.size()]++;
            }
        }

        return words_map;
    }

    std::tuple<uint32_t, uint32_t> GetMinMaxNumbers(uint32_t number)
    {
        uint32_t min_number = 0;
        uint32_t max_number = 0;
        uint32_t bit_shift  = 0;
        uint32_t bits_size  = sizeof(number)*8;

        for (uint32_t i = 0; i < bits_size; i++)
        {
            if (number >> i & uint32_t(0x01))
            {
                min_number |= uint32_t(0x01) << bit_shift;
                max_number |= uint32_t(0x01) << (bits_size - 1 - bit_shift);

                bit_shift++;
            }
        }

        return std::make_tuple(min_number, max_number);
    }

} // utils
