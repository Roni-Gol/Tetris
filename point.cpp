#include "point.h"

#include <iostream>


const Point Point::EMPTY_POINT = Point(-1, -1, GameConfig::COLORS[(int)GameConfig::eColors::BLACK]);

void Point::draw(int color, int playerDiff, bool isBomb) const
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	gotoxy(x + GameConfig::MIN_X + playerDiff, y + GameConfig::MIN_Y);
	if (!isBomb)
		std::cout << ' ';
	else
		std::cout << '*';
}

bool Point::operator==(const Point& other) const
{
	bool res = (x == other.x && y == other.y);
	return res;
}


