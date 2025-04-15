#ifndef UTIL_H
#define UTIL_H

void print_dice(short* dice);

void reset_dice(short* dice);

short get_num_dice_left(short* dice);

short get_mode(short* nums);

short get_mode_frequency(short* nums);

void to_set(short nums[], short set[], short *setSize);

#endif