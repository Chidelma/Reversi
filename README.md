# Reversi

## Overview
This C program implements a module that finds the best move in the game Reversi. Reversi is a board game played by two players on an 8x8 grid board. Each player has discs of their color (black or white), and the goal of the game is to have the majority of their discs on the board at the end of the game. Players can make moves by placing a disc on the board such that they trap one or more of the opposing player's discs between two of their own. All of the trapped discs are then turned over to the opposing player's color.

This program reads one board from standard input and computes a player's best move. It outputs the row and column of the best move.

## Functionality
### readGameBoard()
This function reads a game board from standard input. The input must have the board's title on the first line, the number of columns, number of rows, and current player ('B' or 'W') on the second (space as a delimiter), the board's row on each line (' ' for NONE, 'B' for BLACK, and 'W' for WHITE), and an empty line at the end.

### printBoard()
This function prints the board in a pretty format.

### printBoardColumnName()
This function prints the board's column head. It is a support function for the printBoard() function.

### printBoardRowSeparator()
This function prints the board's row separator. It is a support function for the printBoard() function.

### canPlayAt()
This function checks if the current player perhaps can play at the given row and column. It returns true if the cell is possibly playable. To check if the cell is indeed playable, the caller must make sure that there will be at least one piece that will be reversed by playing at this cell.

### numReverseDirection()
This function finds out all the number of reverses from the given position towards the given direction.

### numAllReverse()
This function finds out all the number of reverses by playing at the given position.

### computeBestMove()
This function reads one board from standard input and computes a player's best move. It outputs the row and column of the best move.

### checkstate()
This function checks if the given board is valid. It returns true if the board is valid; otherwise, false.

## Compilation and Execution
This program requires a C compiler to build. To compile the program, execute the following command in a terminal:

```bash
gcc -o reversi reversi.c
```

To execute the program, run the following command in a terminal:

```bash
./reversi
```
