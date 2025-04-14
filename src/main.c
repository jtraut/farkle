#include "lib/prompt_user.h"
#include "lib/roll.h"
#include <stdio.h>

int main() {
	printf("FARKLE DICE GAME\n");

	// TODO: various classes for...
	// dice, rolling (random num generating), directions, scorekeeping, players
	// test...

	short i;
	short* result = (short*)malloc(6 * sizeof(short));

	for (i = 6; i > 0; i--) {
		result = roll_dice(i);
		printf("Roll result: ");
		for (int j = 0; j < i; j++) {
			printf("[%d] ", result[j]);
		}
		printf("\n");
		select_dice(result);
	}

	return 0;
}
