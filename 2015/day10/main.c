// ====================================================================
//  $File: main.c $
//  $Date: 04-07-2025 @ 05-05-49 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <stdlib.h>
const char input[] = "3113322113";

#define PAGE 4096

int count(char* ptr) {
    char c = *ptr;
    int count = 0;
    while(c == *ptr++) count++;
    return count;
}

int
iterate(char* buf, int sz) {
    char* tmp = calloc(PAGE * PAGE, sizeof(char));
    int ptr = 0;
    int itr = 0;
    char c = buf[itr];
    do {
        int cnt = count(&buf[itr]);
        itr += cnt;
        
        int cnt_tmp = cnt;
        int digits = 0;
        while(cnt_tmp) {
            cnt_tmp /= 10;
            digits++;
        }
        ptr+= digits;
        for (int i = digits; i != 0; i--) {
            tmp[ptr-i] = (cnt % 10) + '0';
            cnt /= 10;
        }
        tmp[ptr++] = c;
        c = buf[itr];
    } while (c);

    for (int i = 0; i < sz; i++) buf[i] = 0;

    char* t = tmp;
    int i;
    for (i=0; *t; i++) buf[i] = *t++;
    free(tmp);
    return i;
}

/*
 * Today, the Elves are playing a game called look-and-say. They take turns making sequences by reading aloud the previous sequence and using that reading as the next sequence. For example, 211 is read as "one two, two ones", which becomes 1221 (1 2, 2 1s).
 * 
 * Look-and-say sequences are generated iteratively, using the previous value as input for the next step. For each step, take the previous value, and replace each run of digits (like 111) with the number of digits (3) followed by the digit itself (1).
 * 
 * For example:
 * 
 * - `1` becomes `11` (`1` copy of digit `1`).
 * - `11` becomes `21` (`2` copies of digit `1`).
 * - `21` becomes `1211` (one `2` followed by one `1`).
 * - `1211` becomes `111221` (one `1`, one 2, and two `1`s).
 * - `111221` becomes `312211` (three `1`s, two `2`s, and one `1`).
 * Starting with the digits in your puzzle input, apply this process 40 times. What is the length of the result?
 */
int part_one() {
    char* buf = calloc(PAGE * PAGE, sizeof(char));
    for (int i = 0; i < sizeof(input); i++) buf[i] = input[i];
    int sz = 0;
    char* c = buf;
    while (*c++) sz++;
    int prev = sz;
    for (int itr = 0; itr < 40; itr++) {
        prev = sz;
        sz = iterate(buf, sz);
    }
    free(buf);
    return sz;
}


/*
 * Neat, right? You might also enjoy hearing John Conway talking about this sequence (that's Conway of Conway's Game of Life fame).
 * 
 * Now, starting again with the digits in your puzzle input, apply this process 50 times. What is the length of the new result?
 */
int part_two() {
    char* buf = calloc(PAGE * PAGE, sizeof(char)); // I'm just over shooting now; have 16 MB of heap.
    for (int i = 0; i < sizeof(input); i++) buf[i] = input[i];
    int sz = 0;
    char* c = buf;
    while (*c++) sz++;
    for (int itr = 0; itr < 50; itr++) {
        sz = iterate(buf, sz);
    }
    free(buf);
    return sz;
}

// After seeing the video, in Part Two. First, Conway is a madman, GG my guy.
// Second, I was sure there was a less dumb/brute force way than what I was doing, but am more sure now.
int main() {
    printf("After 40 iterations, %s becomes a %d length number.\n", input, part_one());
    printf("After 50 iterations, %s becomes a %d length number.\n", input, part_two());
    return 0;
}
