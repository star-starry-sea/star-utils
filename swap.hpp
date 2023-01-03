#ifndef UTILS_SWAP_HPP
#define UTILS_SWAP_HPP

#if __cplusplus


#else

void swap_int(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap_double(double *a, double *b) {
    double temp = *a;
    *a = *b;
    *b = temp;
}

void swap_char(char *a, char *b) {
    char temp = *a;
    *a = *b;
    *b = temp;
}

void swap_float(float *a, float *b) {
    float temp = *a;
    *a = *b;
    *b = temp;
}

void swap_long(long *a, long *b) {
    long temp = *a;
    *a = *b;
    *b = temp;
}

void swap_unsigned(unsigned *a, unsigned *b) {
    unsigned temp = *a;
    *a = *b;
    *b = temp;
}

#endif


#endif //UTILS_SWAP_HPP
