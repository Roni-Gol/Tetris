#ifndef __ROUTE_H
#define __ROUTE_H

#include <iostream>
#include "gameConfig.h"

class Route
{
	int deletedRows;
	int numOfContacts;
	int numOfHoles;
	int destinationRow;
	int addedRows;
	int rotations;
	int numOfSteps;
	int goDown = 1;

public:

	Route() {}

	Route(int _deletedRows, int _numOfContacts, int _numOfHoles, int _destinationRow, int _addedRows, int _rotations, int _numOfSteps);

	bool isBetterRoute(const Route& bestRoute) const;

	int getGoDown() const { return goDown; }

	void setGoDown(int _goDown) { goDown = _goDown; }

	int getRotations() const { return rotations; }

	void setRotations(int _rotations) { rotations = _rotations; }

	int getNumOfSteps()const { return numOfSteps; }

	void setNumOfSteps(int _numOfSteps) { numOfSteps = _numOfSteps; }
};
#endif
