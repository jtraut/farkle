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

// Accepted args are player count followed by fully auto flag
// i.e. ./main.exe 4 auto 
// for 4 players that will be fully automated in scoring
// or ./main.exe 6
// for 6 players with standard play prompting between rolls
// default (no args provided) will be single player with actions required
int main(int argc, char *argv[]) {
	short playerCount;
	bool autoTurns = false;
	for (int i = 0; i < argc; i++) {
		// printf("Argument %d: %s\n", i, argv[i]);
		if (i == 1) {
			// Expect first arg to be player count
			short players = atoi(argv[i]);
			// Trust, nobody want to play farkle with too many players, too much waiting
			// The sweet spot is really between 2-6 players
			playerCount = MIN(MAX(players, 1), 10);
		} else if (i == 2) {
			if (strcmp("AUTO", to_uppercase(argv[i])) == 0) {
				autoTurns = true;
			}
		}
	}

	printf("FARKLE DICE GAME START WITH %d PLAYERS AND AUTO SCORING %s\n", playerCount, TRUE_FALSE(autoTurns));

	// TODO: Support multiple players, add more game instructions, and maintain a leaderboard
	// and also handle fully auto vs player engagement modes

	short turnCount = 1;
	short* totalPoints = (short*)calloc(playerCount, sizeof(short)); // create point scoring array per player starting at 0
	short activePlayer = 1;
	while (totalPoints[activePlayer-1] < MIN_TO_WIN) {
		printf("\nBeginning player %d turn %d\n", activePlayer, turnCount);
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
				if (totalPoints[activePlayer-1] < 500) {
					printf("Reminder, a minimum of %d points is required to get on the scoreboard!\nAfter which, welcome to take any amount of points.\n", MIN_ON_BOARD);
				}
				if (!autoTurns) {
					printf("Enter Y if you would like to continue rolling, or N to end turn now and take current points.\n");
					endTurn = !yes_no();					
				} else {
					// Auto decide what to do, roll down to 3 dice left or turn worth 1000+
					if (numDiceLeft < 3 || currentTurnPoints >= 1000) {
						endTurn = true;
					}
				}

			} else {
				if (autoTurns) {
					printf("Auto turns ALWAYS going for the hot-hand!");
					// TODO: maaaaaybe stop after like 3000+ points in a turn tho? typically how I would play
					numDiceLeft = 6;
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
			}
			if (endTurn) {
				// TODO: print leaderboard method
				if (totalPoints[activePlayer-1] >= 500 || currentTurnPoints >= 500) {
					totalPoints[activePlayer-1] += currentTurnPoints;
				} else if (currentTurnPoints > 0 && currentTurnPoints < 500) {
					printf("Sorry, not enough points to get on the scoreboard!\n");
				}
				printf("Player %d current overall total points: %d\n", activePlayer, totalPoints[activePlayer-1]);
			}
		}
		if (++activePlayer > playerCount) {
			printf("Back to player 1 turn!\n");
			activePlayer = 1;
			turnCount++;
		}
	}

	// Subtract a turn for the final iteration before exiting while loop
	// TODO: will need to properly get the winning player number
	// especially after implementing the "sudden death" round of all other players receiving 1 extra turn
	// oh snap, the sudden death round might already be implemented lol because of the active player already being incremented
	// before the while loop notices the first player to hit over 10000
	printf("Congrats player %d won with %d points in %d turns", activePlayer, totalPoints[activePlayer-1], turnCount-1);

	return 0;
}
