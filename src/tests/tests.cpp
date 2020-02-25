#include <gtest/gtest.h>

#include "functions.h"

defs::List* GenerateList(const uint32_t list_size, const uint32_t first_node_payload = 1) {
    auto first_node = new defs::List{};
    auto prev_node = first_node;
    first_node->payload = first_node_payload;

    for (uint32_t idx = first_node_payload+1; idx <= list_size; idx++) {
        auto curr_node = new defs::List{};
        curr_node->payload = idx;
        prev_node->next = curr_node;
        prev_node = curr_node;
    }

    return first_node;
}

uint32_t CalcListSize(const defs::List* list) {
    uint32_t list_size = 0;
    auto curr_node = list;
    while (curr_node) {
        list_size++;
        curr_node = curr_node->next;
    }

    return list_size;
}

defs::TreeNode* GenerateTree(const uint32_t tree_depth, const bool balanced = true) {
    auto root = new defs::TreeNode{};

    std::vector<defs::TreeNode*> nodes_list;
    nodes_list.emplace_back(root);

    uint32_t processed_nodes = 0;
    for (uint32_t depth = 0; depth < tree_depth; depth++) {
        auto node_list_size = nodes_list.size();
        for (uint32_t idx = processed_nodes; idx < node_list_size; idx++) {
            if (balanced) {
                nodes_list[idx]->left_child = new defs::TreeNode{};
                nodes_list.emplace_back(nodes_list[idx]->left_child);
            }

            nodes_list[idx]->right_child = new defs::TreeNode{};
            nodes_list.emplace_back(nodes_list[idx]->right_child);

            processed_nodes++;
        }
    }

    return root;
}

TEST(CalcPrimeNumbers, NothingToCalc) {
    std::vector<uint64_t> actual_prime_numbers;
    functions::CalcPrimeNumbers(actual_prime_numbers, 0);

    ASSERT_EQ(actual_prime_numbers.size(), 0);
};

TEST(CalcPrimeNumbers, FirstTwentyPrimeNumbers) {
    std::vector<uint64_t> expected_prime_number {
        2, 3, 5, 7, 11,
        13, 17, 19, 23, 29,
        31, 37, 41, 43, 47,
        53, 59, 61, 67, 71,
    };
    std::vector<uint64_t> actual_prime_numbers;

    functions::CalcPrimeNumbers(actual_prime_numbers, 20);

    ASSERT_EQ(actual_prime_numbers.size(), expected_prime_number.size());
    ASSERT_EQ(actual_prime_numbers, expected_prime_number);
};

TEST(CountWordsNumber, EmptyText) {
    std::stringstream text_stream;
    const auto actual_words_number = functions::CountWordsNumber(text_stream);

    ASSERT_EQ(actual_words_number.size(), 0);
}

TEST(CountWordsNumber, SimpleText) {
    // first - number of letters in word, second - number of such words
    std::map<uint32_t, uint32_t> actual_words_number;
    std::map<uint32_t, uint32_t> expected_words_number{
            {2, 3},
            {3, 2},
            {4, 2},
            {6, 3},
    };
    std::stringstream text_stream("Almost before we knew it we had left the ground");

    actual_words_number = functions::CountWordsNumber(text_stream);

    ASSERT_EQ(actual_words_number.size(), expected_words_number.size());
    ASSERT_EQ(actual_words_number, expected_words_number);
}

TEST(CountWordsNumber, TextWithInvalidCharacters) {
    // first - number of letters in word, second - number of such words
    std::map<uint32_t, uint32_t> actual_words_number;
    std::map<uint32_t, uint32_t> expected_words_number{
            {2, 5},
            {3, 6},
            {4, 1},
            {5, 3},
            {6, 1},
            {7, 2},
            {8, 2},
            {9, 1},
            {11, 1},
    };
    std::stringstream text_stream("C++ standard up to C++17. Use GNU make, GNU autotools or CMake. Windows users may consider WSL or MinGW64 to verify compilation.");

    actual_words_number = functions::CountWordsNumber(text_stream);

    ASSERT_EQ(actual_words_number.size(), expected_words_number.size());
    ASSERT_EQ(actual_words_number, expected_words_number);
}

