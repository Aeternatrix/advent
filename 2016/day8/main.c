// ====================================================================
//  $File: main.c $
//  $Date: 07-08-2025 @ 15-30-10 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>

#include "day8_input.h"

#define PAGE 4096
#define WIDTH 50
#define HEIGHT 6

typedef unsigned char   uint8;
typedef uint8           bool8;

typedef enum { UNDEF, CREATE, RIGHT_SHIFT, DOWN_SHIFT } command;
typedef struct { command cmd; int a, b; } instruction;

instruction instructions[PAGE] = {};
void read_instructions();
bool8 arr[WIDTH * HEIGHT] = {};

int part_one() {
    instruction* instr = instructions;
    while (instr->cmd) {
        switch (instr->cmd) {
            case CREATE: // a=x b=y
                for (int y = 0; y < instr->b; y++) {
                    for (int x = 0; x < instr->a; x++) {
                        arr[y*WIDTH + x] = 1;
                    }
                }
                break;
            case RIGHT_SHIFT: {
                    int shift = instr->b;
                    int y = instr->a;
                    for (int i=0;i<WIDTH;i++) arr[instr->a*WIDTH + i] <<= 1;
                    for (int i=0;i<WIDTH;i++) {
                        arr[y*WIDTH + ((shift + i) % WIDTH)] |= arr[y*WIDTH + i] >> 1;
                    }
                }
                break;
            case DOWN_SHIFT: {
                    int shift = instr->b;
                    int x = instr->a;
                    for (int i=0;i<HEIGHT;i++) arr[i*WIDTH + x] <<= 1;
                    for (int i=0;i<HEIGHT;i++) {
                        arr[((shift+i)%HEIGHT)*WIDTH + x] |= arr[i*WIDTH + x] >> 1;
                    }
                }
                break;
            default:
                break;
        }
        for (int i=0;i<WIDTH*HEIGHT;i++) arr[i] &= 1;
        instr++;
    }

    int count = 0;
    for (int i=0;i<WIDTH*HEIGHT;i++) count += arr[i];

    return count;
}

void part_two() {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            printf("%s ", arr[y*WIDTH + x] ? "#" : " ");
        }
        printf("\n");
    }
}

int main() {
    read_instructions();
    printf("There should be %d pixels lit.\n", part_one());
    printf("Which gives the lettering:\n");
    part_two();
}

bool8 is_num(char c) { return c <= '9' && c >= '0'; }

void
read_instructions() {
    const char* c = day8_input;
    int ptr = 0;
    instruction instr = {};
    bool8 digit = 0;
    bool8 a = 1;

    while (*c) {
        if (c[0] == 'r' && c[1] == 'e') instr.cmd = CREATE;
        if (c[0] == 'r' && c[1] == 'o') instr.cmd = RIGHT_SHIFT;
        if (c[0] == 'c' && c[1] == 'o') instr.cmd = DOWN_SHIFT;
        
        if (digit && !is_num(*c)) {
            digit = 0;
            a = !a;
        }
        if (is_num(*c)) {
            if (a) {
                instr.a = instr.a * 10 + *c - '0';
            } else {
                instr.b = instr.b * 10 + *c - '0';
            }
            digit = 1;
        }          

        if (*c == '\n') {
            instructions[ptr++] = instr;
            instr = (instruction){};
            a = 1;
        }
        c++;
    }
    instructions[ptr++] = instr;
}
