# Connect 4 Game

## Overview

This is a console-based implementation of the classic Connect 4 game, featuring color-coded pieces, customizable board dimensions, save/load functionality, a high scores leaderboard, and a simple AI opponent.
[]()

https://github.com/user-attachments/assets/2fa1c156-e7f3-4cac-9c71-7a9a83c723ea

## Features

1. **Customizable Board Dimensions**:
    - The game reads and validates board dimensions from an XML file (`readXML.xml`).
    - If there is any issue with reading the XML file, default values are applied (height = 7 and width = 6).
2. **Save/Load Game**:
    - Players can save their current game state to a binary file (`savedgames.bin`) and load it later to continue from where they left off.
    - The game efficiently handles file storage, and if the save file is removed or an error occurs, a new file is created automatically.
3. **High Scores Leaderboard**:
    - The game maintains a leaderboard of high scores, stored in a binary file (`highscores.bin`).
4. **AI Opponent**:
    - The game includes a basic AI opponent that simulates a simple algorithm to play against the human player.
5. **Unique Win Evaluation**:
    - The game evaluates the winner based on how many sets of 4-in-a-rows are achieved in rows, columns, and diagonals.
6. **Redo/Undo Functionality**:
    - The game features redo/undo options available in both the in-game and main menus.
7. **Modular Code Structure**:
    - The code is divided into six files for better organization and maintainability:
        - `Rxml.h`
        - `connect 4 project.c`
        - `function.h`
        - `highscores.bin`
        - `readXML.xml`
        - `savedgames.bin`

## File Descriptions

- **`Rxml.h`**:
    - Header file for reading and validating XML data related to the board dimensions.
- **`connect 4 project.c`**:
    - The main source file containing the game logic, user interface, and flow control.
- **`function.h`**:
    - Header file containing function declarations used across the project.
- **`highscores.bin`**:
    - Binary file for storing the high scores leaderboard.
- **`readXML.xml`**:
    - XML file used for reading the board dimensions.
- **`savedgames.bin`**:
    - Binary file used for saving and loading game states.

## Installation and Running the Game

1. **Clone the Repository**:
    
    ```bash
    bash
    Copy code
    git clone https://github.com/yourusername/connect4.git
    cd connect4
    ```
    
2. **Compile the Code**:
    
    ```arduino
    arduino
    Copy code
    gcc -o connect4 connect\ 4\ project.c -lm
    ```
    
3. **Run the Game**:
    
    ```bash
    bash
    Copy code
    ./connect4
    ```
    

## How to Play

1. **Starting the Game**:
    - Run the executable and follow the on-screen instructions to start a new game or load a saved game.
2. **Gameplay**:
    - Players take turns dropping colored pieces into the columns of the board.
    - The goal is to connect as many sets of four of your pieces vertically, horizontally, or diagonally before your opponent does.
3. **Saving and Loading**:
    - You can save the current game state at any time and load it later to continue playing.
4. **AI Opponent**:
    - If you choose to play against the AI, the game will automatically simulate the AI's moves based on a simple algorithm.
5. **In-Game Menu Options**:
    - During the game, you can access the in-game menu for additional options:
        - **c**: Continue the game.
        - **u**: Undo the last move.
        - **r**: Redo the last undone move.
        - **s**: Save the current game state.
        - **e**: Exit the game.
    - You can access the main menu for options such as starting a new game, loading a game, viewing top players, and quitting the game.
