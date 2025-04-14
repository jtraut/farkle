#include "prompt_user.h"
// Well this seems to defeat the purpose of the include path... why can't find the header file shorthand...
#include "../include/dice_stats.h"
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private 
// TODO: probably will move scoring and input validity checks into own classes
bool valid_input(char* input, short* available, short len) {
    bool valid = false; // TODO: why is the scope of this var not working... just keeps getting reset back to false per iteration
    short i;
    for (i = 0; i < len; i++) {
        printf("Validity check scanning for: %d, current validity flag: %d\n", available[i], valid);
        char numStr[1];
        sprintf(numStr, "%d", available[i]);
        printf("Number as str: %s\n", numStr);
        char *match;
        match = strstr(input, numStr);
        // TODO: also need to check for if input 3 1's, have at least 3 1's available...
        if (match != NULL) {
            printf("Substring found at position: %ld\n", match - input);
            valid = true; // TODO: this value is not holding, even for the following iteration
            // well... after not initializing bool valid = false, it SOMETIMES holds...
            // jk has nothing to do with whether or not init to false, just needs to match the final die...
            // ah... now it only holds if it matches on the final iteration (last die needs to match input)
            printf("Set valid flag to true: %d\n", valid);
            // Technically don't really want this break...
            // but for some reason our validity flag is resetting without it
            break;
        }
        printf("Current value of valid flag: %d\n", valid);
    }
    printf("WHY IS MY VALID BOOL NOT UPDATING? OR THIS CONDITION NOT WORKING... %d\n", valid);
    // TODO: after not implicitly initializing to false (bool valid = false;)
    // this works better, but still occassionally resets back to 0... what the hell
    // EXAMPLE OF BUG... (DONT MIND THE LACK OF TAKING ALL DICE ENTERED, THAT REMAINS UNIMPLEMENTED)
    // Roll result: [6] [6] [6] [6]
    // DICE IS VALID: 6
    // DICE IS VALID: 6
    // DICE IS VALID: 6
    // DICE IS VALID: 6
    // HAVE 4 AVAILABLE DICE
    // Please enter the number(s) of the dice you want to keep for this roll, separated by space.
    // 6 6 6 6
    // Player entered: 6 6 6 6

    // Validity check scanning for: 6
    // Number as str: 6
    // Substring found at position: 0
    // Set valid flag to true: 1
    // Current value of valid flag: 1
    // Validity check scanning for: 6
    // Number as str: 6
    // Substring found at position: 0
    // Set valid flag to true: 1
    // Current value of valid flag: 1
    // Validity check scanning for: 6
    // Number as str: 6
    // Substring found at position: 0
    // Set valid flag to true: 1
    // Current value of valid flag: 1
    // Validity check scanning for: 6
    // Number as str: 6
    // Substring found at position: 0
    // Set valid flag to true: 1
    // Current value of valid flag: 1
    // WHY IS MY VALID BOOL NOT UPDATING? OR THIS CONDITION NOT WORKING... 1
    // Roll result: [1] [2] [3]
    // DICE IS VALID: 1
    // DICE IS VALID: 2
    // DICE IS VALID: 3
    // HAVE 3 AVAILABLE DICE
    // Please enter the number(s) of the dice you want to keep for this roll, separated by space.
    // 1
    // Player entered: 1

    // Validity check scanning for: 1
    // Number as str: 1
    // Substring found at position: 0
    // Set valid flag to true: 1
    // Current value of valid flag: 1
    // Validity check scanning for: 2
    // Number as str: 2
    // Current value of valid flag: 0
    // Validity check scanning for: 3
    // Number as str: 3
    // Current value of valid flag: 0


    // WHY IS MY VALID BOOL NOT UPDATING? OR THIS CONDITION NOT WORKING... 0
    // Input does not match any available numbers!

    if (!valid) {
        printf("Input does not match any available numbers!\n");
    }
    return valid;
}

// Public

char* select_dice(short* available) {
    // Input the dice numbers you want to keep from the available dice
    bool isEmpty = true;
    short length = 0;
    short i = 0;
    while (available[i] > 0 && available[i] <= 6 && i < 6) {
        // TODO: this is broken... bad example output:
        // Roll result: [2] [1] [1] [6] [6]
        // DICE IS VALID: 2
        // DICE IS VALID: 1
        // DICE IS VALID: 1
        // DICE IS VALID: 6
        // DICE IS VALID: 6
        // DICE IS VALID: 29554
        // HAVE 6 AVAILABLE DICE
        printf("DICE IS VALID: %d\n", available[i]);
        i++;
    }
    if (i > 0) {
        printf("HAVE %d AVAILABLE DICE\n", i);
        length = i;
        isEmpty = false;
    }
    if (isEmpty) {
        printf("INAVLID DICE LIST\n");
        return NULL;
    }
    char input[20];
    printf("Please enter the number(s) of the dice you want to keep for this roll, separated by space.\n");
    fgets(input, sizeof(input), stdin); // support spaces (as opposed to scanf)
    printf("Player entered: %s\n", input);
    while (!valid_input(input, available, length)) {
        printf("Inavlid dice selection. Please enter valid input of numbers from available dice.\n");
        fgets(input, sizeof(input), stdin); // support spaces (as opposed to scanf)
        printf("Player entered: %s\n", input);
    }
    return input;
}
