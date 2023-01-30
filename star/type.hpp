#pragma once
#ifndef UTILS_TYPE_HPP
#define UTILS_TYPE_HPP

#include <typeinfo>

template<typename T>
constexpr inline const char *get_type(T value) {
    return typeid(value).name();
}

namespace star {
    template<typename T>
    concept integral = requires {
        requires std::is_same_v<T, short> || std::is_same_v<T, unsigned short> || std::is_same_v<T, int> ||
                 std::is_same_v<T, unsigned int> || std::is_same_v<T, long> || std::is_same_v<T, unsigned long> ||
                 std::is_same_v<T, long long> || std::is_same_v<T, unsigned long long>;
    };
}

#endif //UTILS_TYPE_HPP
