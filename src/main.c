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
	short* result = (short*)malloc(maxDice * sizeof(short));
	short numDiceLeft = maxDice;
	short currentTurnPoints = 0;
	while (numDiceLeft > 0) {
		result = roll_dice(numDiceLeft);
		print_dice(result);
		short points = auto_score(result);
		currentTurnPoints += points;
		if (points > 0) {
			printf("Congrats on the scoring hand worth %d points.\n", points);
			printf("Would you like to keep rolling with a hot-hand (6 dice) OR stop now and take your current turn points %d\n", currentTurnPoints);
			// TODO: prompt a Y/N input (will define in prompt_user)
			// Right now just assume hot hand I guess
			numDiceLeft = 6;
		} else {
			char* selection = select_dice(result);
			points = score_selection(selection);
			currentTurnPoints += points;
			numDiceLeft = remove_dice(selection, result);
			printf("Number of dice left: %d\n", numDiceLeft);
		}
		printf("Current turn total points: %d\n", currentTurnPoints);
	}

	return 0;
}
