// ====================================================================
//  $File: main.c $
//  $Date: 08-07-2025 @ 09-40-52 $
//  $Revision: 0.0.0 $
//  $Creator: aeternatrix $
//  $Notice: (C) Copyright 2025 by aeternatrix. All Rights Reserved. $
// ===================================================================

#include <stdio.h>
#include "input.h"

typedef union { int E[10]; struct { int children, cats, samoyeds, pomeranians, akitas, vizslas, goldfish, trees, cars, perfumes; }; }
aunt;
aunt aunts[500] = {};

void read_input();
/*
 * Your Aunt Sue has given you a wonderful gift, and you'd like to send her a thank you card. However, there's a small problem: she signed it "From, Aunt Sue".
 * 
 * You have 500 Aunts named "Sue".
 * 
 * So, to avoid sending the card to the wrong person, you need to figure out which Aunt Sue (which you conveniently number 1 to 500, for sanity) gave you the gift. You open the present and, as luck would have it, good ol' Aunt Sue got you a My First Crime Scene Analysis Machine! Just what you wanted. Or needed, as the case may be.
 * 
 * The My First Crime Scene Analysis Machine (MFCSAM for short) can detect a few specific compounds in a given sample, as well as how many distinct kinds of those compounds there are. According to the instructions, these are what the MFCSAM can detect:
 * 
 * - `children`, by human DNA age analysis.
 * - `cats`. It doesn't differentiate individual breeds.
 * - Several seemingly random breeds of dog: `samoyeds`, `pomeranians`, `akitas`, and `vizslas`.
 * - `goldfish`. No other kinds of fish.
 * - `trees`, all in one group.
 * - `cars`, presumably by exhaust or gasoline or something.
 * - `perfumes`, which is handy, since many of your Aunts Sue wear a few kinds.
 * In fact, many of your Aunts Sue have many of these. You put the wrapping from the gift into the MFCSAM. It beeps inquisitively at you a few times and then prints out a message on ticker tape:
 * 
 * - children: 3
 * - cats: 7
 * - samoyeds: 2
 * - pomeranians: 3
 * - akitas: 0
 * - vizslas: 0
 * - goldfish: 5
 * - trees: 3
 * - cars: 2
 * - perfumes: 1
 * You make a list of the things you can remember about each Aunt Sue. Things missing from your list aren't zero - you simply don't remember the value.
 * 
 * What is the number of the Sue that got you the gift?
 */
int part_one() {
    aunt target = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };
    for (int a = 0; a < 500; a++) {
        aunt c = aunts[a];
        int valid = 0;
        for (int i=0; i < 10; i++) {
            if (c.E[i] == -1) continue;
            if (c.E[i] != target.E[i]) {
                valid = 0;
                break;
            }
            valid = 1;
        }
        if (valid) return a+1;
    }
    return -1; // Not Found
}

/*
 * As you're about to send the thank you note, something in the MFCSAM's instructions catches your eye. Apparently, it has an outdated retroencabulator, and so the output from the machine isn't exact values - some of them indicate ranges.
 * 
 * In particular, the `cats` and `trees` readings indicates that there are greater than that many (due to the unpredictable nuclear decay of cat dander and tree pollen), while the `pomeranians` and `goldfish` readings indicate that there are fewer than that many (due to the modial interaction of magnetoreluctance).
 * 
 * What is the number of the real Aunt Sue?
 */
int part_two() {
    aunt target = { 3, 7, 2, 3, 0, 0, 5, 3, 2, 1 };
    for (int a = 0; a < 500; a++) {
        aunt c = aunts[a];
        if (
                   (c.children != -1 ? c.children == target.children : 1)
                && (c.cats != -1 ? c.cats > target.cats : 1)
                && (c.samoyeds != -1 ? c.samoyeds == target.samoyeds : 1)
                && (c.pomeranians != -1 ? c.pomeranians < target.pomeranians : 1)
                && (c.akitas != -1 ? c.akitas == target.akitas : 1)
                && (c.vizslas != -1 ? c.vizslas == target.vizslas : 1)
                && (c.goldfish != -1 ? c.goldfish < target.goldfish : 1)
                && (c.trees != -1 ? c.trees > target.trees : 1)
                && (c.cars != -1 ? c.cars == target.cars : 1)
                && (c.perfumes != -1 ? c.perfumes == target.perfumes : 1)
            )
            return a+1;
    }
    return -1; // Not Found
}

int main() {
    read_input();
    printf("The Aunt Sue that got the gift is Number %d.\n", part_one());
    printf("The *real* Aunt Sue that got the gift is Number %d.\n", part_two());
}

const char idstr[] = "childrencatssamoyedspomeraniansakitasvizslasgoldfishtreescarsperfumes";
typedef struct { const char* start, *end; } id_;
id_ ids[10] = {
    {&idstr[ 0], &idstr[ 8]},
    {&idstr[ 8], &idstr[12]},
    {&idstr[12], &idstr[20]},
    {&idstr[20], &idstr[31]},
    {&idstr[31], &idstr[37]},
    {&idstr[37], &idstr[44]},
    {&idstr[44], &idstr[52]},
    {&idstr[52], &idstr[57]},
    {&idstr[57], &idstr[61]},
    {&idstr[61], &idstr[69]},
};

int m_strcmp(const char* a, int alen, const char* b, int blen) {
    if (alen != blen) return 0;
    for (int itr=0;itr<alen;itr++) if (a[itr] != b[itr]) return 0;
    return 1;
}

int get_id(id_ id) {
    int i;
    for (i = 0; i < 10; i++) {
        int alen = id.end - id.start;
        int blen = ids[i].end - ids[i].start;
        if (m_strcmp(id.start, alen, ids[i].start, blen)) return i;
    }
    return 0;
}

void read_input(){
    const char* c = input;
    id_ str;
    int rec_str = 0;
    int rec = 0;
    int itr = 0;
    int cwid = 0;
    int skip = 1;
    aunt at = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
    while(*c) {
        if (!rec_str) {
            switch (*c) {
                case 'c': 
                case 's': 
                case 'p': 
                case 'a': 
                case 'v': 
                case 'g': 
                case 't': 
                    rec_str = 1;
                    str.start = c;
                    break;
            }
        }
        if (rec_str && (*c == ':' || *c == '\n' || *c == '\0')) {
            str.end = c;
            cwid = get_id(str);
            str = (id_){};
            rec_str = 0;
        }
        if (skip && *c == ':') skip = 0;

        if (!skip && c[0] <= '9' && c[0] >= '0') {
            if (at.E[cwid] == -1) at.E[cwid] = 0;
            at.E[cwid] = at.E[cwid] * 10 + c[0] - '0';
            rec = 1;
        }


        if (c[0] == '\n' || c[0] == '\0') {

            aunts[itr++] = at;

            at = (aunt) { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
            skip = 1;
        }
        c++;
    }
}
