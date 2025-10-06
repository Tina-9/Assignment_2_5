# Game of two Robots Look-for coins

This program involves two robots moving by the zigzag method in a 10 * 10 square world, to find three coins. 
This is a game to see who is the winner, which is the first collect all three randomly located coins.
The program terminates when the robot finds all three coins and when the user presses Q to quit.
The computer robot has an AI algorithm to find the closest coin in priority from the point (9,9).
The user robot starts from point (0,0), and is controlled by pressing the key "F/A/T" to move the robot.

## Features

- 1. Counts movements, the number of coins found, and detects locations. 
  - 1. Command-control robot movements: F-Forward,
                T-TurnCW (clockwise),
                A-TurnAntiCW (counter-clockwise),
                Q-Quit.
  
  - b. example
    ````bash
     --- Roomba VS Robot  ---
     Player 'P' starts at (0,0). Computer 'C' starts at (9,9).
     First find the 3 coins wins!
     Please press enter to start the game.
     ------- BOARD ------
     0 1 2 3 4 5 6 7 8 9
     ---------------------
     9 |. . . . . . . . . C |
     8 |. . . . . . . . . . |
     7 |O . . . O . . O . . |
     6 |. . . . . . . . . . |
     5 |. . . . . . . . . . |
     4 |. . . . . . . . . . |
     3 |. . . . . . . . . . |
     2 |. . . . . . . . . . |
     1 |. . . . . . . . . . |
     0 |P . . . . . . . . . |
        --------------------

     ------------------------
     Player-robot-'P': Coins: 0 | Moves: 0
     I am at (0, 0)
     I am facing east.
     Computer-robot-'C': Coins: 0 | Moves: 0
     I am at (9, 9)
     I am facing west.
     ------------------------
     Player 'P' Turn. Enter command 
     F-Forward | T-TurnCW | A-TurnAntiCW | Q:Quit
  































