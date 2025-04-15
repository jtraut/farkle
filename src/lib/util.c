#include "util.h"
// Well this seems to defeat the purpose of the include path... why can't find the header file shorthand...
#include "../include/dice_stats.h"
#include <stdio.h>
#include <stdlib.h>

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

short most_common(short* nums) {
    // Two assumptions, working with length 6 and don't count zeros
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