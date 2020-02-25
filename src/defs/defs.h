#pragma once

#include <cstdint>

namespace defs
{

    struct List {
        struct List* next;
        uint32_t payload;
    };

    struct TreeNode {
        struct TreeNode* left_child;
        struct TreeNode* right_child;
    };

}
