#pragma once

#include "swap.hpp"

#if !__cplusplus

#include <string.h>

#else

#endif

#if !__cplusplus

void reverse(char *s) {
    unsigned long len = strlen(s);
    for (unsigned long i = 0; i < len / 2; i++) {
        swap_char(s + i, s + len - i - 1);
    }
}

#else

#endif