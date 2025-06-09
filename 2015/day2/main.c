// ====================================================================
//  $File: main.c $
//  $Date: 09-06-2025 @ 15-46-30 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
// Putting it in a .h also puts it in the binary, so the binary doesn't rely on an input file (Obvs, if the input changes, that would be a reason to do IO; but so far, it has not changed).
#include "input.h"
/*
 * The elves are running low on wrapping paper, and so they need to submit an order for more. They have a list of the dimensions (length `l`, width `w`, and height `h`) of each present, and only want to order exactly as much as they need.
 *
 * Fortunately, every present is a box (a perfect right rectangular prism), which makes calculating the required wrapping paper for each gift a little easier: find the surface area of the box, which is `2*l*w + 2*w*h + 2*h*l`. The elves also need a little extra paper for each present: the area of the smallest side.
 * 
 * For example:
 * 
 * - A present with dimensions `2x3x4` requires `2*6 + 2*12 + 2*8 = 52` square feet of wrapping paper plus `6` square feet of slack, for a total of `58` square feet.
 * - A present with dimensions `1x1x10` requires `2*1 + 2*10 + 2*10 = 42` square feet of wrapping paper plus `1` square foot of slack, for a total of `43` square feet.
 * All numbers in the elves' list are in feet. How many total square feet of wrapping paper should they order?
 */

typedef union {
    struct {
        int l, w, h;
    };
    int E[3];
} vol;

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int part_one() {
    char c;
    
    vol r = { 0 };  // Read
    int w = 0;      // Working

    int itr = 0;
    int sqft = 0;
    do {
        c = input[itr++]; // Read and consume character
        if (c == 'x') { w++; continue; }
        if (c == '\n' || c == '\0') {
            if (r.l > r.w) swap(&r.l, &r.w);
            if (r.w > r.h) swap(&r.w, &r.h);
            if (r.l > r.w) swap(&r.l, &r.w);

            sqft += 3*r.l*r.w + 2*r.w*r.h + 2*r.h*r.l;
            r = (vol) { 0 };
            w = 0;
            continue;
        }
        r.E[w] = r.E[w] * 10 + c - '0';
    } while (c != '\0');
    return sqft;
}

/*
 * The elves are also running low on ribbon. Ribbon is all the same width, so they only have to worry about the length they need to order, which they would again like to be exact.
 * 
 * The ribbon required to wrap a present is the shortest distance around its sides, or the smallest perimeter of any one face. Each present also requires a bow made out of ribbon as well; the feet of ribbon required for the perfect bow is equal to the cubic feet of volume of the present. Don't ask how they tie the bow, though; they'll never tell.
 * 
 * For example:
 * 
 * - A present with dimensions `2x3x4` requires `2+2+3+3 = 10` feet of ribbon to wrap the present plus `2*3*4 = 24` feet of ribbon for the bow, for a total of `34` feet.
 * - A present with dimensions `1x1x10` requires `1+1+1+1 = 4` feet of ribbon to wrap the present plus `1*1*10 = 10` feet of ribbon for the bow, for a total of `14` feet.
 * How many total feet of ribbon should they order?
 */
int part_two() {
    char c;
    
    vol r = { 0 };  // Read
    int w = 0;      // Working

    int itr = 0;
    int length = 0;
    do {
        c = input[itr++]; // Read and consume character
        if (c == 'x') { w++; continue; }
        if (c == '\n' || c == '\0') {
            if (r.l > r.w) swap(&r.l, &r.w);
            if (r.w > r.h) swap(&r.w, &r.h);
            if (r.l > r.w) swap(&r.l, &r.w);

            length += 2*(r.l+r.w) + r.l*r.w*r.h;
            r = (vol) { 0 };
            w = 0;
            continue;
        }
        r.E[w] = r.E[w] * 10 + c - '0';
    } while (c != '\0');
    return length;
}

typedef struct {
    int part_one;
    int part_two;
} answer;

/*
 * The only difference between the two parts is the math; which is to say they can both be done at the same time.
 */
answer
together() {
    answer rt = { 0 };
    char c;
    
    vol r = { 0 };
    int w = 0;

    int itr = 0;
    do {
        c = input[itr++];
        if (c == 'x') { w++; continue; }
        if (c == '\n' || c == '\0') {
            if (r.l > r.w) swap(&r.l, &r.w);
            if (r.w > r.h) swap(&r.w, &r.h);
            if (r.l > r.w) swap(&r.l, &r.w);

            rt.part_one += 3*r.l*r.w + 2*r.w*r.h + 2*r.h*r.l;
            rt.part_two += 2*(r.l+r.w) + r.l*r.w*r.h;
            r = (vol) { 0 };
            w = 0;
            continue;
        }
        r.E[w] = r.E[w] * 10 + c - '0';
    } while (c != '\0');
    return rt;
}

int main() {
    answer ans = together();
    printf("They should order %dft² of wrapping papper.\n", ans.part_one);
    printf("They should order %dft of ribbon.\n", ans.part_two);
}

