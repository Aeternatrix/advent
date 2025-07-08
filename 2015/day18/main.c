// ====================================================================
//  $File: main.c $
//  $Date: 08-07-2025 @ 16-54-13 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "input.h"

#define SZ 100

#define DEAD  0x00
#define ALIVE 0x01
#define BORN  0x02
#define DYING 0x04

typedef struct { int dies_lt, dies_gt; int born_lt, born_gt; } conway_rules;
void update(conway_rules rules);

int working_grid[SZ*SZ] = {};


/*
 * After the million lights incident, the fire code has gotten stricter: now, at most ten thousand lights are allowed. You arrange them in a 100x100 grid.
 * 
 * Never one to let you down, Santa again mails you instructions on the ideal lighting configuration. With so few lights, he says, you'll have to resort to animation.
 * 
 * Start by setting your lights to the included initial configuration (your puzzle input). A # means "on", and a . means "off".
 * 
 * Then, animate your grid in steps, where each step decides the next configuration based on the current one. Each light's next state (either on or off) depends on its current state and the current states of the eight lights adjacent to it (including diagonals). Lights on the edge of the grid might have fewer than eight neighbors; the missing ones always count as "off".
 * 
 * For example, in a simplified 6x6 grid, the light marked `A` has the neighbors numbered `1` through `8`, and the light marked `B`, which is on an edge, only has the neighbors marked `1` through `5`:
 * 
 * - 1B5...
 * - 234...
 * - ......
 * - ..123.
 * - ..8A4.
 * - ..765.
 * The state a light should have next is based on its current state (on or off) plus the number of neighbors that are on:
 * 
 * - A light which is on stays on when `2` or `3` neighbors are on, and turns off otherwise.
 * - A light which is off turns on if exactly `3` neighbors are on, and stays off otherwise.
 * - All of the lights update simultaneously; they all consider the same current state before moving to the next.
 * 
 * Here's a few steps from an example configuration of another 6x6 grid:
 * 
 * - Initial state:
 * - .#.#.#
 * - ...##.
 * - #....#
 * - ..#...
 * - #.#..#
 * - ####..
 * - 
 * - After 1 step:
 * - ..##..
 * - ..##.#
 * - ...##.
 * - ......
 * - #.....
 * - #.##..
 * - 
 * - After 2 steps:
 * - ..###.
 * - ......
 * - ..###.
 * - ......
 * - .#....
 * - .#....
 * - 
 * - After 3 steps:
 * - ...#..
 * - ......
 * - ...#..
 * - ..##..
 * - ......
 * - ......
 * - 
 * - After 4 steps:
 * - ......
 * - ......
 * - ..##..
 * - ..##..
 * - ......
 * - ......
 * After 4 steps, this example has four lights on.
 * 
 * In your grid of 100x100 lights, given your initial configuration, how many lights are on after 100 steps?
 */
int part_one() {
    // I do like me a Conway's Game of Life
    // Cells die on 1, 4, 5, 6, 7, 8, 9
    // Cells live on 2, 3
    // Cells birth on 3
    // Borders are dead

    conway_rules rules = { 2, 3, 4, 2 };

    for (int step=0;step < 100; step++) {
        update(rules);
    }
    int count = 0;
    for (int i=0; i< SZ*SZ;i++) {
        count += (working_grid[i] & ALIVE) == ALIVE;
    }
    return count;
}

/*
 * You flip the instructions over; Santa goes on to point out that this is all just an implementation of Conway's Game of Life. At least, it was, until you notice that something's wrong with the grid of lights you bought: four lights, one in each corner, are stuck on and can't be turned off. The example above will actually run like this:
 * 
 * - Initial state:
 * - ##.#.#
 * - ...##.
 * - #....#
 * - ..#...
 * - #.#..#
 * - ####.#
 * - 
 * - After 1 step:
 * - #.##.#
 * - ####.#
 * - ...##.
 * - ......
 * - #...#.
 * - #.####
 * - 
 * - After 2 steps:
 * - #..#.#
 * - #....#
 * - .#.##.
 * - ...##.
 * - .#..##
 * - ##.###
 * - 
 * - After 3 steps:
 * - #...##
 * - ####.#
 * - ..##.#
 * - ......
 * - ##....
 * - ####.#
 * - 
 * - After 4 steps:
 * - #.####
 * - #....#
 * - ...#..
 * - .##...
 * - #.....
 * - #.#..#
 * - 
 * - After 5 steps:
 * - ##.###
 * - .##..#
 * - .##...
 * - .##...
 * - #.#...
 * - ##...#
 * After 5 steps, this example now has 17 lights on.
 * 
 * In your grid of 100x100 lights, given your initial configuration, but with the four corners always in the on state, how many lights are on after 100 steps?
 */
int part_two() {
    conway_rules rules = { 2, 3, 4, 2 };

    working_grid[0] = ALIVE;
    working_grid[SZ-1] = ALIVE;
    working_grid[(SZ-1) * SZ] = ALIVE;
    working_grid[(SZ-1) * SZ + SZ-1] = ALIVE;

    for (int step=0;step < 100; step++) {
        update(rules);
        working_grid[0] = ALIVE;
        working_grid[SZ-1] = ALIVE;
        working_grid[(SZ-1) * SZ] = ALIVE;
        working_grid[(SZ-1) * SZ + SZ-1] = ALIVE;
    }

    int count = 0;
    for (int i=0; i< SZ*SZ;i++) {
        count += (working_grid[i] & ALIVE) == ALIVE;
    }
    return count;
}

void copy_init() {
    const char* c = input;
    do working_grid[c-input] = *c == '#'; while(*c++);
}

int main() {
    copy_init();
    printf("There are %d lights on after 100 steps.\n", part_one());
    copy_init();
    printf("There are %d lights on after 100 steps.\n", part_two());
}

int get_surrounding(int x, int y) {
    int left   = x-1 >= 0;
    int right  = x+1 < SZ;
    int top    = y-1 >= 0;
    int bottom = y+1 < SZ;

    int pos    = y * SZ + x;
    int pos_up = (y-1) * SZ + x;
    int pos_dn = (y+1) * SZ + x;

    int count = 0;
    if (left)           count += (working_grid[pos-1]       & ALIVE) == ALIVE;
    if (right)          count += (working_grid[pos+1]       & ALIVE) == ALIVE;
    if (top)            count += (working_grid[pos_up]      & ALIVE) == ALIVE;
    if (top && left)    count += (working_grid[pos_up-1]    & ALIVE) == ALIVE;
    if (top && right)   count += (working_grid[pos_up+1]    & ALIVE) == ALIVE;
    if (bottom)         count += (working_grid[pos_dn]      & ALIVE) == ALIVE;
    if (bottom && left) count += (working_grid[pos_dn-1]    & ALIVE) == ALIVE;
    if (bottom && right)count += (working_grid[pos_dn+1]    & ALIVE) == ALIVE;
    return count;
}


void update(conway_rules rules) {
    for (int y = 0; y < SZ; y++) {
        for (int x = 0; x < SZ; x++) {
            int surr = get_surrounding(x, y);
            if (surr < rules.dies_lt || surr > rules.dies_gt) working_grid[y * SZ + x] |= DYING;
            if (surr < rules.born_lt && surr > rules.born_gt) working_grid[y * SZ + x] |= BORN;
        }
    }
    for (int i=0; i < SZ*SZ; i++) {
        if ((working_grid[i] & BORN) == BORN) working_grid[i] = ALIVE;
        if ((working_grid[i] & DYING) == DYING) working_grid[i] = DEAD;
    }
}
