#include "prompt_user.h"
// Well this seems to defeat the purpose of the include path... why can't find the header file shorthand...
#include "../include/dice_stats.h"
#include "util.h"
// #include <stdbool.h> # Currently in header
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Private 
// TODO: probably will move scoring and input validity checks into own classes
bool valid_input(char* input, short* available, short len) {
    bool valid = false; // TODO: why is the scope of this var not working... just keeps getting reset back to false per iteration
    short i;
    for (i = 0; i < len; i++) {
        // printf("Validity check scanning for: %d, current validity flag: %d\n", available[i], valid);
        char numStr[1];
        sprintf(numStr, "%d", available[i]);
        // printf("Number as str: %s\n", numStr);
        char *match;
        match = strstr(input, numStr);
        // TODO: also need to check for if input 3 1's, have at least 3 1's available...
        if (match != NULL) {
            // printf("Substring found at position: %ld\n", match - input);
            valid = true; // TODO: this value is not holding, even for the following iteration
            // well... after not initializing bool valid = false, it SOMETIMES holds...
            // jk has nothing to do with whether or not init to false, just needs to match the final die...
            // ah... now it only holds if it matches on the final iteration (last die needs to match input)
            // printf("Set valid flag to true: %d\n", valid);
            // Technically don't really want this break...
            // but for some reason our validity flag is resetting without it
            break;
        }
        // printf("Current value of valid flag: %d\n", valid);
    }
    // printf("WHY IS MY VALID BOOL NOT UPDATING? OR THIS CONDITION NOT WORKING... %d\n", valid);
    if (!valid) {
        printf("Input does not match any available numbers!\n");
    }
    return valid;
}

// Modifies both params, removing selections from available
short remove_dice(char* selection, short* available) {
    bool success = false;
    short numLeft = 0;
    char* selCpy = (char*)malloc(strlen(selection) + 1);
    strcpy(selCpy, selection);
    char *token = strtok(selCpy, " ");
    while (token != NULL) {
        // printf("split string token: %s\n", token);
        short i = 0;
        // TODO: validation check...
        short removeNum = atoi(token);
        while (removeNum != available[i] && i < 6) {
            // printf("Remove number: %d doesn't match %d for index %d\n", removeNum, available[i], i);
            i++;
        }
        // printf("Maybe time to replace available num %d at index %d\n", available[i], i);
        available[i] = 0;
        token = strtok(NULL, " ");
    }

    short i;
    for (i = 0; i < 6; i++) {
        if (available[i] > 0 && available[i] <= 6) {
            printf("Incrementing number of dice left for [%d]\n", available[i]);
            numLeft++;
        }
    }
    return numLeft;
}

// Public

char* select_dice(short* available) {
    // Input the dice numbers you want to keep from the available dice
    bool isEmpty = true;
    short length = 0;
    short i = 0;
    while (available[i] > 0 && available[i] <= 6 && i < 6) {
        // printf("DICE IS VALID: %d\n", available[i]);
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
    // Now copy the input to a safe to return string
    char *inputStr = (char*)malloc(strlen(input) + 1);
    if (inputStr == NULL) {
        perror("Failed to allocate memory for the input string!\n");
        return NULL; // TODO: need to handle...
    }
    strcpy(inputStr, input);
    return inputStr;
}

bool yes_no() {
    char input[10]; // Little extra mem space to be safer from a-holes
    printf("Please enter Y/N: ");
    scanf("%s", input);
    to_uppercase(input);
    while (!strcmp("Y\n", input) && !strcmp("N\n", input) && !strcmp("YES\n", input) && !strcmp("NO\n", input)) {
        printf("Invalid YES/NO input! Try again...\n");
        printf("Previous input: %s", input);
        scanf("%s", input);
        to_uppercase(input);
    }
    if (strcmp("Y\n", input) || strcmp("YES\n", input)) {
        return true;
    }
    return false;
}