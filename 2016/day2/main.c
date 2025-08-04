// ====================================================================
//  $File: main.c $
//  $Date: 04-08-2025 @ 15-47-23 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <day2_input.h>

//	const char day2_input[] = "ULL\nRRDDD\nLURDL\nUUUUD";

const char keypad_po[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
const char keypad_pt[] = {
   0, 0, '1', 0, 0,
   0, '2', '3', '4', 0, 
   '5', '6', '7', '8', '9',
   0, 'A', 'B', 'C', 0,
   0, 0, 'D', 0, 0
};
typedef enum { UNDEF, UP, DOWN, LEFT, RIGHT } dir_t;
typedef struct instruction { dir_t dir; struct instruction* next; } instruction;
#define PAGE 4096
instruction instructions[PAGE] = {};
#define PO_SZ 3
#define PT_SZ 5
void read_instructions();

int part_one() {
    int x = 1, y = 1, code = 0;
    instruction* curr = &instructions[1];
    while (curr) {
        switch(curr->dir) {
            case UNDEF:
                code = code * 10 + keypad_po[y * PO_SZ + x];
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
        }
        
        x = x < 0 ? 0 : x;
        y = y < 0 ? 0 : y;
        x = x > PO_SZ-1 ? PO_SZ-1 : x;
        y = y > PO_SZ-1 ? PO_SZ-1 : y;
        curr=curr->next;
    }
    return code;
}

char* part_two(char* code) {
    int x = 0, y = 2, tx, ty, ptr = 0;
    instruction* curr = &instructions[1];
    while (curr) {
        switch(curr->dir) {
            case UNDEF:
                code[ptr++] = keypad_pt[y * PT_SZ + x];
                break;
            case UP:
                ty = y-1;
                ty = ty < 0 ? 0 : ty;
                y = (keypad_pt[ty * PT_SZ + x]) ? ty : y;
                break;
            case DOWN:
                ty = y+1;
                ty = ty > PT_SZ-1 ? PT_SZ-1 : ty;
                y = (keypad_pt[ty * PT_SZ + x]) ? ty : y;
                break;
            case LEFT:
                tx = x-1;
                tx = tx > PT_SZ-1 ? PT_SZ-1 : tx;
                x = (keypad_pt[y * PT_SZ + tx]) ? tx : x;
                break;
            case RIGHT:
                tx = x+1;
                tx = tx > PT_SZ-1 ? PT_SZ-1 : tx;
                x = (keypad_pt[y * PT_SZ + tx]) ? tx : x;
                break;
        }
        curr=curr->next;
    }
    return code;
}

int main() {
    read_instructions();
    printf("The bathroom key code is: %d\n", part_one());
    char buf[6] = {};
    printf("The bathroom key code is: %s\n", part_two(buf));
}

void read_instructions() {
    const char* c = day2_input;
    int ptr = 0;
    do {
        instructions[ptr].next = &instructions[ptr+1];
        switch (*c) {
            case 'U':
                instructions[++ptr] = (instruction) { UP, 0 };
                break;
            case 'D':
                instructions[++ptr] = (instruction) { DOWN, 0 };
                break;
            case 'L':
                instructions[++ptr] = (instruction) { LEFT, 0 };
                break;
            case 'R':
                instructions[++ptr] = (instruction) { RIGHT, 0 };
                break;
        default:
                instructions[++ptr] = (instruction) { 0, 0 };
                break;
        }
    } while (*c++);
}

