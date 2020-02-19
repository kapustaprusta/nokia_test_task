#pragma once

#include <vector>
#include <iostream>

namespace functions
{
    //
    void CalcPrimeNumbers(int n, std::vector<int>& primes)
    {
        if (n <= 0)
        {
            return;
        }

        auto tmp_primes = std::vector<bool>();
             tmp_primes.resize(10*n+1, true);

        tmp_primes[0] = tmp_primes[1] = false;

        auto prev_bound = 0;
        while (true)
        {
            for (auto i = 2; i*i <= tmp_primes.size(); i++)
            {
                if (tmp_primes[i])
                {
                    auto start_pos = 0;
                    if (prev_bound == 0)
                    {
                        start_pos = i*i;
                    }
                    else
                    {
                        start_pos = (prev_bound/i)*i;
                    }

                    for(auto j = start_pos; j <= tmp_primes.size(); j+= i)
                    {
                        tmp_primes[j] = false;
                    }
                }
            }

            for(auto i = prev_bound; i < tmp_primes.size(); i++)
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

} // functions
