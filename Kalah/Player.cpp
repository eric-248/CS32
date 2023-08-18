#include <iostream>
#include "Player.h"

/////////////////////PLAYER/////////////////

//Create a Player with the indicated name.
Player::Player(std::string name):m_name(name) {

}

//Return the name of the player.
std::string Player::name() const {
	return m_name;
}

//Return false if the player is a computer player.Return true if the player is human.Most kinds of players will be computer players.
bool Player::isInteractive() const {
	return false;
}

Player::~Player() {};

///////////////////HUMANPLAYER////////////////////

HumanPlayer::HumanPlayer(std::string name):Player(name) {

}

bool HumanPlayer::isInteractive() const {
	return true;
}
int HumanPlayer::chooseMove(const Board& b, Side s) const {
	
	int hole = -1;

	while (hole == -1) {
		
		int num;

		cout << "Enter a hole number: " << endl;
		cin >> num;

		//invalid input
		if (num < 1 || num > b.holes()) {
			continue;
		}
		//set hole equal to user input
		else {
			hole = num;
		}

	}

	return hole;
}


//////////////////BADPLAYER////////////////////

BadPlayer::BadPlayer(std::string name):Player(name) {

}
bool BadPlayer::isInteractive() const {
	return false;
}
int BadPlayer::chooseMove(const Board& b, Side s) const {
	
	for (int i = 1; i < b.holes(); i++) {
		if (b.beans(s, i) != 0){
			return i;
		}
	}

	return -1;
	
}


//////////////////SMARTPLAYER////////////////////
SmartPlayer::SmartPlayer(std::string name):Player(name) {

}
bool SmartPlayer::isInteractive() const {
	return false;
}
int SmartPlayer::chooseMove(const Board& b, Side s) const {
	int bestHole = -1;
	int maxScore = -1;

	for (int i = 1; i <= b.holes(); i++) {
		if (b.beans(s, i) > 0) {
			Board copyBoard(b);
			Side endSide;
			int endHole;

			copyBoard.sow(s, i, endSide, endHole);

			if (endSide == s && copyBoard.beans(s, endHole) == 1 && copyBoard.beans(opponent(s), endHole) > 0) {
				copyBoard.moveToPot(s, endHole, s);
				copyBoard.moveToPot(opponent(s), endHole, s);
			}

			int score = evaluate(copyBoard, s);

			if (bestHole == -1 || score > maxScore) {
				bestHole = i;
				maxScore = score;
			}
		}
	}

	return bestHole;
}

int SmartPlayer::evaluate(const Board& b, Side s) const{
	int score = b.beans(s, 0) - b.beans(opponent(s), 0);

	// Add additional scoring factors based on game strategy
	int capturedSeeds = b.beans(s, 0) - b.beansInPlay(s);
	int opponentCapturedSeeds = b.beans(opponent(s), 0) - b.beansInPlay(opponent(s));
	score += capturedSeeds - opponentCapturedSeeds;

	// Prioritize capturing opponent's seeds when possible
	if (opponentCapturedSeeds > 0 && capturedSeeds == 0)
		score -= 5;

	// Avoid leaving empty holes on the player's side
	for (int i = 1; i <= b.holes(); i++) {
		if (b.beans(s, i) == 0 && b.beans(opponent(s), i) > 0)
			score -= 2;
	}

	return score;
}

