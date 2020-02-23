#include <iostream>
#include "time.h"
#include <fstream>

#include "utils/utils.h"

int main() {
//    clock_t tStart = clock();
//    // some actions
//    printf("Time taken: %.2fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    auto first_node = new defs::List{};
    first_node->payload = 1;

    auto prev_node = first_node;
    for (uint64_t i = 2; i <= 13; i++)
    {
        auto node = new defs::List{};
        node->payload = i;
        prev_node->next = node;
        prev_node = node;
    }

    utils::ListSieve(first_node);
    auto curr_node = first_node;
    while(curr_node)
    {
        std::cout << curr_node->payload << " ";
        curr_node = curr_node->next;
    }

    return 0;
}
