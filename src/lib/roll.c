#include "roll.h"
// Well this seems to defeat the purpose of the include path... why can't find the header file shorthand...
#include "../include/dice_stats.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Public

short* roll_dice(short numDice) {
    // Confirm rolling 1-6 dice
    if (numDice <= 0 || numDice > 6) {
        printf("INAVLID NUMBER OF DICE!!!\n");
        return NULL;
    }
    short randRoll, i;
    // TODO: should probably be passing the dice var by ref instead of allocating new here
    // As the other makes sense to maintain for entirety of the program but this is pretty much temp
    short *rolls = (short*)malloc(MAX_DICE * sizeof(short));
    // Roll number of dice left
    for (i = 0; i < numDice; i++) {
        // printf("Rolling dice %d of %d\n", i+1, numDice);
        // Generate num between min and max rolls
        randRoll = (rand() % (MAX_ROLL - MIN_ROLL + 1)) + MIN_ROLL;
        // printf("Rolled a %d\n", randRoll);
        // TODO: append roll to a list
        rolls[i] = randRoll; 
    }
    return rolls;
}