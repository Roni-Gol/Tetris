#ifndef __GAME_CONFIG_H
#define __GAME_CONFIG_H

#include "general.h"

#include <windows.h>
#include <iostream>


class GameConfig
{
public:
	enum class eKeysLeftP { LEFT = 'a', LEFT_UC = 'A', RIGHT = 'd', RIGHT_UC = 'D', ROTATE_CW = 's', ROTATE_CW_UC = 'S', ROTATE_COUNTER_CW = 'w', ROTATE_COUNTER_CW_UC = 'W', DROP = 'x', DROP_UC = 'X' };
	enum class eKeysRightP { LEFT = 'j', LEFT_UC = 'J', RIGHT = 'l', RIGHT_UC = 'L', ROTATE_CW = 'k', ROTATE_CW_UC = 'K', ROTATE_COUNTER_CW = 'i', ROTATE_COUNTER_CW_UC = 'I', DROP = 'm', DROP_UC = 'M' };

	static constexpr int ESC = 27;

	enum  class ePlayer { L_PLAYER, R_PLAYER };

	enum class eComputerLevels { BEST = -1, GOOD = 40, NOVICE = 10 };

	static constexpr int NO_VAL = -1;
	static constexpr int SHAPE_SIZE = 4;
	static constexpr int NUM_OF_ROTATIONS = 4;
	static constexpr int NUM_OF_SHAPES = 7;

	static constexpr int GAME_WIDTH = 12;
	static constexpr int GAME_HEIGHT = 18;

	static constexpr int MIN_X = 5;
	static constexpr int MIN_Y = 3;

	enum class ePlayerStartingPoint { L_PLAYER_START, R_PLAYER_START = 17 };

	static constexpr int ZERO_CH = '0';

	static const int COLORS[];
	static const int NUM_OF_COLORS;

	enum class eColors { BLACK, WHITE };

	enum class ePlayersType { H_H = 1, H_C = 2, C_C = 3 };

	enum class eMenuKeys { START_H_VS_H = 1, START_H_VS_C = 2, START_C_VS_C = 3, CONTINUE = 4, START_H_VS_H_WITOUT_COLORS = 5, START_H_VS_C_WITOUT_COLORS = 6, START_C_VS_C_WITOUT_COLORS = 7, INSTRUCTIONS = 8, EXIT = 9 };

	static void printInstructions();

	static bool isInEnumLeft(int key);

	static bool isInEnumRight(int key);

	static constexpr int BOMB_DISTANCE = 4;
};
#endif