TEST(SieveList, EmptyList) {
    auto list = GenerateList(1);

    ASSERT_NO_THROW(functions::SieveList(list));
    ASSERT_NO_THROW(functions::SieveList(nullptr));
}

TEST(SieveList, LastNodeToSieve) {
    std::list<uint32_t> expected_list_payloads {
        1, 2, 3, 4,
    };
    auto actual_list = GenerateList(5);

    functions::SieveList(actual_list);
    const auto actual_list_size = CalcListSize(actual_list);

    ASSERT_EQ(actual_list_size, expected_list_payloads.size());
    auto actual_curr_node = actual_list;
    for (const auto& expected_payload : expected_list_payloads) {
        ASSERT_EQ(actual_curr_node->payload, expected_payload);
        actual_curr_node = actual_curr_node->next;
    }
}

TEST(SieveList, SeveralNodesToSieve) {
    std::list<uint32_t> expected_list_payloads{
         1,  2,  3,  4,
         6,  7,  8,  9,
        11, 12, 13, 14,
        16, 17, 18, 19,
        21
    };
    auto actual_list = GenerateList(21);

    functions::SieveList(actual_list);
    const auto actual_list_size = CalcListSize(actual_list);

    ASSERT_EQ(actual_list_size, expected_list_payloads.size());
    auto actual_curr_node = actual_list;
    for (const auto& expected_payload : expected_list_payloads) {
        ASSERT_EQ(actual_curr_node->payload, expected_payload);
        actual_curr_node = actual_curr_node->next;
    }
}

TEST(GetMinMaxNumbers, MinValue) {
    uint32_t test_number = 0x00;

    auto [min_number, max_number] = functions::GetMinMaxNumbers(test_number);

    ASSERT_EQ(min_number, 0x00);
    ASSERT_EQ(max_number, 0x00);
}

TEST(GetMinMaxNumbers, MaxValue) {
    uint32_t test_number = 0xffffffff;

    auto[min_number, max_number] = functions::GetMinMaxNumbers(test_number);

    ASSERT_EQ(min_number, 0xffffffff);
    ASSERT_EQ(max_number, 0xffffffff);
}

TEST(CalcTreeDepth, EmptyTree) {
    auto root = GenerateTree(0);
    std::list<std::list<defs::TreeNode*>> actual_found_paths;
  
    ASSERT_NO_THROW(actual_found_paths = functions::CalcTreeDepth(root));
    ASSERT_EQ(actual_found_paths.size(), 0);

    ASSERT_NO_THROW(actual_found_paths = functions::CalcTreeDepth(nullptr));
    ASSERT_EQ(actual_found_paths.size(), 0);
}

TEST(CalcTreeDepth, BalancedTree) {
    auto depth = 3;
    auto root = GenerateTree(depth);
    std::list<std::list<defs::TreeNode*>> actual_found_paths;

    actual_found_paths = functions::CalcTreeDepth(root);

    ASSERT_EQ(actual_found_paths.size(), 8);
    for (const auto& path : actual_found_paths) {
        ASSERT_EQ(path.size(), 4);
    }
}

TEST(CalcTreeDepth, UnbalancedTree) {
    auto depth = 3;
    auto root = GenerateTree(depth, false);
    std::list<std::list<defs::TreeNode*>> actual_found_paths;

    actual_found_paths = functions::CalcTreeDepth(root);

    ASSERT_EQ(actual_found_paths.size(), 1);
    for (const auto& path : actual_found_paths) {
        ASSERT_EQ(path.size(), depth+1);
    }
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    const auto res = RUN_ALL_TESTS();

    return res;
}