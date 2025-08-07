// ====================================================================
//  $File: main.c $
//  $Date: 07-08-2025 @ 09-46-31 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <md5.h>
#include <stdio.h>

const char input[] = "wtnhxymk";

typedef unsigned char       uint8;
typedef unsigned int        uint32;
typedef unsigned long long  uint64;

typedef uint8               byte;


void part_one(char* out, int sz) {
    char buf[32] = {};
    byte digest[16];
    MD5_CTX ctx;

    uint64 itr = 0;

    int ptr = 0;

    while (ptr < 8) {
        snprintf(buf, sizeof(buf), "%s%llu", input, itr);
        MD5Init(&ctx);
        uint32 size = 0;
        for (char*c = buf; *c; c++) size++;
        MD5Update(&ctx, buf, size);
        MD5Final(digest, &ctx);
        if (digest[0] == 0 && digest[1] == 0 && (digest[2] & 0xF0) == 0) {
            digest[2] += digest[2] < 9 ? '0' : 'a' - 10;
            out[ptr++] = digest[2];
        };
        itr++;
    }
}

void part_two(char* out, int sz) {
    char buf[32] = {};
    byte digest[16];
    MD5_CTX ctx;

    uint64 itr = 0;

    int count = 0;

    while (count < 8) {
        snprintf(buf, sizeof(buf), "%s%llu", input, itr);
        itr++;
        MD5Init(&ctx);
        uint32 size = 0;
        for (char*c = buf; *c; c++) size++;
        MD5Update(&ctx, buf, size);
        MD5Final(digest, &ctx);
        if (digest[0] == 0 && digest[1] == 0 && (digest[2] & 0xF0) == 0) {
            int pos = digest[2];
            if (pos >= 8 || out[pos]) continue;
            char val = (digest[3] & 0xF0) >> 4;
            val += val < 9 ? '0' : 'a' - 10;
            out[pos] = val;
            count++;
        };
    }
}

int main() {
    char p1_buf[128] = {};
    char p2_buf[128] = {};
    part_one(p1_buf, 128);
    part_two(p2_buf, 128);
    printf("The password is: %s\n", p1_buf);
    printf("The new password is: %s\n", p2_buf);
}
