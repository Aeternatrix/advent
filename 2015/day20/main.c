// ====================================================================
//  $File: main.c $
//  $Date: 11-07-2025 @ 20-24-39 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <stdlib.h>

const int input = 36000000;
#define PAGE 4096
#define LIMIT (PAGE*PAGE)
static int*  sigma_cache;
static int   sigma_limit = 1;

//
// This is code pulled from the interwebs
// My version of this took like, 10 minutes to precompute
// This tief'd code does it in like, 20s
// (https://codereview.stackexchange.com/questions/120572/computing-the-divisor-sum-in-bulk-without-division-multiplication-or-factorisat/120934#120934)
//
static void extend_sigma_cache (int new_limit) {
    for (int n = sigma_limit + 1; n <= new_limit; ++n) {
        int gpn_index = 1;
        int gpn_value = 1;
        int gpn_delta = 1;
        int sum = 0, k;

        for ( ; ; ) {
            if ((k = gpn_value) >= n) break;
            sum += sigma_cache[n - k];
            if ((k += gpn_index) >= n) break;
            sum += sigma_cache[n - k];
            ++gpn_index;
            gpn_value += (gpn_delta += 3);
            if ((k = gpn_value) >= n) break;
            sum -= sigma_cache[n - k];
            if ((k += gpn_index) >= n) break;
            sum -= sigma_cache[n - k];
            ++gpn_index;
            gpn_value += (gpn_delta += 3);
        }
        if (k == n) sum += (gpn_index & 1) != 0 ? n : -n;
        sigma_cache[n] = sum;
    }
    sigma_limit = new_limit;
}

int sigma(int n) {
    if (n > sigma_limit) extend_sigma_cache(n);
    return sigma_cache[n];
}

int part_one() {
    sigma_cache = calloc(LIMIT+1, sizeof(int));
    sigma_cache[0] = 0;
    sigma_cache[1] = 1;
    sigma(input/10);
    int i = 0;
    for (; i < LIMIT; i++) {
        if (sigma_cache[i] >= input/10) break;
    }
    free(sigma_cache);
    return i;
}

int part_two() {
    int v = 0;
    int arr[50];
    for (int n = 1; ; n++) {
        v = 0;
        for (int i=1; i <= 50; i++) v+= !(n%i) ? n / i : 0;
        if (v >= input/11) return n;
    }
    return 0;
}

int min(int a, int b) { return a < b ? a : b; }

int main() {
    printf("The lowest number house that gets %d presents is House #%d.\n", input, part_one());
    printf("The lowest number house that gets %d presents is House #%d.\n", input, part_two());
}
