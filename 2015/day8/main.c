// ====================================================================
//  $File: main.c $
//  $Date: 23-06-2025 @ 01-10-10 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================
#include <stdio.h>

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
// I feel #include "input.h" for this one is a bit... too much effort to format for this question to handwave it

#define PAGE 4096

long
read_file(char* buff) {
    const char filename[] = "input";
    char mainc_path[PAGE] = {};
    char input_path[PAGE] = {};
    char* last_slash = mainc_path;
    int ptr = 0;
    struct stat st;

    realpath(__FILE__, mainc_path);

    for (char* scanner = mainc_path; *scanner; scanner++) {
        if (*scanner == '/') last_slash = scanner+1;
    }

    // main.c file path, excluding "main.c"
    for (int a = 0; a < (last_slash - mainc_path); a++) input_path[ptr++] = mainc_path[a];
    // append "input"
    for (int b = 0; b < 5; b++) input_path[ptr++] = filename[b];

    ptr = open(input_path, O_RDONLY);
    if (ptr < 0) { printf("input file not found with main.c\n"); return 0; }

    fstat(ptr, &st);

    long bytes = read(ptr, buff, st.st_size);
    close(ptr);

    if (bytes < st.st_size) printf("Couldn't read file\n");

    return st.st_size;
}

/*
 * Space on the sleigh is limited this year, and so Santa will be bringing his list as a digital copy. He needs to know how much space it will take up when stored.
 * 
 * It is common in many programming languages to provide a way to escape special characters in strings. For example, C, JavaScript, Perl, Python, and even PHP handle special characters in very similar ways.
 * 
 * However, it is important to realize the difference between the number of characters in the code representation of the string literal and the number of characters in the in-memory string itself.
 * 
 * For example:
 * 
 * - `""` is `2` characters of code (the two double quotes), but the string contains zero characters.
 * - `"abc"` is `5` characters of code, but 3 characters in the string data.
 * - `"aaa\"aaa"` is `10` characters of code, but the string itself contains six "a" characters and a single, escaped quote character, for a total of `7` characters in the string data.
 * - `"\x27"` is `6` characters of code, but the string itself contains just one - an apostrophe (`'`), escaped using hexadecimal notation.
 * Santa's list is a file that contains many double-quoted string literals, one on each line. The only escape sequences used are `\\` (which represents a single backslash), `\"` (which represents a lone double-quote character), and `\x` plus two hexadecimal characters (which represents a single character with that ASCII code).
 * 
 * Disregarding the whitespace in the file, what is the number of characters of code for string literals minus the number of characters in memory for the values of the strings in total for the entire file?
 * 
 * For example, given the four strings above, the total number of characters of string code (2 + 5 + 10 + 6 = 23) minus the total number of characters in memory for string values (0 + 3 + 7 + 1 = 11) is 23 - 11 = 12.
 * 
 */
int is_hex(char c) {
    return (c <= '9' && c >= '0') || (c <= 'f' && c >= 'a');
}

int part_one(char* buf, long sz) {
    int literal = 0;
    char c;
    int ptr = 0;

    do {
        c = buf[ptr++];

        switch (c) {
            case '\\':
                literal++;
                if (buf[ptr] == 'x' && is_hex(buf[ptr+1]) && is_hex(buf[ptr+2])) ptr+=2; // \x##
                ptr++;
            case '"':
            case '\0':
                break;
            case '\n':
                sz--;
                break;
            default:
                literal++;
        }
    } while (c != '\0');

    return sz - literal;
}

/*
 * Now, let's go the other way. In addition to finding the number of characters of code, you should now encode each code representation as a new string and find the number of characters of the new encoded representation, including the surrounding double quotes.
 * 
 * For example:
 * 
 * - `""` encodes to `"\"\""`, an increase from `2` characters to `6`.
 * - `"abc"` encodes to `"\"abc\""`, an increase from `5` characters to `9`.
 * - `"aaa\"aaa"` encodes to `"\"aaa\\\"aaa\""`, an increase from `10` characters to `16`.
 * - `"\x27"` encodes to `"\"\\x27\""`, an increase from `6` characters to `11`.
 * Your task is to find the total number of characters to represent the newly encoded strings minus the number of characters of code in each original string literal. For example, for the strings above, the total encoded length (`6 + 9 + 16 + 11 = 42`) minus the characters in the original code representation (`23`, just like in the first part of this puzzle) is `42 - 23 = 19`.
 */
int part_two(char* buf, long sz) {
    int encoded = 0;
    char c;
    int ptr = 0;

    do {
        c = buf[ptr++];

        switch (c) {
            case '\\':
                encoded+=2; // \ → \\''
                if (buf[ptr] == 'x' && is_hex(buf[ptr+1]) && is_hex(buf[ptr+2])) {
                    ptr+=3;
                    encoded+=3; // x##
                }
                break;
            case '"':
                encoded+=2; // " → \"
            case '\0':
                break;
            case '\n':
                sz--;
                encoded+=2; // encapsulating "
                break;
            default:
                encoded++;
        }
    } while (c != '\0');

    return encoded - sz;
}

int main() {
    char input[2 * PAGE] = {}; // 8KB; the file is ~6.5KB
    long sz = read_file(input);
    printf("Memory - Literal = %d.\n", part_one(input, sz));
    printf("Encoded - Literal = %d.\n", part_two(input, sz));
}
