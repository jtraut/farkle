// THIS FILE IS PURELY FOR DEFINING VALS
#ifndef DICE_STATS_H
#define DICE_STATS_H

#define MAX_ROLL 6
#define MIN_ROLL 1

#define MAX_DICE 6

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
#define FIVE 50
#define ONE 100
#define TRIPLE_ONE 300
#define TRIPLE_TWO 200
#define TRIPLE_THREE 300 
#define TRIPLE_FOUR 400
#define TRIPLE_FIVE 500
#define TRIPLE_SIX 600
#define FOUR_KIND 1000
#define FIVE_KIND 2000
#define SIX_KIND 3000
#define STRAIGHT 1500
#define TRIPLE_DOUBLE 1500
#define DOUBLE_TRIPLET 2500
#define FOUR_KIND_PAIR 1500

#endif