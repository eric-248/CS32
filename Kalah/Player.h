#ifndef PLAYER
#define PLAYER

#include <string>
#include "Side.h"
#include "Board.h"

class Player {
public:
	Player(std::string name);
	std::string name() const;
	virtual bool isInteractive() const;
	virtual int chooseMove(const Board & b, Side s) const = 0;
	virtual ~Player();

private:
	string m_name;
};

class HumanPlayer : public Player {
public:
	HumanPlayer(std::string name);
	bool isInteractive() const;
	int chooseMove(const Board& b, Side s) const;

};

class BadPlayer : public Player {
public:
	BadPlayer(std::string name);
	bool isInteractive() const;
	int chooseMove(const Board& b, Side s) const;
};

class SmartPlayer : public Player {
public:
	SmartPlayer(std::string name);
	bool isInteractive() const;
	int chooseMove(const Board& b, Side s) const;
private:
	int evaluate(const Board& b, Side s) const;
};

#endif //PLAYER