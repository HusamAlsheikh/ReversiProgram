//	Husam Alsheikh

#include <iostream>
#include "Reversi.h"

using namespace std;

//	Description:	Default Constructor
//	Pre-Condition:	Called from the Reversi class object
//	Post-Condition:	Sets all board coordinates to blank
Reversi::Reversi() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			gameboard[r][c] = ' ';
		}
	}
}

//	Description:	Member Function
//	Pre-Condition:	Called from the Reversi class object
//	Post-Condition:	Prints the lines for the visible game board
void Reversi::printLines() {
	cout << "   ";
	for (int i = 0; i < 8; i++)
	{
		cout << " ---";
	}
	cout << endl;
}

//	Description:	Member Function
//	Pre-Condition:	Called from the Reversi class object
//	Post-Condition:	Prints the numbers along the game board border
void Reversi::printNumbers() {
	cout << "   ";
	for (int i = 0; i < 8; i++)
	{
		cout << "  " << i + 1 << " ";
	}
	cout << endl;
}

//	Description:	Member Function, uses printlines() and printNumbers()
//	Pre-Condition:	Called from the Reversi class object
//	Post-Condition:	Prints the complete board with lines and numbers
void Reversi::printBoard() {
	cout << endl;

	printNumbers();
	printLines();
	for (int i = 0; i < ROWS; i++)
	{
		cout << " " << i + 1;
		for (int j = 0; j < COLS; j++)
		{
			cout << " | " << gameboard[i][j];
		}

		cout << " | " << i + 1 << endl;
		printLines();
	}
	printNumbers();
}

//	Description:	Member Function to reset entire board
//	Pre-Condition:	Called from the Reversi class object
//	Post-Condition:	Resets all coordinates to blank and initializes the 4 middle pieces
void Reversi::resetBoard() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			gameboard[r][c] = ' ';
		}
	}

	gameboard[3][3] = 'w';
	gameboard[3][4] = 'b';
	gameboard[4][4] = 'w';
	gameboard[4][3] = 'b';
}

//	Description:	Member Function to wipe the board of anything unecessary
//	Pre-Condition:	Called from the Reversi class object
//	Post-Condition:	Will remove all occurences of possible move indications on the board, 'x'
void Reversi::cleanBoard() {
	//	after move is made remove all possible moves 'x' from the board
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (gameboard[r][c] == 'x') {
				gameboard[r][c] = ' ';
			}
		}
	}
}

//	Description:	Member Function to count number of disks
//	Pre-Condition:	Valid char parameter
//	Post-Condition:	Will count the number of occurences of the char parameter on the board
int Reversi::count(char color) {
	int count = 0;

	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (gameboard[r][c] == color) {
				count++;
			}
		}
	}

	return count;
}

//	Description:	Member Function to play players move
//	Pre-Condition:	Valid int, and char parameters
//	Post-Condition:	Will set disk of color and coordinates and flip appropriate game disks
void Reversi::setDisk(int row, int col, char color) {
	char opponent = color == 'w' ? 'b' : 'w';
	int tempRow = 0, tempCol = 0;
	row--;
	col--;

	//	set the players move
	gameboard[row][col] = color;

	//	loop through and flip pieces
	for (int r = -1; r <= 1; r++) {
		for (int c = -1; c <= 1; c++) {
			//	make sure we dont go overbounds
			if (row + r < 0 || row + r >= ROWS || col + c < 0 || col + c >= COLS || (r == 0 && c == 0)) {
				continue;
			}

			if (gameboard[row + r][col + c] == opponent) {
				//	found opponents disk
				//	set temp variables to location of opponents disk
				tempRow = row + r;
				tempCol = col + c;
				
				while(1) {
					tempRow += r;
					tempCol += c;

					//	break if we hit the end of the board
					if (tempRow < 0 || tempRow >= ROWS || tempCol < 0 || tempCol >= COLS) {
						break;
					}

					//	break if we find a blank
					if (gameboard[tempRow][tempCol] == ' ') {
						break;
					}

					//	after going in r and c direction, stop if found same color disk
					if (gameboard[tempRow][tempCol] == color)
					{
						//	then loop backwards to flip all pieces in between
						while (gameboard[tempRow -= r][tempCol -= c] == opponent) {
							gameboard[tempRow][tempCol] = color;
						}

						break;
					}
				}
			}
		}
	}

	cleanBoard();
}

