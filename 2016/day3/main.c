// ====================================================================
//  $File: main.c $
//  $Date: 04-08-2025 @ 16-53-25 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "day3_input.h"

int part_one() {
    int rt = 0;

    for (int i = 0; i < day3_input_size; i++) {
        rt += (day3_input[i].x < day3_input[i].y + day3_input[i].z) &&
              (day3_input[i].y < day3_input[i].x + day3_input[i].z) &&
              (day3_input[i].z < day3_input[i].x + day3_input[i].y);
    }

    return rt;
}

int part_two() {
    int rt = 0;

    for (int i = 0; i < day3_input_size; i+=3) {
        rt += (day3_input[i+0].x < day3_input[i+1].x + day3_input[i+2].x) &&
              (day3_input[i+1].x < day3_input[i+0].x + day3_input[i+2].x) &&
              (day3_input[i+2].x < day3_input[i+0].x + day3_input[i+1].x);
        rt += (day3_input[i+0].y < day3_input[i+1].y + day3_input[i+2].y) &&
              (day3_input[i+1].y < day3_input[i+0].y + day3_input[i+2].y) &&
              (day3_input[i+2].y < day3_input[i+0].y + day3_input[i+1].y);
        rt += (day3_input[i+0].z < day3_input[i+1].z + day3_input[i+2].z) &&
              (day3_input[i+1].z < day3_input[i+0].z + day3_input[i+2].z) &&
              (day3_input[i+2].z < day3_input[i+0].z + day3_input[i+1].z);
    }

    return rt;
}

int main() {
    printf("There are %d possible triangles.\n", part_one());
    printf("There are actually %d possible triangles.\n", part_two());
}
