#include <iostream>
#include "Game.h"

//Construct a Game to be played with the indicated players on a copy of the board b.The player on the south side always moves first.
Game::Game(const Board& b, Player* south, Player* north) :m_board(b), m_south(south), m_north(north), current_turn(SOUTH) {

}

//Display the game's board in a manner of your choosing, provided you show the names of the players and a reasonable representation of 
//the state of the board.
void Game::display() const {

    cout << "\t" + m_north->name() << endl;

    cout << "   ";
    for (int i = 1; i <= m_board.holes(); i++) {
        cout << " " + to_string(m_board.beans(NORTH, i)) + " ";
    }
    cout << endl;

    cout << " " + to_string(m_board.beans(NORTH, POT)) + " ";
    for (int i = 1; i <= m_board.holes(); i++) {
        cout << "   ";
    }
    cout << " " + to_string(m_board.beans(SOUTH, POT)) + " ";
    cout << endl;

    cout << "   ";
    for (int i = 1; i <= m_board.holes(); i++) {
        cout << " " + to_string(m_board.beans(SOUTH, i)) + " ";
    }
    cout << endl;

    cout << "\t" + m_south->name() << endl;
}

/*If the game is over(i.e., the move member function has been called and returned false), set over to true; otherwise, set over to false
and do not change anything else.If the game is over, set hasWinner to true if the game has a winner, or false if it resulted in a
tie.If hasWinner is set to false, leave winner unchanged; otherwise, set it to the winning side.*/
void Game::status(bool& over, bool& hasWinner, Side& winner) const {

    //game not over
    if (m_board.beansInPlay(SOUTH) != 0 && m_board.beansInPlay(NORTH) != 0) {
        over = false;
        hasWinner = false;
        return;
    }
    else {

        over = true;

        //check for winner
        int sBeans = m_board.beans(SOUTH, POT);
        int nBeans = m_board.beans(NORTH, POT);

        //south wins
        if (sBeans > nBeans) {
            hasWinner = true;
            winner = SOUTH;
         
        }//north wins
        else if (nBeans > sBeans) {
            hasWinner = true;
            winner = NORTH;
          
        }//draw
        else {
            hasWinner = false;
        }

        return;

    }
        
    
}

/*Attempt to make a complete move for the player playing side s. "Complete" means that the player sows the seeds from a hole and takes
any additional turns required or completes a capture.Whenever the player gets an additional turn, you should display the board so
someone looking at the screen can follow what's happening. If the move can be completed, return true; if not, because the move is
not yet completed but side s has no holes with beans to pick up and sow, sweep any beans in s's opponent's holes into that
opponent's pot and return false.*/
bool Game::move(Side s) {

    int endingHole;
    Side endingSide;

    //south's turn
    if (current_turn == SOUTH) {
        
        //move
        int hole = m_south->chooseMove(m_board, current_turn);
        //computer
        if (!m_south->isInteractive()) {
            cout << m_south->name() + " chooses hole " + to_string(hole) << endl;
        }
        //sow
        if (m_board.sow(current_turn, hole, endingSide, endingHole)) {
            //ends in pot
            if (endingHole == POT) {
                display();

                //another turn if there are beans left on side
                if (m_board.beansInPlay(SOUTH) > 0) {
                    cout << m_south->name() + " goes again." << endl;
                    return move(current_turn);
                }
            }
            else if (endingSide == current_turn) {
                //capture
                if (m_board.beans(current_turn, endingHole) == 1 && m_board.beans(opponent(current_turn), endingHole) > 0 && endingHole != POT) {
                    //move beans from opponent and player's hole to pot
                    m_board.moveToPot(opponent(current_turn), endingHole, current_turn);
                    m_board.moveToPot(current_turn, endingHole, current_turn);

                }
            }
        }
    }//north's turn
    else {
        //move
        int hole = m_north->chooseMove(m_board, current_turn);
        //computer
        if (!m_north->isInteractive()) {
            cout << m_north->name() + " chooses hole " + to_string(hole) << endl;
        }
        //sow
        if (m_board.sow(current_turn, hole, endingSide, endingHole)) {
            //ends in pot
            if (endingHole == POT) {
                display();

                //another turn if there are beans left on side
                if (m_board.beansInPlay(NORTH) > 0) {
                    cout << m_north->name() + " goes again." << endl;
                    return move(current_turn);
                }
            }
            else if (endingSide == current_turn) {
                //capture
                if (m_board.beans(current_turn, endingHole) == 1 && m_board.beans(opponent(current_turn), endingHole) > 0 && endingHole != POT) {
                    //move beans from opponent and player's hole to pot
                    m_board.moveToPot(opponent(current_turn), endingHole, current_turn);
                    m_board.moveToPot(current_turn, endingHole, current_turn);

                }
            }
        }
    }

    //switch turns
    current_turn = opponent(current_turn);

    //game over, move cannot be made so return false
    if (m_board.beansInPlay(NORTH) == 0) {

        display();

        //sweep opponents beans into pot
        cout << "Sweeping " + m_south->name() + " 's beans into pot." << endl;

        for (int i = 1; i <= m_board.holes(); i++) {
            m_board.moveToPot(SOUTH, i, SOUTH);
        }

        return false;
    }
    else if (m_board.beansInPlay(SOUTH) == 0) {

        display();

        cout << "Sweeping " + m_north->name() + " 's beans into pot." << endl;

        for (int i = 1; i <= m_board.holes(); i++) {
            m_board.moveToPot(NORTH, i, NORTH);
        }

        return false;
    }

    return true;
}

/*Play the game.Display the progress of the game in a manner of your choosing, provided that someone looking at the screen can follow
what's happening. If neither player is interactive, then to keep the display from quickly scrolling through the whole game, it
would be reasonable periodically to prompt the viewer to press ENTER to continue and not proceed until ENTER is pressed.
(The ignore function for input streams is useful here.) Announce the winner at the end of the game. You can apportion to your
liking the responsibility for displaying the board between this function and the move function.*/
void Game::play() {
    
    //trackers
    bool gameOver = false;
    bool hasWinner = false;
    Side winner;

    //first display state of game to user
    display();

    //play game until over
    while (!gameOver) {
        move(current_turn);
        display();

        //if neither player is interactive, prompt user
        if (!m_north->isInteractive() && !m_south->isInteractive()) {
            cout << "Press ENTER to continue the game: " << endl;
            cin.ignore(10000, '\n');

        }

        //update status
        status(gameOver, hasWinner, winner);
    }

    //game over
    if (hasWinner) {

        if (winner == SOUTH) {
            cout << "Winner is " + m_south->name() << endl;
        }
        else {
            cout << "Winner is " + m_north->name() << endl;
        }
    }
    else {
        cout << "Game ended in a tie." << endl;
    }

}

/*Return the number of beans in the indicated hole or pot of the game's board, or -1 if the hole number is invalid. This function exists
so that we and you can more easily test your program.*/
int Game::beans(Side s, int hole) const {

    return m_board.beans(s, hole);

}
