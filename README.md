# Gomoku Game

This is a console-based implementation of the Gomoku game, also known as Five in a Row. The game allows two players to play against each other or against a computer opponent. The game board is represented as a 15x15 grid, and the goal is to be the first player to get five consecutive stones of their color in a horizontal, vertical, or diagonal line.

## Dependencies

The project requires the following dependencies:
- iostream
- string
- limits
- ios
- random
- cctype
- conio.h (Windows-specific header for console input/output)
- fstream

## Game Rules

1. The game board is a 15x15 grid. Players take turns placing their stones on empty cells of the grid.
2. The first player to get five consecutive stones of their color in a horizontal, vertical, or diagonal line wins the game.
3. Players can choose to play against each other or against a computer opponent.
4. In player vs. player mode, the players take turns entering the row and column numbers to place their stones.
5. In player vs. computer mode, the human player enters the row number, and the computer randomly selects a column number to place its stone.
6. The game continues until a player wins or the players decide to quit.

## Code Structure

The code is organized into several classes and functions:

- `goban`: Represents the game board and provides methods for printing the board, checking for a win, and resetting the board.
- `player`: Represents a player and stores their stone color (Black or White). It provides a method to check if a position is valid for placing a stone.
- `person`: Inherits from `player` and represents a human player. It provides a method to place a stone on the board by taking input from the user.
- `computer`: Inherits from `player` and represents a computer opponent. It provides a method to randomly place a stone on the board.
- `N_int_check`: Utility function for input validation of natural numbers within a given range.
- `menu`: Displays the game menu options.
- `is_saved`: Checks if a save file exists.
- `human_turn`: Handles the turn process for a human player.
- `pc_turn`: Handles the turn process for a computer opponent.
- `save_game`: Allows the user to save the current game state.
- `load_game`: Loads the last saved game state.

The `main` function handles the overall flow of the game, including displaying the menu, choosing game modes, and starting new games or continuing from a saved state.

## Save File

The game allows the player to save the current game state and continue it later. The save file is named "Save file.txt" and stores the current board state, round number, and game mode choice.
