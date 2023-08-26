#ifndef GAME
#define GAME

#include "Player.h"

class Game {

public:
	Game(const Board& b, Player* south, Player* north);
	void display() const;
	void status(bool& over, bool& hasWinner, Side& winner) const;
	bool move(Side s);
	void play();
	int beans(Side s, int hole) const;

private:
	Board m_board;
	Player* m_south;
	Player* m_north;
	Side current_turn;

};
#endif //GAME