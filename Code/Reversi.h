//	Husam Alsheikh

#pragma once
#include <iostream>

using namespace std;

class Reversi {
private:
	const static int ROWS = 8;
	const static int COLS = 8;
	char gameboard[ROWS][COLS];

public:
	Reversi();

	void printLines();

	void printNumbers();

	void printBoard();

	void resetBoard();

	void cleanBoard();

	int count(char color);

	void setDisk(int row, int col, char color);

	int resultOfMove(int row, int col, char color);

	void bestMove(int& row, int& col, int& fliped, char color);

	void possibleMoves(char color, int& moves, int change = 1);
	
	int validation(int row, int col, char color);

	void isWin(char color, int& win, int moves);
};