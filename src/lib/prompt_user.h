#ifndef PROMPT_USER_H
#define PROMPT_USER_H
#include <stdbool.h>

// Check validity of user input matching the available dice from last roll
// Just trying out here, technically was going to keep private so shouldn't need here
// But the scope of the valid bool flag is broken and auto resetting per loop iteration... (defined before loop)
// bool valid_input(char* input, short* available, short len);

short remove_dice(char* selection, short* available);

// Prompt user to enter the dice numbers they want to keep
char* select_dice(short* available);

bool yes_no();

#endif