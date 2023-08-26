#include <iostream>
#include "History.h"

using namespace std;

History::History(int nRows, int nCols) {

	//set member variables
	rows = nRows;
	cols = nCols;

	//create dot 2d array
	for (int i(1); i <= nRows; i++) {

		for (int j(1); j <= nCols; j++) {

			board[i-1][j-1] = '.';
		}
	}

}

bool History::record(int r, int c) {
	
	if (r > MAXROWS || c > MAXCOLS) {
		return false;
	}

	char alpha = 'A';

	//find correct letter
	switch (board[r-1][c-1]) {

	case 'A':
		alpha = 'B';
		break;
	case 'B':
		alpha = 'C';
		break;
	case 'C':
		alpha = 'D';
		break;
	case 'D':
		alpha = 'E';
		break;
	case 'F':
		alpha = 'G';
		break;
	case 'G':
		alpha = 'H';
		break;
	case 'H':
		alpha = 'I';
		break;
	case 'I':
		alpha = 'J';
		break;
	case 'J':
		alpha = 'K';
		break;
	case 'K':
		alpha = 'L';
		break;
	case 'L':
		alpha = 'M';
		break;
	case 'M':
		alpha = 'N';
		break;
	case 'N':
		alpha = 'O';
		break;
	case 'O':
		alpha = 'P';
		break;
	case 'P':
		alpha = 'Q';
		break;
	case 'Q':
		alpha = 'R';
		break;
	case 'R':
		alpha = 'S';
		break;
	case 'S':
		alpha = 'T';
		break;
	case 'T':
		alpha = 'U';
		break;
	case 'U':
		alpha = 'V';
		break;
	case 'V':
		alpha = 'W';
		break;
	case 'W':
		alpha = 'X';
		break;
	case 'X':
		alpha = 'Y';
		break;
	case 'Y':
		alpha = 'Z';
		break;
	case 'Z':
		break;

	}

	//set spots in char array to appropriate letters
	
	for (int i(1); i <= r; i++) {

		for (int j(1); j <= c; j++) {

			if (i == r && j == c) {

				board[i - 1][j - 1] = alpha;
			}
			
		}
	}

	return true;

}

void History::display() const {

	//first clear the screen
	void clearScreen();

	for (int i(1); i <= rows; i++) {

		for (int j(1); j <= cols; j++) {

			cout << board[i - 1][j - 1];
		}
		cout << endl;
	}
}