//	Description:	Member Function to see how good a move is
//	Pre-Condition:	Valid int and char parameters
//	Post-Condition:	Returns score differential of said move
int Reversi::resultOfMove(int row, int col, char color) {
	char opponent = color == 'w' ? 'b' : 'w';
	int playerCount = 0, opponentCount = 0;
	char tempBoard[ROWS][COLS];

	row++;
	col++;

	//	copy game board to temporary board
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			tempBoard[r][c] = gameboard[r][c];
		}
	}

	//	changing the actual gameBoard
	setDisk(row, col, color);

	playerCount = count(color);
	opponentCount = count(opponent);

	//	copy the tempBoard to the real board to remove any edits we did
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			gameboard[r][c] = tempBoard[r][c];
		}
	}

	return (playerCount - opponentCount);
}

//	Description:	Member Function to suggest best move to user
//	Pre-Condition:	Valid int and char parameters
//	Post-Condition:	Will display to user best move possible at this point (highest score differential)
void Reversi::bestMove(int& row, int& col, int& fliped, char color) {
	int moves = 0;
	bool change = 0;

	int allMoves[ROWS][COLS];
	int tempBest = -1, tempRow = 0, tempCol = 0;

	//	initialize allMoves array to have values of -1
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			allMoves[r][c] = -64;
		}
	}

	//	add all possible moves to board
	possibleMoves(color, moves);

	//	loop through board and store all possible moves in array
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (gameboard[r][c] == 'x') {
				allMoves[r][c] = resultOfMove(r, c, color);
			}
		}
	}

	//	since we have collected the moves in new array, clean board of possible moves 'x'
	cleanBoard();

	//	loop through allMoves array and find the highest score differential
	for (int r = 0; r < ROWS; r++) {
		for (int c = 0; c < COLS; c++) {
			if (allMoves[r][c] > -64) {	// stop if its an actual score differential
				if (tempBest < 0) {	//	if tempBest is still not set, set to first number we find
					tempBest = allMoves[r][c];

					tempRow = r;
					tempCol = c;
				}
				else {	// if tempBest is set, see if greater than or equal to score
					if (allMoves[r][c] > tempBest) {	// tempBest is less than so set tempBest to this new high score
						tempBest = allMoves[r][c];

						tempRow = r;
						tempCol = c;
					}
					else if(allMoves[r][c] == tempBest) {	// if tempBest is equal to score
						if (r < tempRow) {	// if r for current move is greater than the r of best move
							allMoves[r][c] = tempBest;

							tempRow = r;
							tempCol = c;
						}
						else if (r == tempRow) {
							if (c < tempCol) {	// if c for current move is greater than the the c of best move
								allMoves[r][c] = tempBest;

								tempRow = r;
								tempCol = c;
							}
						}
					}
				}
			}
		}
	}

	gameboard[tempRow][tempCol] = 'x';

	row = tempRow + 1;
	col = tempCol + 1;
	fliped = tempBest;
}

