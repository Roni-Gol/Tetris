#ifndef __USER_H
#define __USER_H

#include "point.h"
#include "gameConfig.h"
#include "shape.h"
#include "general.h"


class User
{
	int playerDiff;

	bool withColors;

	int score;

protected:

	Shape currShape, tempShape;

	Point boardArr[GameConfig::GAME_HEIGHT][GameConfig::GAME_WIDTH] = { Point(-1,-1, (int)GameConfig::eColors::BLACK) };

public:
	User(int player, bool withColors);

	virtual int getKey(int round) = 0;

	int getPlayerDiff() const { return playerDiff; }

	bool getWithColors() const { return withColors; }

	Point& getPointFromCurrShapeArr(int index) const { return currShape.getPointFromShapeArr(index); }

	Point& getPointFromTempShapeArr(int index) const { return tempShape.getPointFromShapeArr(index); }

	int getScore() const { return score; }

	Shape& getCurrShape() { return currShape; }

	Shape& getTempShape() { return tempShape; }

	void setCurrShape(Shape& other) { currShape = other; }

	void setTempShape(Shape& other) { tempShape = other; }

	void setPlayerDiff(int _playerDiff) { playerDiff = _playerDiff; }

	void setScore() { score += 1; }

	void setCurrShapeArr(int index, Point p) { currShape.setPointInShapeArr(index, p); }

	void setCurrShapeColor(int index, int color) { currShape.getPointFromShapeArr(index).setColor(GameConfig::COLORS[color]); }

	void saveShape() { tempShape = currShape; }

	virtual void createShape(bool withColors);

	void moveShape();

	void updateBoard();

	void insertShapeToBoard();

	virtual bool checkMove() = 0;

	void checkFullRow();

	bool isFullRow(int row) const;

	void clearRow(int row);

	virtual bool move() = 0;

	bool reachedMaxHeight();

	int getDiffForDrop() const;

	void setMove(char key);

	bool isFinalLocation();

	void setDefault();

	void initializeBoard();

	void printBoard();

	virtual void setLevel(int _level) {};

	virtual void getLevel(const char* playerSide) = 0;

	void boom();

	void shiftDownBoard(int shift, int minY, int minX, int maxX); 
};
#endif
