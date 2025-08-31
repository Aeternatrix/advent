// ====================================================================
//  $File: main.c $
//  $Date: 09-08-2025 @ 09-38-09 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

#include "day10_input.h"

typedef unsigned int    uint32;
typedef unsigned char   uint8;
typedef uint8           bool8;

// L Low Value
// H High Value
// A Low Value → Bot A
// B High Value → Bot B
// uint32 (LL HH AA BB)
// Sort says there's 210 values in the input; so...
// Output N = (0xFF-1)-N
#define LOW_VALUE   (0xFF000000)
#define HIGH_VALUE  (0x00FF0000)
#define LOW_BOT     (0x0000FF00)
#define HIGH_BOT    (0x000000FF)

#define CLEAR_VALUE (LOW_BOT | HIGH_BOT)
uint32 instructions[0xFF] = {};
void read_instructions();

int part_one() {
    uint32 target = (17 << 8 | 61) << 16;
    int rt;
    for (rt=0;(instructions[rt] & target) != target; rt++);
    return rt;
}

int part_two() {
    uint32* out = &instructions[0xFF-1];
    int out0 = (out[ 0] & LOW_VALUE) >> 24;
    int out1 = (out[-1] & LOW_VALUE) >> 24;
    int out2 = (out[-2] & LOW_VALUE) >> 24;
    return out0*out1*out2;
}

int main() {
    read_instructions();
    printf("The bot that compares 61 with 17 is bot %d\n", part_one());
    printf("Outputs 1, 2, and 3 multiply to %d\n", part_two());
}

void
give(int bot, int value) {
    uint32 instruction = instructions[bot];
    int low = (instruction & LOW_VALUE) >> 24;
    instructions[bot] &= CLEAR_VALUE;
    if (low) {
        if (low < value) instructions[bot] |= (low << 8 | value) << 16;
        else             instructions[bot] |= (value << 8 | low) << 16;
    }
    else                 instructions[bot] |= value << 24;
}

bool8
recurse(int key) {
    if (!(instructions[key] & LOW_VALUE) || !(instructions[key] & HIGH_VALUE)) return 0;
    uint32 instruction = instructions[key];
    int high_bot    =  instruction & HIGH_BOT;
    int low_bot     = (instruction & LOW_BOT) >> 8;

    give(high_bot, (instruction & HIGH_VALUE) >> 16);
    give(low_bot, (instruction & LOW_VALUE) >> 24);
    
    recurse(high_bot);
    recurse(low_bot);
    return 1;
}

void
read_instructions() {
    int i=-1, l=-1, h=-1, n=-1;
    const char *c = day10_input;
    char bufa[10] = {};
    char bufb[10] = {};

    while(sscanf(c, "bot %d gives low to %s %d and high to %s %d%n", &i, bufa, &l, bufb, &h, &n) ||
          sscanf(c, "value %d goes to bot %d%n", &i, &l, &n)) {
        if (h != -1) {
            instructions[i] |= ((*bufa == 'b') * l + (*bufa == 'o') * (0xFE - l)) << 8 |
                              ((*bufb == 'b') * h + (*bufb == 'o') * (0xFE - h));
        } else {
            give(l, i);
        }
        c += n;
        i=-1, l=-1, h=-1, n=-1;
        if (*c == '\n') c++;
        if (*c == '\0') break;
    }
    int start;
    for (start = 0; !(instructions[start] & LOW_VALUE) || !(instructions[start] & HIGH_VALUE); start++);
    recurse(start);
}
