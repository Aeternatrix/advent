// ====================================================================
//  $File: main.c $
//  $Date: 09-08-2025 @ 07-41-58 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "day9_input.h"

typedef unsigned char       uint8;
typedef unsigned long long  uint64;
typedef uint8               bool8;

bool8 is_num(char c) { return c <= '9' && c >= '0'; }
uint64 chain(const char *start, const char* end, int depth);

#define FULL    1
#define SINGLE  0

int part_one() {
    return chain(day9_input, &day9_input[day9_input_size-1], SINGLE);
}

uint64 part_two() {
    return chain(day9_input, &day9_input[day9_input_size-1], FULL);
}

int main() {
    printf("The decompressed file length is %d bytes.\n", part_one());
    printf("The fully decompressed file length is %llu bytes.\n", part_two());
}

uint64 chain(const char *start, const char* end, int depth) {
    uint64 len = 0;
    uint64 skip_bytes = 0;
    int multi = 0;
    int skip = 0;
    bool8 in_parenthesis = 0;
    bool8 x = 0;
    for (const char* c = start; c < end; c++) {
        if (*c == ')') {
            multi = multi ? multi : 1;
            uint64 inc;
            if (depth == FULL) inc = chain(c+1, c + skip_bytes+1, depth) * multi;
            else inc = skip_bytes * multi;
            c += skip_bytes;
            len += inc - 1;
            skip_bytes = 0;
            multi = 0;
            x = 0;
            in_parenthesis = 0;
        }
        if (*c == '(') {
            in_parenthesis = 1;
        }
        if (in_parenthesis && *c == 'x') x = 1;
        if (in_parenthesis && is_num(*c)) {
            if (x)
                multi = multi * 10 + *c - '0';
            else
                skip_bytes = skip_bytes * 10 + *c - '0';
        }
        if (!in_parenthesis) len++;
    }

    return len;
}

