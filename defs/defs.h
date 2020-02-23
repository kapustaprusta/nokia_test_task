#pragma once

#include <cstdint>

namespace defs
{

    struct List {
        struct List* next;
        uint64_t payload;
    };

}
