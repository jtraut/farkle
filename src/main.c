#include "include/dice_stats.h"
#include "lib/prompt_user.h"
#include "lib/roll.h"
#include "lib/scorekeeper.h"
#include "lib/util.h"
#include <stdbool.h>
#include <stdio.h>
// #include <unistd.h> // Unix only, but running on Windows so...
#include <windows.h>
#define sleep(x) Sleep(1000 * (x));

int main() {
	printf("FARKLE DICE GAME\n");

	// TODO: Support multiple players, add more game instructions, and maintain a leaderboard

	short turnCount = 1;
	short totalPoints = 0; // eventually will be an array per player
	while (totalPoints < MIN_TO_WIN) {
		printf("\nBeginning turn %d\n", turnCount);
		short* dice = (short*)malloc(MAX_DICE * sizeof(short)); // TODO: probably could just allocate this once outside of loops
		// also do need to free? It should be in use pretty much the entirety of the program lifecycle so maybe not
		short numDiceLeft = MAX_DICE;
		short currentTurnPoints = 0;
		bool endTurn = false;
		while (!endTurn) {
			sleep(2); // Slight delay before rolls for more authentic feel
			// TODO: should dice just be passed by ref?
			dice = roll_dice(numDiceLeft);
			printf("\n");
			print_dice(dice);
			short points = auto_score(dice);
			currentTurnPoints += points;
			if (points > 0) {
				printf("Your roll scored %d points.\n", points);
				numDiceLeft = get_num_dice_left(dice);
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
			if (currentTurnPoints == 0) {
				printf("Oh no, you Farkled!\n\n");
				endTurn = true;
			} else if (numDiceLeft > 0) {
				printf("Current turn %d total points: %d with %d dice left\n", turnCount, currentTurnPoints, numDiceLeft);
				printf("Enter Y if you would like to continue rolling, or N to end turn now and take current points.\n");
				if (totalPoints < 500) {
					printf("Reminder, a minimum of %d points is required to get on the scoreboard!\nAfter which, welcome to take any amount of points.\n", MIN_ON_BOARD);
				}
				endTurn = !yes_no();
			} else {
				// Decide on hot hand or not
				printf("Would you like to keep rolling with a hot-hand (6 dice) OR stop now and take your current turn points %d\n", currentTurnPoints);
				printf("Please enter Y if want to continue rolling with a hot-hand, or N to end turn.\n");
				if (yes_no()) {
					numDiceLeft = 6;
				} else {
					endTurn = true;
				}
			}
			if (endTurn) {
				// TODO: print leaderboard method
				if (totalPoints >= 500 || currentTurnPoints >= 500) {
					totalPoints += currentTurnPoints;
				} else if (currentTurnPoints > 0 && currentTurnPoints < 500) {
					printf("Sorry, not enough points to get on the scoreboard!\n");
				}
				printf("Current overall total points: %d\n", totalPoints);
			}
		}
		turnCount++;
	}

	// Subtract a turn for the final iteration before exiting while loop
	printf("Congrats player X won with %d points in %d turns", totalPoints, turnCount-1);

	return 0;
}
