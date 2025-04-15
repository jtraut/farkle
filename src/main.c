#include "include/dice_stats.h"
#include "lib/prompt_user.h"
#include "lib/roll.h"
#include "lib/scorekeeper.h"
#include "lib/util.h"
#include <stdbool.h>
#include <stdio.h>
// #include <unistd.h>

int main() {
	printf("FARKLE DICE GAME\n");

	// TODO: Support multiple players, add more game instructions, and maintain a leaderboard

	short turnCount = 0;
	short totalPoints = 0; // eventually will be an array per player
	while (totalPoints < MIN_TO_WIN) {
		short* dice = (short*)malloc(MAX_DICE * sizeof(short));
		short numDiceLeft = MAX_DICE;
		short currentTurnPoints = 0;
		bool endTurn = false;
		while (!endTurn) {
			srand(time(NULL)); // Once added the double loop, not getting random rolls anymore... only repeating...
			// TODO: should dice just be passed by ref?
			// TODO: somehow it seems when moved dice array creation into the totalPoints while loop, now only get repeated identical rolls
			// short* dice = (short*)malloc(MAX_DICE * sizeof(short));
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
				} else if (numDiceLeft <= 3) {
					// For now will just stick to mostly automated play lol
					endTurn = true;
				}
			} else {
				// TODO: need to modify some things about how handle auto scoring
				// right now probably will never hit this because auto score will just take whatever it can get
				// char* selection = select_dice(dice);
				// points = score_selection(selection);
				// currentTurnPoints += points;
				// numDiceLeft = remove_dice(selection, dice);

				// Thus, in the mean time, this pretty much only implies the player farkled
				numDiceLeft = 0;
				currentTurnPoints = 0; // :(
			}
			printf("************************************************\n");
			if (numDiceLeft > 0) {
				printf("Current turn %d total points: %d with %d dice left\n", turnCount, currentTurnPoints, numDiceLeft);
				// TODO: could be a good time to prompt user if they want to keep rolling
			} else if (currentTurnPoints == 0) {
				printf("Oof, turn ended in a Farkle...\n");
				endTurn = true;
			}
			if (endTurn) {
				// TODO: print leaderboard method
				totalPoints += currentTurnPoints;
				printf("Current overall total points: %d\n", totalPoints);
			}
			// sleep(1); // TODO: really just trying to figure out why RNG stopped working... just getting repeat rolls now
			// Something similar happened last time was using bools in a loop, so what the hell try removing that
		}
		turnCount++;
	}

	printf("Congrats player X won with %d points in %d turns", totalPoints, turnCount);

	return 0;
}
