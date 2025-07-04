// ====================================================================
//  $File: main.c $
//  $Date: 09-06-2025 @ 15-15-11 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
// Input as a char[] because I don't want to do FILE IO just to read it into a char[] at the end
#include "input.h"

/*
 * Santa is trying to deliver presents in a large apartment building, but he can't find the right floor - the directions he got are a little confusing. He starts on the ground floor (floor 0) and then follows the instructions one character at a time.
 * 
 * An opening parenthesis, (, means he should go up one floor, and a closing parenthesis, ), means he should go down one floor.
 * 
 * The apartment building is very tall, and the basement is very deep; he will never find the top or bottom floors.
 * 
 * For example:
 * 
 * - `(())` and `()()` both result in floor 0.
 * - `(((` and `(()(()(` both result in floor 3.
 * - `))(((((` also results in floor 3.
 * - `())` and `))(` both result in floor -1 (the first basement level).
 * - `)))` and `)())())` both result in floor -3.
 * To what floor do the instructions take Santa?
 */
int part_one() {
    char c;
    int itr = 0;
    int floor = 0;
    do {
        c = input[itr++];
        floor += (c == '(') - (c == ')');
    } while (c != '\0');

    return floor;
}

/*
 * Now, given the same instructions, find the position of the first character that causes him to enter the basement (floor -1). The first character in the instructions has position 1, the second character has position 2, and so on.
 * 
 * For example:
 *
 * - `)` causes him to enter the basement at character position 1.
 * - `()())` causes him to enter the basement at character position 5.
 * What is the position of the character that causes Santa to first enter the basement?
 */
int part_two() {
    char c;
    int itr = 0;
    int floor = 0;
    do {
        c = input[itr++];
        floor += (c == '(') - (c == ')');

    } while (c != '\0' && floor > 0);
    return ++itr;
}

int main() {
    printf("Santa ends on F%d.\n", part_one());
    printf("Santa goes to the basement on instruction %d.\n", part_two());
}
