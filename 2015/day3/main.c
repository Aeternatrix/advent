// ====================================================================
//  $File: main.c $
//  $Date: 09-06-2025 @ 17-06-02 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "input.h"

typedef struct { int x, y; } location_santa;

/*
 * Santa is delivering presents to an infinite two-dimensional grid of houses.
 * 
 * He begins by delivering a present to the house at his starting location, and then an elf at the North Pole calls him via radio and tells him where to move next. Moves are always exactly one house to the north (`^`), south (`v`), east (`>`), or west (`<`). After each move, he delivers another present to the house at his new location.
 * 
 * However, the elf back at the north pole has had a little too much eggnog, and so his directions are a little off, and Santa ends up visiting some houses more than once. How many houses receive at least one present?
 * 
 * For example:
 * 
 * - `>` delivers presents to `2` houses: one at the starting location, and one to the east.
 * - `^>v<` delivers presents to `4` houses in a square, including twice to the house at his starting/ending location.
 * - `^v^v^v^v^v` delivers a bunch of presents to some very lucky children at only `2` houses.
 * 
 */
int part_one() {
    int grid[1000][1000] = {}; // A sufficiently large grid
    location_santa santa = {500, 500};
    char c;
    int itr = 0;
    int unique_houses = 0;
    do {
        c = input[itr++];
        switch (c) {
            case '>': santa.x++; break;
            case '^': santa.y++; break;
            case '<': santa.x--; break;
            case 'v': santa.y--; break;
        }
        unique_houses += (grid[santa.x][santa.y]++) == 0;
    } while (c != '\0');

    return unique_houses;
}


/*
 * The next year, to speed up the process, Santa creates a robot version of himself, Robo-Santa, to deliver presents with him.
 * 
 * Santa and Robo-Santa start at the same location (delivering two presents to the same starting house), then take turns moving based on instructions from the elf, who is eggnoggedly reading from the same script as the previous year.
 * 
 * This year, how many houses receive at least one present?
 * 
 * For example:
 * 
 * - `^v` delivers presents to `3` houses, because Santa goes north, and then Robo-Santa goes south.
 * - `^>v<` now delivers presents to `3` houses, and Santa and Robo-Santa end up back where they started.
 * - `^v^v^v^v^v` now delivers presents to `11` houses, with Santa going one direction and Robo-Santa going the other.
 */
int part_two() {
    int grid[1000][1000] = {}; // A sufficiently large grid
    location_santa santa = {500, 500};
    location_santa robo_santa = {500, 500};
    char c;
    int itr = 0;
    int unique_houses = 0;
    do {
        c = input[itr++];
        switch (c) {
            case '>': santa.x += itr % 2; robo_santa.x += !(itr % 2); break;
            case '^': santa.y += itr % 2; robo_santa.y += !(itr % 2); break;
            case '<': santa.x -= itr % 2; robo_santa.x -= !(itr % 2); break;
            case 'v': santa.y -= itr % 2; robo_santa.y -= !(itr % 2); break;
        }
        unique_houses += (grid[santa.x][santa.y]++) == 0;
        unique_houses += (grid[robo_santa.x][robo_santa.y]++) == 0;
    } while (c != '\0');

    return unique_houses;
}

int main() {
    printf("%d houses received at least one present from Santa.\n", part_one());
    printf("%d houses received at least one present from Santa or Robo-Santa.\n", part_two());
}
