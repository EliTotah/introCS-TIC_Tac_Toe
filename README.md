# introCS-TIC_Tac_Toe

This repository contains a simple implementation of the classic game Tic-Tac-Toe. The game allows two players to compete against each other on a grid and determine the winner based on rows, columns, or diagonals filled with their respective symbols.

## Creating the Game

To initiate the game, follow these steps:

1. Run the program and input the names of the players and the desired game size.
2. The program will display the game size and the player names in lexicographical order. You'll need to select two participants for the game.
3. Players are chosen based on the order of selection, with the first player making the initial move.

## how to run the game:

gcc ex_4.c -lm -std=c99 -DNDEBUG

./a.exe

### Running Example:

<img width="665" alt="image" src="https://github.com/EliTotah/introCS-TIC_Tac_Toe/assets/117304079/4d10c10e-c359-4cf3-877e-be39f4593f47">

<img width="342" alt="image" src="https://github.com/EliTotah/introCS-TIC_Tac_Toe/assets/117304079/a5b5e556-bcec-4e4a-acbe-d5c647377c5f">


## Playing the Game

During each turn, the current state of the board is displayed, with empty spaces marked as "_". The player's name and their symbol are then displayed, and they take their turn. The player who was chosen first in the game creation phase starts the game.

If a player selects a cell that is already occupied, they will be informed and prompted to choose another cell.

## End of the Game

The game can conclude in two ways: with a win or a draw.

### Win:
If a player manages to fill a row, column, or diagonal with their symbol, the board will be displayed with their name announced as the winner.

Example:
Dana has won! You played well!


### Draw:
If no player achieves a win and the board is completely filled, the game ends in a tie.

Example:
The game ends, no one wins. You played well!


Enjoy playing the Tic-Tac-Toe game and may the best player win! 
