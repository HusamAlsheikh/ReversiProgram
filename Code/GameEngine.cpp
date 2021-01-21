//	Husam Alsheikh

#include <iostream>
#include <iomanip>
#include "Reversi.h"

using namespace std;

void rules();
char playerToColor(int player);
void switchPlayer(int& player);

//	Description:	Main of the program, contains all the game logic
//	Pre-Condition:	none
//	Post-Condition:	Runs Reversi game
void main() {
	Reversi myReversi;
	int player = 1;
	int choice = 0;
	int error = 0;

	myReversi.resetBoard();

	cout << "\t\t\t\t\tWelcome to Reversi" << endl;
	cout << "\t\t\t" << setfill('-') << setw(50) << "";

	cout << "\n\t- Reversi is a strategy board game for two players, The player with the dark disks always plays first.";
	cout << "\n\t- Player 1 will be dark, Player 2 will be light. Players take turns placing disks on the board with their\n\t  assigned color facing up.";
	cout << "\n\t- During a play, any disks of the opponent's color that are in a straight line and bounded by the\n\t  disk just placed and another disk";
	cout << "of the current player's color are turned over to the current player's color.\n\t- The object of the game is to have the majority of disks";
	cout << "turned to display your color when the last\n\t  playable empty square is filled. ";
	cout << endl << endl;

	cout << "Player 1 is black" << endl;
	cout << "Player 2 is white" << endl;

	cout << endl;

	do {
		int row = 0, col = 0;
		char color = ' ';
		int moves = 0, win = 0;

		//	Changes player number to respective color
		color = playerToColor(player);

		//	Checks if there are any possible moves, if not moves = 0 will result in a pass
		myReversi.possibleMoves(color, moves, 0);

		myReversi.printBoard();

		cout << "Player " << player << "'s turn" << endl;

		if (moves > 0) {
			cout << "Menu:   1) Place a disk\n\t2) See movement rules\n\t3) Display possible moves";
			cout << "\n\t4) Display best move\n\t5) Exit Game";
			cout << "\nSelection: ";
			cin >> choice;

			//	Data Validation - Choice in correct range
			while (choice < 1 || choice > 5) {
				cout << "Invalid Choice, please select an option from the menu, try again: ";
				cin >> choice;
			}

			if (choice == 1) {
				cout << "Row (1 - 8) and column (1 - 8) of the square where you want to place a disk: ";
				cin >> row >> col;

				//	Move Validation
				do {
					//	Data Validation - Row and Col in correct range
					while (row <= 0 || row >= 8 || col <= 0 || col >= 8) {
						cout << "Invalid Move - Row and Col must be between (1 - 8), try again: ";
						cin >> row >> col;
					}

					error = myReversi.validation(row, col, color);

					if (error == 1) {
						cout << "Invalid Move - There already exists a disk on these coordinates, try again: ";
						cin >> row >> col;
					}
					else if (error == 2) {
						cout << "Invalid Move - Disk must be placed next to opponents disk and must result in opponent disks fliped, try again:";
						cin >> row >> col;
					}
				} while (error != 0);

				myReversi.setDisk(row, col, color);

				switchPlayer(player);
			}
			else if (choice == 2) {
				rules();
			}
			else if (choice == 3) {
				myReversi.possibleMoves(color, moves);
			}
			else if (choice == 4) {
				int bestRow = 0, bestCol = 0, fliped = 0;

				myReversi.bestMove(bestRow, bestCol, fliped, color);

				cout << "Your best move is: " << bestRow << ", " << bestCol;
				cout << " and will result in a " << showpos << fliped << " score differential" << endl;
				cout << noshowpos;
			}
			else if (choice == 5) {
				cout << "\n\n\t\tExiting Game, Thank you for playing Reversi!!!\n";
			}
		}

		moves = 0;
		//	Checks if there are any possible moves, if not moves = 0 will result in a pass
		myReversi.possibleMoves(color, moves, 0);

		if(moves == 0) {
			myReversi.printBoard();

			//	Switch player and color back (since player is switched after a disk is placed)
			switchPlayer(player);
			color = playerToColor(player);

			myReversi.isWin(color, win, moves);
			
			//	If there is a winner, display winner. If not, then current player must pass his turn
			if (win == 1) {
				char opponent = color == 'w' ? 'b' : 'w';

				cout << "\n\nCongratz! Player " << player << ": has won the game (" << myReversi.count(color) << " - " <<
					myReversi.count(opponent) << ")" << endl;

				choice = 5;
			}
			else {
				cout << "\nThere are no possible moves, your turn has been passed!" << endl;
			}
		}

		//	If game is won, check to see if user wants to play again, if not exit
		if (win == 1) {
			char playAgain = ' ';

			cout << "Would you like to play again? (y/n): ";
			cin >> playAgain;

			if (playAgain == 'y') {
				myReversi.resetBoard();
				player = 1;
				choice = 0;
			}
			else {
				cout << "\n\n\t" << setfill('-') << setw(35) << "";
				cout << "\n\tThank you for playing Reversi!!\n";
				cout << "\t" << setfill('-') << setw(35) << "";
			}
		}
	} while (choice != 5);

	cout << endl << endl;
	system("pause");
}

//	Description:	Function to print rules
//	Pre-Condition:	none
//	Post-Condition:	Prints specific string messages to console output
void rules() {
	cout << endl << "Movement rules for Reversi \"Othello\":" << endl;
	cout << "A player must place their disk such that :" << endl;
	cout << "\t1) It creates a straight line (horizontally, vertically or diagnolly)";
	cout << "\n\t  between the newly placed disk and another of the player's disk." << endl;
	cout << "\t2) There must be one or more of the opponent's disks between the";
	cout << "\n\t  current player's disks. [A disk must get \"flipped\".]" << endl << endl;
}

//	Description:	Function to switch player number to respective color
//	Pre-Condition:	Valid player number
//	Post-Condition:	Returns color of player as char
char playerToColor(int player) {
	if (player == 1) {
		return 'b';
	}
	else if (player == 2) {
		return 'w';
	}
}

//	Description:	Function to change player turns
//	Pre-Condition:	Valid player number
//	Post-Condition:	Will switch players
void switchPlayer(int& player) {
	player = player == 1 ? 2 : 1;
}