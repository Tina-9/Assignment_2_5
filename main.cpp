#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <cstdlib> // For system("cls") or system("clear")
#include <limits> // For numeric_limits

#include "robot.h"
#include "world.h"
#include "point.h"

using namespace std;

const int ANIMATION_DELAY_MS = 150;

// Clear the whole screen and move the cursor to the top-left corner.
// Uses ANSI codes which work well on Linux/macOS/modern Windows terminals (PowerShell/CMD).
#define ANSI_CLEAR_SCREEN "\033[2J\033[1;1H"

void clearScreen() {
    std::cout << ANSI_CLEAR_SCREEN;
    std::cout.flush();
}


void displayWorld(const World& world, const Robot& player, const Robot& computer) {
    cout << endl;
    cout << "   ------- BOARD ------" << endl;

    // Print column coordinates
    cout << "   ";
    for (int
        x = 0; x <= MAX_NUM_OF_BOARD; ++x) {
        cout << x << " ";
    }
    cout << endl;
    cout << "  ";
    for (int x = 0; x <= MAX_NUM_OF_BOARD; ++x) {
        cout << "--";
    }
    cout << "-" << endl;

    // Loop through the Y-axis (rows) from top (MAX) to bottom (0)
    for (int y = MAX_NUM_OF_BOARD; y >= 0; --y) {
        cout << y << " |"; // Print row coordinate

        // Loop through the X-axis (columns)
        for (int x = 0; x <= MAX_NUM_OF_BOARD; ++x) {
            char symbol = '.';

            bool isPlayer = (player.getX() == x && player.getY() == y);
            bool isComputer = (computer.getX() == x && computer.getY() == y);
            bool hasCoin = false;

            // Check for coin at this location
            for (int i = 0; i < NUMCOIN_POSITION; ++i) {
                const Point& coin_loc = world.getCoin(i);

                if (coin_loc.getX() == x && coin_loc.getY() == y && coin_loc.getX() != -1) {
                    hasCoin = true;
                    break;
                }
            }

            // Robot (P/C) > Coin (o) > Empty (.)
            if (isPlayer && isComputer) {
                // If both robots land on the same spot, show '!'
                symbol = '!';
            } else if (isPlayer) {
                symbol = player.getSymbol();
            } else if (isComputer) {
                symbol = computer.getSymbol();
            } else if (hasCoin) {
                symbol = 'O'; // Coin symbol
            }

            cout << symbol << " ";
        }
        cout << "|" << endl; // End of row
    }
    cout << "  ";
    for (int x = 0; x <= MAX_NUM_OF_BOARD; ++x) {
        cout << "--";
    }
    cout << "-" << endl;

    // Display
    cout << "\n------------------------" << endl;
    cout << "Player-robot-'P': Coins: " << player.getFoundCoins()
         << " | Moves: " << player.getMoves() << endl;
    player.print(); // Prints position and orientation
    cout << "\nComputer-robot-'C': Coins: " << computer.getFoundCoins()
         << " | Moves: " << computer.getMoves() << endl;

    computer.print(); // Prints position and orientation
    cout << "------------------------\n" << endl;
}

void refreshDisplay(const World& world, const Robot& player, const Robot& computer) {
    clearScreen();
    displayWorld(world, player, computer);
    std::cout.flush();
    this_thread::sleep_for(chrono::milliseconds(ANIMATION_DELAY_MS));
}


bool handlePlayerTurn(Robot& player, World& world, const Robot& computer) {
    char option;
    bool valid_action = false;

    // Check for coin collection before the move (just in case)
    player.lookForCoin(world);

    cout << "Player 'P' Turn. Enter command ";
    cout << "F-Forward | T-TurnCW | A-TurnAntiCW | Q:Quit";


    // Read and ignore any remaining newline characters before reading input
    if (cin.peek() == '\n') cin.ignore();
    cin >> option;

    // Convert to uppercase
    option = toupper(option);

    bool moved = false;
    bool turned = false;

    switch (option) {
        case 'Q': // Quit
            return true;
        case 'F': // Forward
            cout << "Player moves to forward." << endl;
            moved = player.forward();
            if (!moved) {
                cout << "Cannot move forward, you are hitting the wall." << endl;
            }
            valid_action = moved;
            break;
        case 'T': // Turn Clockwise
            cout << "To turn clockwise." << endl;
            player.turnCW();
            turned = true;
            valid_action = true;
            break;
        case 'A': // Turn Anti-Clockwise
            cout << "To turn anti-clockwise." << endl;
            player.turnAntiCW();
            turned = true;
            valid_action = true;
            break;
        default:
            cout << "Invalid command. Please use F, T, A, or Q." << endl;
            break;
    }

    if (valid_action) {
        // Refresh display to show the result of the action
        refreshDisplay(world, player, computer);

        // Check for coin collection after the move
        player.lookForCoin(world);
    }

    // Return false if the game continues (not quit)
    return false;
}

