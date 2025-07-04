// ====================================================================
//  $File: main.c $
//  $Date: 04-07-2025 @ 11-47-56 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

// I was prepared to write stuff™ for if the number of characters expanded
// (like, z → aa); but the answers did not require this

#include <stdio.h>

#define PAGE 4096

const char input[] = "vzbxkghb";

int scan_abc(char* buf) {
    if (!buf[0] || !buf[1] || !buf[2]) return 0;
    return buf[0] - 1 == buf[1] && buf[1] - 1 == buf[2];
}

int scan_aa(char* buf) {
    if (!buf[0] || !buf[1]) return 0;
    return buf[0] == buf[1];
}

void increment(char* c) {
    if (!*c) return;
    *c = *c + 1;
    if (*c == 'i' || *c == 'o' || *c == 'l') *c = *c+1;
    if ((*c) > 'z') {
        increment(c+1);
        *c = 'a';
    }
}

#define ABC 0b01
#define DUP 0b10

/*
 * Santa's previous password expired, and he needs help choosing a new one.
 * 
 * To help him remember his new password after the old one expires, Santa has devised a method of coming up with a password based on the previous one. Corporate policy dictates that passwords must be exactly eight lowercase letters (for security reasons), so he finds his new password by incrementing his old password string repeatedly until it is valid.
 * 
 * Incrementing is just like counting with numbers: `xx`, `xy`, `xz`, `ya`, `yb`, and so on. Increase the rightmost letter one step; if it was `z`, it wraps around to `a`, and repeat with the next letter to the left until one doesn't wrap around.
 * 
 * Unfortunately for Santa, a new Security-Elf recently started, and he has imposed some additional password requirements:
 * 
 * - Passwords must include one increasing straight of at least three letters, like `abc`, `bcd`, `cde`, and so on, up to `xyz`. They cannot skip letters; `abd` doesn't count.
 * - Passwords may not contain the letters `i`, `o`, or `l`, as these letters can be mistaken for other characters and are therefore confusing.
 * - Passwords must contain at least two different, non-overlapping pairs of letters, like `aa`, `bb`, or `zz`.
 * For example:
 * 
 * - `hijklmmn` meets the first requirement (because it contains the straight `hij`) but fails the second requirement requirement (because it contains `i` and `l`).
 * - `abbceffg` meets the third requirement (because it repeats `bb` and `ff`) but fails the first requirement.
 * - `abbcegjk` fails the third requirement, because it only has one double letter (`bb`).
 * - The next password after `abcdefgh` is `abcdffaa`.
 * - The next password after `ghijklmn` is `ghjaabcc`, because you eventually skip all the passwords that start with `ghi`..., since `i` is not allowed.
 * Given Santa's current password (your puzzle input), what should his next password be?
 */
int part_one(char* buf, int size) {
    int sz = sizeof(input);
    for (int i = 0; i < sz; i++) {
        buf[(size-1)-i] = input[i];
    }
    int ptr = size-(sz-1);
    int valid = 0;

    char* c = &buf[ptr];
    char dup = '\0';
    while(!valid) {
        for (int i=0; i<sz; i++) {
            if (scan_abc(&buf[ptr+i])) {
                valid |= ABC;
            }
            if (scan_aa(&buf[ptr+i])) {
                if (dup && dup != '\0' && buf[ptr+i] != dup) {
                    valid |= DUP;
                } else {
                    dup = buf[ptr+i];
                }
            }
            if ((valid & (ABC | DUP)) == (ABC | DUP)) {
                break;
            }
        }
        if ((valid & (ABC | DUP)) == (ABC | DUP)) break;
        increment(&buf[ptr]);

        valid = 0;
        dup = 0;
    }

    for (int i=0;i<sz;i++){
        buf[i] = buf[(size-1)-i];
    }
    return sz;
}

// Santa's password expired again. What's the next one?
void part_two(char* buf, int buf_size, char* in, int in_size) {
    int sz = in_size;
    for (int i = 0; i < sz; i++) {
        buf[(buf_size-1)-i] = in[i];
    }
    int ptr = buf_size-(sz-1);
    int valid = 0;

    char* c = &buf[ptr];
    char dup = '\0';
    increment(&buf[ptr]);
    while(!valid) {
        for (int i=0; i<sz; i++) {
            if (scan_abc(&buf[ptr+i])) {
                valid |= ABC;
            }
            if (scan_aa(&buf[ptr+i])) {
                if (dup && dup != '\0' && buf[ptr+i] != dup) {
                    valid |= DUP;
                } else {
                    dup = buf[ptr+i];
                }
            }
            if ((valid & (ABC | DUP)) == (ABC | DUP)) {
                break;
            }
        }
        if ((valid & (ABC | DUP)) == (ABC | DUP)) break;
        increment(&buf[ptr]);

        valid = 0;
        dup = 0;
    }

    for (int i=0;i<sz;i++){
        buf[i] = buf[(buf_size-1)-i];
    }
}

int main() {
    char b1[PAGE] = {};
    char b2[PAGE] = {};
    int sz = part_one(b1, PAGE);
    part_two(b2, PAGE, b1, sz);
    printf("Santa's new password should be: %s\n", b1);
    printf("Santa's new password should be: %s\n", b2);
}
