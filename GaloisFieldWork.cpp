#include "GaloisFIeldWork.h"

const unsigned int g_degree = 8;
const unsigned int g_base = 2;

const galois_num X8 = 195;

galois_num sum(galois_num a, galois_num b) {
    return a ^ b;
}

galois_num prod(galois_num a, galois_num b) {
    galois_num res = 0;

    galois_num i = 0;
    while ((1 << i) <= a) {
        galois_num j = 0;
        while ((1 << j) <= b) {
            if (((1 << i) & a) && ((1 << j) & b)) {
                res ^= (1 << (i + j));
            }
            j++;
        }
        i++;
    }

    return normalize(res);
}


galois_num normalize(galois_num a) {
    galois_num curr = X8;
    unsigned long long shift = g_degree;
    while ((1 << shift) <= a) {
        a = sum(a, a & (1 << shift) ? curr : 0);
        a = sum(a, a & (1 << shift));
        curr = normalize(curr * g_base);
        shift++;
    }
    return a;
}