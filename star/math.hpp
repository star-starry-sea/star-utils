#pragma once
#ifndef UTILS_MATH_HPP
#define UTILS_MATH_HPP

#include <algorithm>

#include "type.hpp"

template<star::integral integral_number>
constexpr integral_number reverse_number(integral_number number) noexcept {
    integral_number reversed_number{};
    while (number) {
        reversed_number *= 10;
        reversed_number += number % 10;
        number /= 10;
    }
    return reversed_number;
}

template<star::integral integral_number>
constexpr bool isprime(integral_number number) noexcept {
    if (number < 2) {
        return false;
    }
    integral_number sqrt_number = sqrt(number);
    for (integral_number i = 2; i < sqrt_number; i++) {
        if (number % i == 0) {
            return false;
        }
    }
    return true;
}

#endif //UTILS_MATH_HPP
