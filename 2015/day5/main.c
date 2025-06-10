// ====================================================================
//  $File: main.c $
//  $Date: 09-06-2025 @ 19-15-37 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "input.h"

typedef struct {
    int vowels[5]; // a e i o u
    char last_char;
    int duplicates;
    int bad;
} meta_word;

/*
 * Santa needs help figuring out which strings in his text file are naughty or nice.
 * 
 * A nice string is one with all of the following properties:
 * 
 * It contains at least three vowels (`aeiou` only), like `aei`, `xazegov`, or `aeiouaeiouaeiou`.
 * It contains at least one letter that appears twice in a row, like `xx`, `abcdde` (`dd`), or `aabbccdd` (`aa`, `bb`, `cc`, or `dd`).
 * It does not contain the strings `ab`, `cd`, `pq`, or `xy`, even if they are part of one of the other requirements.
 * For example:
 * 
 * `ugknbfddgicrmopn` is nice because it has at least three vowels (`u...i...o...`), a double letter (`...dd...`), and none of the disallowed substrings.
 * `aaa` is nice because it has at least three vowels and a double letter, even though the letters used by different rules overlap.
 * - `jchzalrnumimnmhp` is naughty because it has no double letter.
 * - `haegwjzuvuyypxyu` is naughty because it contains the string `xy`.
 * - `dvszwmarrgswjxmb` is naughty because it contains only one vowel.
 * How many strings are nice?
 */
int part_one() {
    char c;
    int itr = 0;
    int nice = 0;
    meta_word word = {};
    do {
        c = input[itr]; // Read
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
            word.vowels[(c == 'e') + (c == 'i') * 2 + (c == 'o') * 3 + (c == 'u')*4]++;
        }

        switch (c) {
            case 'a':
                if (input[itr+1] == 'b') {
                    word.bad = 1;
                }
                break;
            case 'c':
                if (input[itr+1] == 'd') {
                    word.bad = 1;
                }
                break;
            case 'p':
                if (input[itr+1] == 'q') {
                    word.bad = 1;
                }
                break;
            case 'x':
                if (input[itr+1] == 'y') {
                    word.bad = 1;
                }
                break;
        }
        if (word.last_char == c) word.duplicates++;
        if(c == '\n' || c == '\0') {
            int vowel_count = word.vowels[0] + word.vowels[1] + word.vowels[2] + word.vowels[3] + word.vowels[4];
            if (!word.bad && word.duplicates >= 1 && vowel_count >= 3) nice++;
            word = (meta_word) {};
        }
        word.last_char = c;
        itr++;
    } while (c != '\0');
    return nice;
}

int seek_pair(int itr) {
    unsigned short a = *(unsigned short*)(&input[itr]);
    if ((a >> 8) == 0x0 || (a >> 8) == 0xA) return 0;

    const char* c = &input[itr+2];
    if (*c == '\0' || *c == '\n') return 0;
    unsigned short b = *(unsigned short*)(c);
    if ((b >> 8) == 0x0 || (b >> 8) == 0xA) return 0;

    do {
        if (a == b) {
            return 1;
        }
        b = *(unsigned short*)(c++);
    } while ((b >> 8) != 0x0 && (b >> 8) != 0xA);

    return 0;

}

/*
 * Realizing the error of his ways, Santa has switched to a better model of determining whether a string is naughty or nice. None of the old rules apply, as they are all clearly ridiculous.
 * 
 * Now, a nice string is one with all of the following properties:
 * 
 * - It contains a pair of any two letters that appears at least twice in the string without overlapping, like `xyxy` (`xy`) or `aabcdefgaa` (`aa`), but not like `aaa` (`aa`, but it overlaps).
 * - It contains at least one letter which repeats with exactly one letter between them, like `xyx`, `abcdefeghi` (`efe`), or even `aaa`.
 * For example:
 * 
 * - `qjhvhtzxzqqjkmpb` is nice because is has a pair that appears twice (`qj`) and a letter that repeats with exactly one letter between them (`zxz`).
 * - `xxyxx` is nice because it has a pair that appears twice and a letter that repeats with one between, even though the letters used by each rule overlap.
 * - `uurcxstgmygtbstg` is naughty because it has a pair (tg) but no repeat with a single letter between them.
 * - `ieodomkazucvgmuy` is naughty because it has a repeating letter with one between (odo), but no pair that appears twice.
 * How many strings are nice under these new rules?
*/

int part_two() {
    char c;
    int itr = 0;
    int nice = 0;
    meta_word word = {};
    do {
        c = input[itr]; // Read

        word.duplicates += (word.last_char == c);
        word.bad += word.bad ? 0 : seek_pair(itr); // if a pair has been found, no need to keep seeking

        if(c == '\n' || c == '\0') {
            nice += ((word.duplicates >= 1) && (word.bad >= 1));
            word = (meta_word) {};
        }
        if (itr-1 < 0 || input[itr-1] == '\n') word.last_char = '\0';
        else word.last_char = input[itr-1];
        itr++;
    } while (c != '\0');
    return nice;
}

int main() {
    printf("There are %d nice strings.\n", part_one());
    printf("There are %d nice strings under the new rules.\n", part_two());
}
