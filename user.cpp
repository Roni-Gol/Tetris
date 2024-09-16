#include "user.h"


User::User(int player, bool withColors) :score(0)
{
	if (player == (int)GameConfig::ePlayer::L_PLAYER)
		playerDiff = (int)GameConfig::ePlayerStartingPoint::L_PLAYER_START;
	else if (player == (int)GameConfig::ePlayer::R_PLAYER)
		playerDiff = (int)GameConfig::ePlayerStartingPoint::R_PLAYER_START;

	this->withColors = withColors;

	initializeBoard();
}

void User::createShape(bool withColors)
{
	int color, shapeType;
	shapeType = rand() % GameConfig::NUM_OF_SHAPES;

	if (rand() % 100 < 5)  // 5% of the time, set shapeType to bomb
	{
		shapeType = (int)Shape::eShapeName::BOMB;
		currShape.setIsBomb(true);
	}
	else
		currShape.setIsBomb(false);

	if (withColors)
		color = rand() % (GameConfig::NUM_OF_COLORS - 2) + 2; //skip black and white
	else
		color = (int)GameConfig::eColors::WHITE;

	currShape.setName(shapeType);

	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++) //set the shape's array
	{
		setCurrShapeArr(i, Shape::getPointFromShapeTypesArr(shapeType, i));
		setCurrShapeColor(i, color);
		getPointFromCurrShapeArr(i).draw(getPointFromCurrShapeArr(i).getColor(), playerDiff, currShape.getIsBomb());
	}
}

void User::moveShape() //makes the move according to the diff desired from the game move
{
	int i;
	bool isBomb = currShape.getIsBomb();

	for (i = 0; i < GameConfig::SHAPE_SIZE; i++)
		getPointFromTempShapeArr(i).draw((int)GameConfig::COLORS[(int)GameConfig::eColors::BLACK], playerDiff); //deletes previous shape (it is always saved in temp)

	for (i = 0; i < GameConfig::SHAPE_SIZE; i++)
		getPointFromCurrShapeArr(i).draw(getPointFromCurrShapeArr(i).getColor(), playerDiff, isBomb);
}

void User::insertShapeToBoard()
{

	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		boardArr[getPointFromCurrShapeArr(i).getY()][getPointFromCurrShapeArr(i).getX()].setX(getPointFromCurrShapeArr(i).getX());
		boardArr[getPointFromCurrShapeArr(i).getY()][getPointFromCurrShapeArr(i).getX()].setY(getPointFromCurrShapeArr(i).getY());
		boardArr[getPointFromCurrShapeArr(i).getY()][getPointFromCurrShapeArr(i).getX()].setColor(getPointFromCurrShapeArr(i).getColor());
	}
}

void User::checkFullRow()
{
	int minY = currShape.getLowestPoint().getY();

	int maxY = currShape.getHighestPoint().getY();

	for (int i = minY; i <= maxY; i++)
	{
		if (isFullRow(i))
			clearRow(i);
	}
}

bool User::isFullRow(int row) const
{
	bool notShape = true;
	for (int i = 0; i < GameConfig::GAME_WIDTH; ++i)
	{
		if (boardArr[row][i].getX() == -1)
		{
			for (int j = 0; j < GameConfig::SHAPE_SIZE; ++j)
			{
				if (currShape.getPointFromShapeArr(j) == boardArr[row][i])
					notShape = false;
			}
			if (notShape)
				return false; //it's not a full row
		}
	}
	return true;
}

void User::clearRow(int row)
{
	for (int i = row; i > 0; i--)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
		{
			boardArr[i][j] = boardArr[i - 1][j];
			Point temp(j, i);
			temp.draw(boardArr[i][j].getColor(), playerDiff, currShape.getIsBomb());
		}
	}

	for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
	{
		boardArr[0][j] = Point(-1, -1, (int)GameConfig::COLORS[0]);
		boardArr[0][j].draw((int)GameConfig::eColors::BLACK, playerDiff, currShape.getIsBomb());
	}
}

void User::setDefault()
{
	currShape.setDiffX(0);
	currShape.setDiffY(1);
}

bool User::reachedMaxHeight()
{
	for (int i = 0; i < GameConfig::GAME_WIDTH; i++)
		if (boardArr[0][i].getX() != -1)
			return true;

	return false;
}

int User::getDiffForDrop() const
{
	int diff = 0, diffMin = GameConfig::GAME_HEIGHT - 1;

	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		while (boardArr[getPointFromCurrShapeArr(i).getY() + diff][getPointFromCurrShapeArr(i).getX()] == Point(-1, -1) && getPointFromCurrShapeArr(i).getY() + diff < GameConfig::GAME_HEIGHT)
			diff++;

		if (diff < diffMin)
			diffMin = diff;

		diff = 0;
	}
	return diffMin;
}

