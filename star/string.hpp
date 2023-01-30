#pragma once
#ifndef UTILS_STRING_HPP
#define UTILS_STRING_HPP

#include <iostream>

namespace star {
    constexpr void replace(std::string &str, const std::string &old_str, const std::string &new_str) {
        size_t pos;
        while ((pos = str.find(old_str)) != std::string::npos) {
            str.replace(pos, old_str.length(), new_str);
        }
    }
}

#endif //UTILS_STRING_HPP
