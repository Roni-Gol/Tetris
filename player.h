#ifndef __PLAYER_H
#define __PLAYER_H

#include "user.h"
#include "point.h"
#include "gameConfig.h"
#include "shape.h"
#include "general.h"


class Player : public User
{

public:
	Player(int player, bool withColors);

	int getKey(int round);

	virtual bool move();

	bool checkMove();

	void getLevel(const char* playerSide) {}
};
#endif