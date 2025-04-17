#include "util.h"
// Well this seems to defeat the purpose of the include path... why can't find the header file shorthand...
#include "../include/dice_stats.h"
#include <stdio.h>
#include <stdlib.h>

// PRIVATE

// Add a new unique element to set (mimic set behavior)
void add_to_set(short set[], short *setSize, short num) {
    // Don't allow zero
    if (num == 0) {
        return;
    }
    for (int i = 0; i < *setSize; i++) {
        if (set[i] == num) {
            // Set already contains num so don't add
            return;
        }
    }
    // printf("Adding %d to set\n", num);
    set[*setSize] = num;
    (*setSize)++;
    // printf("New set size: %d\n", *setSize);
}

// PUBLIC

void print_dice(short* dice) {
    printf("Current dice on board: ");
    short maxLen = 6;
    short i;
    for (i = 0; i < maxLen; i++) {
        if (dice[i] > 0 && dice[i] <= 6) {
            printf("[%d] ", dice[i]);
        }
    }
    printf("\n");
}

void reset_dice(short* dice) {
    printf("Resetting all dice to zero (cleared the board)!\n");
    for (short i = 0; i < MAX_DICE; i++) {
        dice[i] = 0;
    }
}

short get_num_dice_left(short* dice) {
    short numDice = 0;
    for (short i = 0; i < MAX_DICE; i++) {
        if (dice[i] > 0 && dice[i] <= 6) {
            // VALID DIE
            numDice++;
        }
    }
    return numDice;
}

// Get the most common value
short get_mode(short* nums) {
    // assume working with length 6
    // and don't count zeroes
    short maxCount = 0;
    short mostCommon = nums[0];
    for (short i = 0; i < MAX_DICE; i++) {
        if (nums[i] != 0) {
            short count = 0;
            for (short j = 0; j < MAX_DICE; j++) {
                if (nums[i] == nums[j]) {
                    count++;
                }
            }
            if (count > maxCount) {
                maxCount = count;
                mostCommon = nums[i];
            }
        }
    }
    return mostCommon;
}

// How many times does the most frequent number occur
short get_mode_frequency(short* nums) {
    // assume working with length 6
    short freq = 0;
    short mode = get_mode(nums);
    for (short i = 0; i < MAX_DICE; i++) {
        if (nums[i] == mode) {
            freq++;
        }
    }
    return freq;
}

// Convert int array to "set"
void to_set(short nums[], short set[], short *setSize) {
    *setSize = 0;
    short i;
    for (i = 0; i < MAX_DICE; i++) {
        add_to_set(set, setSize, nums[i]);
    }
    // For debug output
    // printf("Set nums: ");
    // for (i = 0; i < *setSize; i++) {
    //     printf("%d ", set[i]);
    // }
    // printf("\n");
}

char* to_uppercase(char* str) {
    if (str == NULL) {
        return NULL;
    }
    for (short i = 0; str[i] != '\0'; i++) {
        str[i] = toupper(str[i]);
    }
    return str;
}