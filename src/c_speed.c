#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <time.h>
#include "mt64.h"
#include "mt19937-64.c"
#include "xoshiro128plus.c"
#include "xoshiro256plusplus.c"

void speed_mt64(uint64_t seed);
void speed_xorp(uint64_t seed);
void speed_xorpp(uint64_t seed);

int main(int argc, char * argv[])
{
    speed_mt64(1);
    speed_xorp(1);
    speed_xorpp(1);
    return 0;
}

void speed_mt64(uint64_t seed) {
    init_genrand64(seed);
    uint64_t sum = 0;
    clock_t start = clock();
    for (int i = 0; i < 100000000; i++) {
        sum ^= genrand64_int64();
    }
    clock_t end = clock();
    double msec_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("MT19937-64:%.1fms\n", msec_time);
}

void speed_xorp(uint64_t seed) {
    sp[0] = seed;
    uint64_t sum = 0;
    clock_t start = clock();
    for (int i = 0; i < 100000000; i++) {
        sum ^= xorp_next();
    }
    clock_t end = clock();
    double msec_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("xoshiro128+:%.1fms\n", msec_time);
}

void speed_xorpp(uint64_t seed) {
    s[0] = seed;
    uint64_t sum = 0;
    clock_t start = clock();
    for (int i = 0; i < 100000000; i++) {
        sum ^= next();
    }
    clock_t end = clock();
    double msec_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    printf("xoshiro256++:%.1fms\n", msec_time);
}