//	Description:	Member Function to print all possible moves to be played
//	Pre-Condition:	Valid char, int and bool parameters
//	Post-Condition:	Will print 'x' on the game board as a possible move
void Reversi::possibleMoves(char color, int& moves, int change) {
	char opponent = color == 'w' ? 'b' : 'w';
	int tempRow = 0, tempCol = 0;

	//	loop through entire board
	for (int row = 0; row < ROWS; row++) {
		for (int col = 0; col < COLS; col++) {
			// once we find one of this players disks
			if (gameboard[row][col] == color) {
				// loop through to find direction of possible plays
				for (int r = -1; r <= 1; r++) {
					for (int c = -1; c <= 1; c++) {
						//	make sure we dont go overbounds
						if ((row + r) < 0 || (row + r) >= ROWS || (col + c) < 0 || (col + c) >= COLS || (r == 0 && c == 0)) {
							continue;
						}
						
						//	stop if opponent is found
						if (gameboard[row + r][col + c] == opponent) {
							tempRow = row;	// tempRow is opponent row
							tempCol = col;	// tempCol is opponent col

							while (1) {
								//	move in direction of opponent
								tempRow += r;	// r is row direction opponent is in
								tempCol += c;	// c is col direction opponent is in

								//	break if we go overbounds
								if (tempRow < 0 || tempRow >= ROWS || tempCol < 0 || tempCol >= COLS) {
									break;
								}

								//	break if we find a blank
								if (gameboard[tempRow][tempCol] == ' ') {
									break;
								}

								if (gameboard[tempRow + r][tempCol + c] == ' ' || gameboard[tempRow + r][tempCol + c] == 'x') {
									//	break if we go overbounds
									if (tempRow + r < 0 || tempRow + r >= ROWS || tempCol + c < 0 || tempCol + c >= COLS) {
										break;
									}

									int temp1 = tempRow + r + 1;
									int temp2 = tempCol + c + 1;

									if (validation(temp1, temp2, color) == 0) {
										if (change == 1) {
											gameboard[tempRow + r][tempCol + c] = 'x';
										}

										moves++;
									}

									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

//	Description:	Member Function to validate players move
//	Pre-Condition:	Valid int and char parameters
//	Post-Condition:	Returns int based on wether move is valid or not
int Reversi::validation(int row, int col, char color) {
	char opponent = color == 'w' ? 'b' : 'w';
	row--;
	col--;
	// here temp is used as a flag, 0 means nothing is invalid, any other number means there is an error
	int temp = 0;

	if (gameboard[row][col] != ' ') {
		temp = 1;	// temp set to 1, meaning we have an error of the condition above

		if (gameboard[row][col] == 'x') {
			temp = 0;
		}
	}
	if (temp == 0) {
		int tempRow = 0;
		int tempCol = 0;

		//	setting flag with meaningful number, to be returned by function if not changed by double for loops
		temp = 2;

		for (int r = -1; r <= 1; r++) {
			for (int c = -1; c <= 1; c++) {
				//	make sure we dont go overbounds
				if ((row + r) < 0 || (row + r) >= ROWS || (col + c) < 0 || (col + c) >= COLS || (r == 0 && c == 0)) {
					continue;
				}

				if (gameboard[row + r][col + c] == opponent) {
					//	found opponents disk
					//	set temp variables to location of opponents disk
					tempRow = row + r;
					tempCol = col + c;

					//	heading in the direction of r and c, if we find players disk then it is a valid move
					while(1) {
						tempRow += r;
						tempCol += c;

						//	break if we hit the end of the board
						if (tempRow < 0 || tempRow >= ROWS || tempCol < 0 || tempCol >= COLS) {
							temp = 2;
							break;
						}

						//	break if we find a blank
						if (gameboard[tempRow][tempCol] == ' ') {
							temp = 2;
							break;
						}

						//	valid move since we found opponent disk in between two player disks
						if (gameboard[tempRow][tempCol] == color) {
							temp = 0;
							return temp;
						}
					}
				}
			}
		}
	}
	
	return temp;
}

//	Description:	Member Function to decided if and who is the winner
//	Pre-Condition:	Valid int and char parameters
//	Post-Condition:	Will see if game is won and print scores
void Reversi::isWin(char color, int& win, int moves) {
	char opponent = color == 'w' ? 'b' : 'w';
	int tempRow = 0, tempCol = 0;
	int tempMoves = 0;

	possibleMoves(opponent, tempMoves, 0);

	if (tempMoves == 0) {
		win = 1;
	}
}