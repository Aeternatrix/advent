// ====================================================================
//  $File: main.c $
//  $Date: 15-07-2025 @ 23-17-01 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

typedef unsigned long long uint64;

uint64 input[] = { 1, 3, 5, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113 };


#define SZ sizeof(input)/sizeof(input[0])


uint64 min(uint64 a, uint64 b) { return a < b ? a : b; }
uint64 sum(uint64* arr, int size) { uint64 rt = 0; for (int i = 0; i < size; i++) rt += arr[i]; return rt; }

void recurse(int pos, int total, int max, uint64 mt, uint64* mmt) {
    if (pos == SZ) return;

    total += input[pos];
    if (total > max) return;
    mt = mt * input[pos];
    if (total == max) {
        *mmt = min(*mmt, mt);
        return;
    }
    for (int i=pos+1; i < SZ; i++) recurse(i, total, max, mt, mmt);
}

uint64 part_one() {
    uint64 total = sum(input, SZ) / 3;
    uint64 mt, out = -1;
    for (int i=0; i < SZ; i++) {
        recurse(i, 0, total, 1, &out);
    }
    return out;
}

uint64 part_two() {
    uint64 total = sum(input, SZ) / 4;
    uint64 mt, out = -1;
    for (int i=0; i < SZ; i++) {
        recurse(i, 0, total, 1, &out);
    }
    return out;
}

int main() {
    printf("QE of the first group of packages in the ideal configuration of 3 groups is: %llu.\n", part_one());
    printf("QE of the first group of packages in the ideal configuration of 4 groups is: %llu.\n", part_two());
}
