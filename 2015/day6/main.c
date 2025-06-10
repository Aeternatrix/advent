// ====================================================================
//  $File: main.c $
//  $Date: 10-06-2025 @ 15-11-06 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <stdlib.h>
#include "input.h"

typedef enum {
    NONE, ON, OFF, TOGGLE
} token;

typedef union {
    struct { int x, y; };
    int E[2];
} vec2;

typedef struct {
    union {    
        struct {
            vec2 start, end;
        };
        int E[4];
    };
    token operator;
} instruction;

typedef struct list_node {
    instruction ins;
    struct list_node* next;
} list_node;

typedef struct {
    list_node* head;
    list_node* tail;
} list;

list instructions = {0};

list_node* create_node(instruction ins) {
    list_node* rt = malloc(sizeof(list_node));
    rt->ins = ins;
    rt->next = 0;
    return rt;
}

void
list_free(list* l) {
    list_node*t;
    list_node*node = l->head;
    while(node->next) {
        t = node;
        node = node->next;
        free(t);
    }
}

void
read_instructions() {
    char c;
    int itr = 0;
    int w = 0;
    instruction ins = {};
    do {
        c = input[itr++];

        if (c >= '0' & c <= '9') {
            ins.E[w] = ins.E[w] * 10 + c - '0';
        }
        w += c == ',' || (w == 1 && c == 't');

        if (c == 'o') {
            char n = input[itr];
            if (n == 'n' || n == 'f' || n == 'g') ins.operator = (n == 'n') + (n == 'f') * 2 + (n == 'g') * 3;
        }

        if (c == '\n' || c == '\0') {
            list_node* node = create_node(ins);
            if (__builtin_expect(instructions.head == 0, 0)) {
                instructions.head = node;
                instructions.tail = node;
            } else {
                instructions.tail->next = node;
                instructions.tail = node;
            }

            ins = (instruction) {0};
            w = 0;
        }
    } while (c != '\0');
}

/*
 * Because your neighbors keep defeating you in the holiday house decorating contest year after year, you've decided to deploy one million lights in a 1000x1000 grid.
 * 
 * Furthermore, because you've been especially nice this year, Santa has mailed you instructions on how to display the ideal lighting configuration.
 * 
 * Lights in your grid are numbered from 0 to 999 in each direction; the lights at each corner are at `0,0`, `0,999`, `999,999`, and `999,0`. The instructions include whether to turn on, turn off, or toggle various inclusive ranges given as coordinate pairs. Each coordinate pair represents opposite corners of a rectangle, inclusive; a coordinate pair like `0,0 through 2,2` therefore refers to 9 lights in a 3x3 square. The lights all start turned off.
 * 
 * To defeat your neighbors this year, all you have to do is set up your lights by doing the instructions Santa sent you in order.
 * 
 * For example:
 * 
 * - `turn on 0,0 through 999,999` would turn on (or leave on) every light.
 * - `toggle 0,0 through 999,0` would toggle the first line of 1000 lights, turning off the ones that were on, and turning on the ones that were off.
 * - `turn off 499,499 through 500,500` would turn off (or leave off) the middle four lights.
 * After following the instructions, how many lights are lit?
 */
int part_one() {
    int g[1000][1000] = {};
    list_node* t = instructions.head;
    while (t->next) {
        instruction ins = t->ins;
        if (ins.operator == ON) {
            for (int x = ins.start.x; x <= ins.end.x; x++) {
                for (int y = ins.start.y; y <= ins.end.y; y++) {
                    g[x][y] = 1;
                }
            }
        }
        if (ins.operator == OFF) {
            for (int x = ins.start.x; x <= ins.end.x; x++) {
                for (int y = ins.start.y; y <= ins.end.y; y++) {
                    g[x][y] = 0;
                }
            }
        }
        if (ins.operator == TOGGLE) {
            for (int x = ins.start.x; x <= ins.end.x; x++) {
                for (int y = ins.start.y; y <= ins.end.y; y++) {
                    g[x][y] = !g[x][y];
                }
            }
        }
        t = t->next;
    }
    int lights = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            lights += g[x][y];
        }
    }

    return lights;
}

/*
 * You just finish implementing your winning light pattern when you realize you mistranslated Santa's message from Ancient Nordic Elvish.
 * 
 * The light grid you bought actually has individual brightness controls; each light can have a brightness of zero or more. The lights all start at zero.
 * 
 * The phrase `turn on` actually means that you should increase the brightness of those lights by `1`.
 * 
 * The phrase `turn off` actually means that you should decrease the brightness of those lights by `1`, to a minimum of zero.
 * 
 * The phrase `toggle` actually means that you should increase the brightness of those lights by `2`.
 * 
 * What is the total brightness of all lights combined after following Santa's instructions?
 * 
 * For example:
 * 
 * - `turn on 0,0 through 0,0` would increase the total brightness by `1`.
 * - `toggle 0,0 through 999,999` would increase the total brightness by `2000000`.
 */
int part_two() {
    int g[1000][1000] = {};
    list_node* t = instructions.head;
    while (t->next) {
        instruction ins = t->ins;
        if (ins.operator == ON) {
            for (int x = ins.start.x; x <= ins.end.x; x++) {
                for (int y = ins.start.y; y <= ins.end.y; y++) {
                    g[x][y] += 1;
                }
            }
        }
        if (ins.operator == OFF) {
            for (int x = ins.start.x; x <= ins.end.x; x++) {
                for (int y = ins.start.y; y <= ins.end.y; y++) {
                    g[x][y] += (g[x][y] - 1 != -1) * -1;
                }
            }
        }
        if (ins.operator == TOGGLE) {
            for (int x = ins.start.x; x <= ins.end.x; x++) {
                for (int y = ins.start.y; y <= ins.end.y; y++) {
                    g[x][y] += 2;
                }
            }
        }
        t = t->next;
    }
    int lights = 0;
    for (int x = 0; x < 1000; x++) {
        for (int y = 0; y < 1000; y++) {
            lights += g[x][y];
        }
    }

    return lights;
}

int main() {
    read_instructions();
    printf("%d lights are lit.\n", part_one());
    printf("The total brightness is %d.\n", part_two());
    list_free(&instructions);
}
