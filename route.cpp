#include "route.h"


Route::Route(int _deletedRows, int _numOfContacts, int _numOfHoles, int _destinationRow, int _addedRows, int _rotations, int _numOfSteps)
{
	deletedRows = _deletedRows;
	numOfContacts = _numOfContacts;
	numOfHoles = _numOfHoles;
	destinationRow = _destinationRow;
	addedRows = _addedRows;
	rotations = _rotations;
	numOfSteps = _numOfSteps;
}

bool Route::isBetterRoute(const Route& bestRoute) const
{
	if (deletedRows > bestRoute.deletedRows)
		return true;
	else if (deletedRows < bestRoute.deletedRows)
		return false;
	if (destinationRow >= bestRoute.destinationRow)
	{

		if (numOfContacts >= bestRoute.numOfContacts && numOfHoles <= bestRoute.numOfHoles)
			return true;
		if (addedRows < bestRoute.addedRows && (numOfContacts >= bestRoute.numOfContacts || numOfHoles <= bestRoute.numOfHoles))
			return true;
	}
	return false;
}