void handleComputerTurn(Robot& computer, World& world, const Robot& player) {
    cout << "Computer 'C' Turn: Thinking..." << endl;

    // Check for coin collection before the move (if the player just missed one)
    computer.lookForCoin(world);

    // AI makes one move (which might be a turn or a forward step)
    bool moved_or_turned = computer.aIMovement(world);

    if (moved_or_turned) {
        cout << "Computer moved/turned." << endl;

        // refresh screen display to show the animation step
        refreshDisplay(world, player, computer);

        // Check for coin collection after the move
        computer.lookForCoin(world);
    } else {
        cout << "Computer has nowhere to go or all coins are collected." << endl;
    }

    // show result
    this_thread::sleep_for(chrono::milliseconds(500));
}


int main() {
    World robot_world;
    Robot player_robot;
    player_robot.init(0, 0, EAST, 'P');

    // Computer starts at (MAX_NUM_OF_BOARD, MAX_NUM_OF_BOARD) (9,9) facing WEST, symbol 'C'
    Robot computer_robot;
    computer_robot.init(MAX_NUM_OF_BOARD, MAX_NUM_OF_BOARD, WEST, 'C');

    robot_world.randomlyPlaceCoins(MAX_NUM_OF_BOARD);

    // Initial display before the game loop starts
    clearScreen();
    cout << "--- Roomba VS Robot  ---" << endl;
    cout << "Player 'P' starts at (0,0). Computer 'C' starts at (" << MAX_NUM_OF_BOARD << ","
         << MAX_NUM_OF_BOARD << ")." << endl;

    cout << "First find the " << NUMCOIN_POSITION << " coins wins!" << endl;
    cout << "Please press enter to start the game." << endl;


    // Clear any existing input buffer,
    // then wait for the user to press Enter

    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    bool game_quit = false;
    int total_coins_collected = 0;

    while (!game_quit && total_coins_collected < NUMCOIN_POSITION) {

        // Roomba-palyer
        refreshDisplay(robot_world, player_robot, computer_robot);

        bool valid_action = false;
        while(!valid_action && !game_quit) {
            int pre_moves = player_robot.getMoves();
            int pre_coins = player_robot.getFoundCoins();

            // updates
            game_quit = handlePlayerTurn(player_robot, robot_world, computer_robot);

            // check if a move or turn successful
            if (player_robot.getMoves() > pre_moves || player_robot.getFoundCoins() > pre_coins || game_quit) {
                valid_action = true;
            } else if (!game_quit) {

                // failed move
                cout << "Input was invalid. Enter (F/T/A) to move." << endl;
            }

            total_coins_collected = player_robot.getFoundCoins() + computer_robot.getFoundCoins();
            if (total_coins_collected >= NUMCOIN_POSITION || game_quit) break;
        }
        if (game_quit || total_coins_collected >= NUMCOIN_POSITION) break;

        // computer-robot
        refreshDisplay(robot_world, player_robot, computer_robot);
        handleComputerTurn(computer_robot, robot_world, player_robot);
        total_coins_collected = player_robot.getFoundCoins() + computer_robot.getFoundCoins();

    }

    clearScreen();
    displayWorld(robot_world, player_robot, computer_robot);

    cout << "\n********************************" << endl;
    if (game_quit) {
        cout << "Game terminate: Player quit." << endl;
    } else {
        cout << "GAME OVER! All " << NUMCOIN_POSITION << " coins collected." << endl;
    }
    cout << "*********************************" << endl;

    int p_coins = player_robot.getFoundCoins();
    int c_coins = computer_robot.getFoundCoins();

    cout << "Player-robot-'P' found coins number: " << p_coins << endl;
    cout << "Computer-robot-'C' found coins number: " << c_coins << endl;


    cout << "\n--- Record ---" << endl;
    if (p_coins > c_coins) {
        cout << "!!! Player-robot-'P' WINS !!!" << endl;
    } else if (c_coins > p_coins) {
        cout << "!!! Computer-robot-'C' WINS !!!" << endl;
    } else {
        cout << "!!! It's a tie !!!" << endl;
    }
    cout << "--------------------" << endl;


    return 0;
}
