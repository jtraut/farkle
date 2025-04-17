#ifndef UTIL_H
#define UTIL_H

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

#define TRUE_FALSE(b) ((b) ? "TRUE" : "FALSE")

void print_dice(short* dice);

void reset_dice(short* dice);

short get_num_dice_left(short* dice);

short get_mode(short* nums);

short get_mode_frequency(short* nums);

void to_set(short nums[], short set[], short *setSize);

char* to_uppercase(char* str);

#endif