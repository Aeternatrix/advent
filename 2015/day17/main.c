// ====================================================================
//  $File: main.c $
//  $Date: 08-07-2025 @ 12-04-32 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#define T 150
int input[] = { 11, 30, 47, 31, 32, 36, 3, 1, 5, 3, 32, 36, 15, 11, 46, 26, 28, 1, 19, 3 };

int recurse1(int pos, int target, int in, int sz);
int recurse2(int pos, int target, int in, int sz, int depth);
int recurse3(int pos, int target, int in, int sz, int depth_limit, int depth);

int min(int a, int b) { return a < b ? a : b; }
/*
 * The elves bought too much eggnog again - `150` liters this time. To fit it all into your refrigerator, you'll need to move it into smaller containers. You take an inventory of the capacities of the available containers.
 * 
 * For example, suppose you have containers of size `20`, `15`, `10`, `5`, and `5` liters. If you need to store `25` liters, there are four ways to do it:
 * 
 * - `15` and `10`
 * - `20` and `5` (the first `5`)
 * - `20` and `5` (the second `5`)
 * - `15`, `5`, and `5`
 * Filling all containers entirely, how many different combinations of containers can exactly fit all 150 liters of eggnog?
 */
int part_one() {
    int sz = sizeof(input) / sizeof(int);
    int target = T;
    int res = 0;
    for (int i=0; i < sz; i++) {
        res += recurse1(i, target, input[i], sz);
    }
    return res;
}

/*
 * While playing with all the containers in the kitchen, another load of eggnog arrives! The shipping and receiving department is requesting as many containers as you can spare.
 * 
 * Find the minimum number of containers that can exactly fit all 150 liters of eggnog. How many different ways can you fill that number of containers and still hold exactly 150 litres?
 * 
 * In the example above, the minimum number of containers was two. There were three ways to use that many containers, and so the answer there would be 3.
 * 
 */

int part_two() {
    int sz = sizeof(input) / sizeof(int);
    int target = T;
    int min_combo = 0x7FFFFFFF;
    for (int i=0; i < sz; i++) {
        min_combo = min(min_combo, recurse2(i, target, input[i], sz, 1));
    }
    int res = 0;
    for (int i=0; i < sz; i++) {
        res += recurse3(i, target, input[i], sz, min_combo, 1);
    }
    return res;
}

int main() {
    printf("There are %d combinations that can fit 150 litres of eggnog exactly.\n", part_one());
    printf("There are %d unique combinations with the minimum number of containers that can fit 150 litres of eggnog exactly.\n", part_two());
}

int recurse1(int pos, int target, int in, int sz) {
    if (pos == sz) return 0;
    if (in > target) return 0;
    if (in == target) return 1;
    int counter = 0;
    for (int i=pos+1; i<sz;i++) {
        counter += recurse1(i, target, in+input[i], sz);
    }
    return counter;
}

int recurse2(int pos, int target, int in, int sz, int containers) {
    if (pos == sz) return 0x7FFFFFFF;
    if (in > target) return 0x7FFFFFFF;
    if (in == target) return containers;
    int counter = 0x7FFFFFFF;
    for (int i=pos+1; i<sz;i++) {
        counter = min(counter, recurse2(i, target, in+input[i], sz, containers+1));
    }
    return counter;
}

int recurse3(int pos, int target, int in, int sz, int depth_limit, int depth) {
    if (pos == sz) return 0;
    if (in > target) return 0;
    if (depth > depth_limit) return 0;
    if (in == target) return 1;
    int counter = 0;
    for (int i=pos+1; i<sz;i++) {
        counter += recurse3(i, target, in+input[i], sz, depth_limit, depth+1);
    }
    return counter;
}
