#include <string>
#include <stack>

#include "functions.h"

namespace functions {

void CalcPrimeNumbers(std::vector<uint64_t> &primes, const size_t n) {
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

std::map<uint32_t, uint32_t> CountWordsNumber(std::istream& text_stream) {
    std::string curr_word;
    std::map<uint32_t, uint32_t> words_map;

    auto l_count_invalid_chars_number = [](const auto& word) -> uint32_t {
        // not sure about list of invalid characters. probably need a smarter filter
        std::string invalid_characters = " .,!?:;\"\'(){}[]<>";
        uint32_t invalid_characters_number = 0;
        for (const char& character : word) {
            if (invalid_characters.find(character) != std::string::npos) {
                invalid_characters_number++;
            }
        }

        return invalid_characters_number;
    };

    while (!text_stream.eof()) {
        text_stream >> curr_word;
        // in case of empty stream
        if (curr_word.size() == 0) {
            break;
        }

        const auto actual_word_size = curr_word.size() - l_count_invalid_chars_number(curr_word);
        words_map[actual_word_size]++;
    }

    return words_map;
}

void  SieveList(defs::List* list, const int deleted_node_number) {
    auto curr_node = list;
    auto node_counter = 0;

    while (curr_node && curr_node->next) {
        node_counter++;
        if (deleted_node_number - node_counter % deleted_node_number == 1) {
            auto sieved_node = curr_node->next;
            curr_node->next = curr_node->next->next;

            node_counter++;
            delete sieved_node;
        }

        curr_node = curr_node->next;
    }
}

std::list<std::list<defs::TreeNode*>> CalcTreeDepth(defs::TreeNode* root) {
    if (!root || (!root->left_child && !root->right_child)) {
        return {};
    }

    std::list<std::list<defs::TreeNode*>> found_paths_list;

    std::queue<std::list<defs::TreeNode*>> found_paths_queue;
    found_paths_queue.push(std::list<defs::TreeNode*>{root});

    std::queue<defs::TreeNode*> nodes_queue;
    nodes_queue.push(root);

    while (!nodes_queue.empty()) {
        const auto curr_node = nodes_queue.front();
        nodes_queue.pop();

        auto prev_path = found_paths_queue.front();
        found_paths_queue.pop();
        // last node in path
        if (!curr_node->left_child && !curr_node->right_child) {
            found_paths_list.emplace_back(prev_path);
        }

        if (curr_node->left_child) {
            nodes_queue.push(curr_node->left_child);

            auto left_path = prev_path;
            left_path.emplace_back(curr_node->left_child);

            found_paths_queue.push(left_path);
        }

        if (curr_node->right_child) {
            nodes_queue.push(curr_node->right_child);

            auto right_path = prev_path;
            right_path.emplace_back(curr_node->right_child);

            found_paths_queue.push(right_path);
        }
    }

    if (!found_paths_list.empty()) {
      // in case of an asymmetrical tree, we should delete some paths, which shorter than longest path. longest path always last
      const auto max_depth = found_paths_list.back().size();
      const auto new_begin = std::find_if(found_paths_list.begin(), found_paths_list.end(), [max_depth](const auto& curr_path) -> bool {
          return curr_path.size() == max_depth;
      });
      found_paths_list.erase(found_paths_list.begin(), new_begin);
    }

    return found_paths_list;
}

} // functions