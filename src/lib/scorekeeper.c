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

// PRIVATE

short six_of_kind(short* dice) {
    if (get_num_dice_left(dice) < 6) {
        return 0;
    }
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
    if (get_num_dice_left(dice) < 6) {
        return 0;
    }
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    short freq = get_mode_frequency(dice);
    if (setSize == 3 && freq == 2) {
        printf("Way to go, you got a triple double!\n");
        reset_dice(dice);
        return TRIPLE_DOUBLE;
    }
    return 0;
}

// 2 triplets
short double_triplet(short* dice) {
    if (get_num_dice_left(dice) < 6) {
        return 0;
    }
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    short freq = get_mode_frequency(dice);
    if (setSize == 2 && freq == 3) {
        printf("Congrats on your double triplets!\n");
        reset_dice(dice);
        return DOUBLE_TRIPLET;
    }
    return 0;
}

// 1-6 straight
short straight(short* dice) {
    if (get_num_dice_left(dice) < 6) {
        return 0;
    }
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
    if (get_num_dice_left(dice) < 6) {
        return 0;
    }
    short set[MAX_DICE]; // allocate for max possible set size
    short setSize = 0;
    to_set(dice, set, &setSize);
    short freq = get_mode_frequency(dice);
    if (setSize == 2 && freq == 4) {
        printf("Is it skill or luck? Nice four of a kind plus a pair.\n");
        reset_dice(dice);
        return FOUR_KIND_PAIR;
    }
    return 0;
}

short five_of_kind(short* dice) {
    if (get_num_dice_left(dice) < 5) {
        return 0;
    }
    short freq = get_mode_frequency(dice);
    if (freq == 5) {
        printf("High five! That's five of a kind.\n");
        short mode = get_mode(dice);
        for (short i = 0; i < MAX_DICE; i++) {
            if (dice[i] == mode) {
                dice[i] = 0;
            }
        }
        return FIVE_KIND;
    }
    return 0;
}

short four_of_kind(short* dice) {
    if (get_num_dice_left(dice) < 4) {
        return 0;
    }
    short freq = get_mode_frequency(dice);
    if (freq == 4) {
        printf("Booyah! That's four of a kind.\n");
        short mode = get_mode(dice);
        for (short i = 0; i < MAX_DICE; i++) {
            if (dice[i] == mode) {
                dice[i] = 0;
            }
        }
        return FOUR_KIND;
    }
    return 0;
}

short three_of_kind(short* dice) {
    if (get_num_dice_left(dice) < 3) {
        return 0;
    }
    short freq = get_mode_frequency(dice);
    if (freq == 3) {
        printf("Nice three of a kind!\n");
        short mode = get_mode(dice);
        for (short i = 0; i < MAX_DICE; i++) {
            if (dice[i] == mode) {
                dice[i] = 0;
            }
        }
        if (mode == 1) {
            return 300;
        }
        // TODO: might want to re-evaluate how auto score if have three 2's
        // because often times better off just taking a 1 or 5 if have any available
        return 100 * mode;
    }
    return 0;
}

// Ones or fives to stay alive!
short ones_or_fives(short* dice) {
    short points = 0;
    for (short i = 0; i < MAX_DICE; i++) {
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

short score_three_dice(short* dice) {
    short points = three_of_kind(dice);
    // TODO: maybe reconsider how want to handle taking the ones and fives
    points += ones_or_fives(dice);
    return points;
}

short score_four_dice(short* dice) {
    short points = four_of_kind(dice);
    points += score_three_dice(dice);
    return points;
}

short score_five_dice(short* dice) {
    short points = five_of_kind(dice);
    points += score_four_dice(dice);
    return points;
}

short score_six_dice(short* dice) {
    short points = six_of_kind(dice);
    points += double_triplet(dice);
    points += triple_double(dice);
    points += straight(dice);
    points += four_kind_with_pair(dice);
    points += score_five_dice(dice);
    return points;
}

// PUBLIC

// Auto score for any 6 or full hand dice matches or FARKLES
// TODO: either need to have auto_score keep track of numDiceLeft (pass by ref) or 
// make sure it's always updating the used dice to 0 so main or whatever caller knows how many dice have left after receiving points
short auto_score(short* dice) {
    // First get number of active dice
    short numDice = get_num_dice_left(dice);
    if (numDice == 0) {
        return 0;
    }
    printf("Current number of dice being scored: %d\n", numDice);
    short points = 0;
    // TODO: maybe eventually switch statement on numDice
    // and have methods pre-defined for how to handle each number range differently

    switch (numDice) {
        case 3:
            points = score_three_dice(dice);
            break;
        case 4:
            points = score_four_dice(dice);
            break;
        case 5:
            points = score_five_dice(dice);
            break;
        case 6:
            points = score_six_dice(dice);
            break;
        default:
            // One or two dice
            printf("Auto scoring for two or less dice left.\n");
            // Technically if rolled two 5's could just take one in hopes of rolling a 1 next, but that would be ill-advised vs. hot hand
            points = ones_or_fives(dice);
            break;
    }
    
    // TODO: in the case of maybe wanting to save some dice like not picking a single 5
    // maybe cancel the auto score if not able to score all remaining dice
    // TODO: also, do need to define a farkle checker or could just suffice right here...
    if (points == 0) {
        printf("Oh no, you Farkled!\n");
    }
    return points;
}

short score_selection(char* selection) {
    // First check if any of the selection can be auto-scored
    // By first converting the selected dice to int array
    short selectionAsNums[MAX_DICE] = {0, 0, 0, 0, 0, 0};
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
    // TODO: now that auto score is pretty flushed out...
    // does this even matter anymore...? might be able to remove everything below, or close to it
    printf("Score selection didn't get points from auto score attempt...");
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