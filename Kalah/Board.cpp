#include "Board.h"
#include <iostream>

/*Construct a Board with the indicated number of holes per side(not counting the pot) and initial number of beans per hole.If nHoles is
not positive, act as if it were 1; if nInitialBeansPerHole is negative, act as if it were 0.*/
Board::Board(int nHoles, int nInitialBeansPerHole):m_numHoles(nHoles + 1),m_beansPerHole(nInitialBeansPerHole) {
	if (nHoles < 1) {
		m_numHoles = 1;
	}
	if (nInitialBeansPerHole < 0) {
		m_beansPerHole = 0;
	}

	//intialize vectors
	initVector(nInitialBeansPerHole, northSide);
	initVector(nInitialBeansPerHole, southSide);

	//totalbeans
	m_totalBeans += 2 * (nInitialBeansPerHole * nHoles);
}

//Return the number of holes on a side(not counting the pot).
int Board::holes() const {
	return m_numHoles - 1;
}

//Return the number of beans in the indicated hole or pot, or -1 if the hole number is invalid.
int Board::beans(Side s, int hole) const {
	
    if (hole < 1 && hole > m_numHoles && hole != 0) {
        return -1;
    }
	//if north
	if (s == NORTH) {
		for (int i = 0; i < hole + 1; i++) {
			//if at hole, return beans
			if (i == hole)
				return northSide[i];
	
		}
	}
	//if south
	if (s == SOUTH) {
		for (int i = 0; i < hole + 1; i++) {
			if (i == hole)
				return southSide[i];
			
		}
	}

	return -1;

}

//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const {

	int beans = 0;

	//if north
	if (s == NORTH) {
		for (int i = 1; i < m_numHoles; i++) {
			beans += northSide[i];
		}
    }//south
    else {
        for (int i = 1; i < m_numHoles; i++) {
            beans += southSide[i];
        }
    }
	
	return beans;

}

//Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const {
	return m_totalBeans;
}

/*If the hole indicated by(s, hole) is empty or invalid or a pot, this function returns false without changing anything.Otherwise, it will
return true after sowing the beans : the beans are removed from hole(s, hole) and sown counterclockwise, including s's pot if
encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the
last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about
these issues, so dealing with them should not be the responsibility of the Board class.)*/
bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {

    // invalid hole
    if (s != NORTH && s != SOUTH) {
        return false;
    }
    if (hole < 1 || hole > m_numHoles || hole == POT) {
        return false;
    }
    if (s == SOUTH) {
        if (southSide[hole] < 1)
            return false;
    }
    else if (s == NORTH) {
        if (northSide[hole] < 1)
            return false;
    }

    // sowing
    int currentHole = hole;
    Side currentSide = s;

    // South's Turn
    if (s == SOUTH) {
        // take all beans from hole
        int beanCounter = southSide[hole];
        southSide[hole] = 0;

        while (beanCounter > 0) {
            // passing the pot
            if (currentHole == 0) {
                currentSide = NORTH;
                currentHole = m_numHoles;
            }
            // current side is south
            if (currentSide == SOUTH) {
                // not right before pot
                if (currentHole < m_numHoles - 1) {
                    currentHole++;
                    southSide[currentHole]++;
                }
                // right before pot
                else {
                    if (s == SOUTH) {
                        currentHole = 0;
                        southSide[0]++;
                    }
                }
            }
            // current side is north
            if (currentSide == NORTH) {
                // not right before pot
                if (currentHole > 1) {
                    currentHole--;
                    northSide[currentHole]++;
                }
                // right before pot
                else {
                    currentSide = SOUTH;
                    southSide[currentHole]++;
                }
            }

            // decrement beans
            beanCounter--;
        }

     
    }

    // North's Turn
    else if (s == NORTH) {
        // take all beans from hole
        int beanCounter = northSide[hole];
        northSide[hole] = 0;

        while (beanCounter > 0) {
            // passing the pot
            if (currentHole == 0) {
                currentSide = SOUTH;
            }
            // current side is south
            if (currentSide == SOUTH) {
                // not right before pot
                if (currentHole < m_numHoles - 1) {
                    currentHole++;
                    southSide[currentHole]++;
                }
                // right before pot
                else {
                    currentSide = NORTH;
                    northSide[currentHole]++;
                }
            }
            // current side is north
            if (currentSide == NORTH) {
                // not right before pot
                if (currentHole > 0) {
                    currentHole--;
                    northSide[currentHole]++;
                }
            }

            // decrement beans
            beanCounter--;
        }
    }

    // ends in pot
    if (currentHole == 0 || currentHole == m_numHoles) {
        currentHole = 0;
    }

    // adjust values
    endHole = currentHole;
    endSide = currentSide;
    return true;
	
}

/*If the indicated hole is invalid or a pot, return false without changing anything.Otherwise, move all the beans in hole(s, hole) into the
pot belonging to potOwner and return true.*/
bool Board::moveToPot(Side s, int hole, Side potOwner) {

	//invalid or pot
	if (hole < 1 || hole > m_numHoles - 1 || hole == POT) {
		return false;
	}
	else {

        if (s == NORTH) {
            if (potOwner == NORTH) {
                northSide[POT] += northSide[hole];
            }
            else {
                southSide[POT] += northSide[hole];
            }
            northSide[hole] = 0;
        }
        else {
            if (potOwner == NORTH) {
                northSide[POT] += southSide[hole];
            }
            else {
                southSide[POT] += southSide[hole];
            }
            southSide[hole] = 0;
        }
	}

	return true;
}

/*If the indicated hole is invalid or beans is negative, this function returns false without changing anything.Otherwise, it will return
true after setting the number of beans in the indicated hole or pot to the value of the third parameter. (This could change what
beansInPlay and totalBeans return if they are called later.) This function exists solely so that we and you can more easily test
your program : None of your code that implements the member functions of any class is allowed to call this function directly or
indirectly. (We'll show an example of its use below.)*/
bool Board::setBeans(Side s, int hole, int beans) {

	//invalid hole or beans
	if (hole < 1 || hole > m_numHoles || beans < 0) {
		return false;
	}

    //store previous beans in hole
    int prev;

	//set number of beans in indicated hole or pot to value of third parameter
	if (s == SOUTH) {
        prev = southSide[hole];
        southSide[hole] = beans;
    }
    else {
        prev = northSide[hole];
        northSide[hole] = beans;
    }

    //adjust total number of beans
    m_totalBeans = m_totalBeans - prev + beans;
	return true;
}


void Board::initVector(int beans, vector<int>& v) {
	//index 0 is pot
	v.push_back(0);

	//push beans into holes
	for (int i = 1; i < m_numHoles; i++) {
		v.push_back(beans);
	}
}