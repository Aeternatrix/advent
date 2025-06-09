// ====================================================================
//  $File: main.c $
//  $Date: 09-06-2025 @ 17-29-25 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include <md5.h>

const char input[] = "iwrupvqb";

/*
 * Santa needs help mining some AdventCoins (very similar to bitcoins) to use as gifts for all the economically forward-thinking little girls and boys.
 * 
 * To do this, he needs to find MD5 hashes which, in hexadecimal, start with at least five zeroes. The input to the MD5 hash is some secret key (your puzzle input, given below) followed by a number in decimal. To mine AdventCoins, you must find Santa the lowest positive number (no leading zeroes: `1`, `2`, `3`, ...) that produces such a hash.
 * 
 * For example:
 * 
 * - If your secret key is `abcdef, the answer is `609043`, because the MD5 hash of `abcdef609043` starts with five zeroes (`000001dbbfa...`), and it is the lowest such number to do so.
 * - If your secret key is `pqrstuv`, the lowest number it combines with to make an MD5 hash starting with five zeroes is `1048970`; that is, the MD5 hash of `pqrstuv1048970` looks like `000006136ef...`.
 */
int part_one() {
    char buf[32] = {};
    unsigned char digest[16];
    MD5_CTX ctx;

    unsigned long long itr = 0;

    for (;;itr++) {
        snprintf(buf, sizeof(buf), "%s%llu", input, itr);

        MD5Init(&ctx);
        unsigned int size = 0;
        char c = buf[0];
        for (;c != '\0';size++) {
            c = buf[size];
        }
        MD5Update(&ctx, buf, --size);


        MD5Final(digest, &ctx);

        if (digest[0] == 0 && digest[1] == 0 && (digest[2] & 0xF0) == 0) break;
    }
    return itr;
}

/*
 * Now find one that starts with 6 zeroes
 */
int part_two() {
    char buf[32] = {};
    unsigned char digest[16];
    MD5_CTX ctx;

    unsigned long long itr = 0;

    for (;;itr++) {
        snprintf(buf, sizeof(buf), "%s%llu", input, itr);

        MD5Init(&ctx);
        unsigned int size = 0;
        char c = buf[0];
        for (;c != '\0';size++) {
            c = buf[size];
        }
        MD5Update(&ctx, buf, --size);


        MD5Final(digest, &ctx);

        if (digest[0] == 0 && digest[1] == 0 && digest[2] == 0) break;
    }
    return itr;
}

typedef struct {
    int part_one;
    int part_two;
} answer;

/*
 * The only difference between the two parts is when you stop searching; so, you can do both at the same time (to save time; and resources)
 */
answer
together() {
    answer ans = {};
    char buf[32] = {};
    unsigned char digest[16];
    MD5_CTX ctx;

    unsigned long long itr = 0;

    for (;;itr++) {
        snprintf(buf, sizeof(buf), "%s%llu", input, itr);

        MD5Init(&ctx);
        unsigned int size = 0;
        char c = buf[0];
        for (;c != '\0';size++) {
            c = buf[size];
        }
        MD5Update(&ctx, buf, --size);

        MD5Final(digest, &ctx);

        if (!ans.part_one && digest[0] == 0 && digest[1] == 0 && (digest[2] & 0xF0) == 0) ans.part_one = itr;
        if (!ans.part_two && digest[0] == 0 && digest[1] == 0 && digest[2] == 0) ans.part_two = itr;
        if (ans.part_one && ans.part_two) break;
    }
    return ans;
}

int main() {
    answer ans = together();
    printf("The lowest positive number following %s to give a md5 hash with 5 leading zeroes is {%d}.\n", input, ans.part_one);
    printf("The lowest positive number following %s to give a md5 hash with 6 leading zeroes is {%d}.\n", input, ans.part_two);
}
