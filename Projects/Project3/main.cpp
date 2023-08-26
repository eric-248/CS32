#include <cassert>
#include <iostream>
#include "Board.h"
#include "Player.h"
#include "Game.h"

void doBoardTests()
{
	HumanPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &bp);

	assert(b.holes() == 3 && b.totalBeans() == 12 &&
		b.beans(SOUTH, POT) == 0 && b.beansInPlay(SOUTH) == 6);
	b.setBeans(SOUTH, 1, 1);
	b.moveToPot(SOUTH, 2, SOUTH);
	assert(b.totalBeans() == 11 && b.beans(SOUTH, 1) == 1);
	assert(b.beans(SOUTH, 2) == 0);
	assert(b.beans(SOUTH, POT) == 2);
	assert(b.beansInPlay(SOUTH) == 3);

	Side es;
	int eh;
	b.sow(SOUTH, 3, es, eh);
	assert(es == NORTH && eh == 3 && b.beans(SOUTH, 3) == 0 &&
		b.beans(NORTH, 3) == 3 && b.beans(SOUTH, POT) == 3 &&
		b.beansInPlay(SOUTH) == 1 && b.beansInPlay(NORTH) == 7);
}

void doPlayerTests()
{
	HumanPlayer hp("Marge");
	assert(hp.name() == "Marge" && hp.isInteractive());
	BadPlayer bp("Homer");
	assert(bp.name() == "Homer" && !bp.isInteractive());
	SmartPlayer sp("Lisa");
	assert(sp.name() == "Lisa" && !sp.isInteractive());
	Board b(3, 2);
	b.setBeans(SOUTH, 2, 0);
	cout << "=========" << endl;
	int n = hp.chooseMove(b, SOUTH);
	cout << "=========" << endl;
	assert(n == 1 || n == 3);
	n = bp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
	n = sp.chooseMove(b, SOUTH);
	assert(n == 1 || n == 3);
}

void doGameTests()
{
	BadPlayer bp1("Bart");
	BadPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);

	bool over;
	bool hasWinner;
	Side winner;
	//    Homer
	//   0  1  2
	// 0         0
	//   2  0  0
	//    Bart
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 0 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 2 &&
		g.beans(SOUTH, 1) == 2 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);

	g.move(SOUTH);
	//   0  1  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	g.display();
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 1 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move(NORTH);
	//   1  0  0
	// 0         3
	//   0  1  0
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 1 && g.beans(SOUTH, 3) == 0);

	g.move(SOUTH);
	//   1  0  0
	// 0         3
	//   0  0  1
	g.status(over, hasWinner, winner);
	assert(!over && g.beans(NORTH, POT) == 0 && g.beans(SOUTH, POT) == 3 &&
		g.beans(NORTH, 1) == 1 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 1);

	g.move(NORTH);
	//   0  0  0
	// 1         4
	//   0  0  0
	g.status(over, hasWinner, winner);
	assert(over && g.beans(NORTH, POT) == 1 && g.beans(SOUTH, POT) == 4 &&
		g.beans(NORTH, 1) == 0 && g.beans(NORTH, 2) == 0 && g.beans(NORTH, 3) == 0 &&
		g.beans(SOUTH, 1) == 0 && g.beans(SOUTH, 2) == 0 && g.beans(SOUTH, 3) == 0);
	assert(hasWinner && winner == SOUTH);
}

int main() {
	
	////test board
	//Board b = Board(6, 3);
	//Side s = SOUTH;
	//Side n = NORTH;

	////intialization
	//assert(b.holes() == 6);
	//assert(b.beans(s, 3) == 3);
	//assert(b.beans(s, 6) == 3);
	//assert(b.beans(n, 1) == 3);
	//assert(b.beansInPlay(s) == 18);
	//assert(b.totalBeans() == 36);


	//Board a = Board(3, 3);
	//Side s1 = SOUTH;
	//Side n1 = NORTH;

	//Side endSide;
	//int endHole;

	//assert(a.sow(SOUTH, 0, endSide, endHole) == false);
	//assert(a.sow(SOUTH, 3, endSide, endHole));
	//assert(a.moveToPot(n1, 1, s1) == true);

	//human vs computer
	HumanPlayer hp("Marge");
	BadPlayer bp("Homer");
	Board b(3, 2);
	Game g(b, &hp, &bp);
	g.play();

	//doBoardTests();
	//doPlayerTests();
	//doGameTests();


	//cout << "YESSIRRR" << endl;

}

