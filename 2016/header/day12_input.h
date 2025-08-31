// ====================================================================
//  $File: day12_input.h $
//  $Date: 01-09-2025 @ 04-56-05 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

const char day12_input[] = {
    "cpy 1 a\n"
    "cpy 1 b\n"
    "cpy 26 d\n"
    "jnz c 2\n"
    "jnz 1 5\n"
    "cpy 7 c\n"
    "inc d\n"
    "dec c\n"
    "jnz c -2\n"
    "cpy a c\n"
    "inc a\n"
    "dec b\n"
    "jnz b -2\n"
    "cpy c b\n"
    "dec d\n"
    "jnz d -6\n"
    "cpy 16 c\n"
    "cpy 17 d\n"
    "inc a\n"
    "dec d\n"
    "jnz d -2\n"
    "dec c\n"
    "jnz c -5"
};
const int day12_input_size = sizeof(day12_input);
