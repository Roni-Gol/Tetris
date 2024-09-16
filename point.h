#ifndef __POINT_H
#define __POINT_H

#include "gameConfig.h"
#include "general.h"

#include <iostream>
#include <Windows.h>


class Point
{
	int x;
	int y;
	int color;

public:

	static const Point EMPTY_POINT;

	Point() :x(0), y(0), color(GameConfig::COLORS[0]) {}

	Point(int x, int y, int color = GameConfig::COLORS[0]) :x(x), y(y), color(color) {}

	Point(const Point& other) : x(other.x), y(other.y), color(other.color) {}

	int getX() const { return x; }

	int getY() const { return y; }

	int getColor() const { return color; }

	void setX(int _x) { x = _x; }

	void setY(int _y) { y = _y; }

	void setColor(int _color) { color = _color; }

	void draw(int color = (int)GameConfig::eColors::BLACK, int playerDiff = 0, bool isBomb = false) const;

	bool operator==(const Point& other) const;
};
#endif 