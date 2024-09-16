#include "player.h"
#include "game.h"

#include <conio.h> 
#include <Windows.h>


Player::Player(int player, bool withColors)
	:User(player, withColors)
{
}

int Player::getKey(int round)
{
	int keyPressed = 0;
	if (_kbhit())
	{
		keyPressed = _getch();

		if (getPlayerDiff() == (int)GameConfig::ePlayerStartingPoint::L_PLAYER_START)
		{
			if (!(GameConfig::isInEnumLeft(keyPressed)))
				keyPressed = 0;
			else
				return keyPressed;
		}
		else //(getPlayerDiff() == (int)GameConfig::ePlayerStartingPoint::R_PLAYER_START)
		{
			if (!(GameConfig::isInEnumRight(keyPressed)))
				keyPressed = 0;
			else
				return keyPressed;
		}
	}
}

bool Player::move()
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

bool Player::checkMove() //checks if the wanted move is possible (checks down, right, left)
{
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if (getPointFromCurrShapeArr(i).getX() < 0 || getPointFromCurrShapeArr(i).getX() >= GameConfig::GAME_WIDTH) //wants to move out of boarder
		{
			currShape = tempShape;
			setDefault();
			currShape.updateShape();
			return true;
		}

		if (getPointFromCurrShapeArr(i).getY() >= GameConfig::GAME_HEIGHT)
			return false;

		if (boardArr[getPointFromCurrShapeArr(i).getY()][getPointFromCurrShapeArr(i).getX()].getX() != -1)
			currShape = tempShape;
	}
	return true;
}