#include "computer.h"
#include <conio.h> 


int Computer::countMiss = 0;

Computer::Computer(int player, bool withColors)
	:User(player, withColors)
{
}

void Computer::calculateComputerMove()
{
	Route currRoute;
	Shape temp;
	bestRoute = Route(0, 0, 44, 0, 0, 0, 0);
	int numOfRotations = getNumOfRotations();

	for (int rotation = 0; rotation < numOfRotations; ++rotation)
	{
		if (rotation != 0)
			getCurrShape().rotateClockwise();

		for (int col = GameConfig::GAME_WIDTH - 1; col >= 0; --col)
		{
			for (int row = 0; row < GameConfig::GAME_HEIGHT; ++row)
			{
				if (row + 1 == GameConfig::GAME_HEIGHT || boardArr[row + 1][col].getX() != -1) //lowest point available in col- check move and continue to next col
				{
					temp = getCurrShape();

					getDiff(col, row);
					getCurrShape().updateShape();

					if (checkMove())
					{
						currRoute = Route(countDeletedRows(), countNumOfContacts(), countNumOfHoles(), row, countAddedRows(), rotation, getCurrShape().getDiffX());

						if (currRoute.isBetterRoute(bestRoute))
							bestRoute = currRoute;
					}
					
					setCurrShape(temp);

					row = GameConfig::GAME_HEIGHT; //found lowest point in row check next row.
				}
			}
		}
	}
	getCurrShape() = getTempShape();
}

int Computer::getNumOfRotations() const
{
	switch (currShape.getName())
	{
	case (int)Shape::eShapeName::SQUARE:
	case (int)Shape::eShapeName::BOMB:
		return 1;
	case (int)Shape::eShapeName::S:
	case (int)Shape::eShapeName::Z:
	case (int)Shape::eShapeName::LINE:
		return 2;
	} //else
	return 4;
}

void Computer::getDiff(int x, int y)
{
	Point lowestY = getCurrShape().getHighestPoint();
	int maxX = getCurrShape().getBiggestX();

	int diffX = x - maxX;
	int diffY = y - lowestY.getY();

	getCurrShape().setDiffX(diffX);
	getCurrShape().setDiffY(diffY);
}

int Computer::countAddedRows() const
{
	int addedRows = 0;
	int i, j;

	int minY = currShape.getLowestPoint().getY();

	int maxY = currShape.getHighestPoint().getY();

	for (i = minY; i <= maxY; ++i)
	{
		for (j = 0; j < GameConfig::GAME_WIDTH; ++j)
		{
			if (boardArr[i][j].getX() != -1)
				break; //not a new row
		}
		if (j == GameConfig::GAME_WIDTH)
		{
			addedRows = maxY - i + 1;
			break;
		}
	}
	return addedRows;
}

int Computer::countDeletedRows() const
{
	int count = 0;

	int minY = currShape.getLowestPoint().getY();

	int maxY = currShape.getHighestPoint().getY();

	for (int i = minY; i <= maxY; ++i)
	{
		if (isFullRow(i))
			++count;
	}
	return count;
}

int Computer::countNumOfContacts() const
{
	int counter = 0;
	int x, y;

	for (int i = 0; i < GameConfig::SHAPE_SIZE; ++i)
	{
		x = currShape.getPointFromShapeArr(i).getX();
		y = currShape.getPointFromShapeArr(i).getY();

		if (x == GameConfig::GAME_WIDTH - 1 || boardArr[y][x + 1].getX() != -1)
			++counter;
		if (x == 0 || boardArr[y][x - 1].getX() != -1)
			++counter;
		if (y == GameConfig::GAME_HEIGHT - 1 || boardArr[y + 1][x].getX() != -1)
			++counter;
	}
	return counter;
}

int Computer::countNumOfHoles() const
{
	int countHoles = 0;
	int i, j;
	bool isEmpty = true;

	int minY = currShape.getLowestPoint().getY();

	int maxY = currShape.getHighestPoint().getY();

	for (i = minY; i <= maxY; ++i)
	{
		for (j = 0; j < GameConfig::GAME_WIDTH; ++j)
		{
			if (boardArr[i][j].getX() == -1)
			{
				for (int k = 0; k < GameConfig::SHAPE_SIZE; ++k)
					if (currShape.getPointFromShapeArr(k) == boardArr[i][j])
						isEmpty = false;

				if (isEmpty)
					++countHoles;
			}
			isEmpty = true;
		}
	}
	return countHoles;
}

int Computer::getKey(int round)
{
	if (round == 19)
	{

		int key = 0;
		int rotations = bestRoute.getRotations();
		int diff = bestRoute.getNumOfSteps();
		int down = bestRoute.getGoDown();

		int keyPressed = 0;

		if (_kbhit())
		{
			if (_getch() == GameConfig::ESC)
				return GameConfig::ESC;
		}

		if (down > 0)
		{
			bestRoute.setGoDown(down - 1);
			return key;
		}

		else if (rotations > 0)
		{
			key = (int)GameConfig::eKeysLeftP::ROTATE_CW;
			bestRoute.setRotations(rotations - 1);
		}

		else if (diff > 0)
		{
			key = (int)GameConfig::eKeysLeftP::RIGHT;
			bestRoute.setNumOfSteps(diff - 1);
		}

		else if (diff < 0)
		{
			key = (int)GameConfig::eKeysLeftP::LEFT;
			bestRoute.setNumOfSteps(diff + 1);
		}

		return key;
	}
	else
		return 0;
}

void Computer::createShape(bool withColors)
{
	User::createShape(withColors);
	tempShape = currShape;

	if (countMiss == level)
		countMiss = 0;
	else
	{
		calculateComputerMove();
		++countMiss;
	}
}

bool Computer::move()
{
	if (checkMove())
	{
		if (isFinalLocation())
		{
			updateBoard();
			checkFullRow();

			if (reachedMaxHeight()) //checks if the board is full and the player lost
				return true;

			createShape(getWithColors());

			if (reachedMaxHeight()) //checks if the board is full and the player lost
				return true;
		}
		else
			moveShape();
	}
	else
		currShape = tempShape;

	return false;
}

bool Computer::checkMove() //checks if the wanted move is possible (checks down, right, left)
{
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if (getPointFromCurrShapeArr(i).getX() < 0 || getPointFromCurrShapeArr(i).getX() >= GameConfig::GAME_WIDTH) //wants to move out of boarder
			return false;

		if (getPointFromCurrShapeArr(i).getY() >= GameConfig::GAME_HEIGHT)
			return false;

		if (boardArr[getPointFromCurrShapeArr(i).getY()][getPointFromCurrShapeArr(i).getX()].getX() != -1)
			currShape = tempShape;
	}
	return true;
}

void Computer::getLevel(const char* playerSide)
{
	std::cout << "Choose " << playerSide << " computer level:" << std::endl << "(a) BEST" << std::endl << "(b) GOOD" << std::endl << "(c) NOVICE";

	switch (_getch())
	{
	case 'a':
		level = (int)GameConfig::eComputerLevels::BEST;
	case 'b':
		level = (int)GameConfig::eComputerLevels::GOOD;
	case 'c':
		level = (int)GameConfig::eComputerLevels::NOVICE;
	}
	clrscr();
}
