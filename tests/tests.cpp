#include <sstream>

#include "gtest/gtest.h"
#include "../src/utils/utils.h"

std::vector<uint64_t> expected_prime_number = {
        2, 3, 5, 7, 11,
        13, 17, 19, 23, 29,
        31, 37, 41, 43, 47,
        53, 59, 61, 67, 71,
};

// first - number of letters in word, second - number of such words
std::map<uint32_t, uint32_t> expected_words_number {
        {2, 3},
        {3, 2},
        {4, 2},
        {6, 3},
};

defs::List* GenerateList(const uint32_t list_size) {
    auto first_node = new defs::List{};
    auto prev_node = first_node;
    first_node->payload = 1;

    for (uint32_t idx = 2; idx <= list_size; idx++) {
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
    while(curr_node) {
        list_size++;
        curr_node = curr_node->next;
    }

    return list_size;
}

TEST(CalcPrimeNumbers, NothingToCalc) {
    std::vector<uint64_t> actual_prime_numbers;
    utils::CalcPrimeNumbers(actual_prime_numbers, 0);

    ASSERT_EQ(actual_prime_numbers.size(), 0);
};

TEST(CalcPrimeNumbers, FirstTwentyPrimeNumbers) {
    std::vector<uint64_t> actual_prime_numbers;
    utils::CalcPrimeNumbers(actual_prime_numbers, 20);

    ASSERT_EQ(actual_prime_numbers.size(), 20);
    ASSERT_EQ(actual_prime_numbers, expected_prime_number);
};

TEST(CountWordsNumber, InvalidStream) {
    std::stringstream text_stream;
    const auto actual_words_number = utils::CountWordsNumber(text_stream);

    ASSERT_EQ(actual_words_number.size(), 0);
}

TEST(CountWordsNumber, SimpleText) {
    std::stringstream text_stream;
    text_stream << "Almost before we knew it we had left the ground";
    const auto actual_words_number = utils::CountWordsNumber(text_stream);

    ASSERT_EQ(actual_words_number.size(), 4);
    ASSERT_EQ(actual_words_number, expected_words_number);
}

TEST(CountWordsNumber, TextWithSpecialCharacters) {
    std::stringstream text_stream;
    text_stream << "#Almost (before) {we} [knew] it, \n we had? left %the $ground!";
    const auto actual_words_number = utils::CountWordsNumber(text_stream);

    ASSERT_EQ(actual_words_number.size(), 4);
    ASSERT_EQ(actual_words_number, expected_words_number);
}

TEST(SieveList, InvalidList) {
    auto list = GenerateList(1);

    ASSERT_NO_THROW(utils::SieveList(list));
    ASSERT_NO_THROW(utils::SieveList(nullptr));
}

TEST(SieveList, LastNodeToSieve) {
    auto list = GenerateList(5);
    utils::SieveList(list);
    uint32_t list_size = CalcListSize(list);

    ASSERT_EQ(list_size, 4);
}

TEST(SieveList, SeveralNodesToSieve) {
    auto list = GenerateList(21);
    utils::SieveList(list);
    uint32_t list_size = CalcListSize(list);

    ASSERT_EQ(list_size, 17);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}