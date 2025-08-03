// ====================================================================
//  $File: main.c $
//  $Date: 30-07-2025 @ 09-25-18 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

//    | 1   2   3   4   5   6  
// ---+---+---+---+---+---+---+
//  1 |  1   3   6  10  15  21
//  2 |  2   5   9  14  20  27
//  3 |  4   8  13  19  26  34
//  4 |  7  12  18  25  33  42
//  5 | 11  17  24  32  41  51
//  6 | 16  23  31  40  50  61

//	  |    1         2         3         4         5         6
// ---+---------+---------+---------+---------+---------+---------+
//  1 | 20151125  18749137  17289845  30943339  10071777  33511524
//  2 | 31916031  21629792  16929656   7726640  15514188   4041754
//  3 | 16080970   8057251   1601130   7981243  11661866  16474243
//  4 | 24592653  32451966  21345942   9380097  10600672  31527494
//  5 |    77061  17552253  28094349   6899651   9250759  31663883
//  6 | 33071741   6796745  25397450  24659492   1534922  27995004

//	 f(1,1) = 20151125
//	 f(x,y) = f(x, y-1) * 252533 % 33554393

//	 target: `row 3010, col 3019`

#include <stdio.h>
typedef unsigned long long uint64;

uint64 part_one() {
    uint64 num = 20151125;
    int target = 0;
    int col = 3019, row = 3010;
    target = 0;
    for (int itr = 0; itr <= col; itr++) {
        if (target + itr > 0xFFFFFFFF) printf("overflow\n");
        target += itr;
    }
    for (int itr = 0; itr < row-1; itr++) {
        if (target + itr > 0xFFFFFFFF) printf("overflow\n");
        target += col + itr;
    }
    for (int itr = 1; itr < target; itr++) {
        num *= 252533;
        num %= 33554393;
    }
    return num;
}

int main() {
    printf("The number at column 3019, row 3010 is: %llu\n", part_one());
}
