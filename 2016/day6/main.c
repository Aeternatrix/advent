// ====================================================================
//  $File: main.c $
//  $Date: 07-08-2025 @ 10-34-51 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "day6_input.h"

#define ALPHA 26
int min_pos_in_arr(int* arr);
int max_pos_in_arr(int* arr);

void part_one(char* buf) {
    // super dumb easy way to do this...
    int pos1[ALPHA] = {};
    int pos2[ALPHA] = {};
    int pos3[ALPHA] = {};
    int pos4[ALPHA] = {};
    int pos5[ALPHA] = {};
    int pos6[ALPHA] = {};
    int pos7[ALPHA] = {};
    int pos8[ALPHA] = {};
    for (const char* c = day6_input; ; c+=8) {
        if (*c == '\n') c++;
        if (*c == '\0') break;
        pos1[c[0]-'a']++;
        pos2[c[1]-'a']++;
        pos3[c[2]-'a']++;
        pos4[c[3]-'a']++;
        pos5[c[4]-'a']++;
        pos6[c[5]-'a']++;
        pos7[c[6]-'a']++;
        pos8[c[7]-'a']++;
    }
    buf[0] = max_pos_in_arr(pos1) + 'a';
    buf[1] = max_pos_in_arr(pos2) + 'a';
    buf[2] = max_pos_in_arr(pos3) + 'a';
    buf[3] = max_pos_in_arr(pos4) + 'a';
    buf[4] = max_pos_in_arr(pos5) + 'a';
    buf[5] = max_pos_in_arr(pos6) + 'a';
    buf[6] = max_pos_in_arr(pos7) + 'a';
    buf[7] = max_pos_in_arr(pos8) + 'a';
}

void part_two(char* buf) {
    // super dumb easy way to do this...
    int pos1[ALPHA] = {};
    int pos2[ALPHA] = {};
    int pos3[ALPHA] = {};
    int pos4[ALPHA] = {};
    int pos5[ALPHA] = {};
    int pos6[ALPHA] = {};
    int pos7[ALPHA] = {};
    int pos8[ALPHA] = {};
    for (const char* c = day6_input; ; c+=8) {
        if (*c == '\n') c++;
        if (*c == '\0') break;
        pos1[c[0]-'a']++;
        pos2[c[1]-'a']++;
        pos3[c[2]-'a']++;
        pos4[c[3]-'a']++;
        pos5[c[4]-'a']++;
        pos6[c[5]-'a']++;
        pos7[c[6]-'a']++;
        pos8[c[7]-'a']++;
    }
    buf[0] = min_pos_in_arr(pos1) + 'a';
    buf[1] = min_pos_in_arr(pos2) + 'a';
    buf[2] = min_pos_in_arr(pos3) + 'a';
    buf[3] = min_pos_in_arr(pos4) + 'a';
    buf[4] = min_pos_in_arr(pos5) + 'a';
    buf[5] = min_pos_in_arr(pos6) + 'a';
    buf[6] = min_pos_in_arr(pos7) + 'a';
    buf[7] = min_pos_in_arr(pos8) + 'a';
}

int main() {
    char buf[9] = {};
    part_one(buf);
    printf("The error corrected message is %s\n", buf);
    part_two(buf);
    printf("The original message is %s\n", buf);
}

int min_pos_in_arr(int* arr) {
    int rt = 0x7FFFFFFF;
    int pos = 0;
    for (int i=0;i<ALPHA;i++) {
        if (arr[i] < rt && arr[i] != 0) {
            rt = arr[i];
            pos = i;
        }
    }
    return pos;
}

int max_pos_in_arr(int* arr) {
    int rt = 0;
    int pos = 0;
    for (int i=0;i<ALPHA;i++) {
        if (arr[i] > rt) {
            rt = arr[i];
            pos = i;
        }
    }
    return pos;
}

