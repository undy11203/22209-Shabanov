#pragma once

#include <string>

namespace Factory {
    template <typename T>
    struct Tag {
        using InterfaceType = T;

        std::string id;
    };
} // namespace Factory
