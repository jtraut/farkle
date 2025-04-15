#include "scorekeeper.h"
// Well this seems to defeat the purpose of the include path... why can't find the header file shorthand...
#include "../include/dice_stats.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

/*
    FARKLE SCORING SHEET
    500 MINIMUM POINTS TO GET ON THE SCOREBOARD
    
    [5]       = 50      4 OF A KIND       = 1000
    [1]       = 100     5 OF A KIND       = 2000
    [1][1][1] = 300     6 OF A KIND       = 3000
    [2][2][2] = 200     1-6 STRAIGHT      = 1500
    [3][3][3] = 300     3 PAIRS           = 1500
    [4][4][4] = 400     2 TRIPLETS        = 2500
    [5][5][5] = 500     4 OF KIND W/ PAIR = 1500
    [6][6][6] = 600

    10,000 MINIMUM POINTS TO WIN (OTHER PLAYERS GET ONE MORE TURN)
*/

// TODO: probably will define methods for each scoring scenario, i.e. three_of_kind, four_of_kind, etc etc
// and once have every scenario implemented, THEN should impement a is_farkle last using them all to check each scenario first

// Roll any ones or fives?
short stay_alive(short* dice) {
    short points = 0;
    short i;
    for (i = 0; i < MAX_DICE; i++) {
        if (dice[i] == 1) {
            points += ONE;
            // And remove the taken die
            dice[i] = 0;
        } else if (dice[i] == 5) {
            points += FIVE;
            // And remove the taken die
            dice[i] = 0;
        }
    }
    return points;
}

short three_of_kind(short* dice) {
    short points = 0;
    short i;
    // for (i = 0; i < MAX_DICE; i++) {

    // }
    return 0;
}

short six_of_kind(short* dice) {
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    // printf("Resulting set size: %d\n", setSize);
    if (setSize == 1) {
        // Only have 1 value!
        printf("Lucky bastard got a 6 of a kind!\n");
        reset_dice(dice);
        return SIX_KIND;
    }
    return 0;
}

// 3 pairs
short triple_double(short* dice) {
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    short mode = most_common(dice);
    if (setSize == 3 && mode == 2) {
        printf("Way to go, you got a triple double!\n");
        reset_dice(dice);
        return TRIPLE_DOUBLE;
    }
    return 0;
}

// 2 triplets
short double_triplet(short* dice) {
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    short mode = most_common(dice);
    if (setSize == 2 && mode == 3) {
        printf("Congrats on your double triplets!\n");
        reset_dice(dice);
        return DOUBLE_TRIPLET;
    }
    return 0;
}

// 1-6 straight
short straight(short* dice) {
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    if (setSize == 6) {
        printf("Look at you go, straight to winning!\n");
        reset_dice(dice);
        return STRAIGHT;
    }
    return 0;
}

// Pretty self explanatory
short four_kind_with_pair(short* dice) {
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    short mode = most_common(dice);
    if (setSize == 2 && mode == 4) {
        printf("Is it skill or luck? Nice four of a kind plus a pair.\n");
        reset_dice(dice);
        return FOUR_KIND_PAIR;
    }
    return 0;
}

// Auto score for any 6 or full hand dice matches or FARKLES
// TODO: either need to have auto_score keep track of numDiceLeft (pass by ref) or 
// make sure it's always updating the used dice to 0 so main or whatever caller knows how many dice have left after receiving points
short auto_score(short* dice) {
    // First get number of active dice
    short numDice = get_num_dice_left(dice);
    // TODO: OR farkle (after implemented)
    if (numDice == 0) {
        return 0;
    }
    printf("Current number of dice being scored: %d\n", numDice);
    short points = 0;
    // TODO: maybe eventually switch statement on numDice
    // and have methods pre-defined for how to handle each number range differently

    switch (numDice) {
        case 3:
            points = three_of_kind(dice);
            if (points == 0) {
                points = stay_alive(dice);
            }
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            // Could only possibly have one of these 6 dice combos
            // So just try them all without checking the points
            // TODO: Might even break this down more to methods for score_six, score_five, score_four etc.
            points = six_of_kind(dice);
            points += double_triplet(dice);
            points += triple_double(dice);
            points += straight(dice);
            points += four_kind_with_pair(dice);
            
            // TODO: check pretty much everything...
            break;
        default:
            // One or two dice
            printf("Auto scoring for two or less dice left.\n");
            // Technically if rolled two 5's could just take one in hopes of rolling a 1 next, but that would be ill-advised vs. hot hand
            points = stay_alive(dice);
            break;
    }

    // Check for complete matches w/ 3 or more dice
    // if (numDice >= 3) {
    //     printf("Checking for a complete match...\n");
    //     i = 0;
    //     while (dice[i] == 0) {
    //         // Get the first valid die
    //         i++;
    //     }
    //     printf("First valid die at index: %d\n", i);
    //     short j = i + 1;
    //     while ((dice[i] == dice[j] || dice[j] == 0) && j < MAX_DICE) {
    //         j++;
    //     }
    //     if (j == MAX_DICE) {
    //         printf("ALL AVAILABLE DICE MATCH, CONGRATS!\n");
    //         // TODO: still need to determine score
    //         return 1000; // just a temp val cause why not
    //     } else {
    //         printf("First non-matching die at: %d\n", j);
    //     }        
    // }
    
    return points;
}

short score_selection(char* selection) {
    // First check if any of the selection can be auto-scored
    // By first converting the selected dice to int array
    short selectionAsNums[6] = {0, 0, 0, 0, 0, 0};
    // TODO: ahh crap think this is screwing up selection for later usage tho
    char* selCpy = (char*)malloc(strlen(selection) + 1);
    strcpy(selCpy, selection);
    char *token = strtok(selCpy, " ");
    short i = 0;
    while (token != NULL && i < MAX_DICE) {
        // printf("split string token: %s\n", token);
        selectionAsNums[i] = atoi(token);
        token = strtok(NULL, " ");
        i++;
    }
    short points = auto_score(selectionAsNums);
    if (points > 0) {
        // Easy score
        return points;
    }
    // Individually add up or whatev
    for (i = 0; i < MAX_DICE; i++) {
        printf("attempting to score %d at index %d\n", selectionAsNums[i], i);
        switch (selectionAsNums[i]) {
            case 1:
                points += 100;
                selectionAsNums[i] = 0;
                break;
            case 5:
                points += 50;
                selectionAsNums[i] = 0;
                break;
            case 0:
                // Do nothing
                break;
            default:
                // TODO: this isn't covering edge cases
                // For example select [5][5][1][5] from available [5][5][1][5][2][6]
                // Would not be scored as 600 (would get 250 instead)
                printf("Non individual dice selection.\n");
        }
    }
    // After removing the individual scorers, try auto scoring once more...
    points += auto_score(selectionAsNums);
    printf("Selection scored %d points\n", points);
    return points;
}