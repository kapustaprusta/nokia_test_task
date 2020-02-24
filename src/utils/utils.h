#pragma once

#include <map>
#include <list>
#include <queue>
#include <tuple>
#include <vector>
#include <istream>
#include <algorithm>

#include "../defs/defs.h"

namespace utils {

    inline void CalcPrimeNumbers(std::vector<uint64_t> &primes, size_t n) {
        if (n == 0) {
            return;
        }

        std::vector<bool> tmp_primes;
        tmp_primes.resize(2*n+1, true);
        tmp_primes[0] = false;
        tmp_primes[1] = false;

        size_t prev_bound = 0;
        while (true) {
            for (size_t i = 2; i*i <= tmp_primes.size(); i++) {
                size_t start_pos = 0;
                if (prev_bound == 0) {
                    start_pos = i*i;
                }
                else {
                    start_pos = (prev_bound/i)*i;
                }

                if (tmp_primes[i]) {
                    for(size_t j = start_pos; j <= tmp_primes.size(); j+= i) {
                        tmp_primes[j] = false;
                    }
                }
            }

            for(size_t i = prev_bound; i < tmp_primes.size(); i++) {
                if (tmp_primes[i]) {
                    primes.push_back(i);
                }

                if (primes.size() == n) {
                    return;
                }
            }

            prev_bound = tmp_primes.size();
            tmp_primes.resize(2*tmp_primes.size()+1, true);
        }
    }

    inline std::map<uint32_t, uint32_t> CountWordsNumber(std::istream& text_stream) {
        std::string curr_word;
        std::map<uint32_t, uint32_t> words_map;

        auto l_count_invalid_chars_number = [](const auto& word) -> uint32_t {
            uint32_t invalid_chars_number = 0;
            for (const uint8_t& character : word) {
                if (!((character >= 0x30 && character <= 0x39) ||  // digits
                      (character >= 0x41 && character <= 0x5a) ||  // uppercase
                      (character >= 0x61 && character <= 0x7a))) { // lowercase
                        invalid_chars_number++;
                }
            }

            return invalid_chars_number;
        };

        while(!text_stream.eof()) {
            text_stream >> curr_word;
            if (curr_word.size() == 0) { // in case empty
                break;
            }

            const auto actual_word_size = curr_word.size() - l_count_invalid_chars_number(curr_word);
            words_map[actual_word_size]++;
        }

        return words_map;
    }

    inline void  SieveList(defs::List* list, int deleted_node_number = 5) {
        auto curr_node = list;
        auto node_counter = 0;

        while (curr_node && curr_node->next) {
            node_counter++;
            if (deleted_node_number - node_counter%deleted_node_number == 1) {
                auto sieved_node = curr_node->next;
                curr_node->next = curr_node->next->next;

                node_counter++;
                delete sieved_node;
            }

            curr_node = curr_node->next;
        }
    }

    template <typename T>
    inline std::tuple<T, T> GetMinMaxNumbers(T number) {
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

    inline std::list<std::list<defs::TreeNode*>> CalcTreeDepth(defs::TreeNode* node) {
        if (!node) {
            return {};
        }

        std::list<std::list<defs::TreeNode*>> found_paths;

        auto l_visit_child = [&found_paths](defs::TreeNode* child) -> void {
            std::queue<defs::TreeNode*> nodes_queue;
            nodes_queue.push(child);

            while (!nodes_queue.empty()) {
                const auto curr_node = nodes_queue.front();
                nodes_queue.pop();

                const auto prev_path = found_paths.back();
                if (curr_node->left_child || curr_node->right_child) {
                    found_paths.pop_back();
                }

                if (curr_node->left_child) {
                    nodes_queue.push(curr_node->left_child);
                    found_paths.emplace_back(prev_path);
                    found_paths.back().emplace_back(curr_node->left_child);
                }

                if (curr_node->right_child) {
                    nodes_queue.push(curr_node->right_child);
                    found_paths.emplace_back(prev_path);
                    found_paths.back().emplace_back(curr_node->right_child);
                }
            }
        };

        if (node->left_child) {
            found_paths.emplace_back(std::list<defs::TreeNode*>{node, node->left_child});
            l_visit_child(node->left_child);
        }

        if (node->right_child) {
            found_paths.emplace_back(std::list<defs::TreeNode*>{node, node->right_child});
            l_visit_child(node->right_child);
        }

        // longest path will always be the last
        const auto max_depth = found_paths.back().size();
        const auto new_begin = std::find_if(found_paths.begin(), found_paths.end(), [max_depth](const auto& curr_path) -> bool {
            return curr_path.size() == max_depth;
        });
        found_paths.erase(found_paths.begin(), new_begin);

        return found_paths;
    }

} // utils
