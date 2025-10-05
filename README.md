# Robot Look-for coins

This program involves a robot moving by the zigzag method in a 10 * 10 square world, to find three coins. 
The program terminates when the robot finds all three coins.
It traversal from the point (0,0), which is located in the bottom-left corner.

## How to Build and Run.
1. The program uses **three classes**:
- 1. **Point** – stores an (x, y) location.
- 2. **World** – stores the locations of 3 coins.
- 3. **Robot** – stores the robot’s position, direction, and movement rules.  

2. The user needs to input 6 integers in the range from 0-9 to set up coin locations.
   - 1. example
         ```bash
          ./look-for 1 2 3 4 5 6

       Which represents  (1,2),(3,4),(5,6)
   
   - The robot moves until it hits the point (9.9).

## Features

- 1. Counts movements and detects locations. 
- 2. After reaching the coins, print cheer sentences.
    - 1. example
      ````bash
      --- Robot Traversal and Search ---
      Moves: 18 | Coins Found: 0
      I am at (1, 1) and I am facing west.
      
      -ROBOT WORLD BOARD-              
      . . . . . . . . . .  
      . . . . . . . . . .  
      . . . . . . . . . .  
      . . C . . . . . . .  
      . . . . . . . . . .
      . . . . . . . . . .  
      . . C . C . . . . .  
      . . . . . . . . . .  
      . R . . . . . . . .  
      . . . . . . . . . .  
      R = Robot
      C = Coin
