#include "lib/prompt_user.h"
#include "lib/roll.h"
#include "lib/scorekeeper.h"
#include "lib/util.h"
#include <stdio.h>

int main() {
	printf("FARKLE DICE GAME\n");

	// TODO: various classes for...
	// dice, rolling (random num generating), directions, scorekeeping, players

	short i;
	short maxDice = 6;
	short* dice = (short*)malloc(maxDice * sizeof(short));
	short numDiceLeft = maxDice;
	short currentTurnPoints = 0;
	while (numDiceLeft > 0) {
		// TODO: should dice just be passed by ref?
		dice = roll_dice(numDiceLeft);
		print_dice(dice);
		// TODO: think need to pass numDiceLeft by reference to auto_score as well
		// to handle various cases of auto scoring points but still having dice leftover 
		short points = auto_score(dice);
		currentTurnPoints += points;
		if (points > 0) {
			printf("Your roll scored %d points.\n", points);
			numDiceLeft = get_num_dice_left(dice);
			if (numDiceLeft == 0) {
				printf("Would you like to keep rolling with a hot-hand (6 dice) OR stop now and take your current turn points %d\n", currentTurnPoints);
				// TODO: prompt a Y/N input (will define in prompt_user)
				// Right now just assume hot hand I guess
				numDiceLeft = 6;				
			}
		} else {
			char* selection = select_dice(dice);
			points = score_selection(selection);
			currentTurnPoints += points;
			numDiceLeft = remove_dice(selection, dice);
		}
		printf("************************************************\n");
		printf("Current turn total points: %d with %d dice left\n", currentTurnPoints, numDiceLeft);
	}

	return 0;
}
