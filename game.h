#ifndef __GAME_H
#define __GAME_H

#include "point.h"
#include "gameConfig.h"
#include "shape.h"
#include "user.h"
#include "player.h"
#include "general.h"
#include "computer.h"


class Game
{
	User* leftP = nullptr;
	User* rightP = nullptr;

	void exitGame();

	void continueGame();

	bool getKeyAndSetMove();

	bool checkIfLost(bool leftPLost, bool rightPLost);

	void init(bool withColors, int players);

	int run(bool withColors, int players);

	void drawBorder(int playerDiff);

	int pauseMenu(bool inGame);

	bool checkGetKeyPressed(int keyPressed);

public:
	void menu(bool firstRound = false);

	~Game() 
	{
		delete leftP;
		delete rightP;
	}
};
#endif