void User::setMove(char key)
{
	switch (key)
	{
	case (int)GameConfig::eKeysLeftP::LEFT:
	case (int)GameConfig::eKeysLeftP::LEFT_UC:
	case (int)GameConfig::eKeysRightP::LEFT:
	case (int)GameConfig::eKeysRightP::LEFT_UC:
		currShape.setDiffX(-1);
		currShape.setDiffY(0);
		currShape.updateShape();
		break;

	case (int)GameConfig::eKeysLeftP::RIGHT:
	case (int)GameConfig::eKeysLeftP::RIGHT_UC:
	case (int)GameConfig::eKeysRightP::RIGHT:
	case (int)GameConfig::eKeysRightP::RIGHT_UC:
		currShape.setDiffX(1);
		currShape.setDiffY(0);
		currShape.updateShape();
		break;

	case (int)GameConfig::eKeysLeftP::DROP:
	case (int)GameConfig::eKeysLeftP::DROP_UC:
	case (int)GameConfig::eKeysRightP::DROP:
	case (int)GameConfig::eKeysRightP::DROP_UC:
		currShape.setDiffX(0);
		currShape.setDiffY(getDiffForDrop() - 1);
		currShape.updateShape();
		break;

	case (int)GameConfig::eKeysLeftP::ROTATE_CW:
	case (int)GameConfig::eKeysLeftP::ROTATE_CW_UC:
	case (int)GameConfig::eKeysRightP::ROTATE_CW:
	case (int)GameConfig::eKeysRightP::ROTATE_CW_UC:
		currShape.setDiffX(0);
		currShape.setDiffY(0);
		currShape.rotateClockwise();
		break;

	case (int)GameConfig::eKeysLeftP::ROTATE_COUNTER_CW:
	case (int)GameConfig::eKeysLeftP::ROTATE_COUNTER_CW_UC:
	case (int)GameConfig::eKeysRightP::ROTATE_COUNTER_CW:
	case (int)GameConfig::eKeysRightP::ROTATE_COUNTER_CW_UC:
		currShape.setDiffX(0);
		currShape.setDiffY(0);
		currShape.rotateCounterClockwise();
		break;

	case 0: //no key pressed, needs to go down
		currShape.updateShape();
	}
}

bool User::isFinalLocation()
{
	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
	{
		if (getPointFromCurrShapeArr(i).getY() >= GameConfig::GAME_HEIGHT - 1)
			return true;
		else if (boardArr[getPointFromCurrShapeArr(i).getY() + 1][getPointFromCurrShapeArr(i).getX()].getX() != -1)
			return true;
	}
	return false;
}

void User::initializeBoard()
{
	for (int i = 0; i < GameConfig::GAME_HEIGHT; ++i)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH; ++j)
			boardArr[i][j] = Point::EMPTY_POINT;
	}
}

void User::printBoard()
{
	for (int i = 0; i < GameConfig::GAME_HEIGHT; i++)
	{
		for (int j = 0; j < GameConfig::GAME_WIDTH; j++)
		{
			if (boardArr[i][j].getX() != -1 && boardArr[i][j].getY() != -1)
				boardArr[i][j].draw(boardArr[i][j].getColor(), playerDiff);
		}
	}
}

void User::updateBoard()
{
	if (currShape.getName() == (int)Shape::eShapeName::BOMB)
		boom();
	else
	{
		insertShapeToBoard();
		moveShape();
	}
}

void User::boom()
{
	for (int i = currShape.getLowestPoint().getY() - GameConfig::BOMB_DISTANCE; i < currShape.getHighestPoint().getY() + GameConfig::BOMB_DISTANCE; ++i)
	{
		for (int j = currShape.getSmallestX() - GameConfig::BOMB_DISTANCE; j < currShape.getBiggestX() + GameConfig::BOMB_DISTANCE; ++j)
		{
			if (i >= 0 && i < GameConfig::GAME_HEIGHT && j >= 0 && j < GameConfig::GAME_WIDTH)
			{
				boardArr[i][j] = Point::EMPTY_POINT;
				Point(j, i).draw(GameConfig::COLORS[(int)GameConfig::eColors::BLACK], playerDiff, false);
			}
		}
	}

	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		getPointFromTempShapeArr(i).draw((int)GameConfig::COLORS[(int)GameConfig::eColors::BLACK], playerDiff); //deletes previous shape (it is always saved in temp)

	for (int i = 0; i < GameConfig::SHAPE_SIZE; i++)
		getPointFromCurrShapeArr(i).draw((int)GameConfig::COLORS[(int)GameConfig::eColors::BLACK], playerDiff, false);

	int minY = currShape.getLowestPoint().getY() - GameConfig::BOMB_DISTANCE; 
	if (minY < 0)
		minY = 0;

	int maxY = currShape.getHighestPoint().getY() + GameConfig::BOMB_DISTANCE;
	if (maxY > GameConfig::GAME_HEIGHT - 1)
		maxY = GameConfig::GAME_HEIGHT - 1;

	int minX = currShape.getSmallestX() - GameConfig::BOMB_DISTANCE;
	if (minX < 0)
		minX = 0;

	int maxX = currShape.getBiggestX() + GameConfig::BOMB_DISTANCE;
	if (maxX > GameConfig::GAME_WIDTH - 1)
		maxX = GameConfig::GAME_WIDTH - 1;

	shiftDownBoard(maxY - minY + 1, minY, minX, maxX); 

}

void User::shiftDownBoard(int shift, int minY, int minX, int maxX) 
{
	for (int i = minY - 1; i >= 0; --i)
	{
		for (int j = minX; j <= maxX; ++j)
		{
			if (i >= 0 && i < GameConfig::GAME_HEIGHT && j >= 0 && j < GameConfig::GAME_WIDTH)
			{
				boardArr[i + shift][j] = boardArr[i][j];
				if (boardArr[i + shift][j].getX() != -1)
					boardArr[i + shift][j].setY(i + shift);
				boardArr[i][j] = Point::EMPTY_POINT;
				Point(j, i).draw((int)GameConfig::COLORS[(int)GameConfig::eColors::BLACK], playerDiff);
				Point(j, i + shift).draw(boardArr[i + shift][j].getColor(), playerDiff);
			}
		}
	}
}
