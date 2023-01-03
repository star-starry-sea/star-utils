#ifndef UTILS_STRING_HPP
#define UTILS_STRING_HPP

#if !__cplusplus

#include "swap.hpp"
#include <string.h>

void reverse(char *s) {
    unsigned long len = strlen(s);
    for (unsigned long i = 0; i < len / 2; i++) {
        swap_char(s + i, s + len - i - 1);
    }
}

#else

#endif

#endif //UTILS_STRING_HPP
