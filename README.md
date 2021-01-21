# ReversiProgram
Reversi Program for Computer Science 2 class. Program is an implementation of the Reversi board game.

## INTRODUCTION: THE GAME OF REVERSI

Reversi is a strategy board game for two players, played on an 8×8 uncheckered board. There are sixty-four identical game pieces called disks (often spelled "discs"), which are light(‘w’) on one side and dark(‘b’) on the other. Players take turns placing disks on the board with their assigned color facing up. During a play, any disks of the opponent's color that are in a straight line and bounded by the disk just placed and another disk of the current player's color are turned over to the current player's color. The object of the game is to have the majority of disks turned to display your color when the last playable empty square is filled.  

To start the game, the board is set-up as show in Fig.1 with two dark pieces and two white pieces placed diagonally with each other. The player with the dark disks always plays first. In order to make a move, the player places a single disk on the board in an open square. In order for the move to be valid, it must meet the following conditions (see example of valid moves for the player with dark pieces in Fig. 2):  

  1. It creates a straight line (horizontally, vertically, or diagonally) between the newly placed piece and another of the player’s pieces currently on the board.  
  2. There must one or more of the opponent player’s pieces between the current player’s pieces.  

Figure 1. The game board set-up to start a new game. | Figure 2. Light black circles showing valid moves for the player with dark pieces.
-----------------------------------------------------|-----------------------------------------------------------------------------------
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture1.png?raw=true) | ![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture2.png?raw=true)

*Reversi Wiki: https://en.wikipedia.org/wiki/Reversi*  

After the current player selects a valid square for a move and places their piece, the opponent’s pieces in between the current player’s pieces are flipped to the current player’s color. For example, say the current player was the one with the dark pieces and chose their next move as (3, 4). Then, the white piece at (4, 4) would be flipped to be a black piece as can be seen in Fig. 3. In other, words you can think of a valid move as one in which at least one piece is flipped. Note, moves might cause pieces to be flipped in multiple directions. Players then alternate turns. See Figures 4 and 5 for an example move by the player with light pieces. If a player can not make a move then they must “pass” their turn. The game then officially ends when neither player can make a move. You should play a few games to get a feel for the rules (see the link  below).  

Figure 3. The result of the play from Fig. 2. | Figure 4. Light white circles indicating valid moves for player with white pieces. | Figure 5. The result of the light player’s move.
----------------------------------------------|------------------------------------------------------------------------------------|------------------------------------------
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture3.png?raw=true) | ![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture4.png?raw=true) | ![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture5.png?raw=true)

After the game has ended, the totals for each player are added together. The player with the higher number of pieces of their color on the board wins (see examples in Figures 6-8 for completed games). The highest theoretical score is 64-0. Although there are many edge cases with scoring, for the purposes of this program you will only need to count the number of pieces on the board to determine a winner or that a draw has occurred.  

Figure 6. Light player wins 13-45 by our scoring rules. | Figure 7. Light player wins 3-17 by our scoring rules. | Figure 8. Light player wins 1-58 by our scoring rules.
--------------------------------------------------------|--------------------------------------------------------|-------------------------------------------------------
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture6.png?raw=true) | ![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture7.png?raw=true) | ![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture8.png?raw=true)

*Free Online Game of Reversi “Othello”: https://cardgames.io/reversi/*  

## ASSIGNMENT REQUIREMENTS  
You will be required to implement a working game of Reversi “Othello” in C++ using the console window to show the playing board. The game will be implemented as per the following specifications:  
- The game board must be implemented as a multidimensional char array of size 8 x 8
  - You must not use vectors or other data structures to implement the game board.
  - You must not use global variables:
  - You must design the board so that it matches clearly visible “squares” as seen in the provided example below
  - Player pieces will be denoted by:
    - ‘b’ for black
    - ‘w’ for white
    - ‘ ‘ for empty (a single space)
- This program must be implemented as a class called Reversi (see the program stub below).
  - All fields you create must be private
    - This includes the game board array
    - Feel free to create as many fields as you may need
  - You must create the following required methods in the class:
    - int count (char color) 
    - void setDisk (int row, int col, char color)
    - int resultOfMove (int row, int col, char color)
    - void bestMove(int& row, int& col, int& flipped, char color)
    - void printBoard ( )
    - void resetBoard ( )
  - Additionally, you will likely need to create additional accessory, mutator, and auxiliary methods.
  - You must use a .h for the class definition and a .cpp for the method definitions separate than the .cpp file for your main function:
    - Reversi.h
    - Reversi.cpp
    - GameEngine.cpp   (contains main only)
- main will have your menu logic and user prompts, etc. 
- anything that manipulates the class however goes in your class
- You must prompt the user with dialogue stating which player’s turn it is.
- You must denote valid moves for the current player on the game board.
  - ‘x’ for valid move
- You must display a menu with the following options:
  - 1) Place a disk in a square
    - User will be prompt to enter two numbers between 0 and 7 for the row and col number of the square they wish to place their disk
      - Reject if invalid move and display error message:
        - “Invalid Move: The Reason Here”
        - Re-prompt user with menu again
  - 2) See movement rules of the game
    - Display the movement rules of the game
    - Re-display the menu
  - 3) Display possible moves
    - Displays all of the possible moves on the board for the player
      - ‘x’ for possible move location
    - Reprints the board and redisplays the menu
  - 4) See best move
    - Call a method to calculate the best possible “greedy” move a player can make
    - A “greedy” algorithm is one that only looks for the current possible best outcome without regard to other information such as future potential moves or moves of the opponent.
    - Your method will select the best move, which is the move that flips the most pieces to their color resulting in the largest score differential (num of player disks – number of opponent disks)
      - If there is a tie, select the move with the lowest possible row and col numbers 
        - e.g. if move 1, 2  ;  5, 7 ; and 6, 1 all result in a +3 differential
          - then output: “Your best move is: 1, 2 and will result in a +3 score differential.” 
      - re-display the menu
- When the game ends, display the winner and the score
  - Congrats the Light Player has Won the Game! # - #
  - Congrats the Dark Player has Won the Game! # - #
  - Ask if the player would like to play again
    - Restart the game if ‘y’
    - Display message “Thank you for playing!” if ‘n’

Sample Program Interface:  
Player Black selects option 1 and places disk at 2, 3:  
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture9.png?raw=true)  

![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture10.png?raw=true)  

Player Black selects option 2:  
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture11.png?raw=true)  

Player Black selects option 3:  
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture12.png?raw=true)  

Player Black selects option 4:  
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture13.png?raw=true)  

Player White has won the game and the players agree to play again:  
![](https://github.com/HusamAlsheikh/ReversiProgram/blob/main/Images/Picture14.png?raw=true)  

