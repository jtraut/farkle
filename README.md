# FARKLE

## Description
C command line program of Farkle dice game implemented in VS Code

Compiled with VS Code build task (tasks.json).

## Instructions
Clone / Fork repo.

Open in VS Code and enter `Ctrl+Shift+B` to build the project.

    - Note this was implemented & compiled on Windows machine, minor changes like header include `#include <unistd.h>`
    
      may be required to run successfully on Linux etc.

Run the main.exe in preferred terminal or directly in VS Code:
```
jaket@DESKTOP-MIR3S3C MINGW64 ~/Workspace/farkle (main)
$ ./src/main.exe
```
Or to set the player count to 4 and fully auto flag to disable user prompting
```
./main.exe 4 auto
```

## Example output (of a pretty stellar start):
```
jaket@DESKTOP-MIR3S3C MINGW64 ~/Workspace/farkle (main)
$ ./src/main.exe
FARKLE DICE GAME
Beginning turn 1

Current dice on board: [4] [2] [6] [2] [4] [6]
Current number of dice being scored: 6
Way to go, you got a triple double!
Resetting all dice to zero (cleared the board)!
Your roll scored 1500 points.
************************************************
Would you like to keep rolling with a hot-hand (6 dice) OR stop now and take your current turn points 1500
Please enter Y if want to continue rolling with a hot-hand, or N to end turn.
Please enter Y/N: y

Current dice on board: [3] [1] [1] [5] [1] [1]
Current number of dice being scored: 6
Booyah! That's four of a kind.
Your roll scored 1050 points.
************************************************
Current turn 1 total points: 2550 with 1 dice left
Enter Y if you would like to continue rolling, or N to end turn now and take current points.
Reminder, a minimum of 500 points is required to get on the scoreboard!
After which, welcome to take any amount of points.
Please enter Y/N: n
Current overall total points: 2550
Beginning turn 2

Current dice on board: [5] [4] [5] [5] [2] [1]
Current number of dice being scored: 6
Nice three of a kind!
Your roll scored 600 points.
************************************************
Current turn 2 total points: 600 with 2 dice left
Enter Y if you would like to continue rolling, or N to end turn now and take current points.
Please enter Y/N:

...

Beginning turn 18

Current dice on board: [4] [6] [6] [2] [2] [5]
Current number of dice being scored: 6
Your roll scored 50 points.
************************************************
Current turn 18 total points: 50 with 5 dice left
Enter Y if you would like to continue rolling, or N to end turn now and take current points.
Please enter Y/N: y

Current dice on board: [3] [1] [3] [3] [6]
Current number of dice being scored: 5
Nice three of a kind!
Your roll scored 400 points.
************************************************
Current turn 18 total points: 450 with 1 dice left
Enter Y if you would like to continue rolling, or N to end turn now and take current points.
Please enter Y/N: n
Current overall total points: 9850
Beginning turn 19

Current dice on board: [4] [3] [6] [4] [6] [3]
Current number of dice being scored: 6
Way to go, you got a triple double!
Resetting all dice to zero (cleared the board)!
Your roll scored 1500 points.
************************************************
Would you like to keep rolling with a hot-hand (6 dice) OR stop now and take your current turn points 1500
Please enter Y if want to continue rolling with a hot-hand, or N to end turn.
Please enter Y/N: y

Current dice on board: [3] [6] [3] [4] [5] [2]
Current number of dice being scored: 6
Your roll scored 50 points.
************************************************
Current turn 19 total points: 1550 with 5 dice left
Enter Y if you would like to continue rolling, or N to end turn now and take current points.
Please enter Y/N: n
Current overall total points: 11400
Congrats player X won with 11400 points in 19 turns
jaket@DESKTOP-MIR3S3C MINGW64 ~/Workspace/farkle (main)
```