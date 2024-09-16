#include "shape.h"

#include <cstdlib>
#include <ctime>


const Point Shape::shapeTypesArr[8][4] = { Point(5, 1), Point(6, 1),Point(5, 0), Point(6, 0),  //Square
		Point(5, 3), Point(5, 2), Point(5, 1), Point(5, 0), //Line
		Point(5, 1), Point(4, 0),Point(5, 0), Point(6, 0),  //T
		Point(5, 2) , Point(6, 2), Point(5, 1) , Point(5, 0) , //L
		Point(5, 2), Point(6, 2), Point(6, 1),Point(6, 0),  //J
		Point(5, 1), Point(6, 1), Point(4, 0), Point(5, 0),  //Z 
		Point(5, 1), Point(6, 1), Point(5, 0), Point(4, 0),  //S 
		Point(5, 1), Point(6, 1),Point(5, 0), Point(6, 0)  //Bomb
};

void Shape::updateShape()
{
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		int newX = shapeArr[i].getX() + diffX;
		shapeArr[i].setX(newX);

		int newY = shapeArr[i].getY() + diffY;
		shapeArr[i].setY(newY);
	}
}

void Shape::rotateClockwise()
{
	if (name == (int)Shape::eShapeName::SQUARE)
		return;

	int centerX = shapeArr[0].getX(); //finds the center of the shape
	int centerY = shapeArr[0].getY();

	for (int i = 0; i < GameConfig::SHAPE_SIZE; ++i) //rotates each point around the center
	{
		int tempX = shapeArr[i].getX() - centerX;
		int tempY = shapeArr[i].getY() - centerY;

		shapeArr[i].setX(centerX + tempY); //rotates the point clockwise
		shapeArr[i].setY(centerY - tempX);
	}
}

void Shape::rotateCounterClockwise()
{
	if (name == (int)Shape::eShapeName::SQUARE)
		return;

	int centerX = shapeArr[0].getX(); //finds the center of the shape
	int centerY = shapeArr[0].getY();

	for (int i = 0; i < GameConfig::SHAPE_SIZE; ++i) //rotates each point around the cente
	{
		int tempX = shapeArr[i].getX() - centerX;
		int tempY = shapeArr[i].getY() - centerY;

		shapeArr[i].setX(centerX - tempY); //rotates the point counterclockwise
		shapeArr[i].setY(centerY + tempX);
	}
}

Point Shape::getHighestPoint() const
{
	Point maxP = shapeArr[0];

	for (int i = 1; i < GameConfig::SHAPE_SIZE; ++i)
	{
		if (shapeArr[i].getY() > maxP.getY())
			maxP = shapeArr[i];
	}

	return maxP;
}

Point Shape::getLowestPoint() const
{
	Point minP = shapeArr[0];

	for (int i = 1; i < GameConfig::SHAPE_SIZE; ++i)
	{
		if (shapeArr[i].getY() < minP.getY())
			minP = shapeArr[i];
	}

	return minP;
}

int Shape::getBiggestX() const
{
	Point maxX = shapeArr[0];

	for (int i = 1; i < GameConfig::SHAPE_SIZE; ++i)
	{
		if (shapeArr[i].getX() > maxX.getX())
			maxX = shapeArr[i];
	}

	return maxX.getX();
}

int Shape::getSmallestX() const
{
	Point minX = shapeArr[0];

	for (int i = 1; i < GameConfig::SHAPE_SIZE; ++i)
	{
		if (shapeArr[i].getX() < minX.getX())
			minX = shapeArr[i];
	}

	return minX.getX();
}

