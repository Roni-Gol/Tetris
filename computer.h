#ifndef __COMPUTER_H
#define __COMPUTER_H

#include "user.h"
#include "point.h"
#include "gameConfig.h"
#include "shape.h"
#include "general.h"
#include "route.h"


class Computer : public User
{
	Route bestRoute;

	int level;

	static int countMiss;

	int countAddedRows() const;

	int countDeletedRows() const;

	int countNumOfContacts() const;

	int countNumOfHoles() const;

	void calculateComputerMove();

	void getDiff(int x, int y);

public:
	void setLevel(int _level) { level = _level; }

	Computer(int player, bool withColors);

	int getKey(int round);

	virtual bool move();

	virtual void createShape(bool withColors);

	bool checkMove(); //checks if the wanted move is possible (checks down, right, left)

	int getNumOfRotations()const;

	void getLevel(const char* playerSide);
};
#endif