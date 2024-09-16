#ifndef __SHAPE_H
#define __SHAPE_H

#include "point.h"
#include "gameConfig.h"


class Shape
{
	int diffX = 0;
	int diffY = 1;

	int name;

	bool isBomb = false;

	static const Point shapeTypesArr[8][4];

	mutable Point shapeArr[GameConfig::SHAPE_SIZE] = { Point() };

public:
	enum class eShapeName { SQUARE, LINE, T, L, J, S, Z, BOMB };

	Shape() : name(GameConfig::NO_VAL) {}

	Shape(int newName) : name(newName) {}

	int getDiffX() const { return diffX; }

	int getDiffY() const { return diffY; }

	int getName() const { return name; }

	static Point getPointFromShapeTypesArr(int x, int y) { return shapeTypesArr[x][y]; }

	Point& getPointFromShapeArr(int index) const { return shapeArr[index]; }

	void setDiffX(int _diffX) { diffX = _diffX; }

	void setDiffY(int _diffY) { diffY = _diffY; }

	void setName(int _name) { name = _name; }

	void setPointInShapeArr(int index, Point p) { shapeArr[index] = p; }

	void updateShape();

	void rotateClockwise();

	void rotateCounterClockwise();

	Point getHighestPoint() const;

	Point getLowestPoint() const;

	int getBiggestX() const;

	int getSmallestX() const;

	bool getIsBomb()const { return isBomb; }

	void setIsBomb(bool _isBomb) { isBomb = _isBomb; }
};
#endif