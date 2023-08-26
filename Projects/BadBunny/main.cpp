#include "Arena.h"
#include "History.h"
#include "globals.h"
#include "Game.h"
#include <iostream>
using namespace std;

int main()
{
	Game g = Game(5, 5, 5);
	g.play();
}