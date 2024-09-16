#include "gameConfig.h"

#include <iostream>
#include <Windows.h>


const int GameConfig::COLORS[] = {
	FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED, //black
	BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY, //white
	BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY, //yellow
	BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY | BACKGROUND_INTENSITY, //light blue
	BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_INTENSITY | BACKGROUND_INTENSITY, //pink
	BACKGROUND_BLUE | BACKGROUND_INTENSITY, //blue
	BACKGROUND_RED | BACKGROUND_INTENSITY, //red
	BACKGROUND_RED | BACKGROUND_GREEN, //orange
	BACKGROUND_GREEN | BACKGROUND_INTENSITY //green
};

void GameConfig::printInstructions()
{
	clrscr();

	std::cout << "Players, welcome to Tetris!" << std::endl <<
		"Here are the rules for the game:" << std::endl <<
		"The game begins with an empty grid for each of you." << std::endl <<
		"The tetriminos will descend from the top of the screen." << std::endl <<
		"You can move them horizontally, rotate them, or accelerate their descent." << std::endl <<
		"The goal is to strategically place Tetriminos to create solid horizontal lines without any gaps." << std::endl <<
		"When you complete a horizontal line, it will disappear from your grid." << std::endl <<
		"The game concludes when one player loses by reaching the top of their grid." << std::endl <<
		"Good luck!" << std::endl << std::endl <<
		"For Left Player:" << std::endl <<
		"\'a\' or \'A' - Moves a Tetramino to the left." << std::endl <<
		"\'d\' or \'D\' - Moves a Tetramino to the right." << std::endl <<
		"\'x\' or \'X\' - Drops the Tetramino." << std::endl <<
		"\'s\' or \'S\' - Rotates Tetramino clockwise." << std::endl <<
		"\'w\' or \'W\' - Rotates Tetramino counterclockwise." << std::endl << std::endl <<
		"For Right Player:" << std::endl <<
		"\'j\' or \'J\' - Moves a Tetramino to the left." << std::endl <<
		"\'l\' or \'L\' - Moves a Tetramino to the right." << std::endl <<
		"\'m\' or \'M\' - Drops the Tetramino." << std::endl <<
		"\'k\' or \'K\' - Rotates Tetramino clockwise." << std::endl <<
		"\'i\' or \'I\' - Rotates Tetramino counterclockwise." << std::endl;
	std::cout << std::endl << std::endl;
}

const int GameConfig::NUM_OF_COLORS = sizeof(COLORS) / sizeof(int);

bool GameConfig::isInEnumLeft(int key)
{
	return   (int)eKeysLeftP::LEFT == key ||
		(int)eKeysLeftP::LEFT_UC == key ||
		(int)eKeysLeftP::RIGHT == key ||
		(int)eKeysLeftP::RIGHT_UC == key ||
		(int)eKeysLeftP::ROTATE_CW == key ||
		(int)eKeysLeftP::ROTATE_CW_UC == key ||
		(int)eKeysLeftP::ROTATE_COUNTER_CW == key ||
		(int)eKeysLeftP::ROTATE_COUNTER_CW_UC == key ||
		(int)eKeysLeftP::DROP == key ||
		(int)eKeysLeftP::DROP_UC == key ||
		ESC == key;
}

bool GameConfig::isInEnumRight(int key)
{
	return   (int)eKeysRightP::LEFT == key ||
		(int)eKeysRightP::LEFT_UC == key ||
		(int)eKeysRightP::RIGHT == key ||
		(int)eKeysRightP::RIGHT_UC == key ||
		(int)eKeysRightP::ROTATE_CW == key ||
		(int)eKeysRightP::ROTATE_CW_UC == key ||
		(int)eKeysRightP::ROTATE_COUNTER_CW == key ||
		(int)eKeysRightP::ROTATE_COUNTER_CW_UC == key ||
		(int)eKeysRightP::DROP == key ||
		(int)eKeysRightP::DROP_UC == key ||
		ESC == key;
}
