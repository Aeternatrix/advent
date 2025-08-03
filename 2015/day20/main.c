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
int* sigma_cache;
int sigma_limit = 1;
void extend_sigma_cache(int new_limit);
int sigma(int n);

/*
 * To keep the Elves busy, Santa has them deliver some presents by hand, door-to-door. He sends them down a street with infinite houses numbered sequentially: 1, 2, 3, 4, 5, and so on.
 * 
 * Each Elf is assigned a number, too, and delivers presents to houses based on that number:
 * 
 *  - The first Elf (number 1) delivers presents to every house: 1, 2, 3, 4, 5, ....
 *  - The second Elf (number 2) delivers presents to every second house: 2, 4, 6, 8, 10, ....
 *  - Elf number 3 delivers presents to every third house: 3, 6, 9, 12, 15, ....
 * There are infinitely many Elves, numbered starting with 1. Each Elf delivers presents equal to ten times his or her number at each house.
 * 
 * So, the first nine houses on the street end up like this:
 * 
 * - `House 1 got 10 presents.`
 * - `House 2 got 30 presents.`
 * - `House 3 got 40 presents.`
 * - `House 4 got 70 presents.`
 * - `House 5 got 60 presents.`
 * - `House 6 got 120 presents.`
 * - `House 7 got 80 presents.`
 * - `House 8 got 150 presents.`
 * - `House 9 got 130 presents.`
 * The first house gets 10 presents: it is visited only by Elf 1, which delivers 1 * 10 = 10 presents. The fourth house gets 70 presents, because it is visited by Elves 1, 2, and 4, for a total of 10 + 20 + 40 = 70 presents.
 * 
 * What is the lowest house number of the house to get at least as many presents as the number in your puzzle input?
 */
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

/*
 * The Elves decide they don't want to visit an infinite number of houses. Instead, each Elf will stop after delivering presents to 50 houses. To make up for it, they decide to deliver presents equal to eleven times their number at each house.
 * 
 * With these changes, what is the new lowest house number of the house to get at least as many presents as the number in your puzzle input?
 */
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


int main() {
    printf("The lowest number house that gets %d presents is House #%d.\n", input, part_one());
    printf("The lowest number house that gets %d presents is House #%d.\n", input, part_two());
}

//
// This is code pulled from the interwebs
// My version of this took like, 10 minutes to precompute
// This tief'd code does it in like, 20s
// (https://codereview.stackexchange.com/questions/120572/computing-the-divisor-sum-in-bulk-without-division-multiplication-or-factorisat/120934#120934)
//
void extend_sigma_cache(int new_limit) {
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
