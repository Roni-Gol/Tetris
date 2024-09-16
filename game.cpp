#include "game.h"

#include <Windows.h>
#include <conio.h> // for kbhit + getch


void Game::init(bool withColors, int players)
{
	delete leftP;
	delete rightP;

	if (players == (int)GameConfig::ePlayersType::H_H)
	{
		leftP = new Player((int)GameConfig::ePlayer::L_PLAYER, withColors);
		rightP = new Player((int)GameConfig::ePlayer::R_PLAYER, withColors);
	}
	else if (players == (int)GameConfig::ePlayersType::H_C)
	{
		leftP = new Player((int)GameConfig::ePlayer::L_PLAYER, withColors);
		rightP = new Computer((int)GameConfig::ePlayer::R_PLAYER, withColors);
	}
	else if (players == (int)GameConfig::ePlayersType::C_C)
	{
		leftP = new Computer((int)GameConfig::ePlayer::L_PLAYER, withColors);
		rightP = new Computer((int)GameConfig::ePlayer::R_PLAYER, withColors);
	}

	if (players == (int)GameConfig::ePlayersType::H_C)
		rightP->getLevel("right");
	else if (players == (int)GameConfig::ePlayersType::C_C)
	{
		leftP->getLevel("right");
		leftP->getLevel("left");
	}

	srand(time(nullptr));
	drawBorder((int)GameConfig::ePlayerStartingPoint::L_PLAYER_START);
	drawBorder((int)GameConfig::ePlayerStartingPoint::R_PLAYER_START);

	leftP->createShape(leftP->getWithColors());
	rightP->createShape(rightP->getWithColors());

	Sleep(500);
}

int Game::pauseMenu(bool inGame)
{
	if (inGame)
		std::cout << "(1) Start a new game - Human vs Human" << std::endl << "(2) Start a new game - Human vs Computer" << std::endl << "(3) Start a new game - Computer vs Computer" <<
		std::endl << "(4) Continue a paused game" << std::endl << "(5) Start a new game - Human vs Human without colors" << std::endl << "(6) Start a new game - Human vs Computer without colors"
		<< std::endl << "(7) Start a new game - Computer vs Computer without colors" << std::endl << "(8) Present instructions and keys" << std::endl << "(9) EXIT";
	else
		std::cout << "(1) Start a new game - Human vs Human" << std::endl << "(2) Start a new game - Human vs Computer" << std::endl << "(3) Start a new game - Computer vs Computer" <<
		std::endl << "(5) Start a new game - Human vs Human without colors" << std::endl << "(6) Start a new game - Human vs Computer without colors" << std::endl <<
		"(7) Start a new game - Computer vs Computer without colors" << std::endl << "(8) Present instructions and keys" << std::endl << "(9) EXIT";

	int keyPressed = _getch() - GameConfig::ZERO_CH;
	return keyPressed;
}

int Game::run(bool withColors, int players)
{
	init(withColors, players);

	bool checkESC;
	bool leftPLost, rightPLost;
	int keyPressed = 0;
	while (true)
	{
		checkESC = getKeyAndSetMove();

		if (checkESC)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			clrscr();
			keyPressed = pauseMenu(true);
			clrscr();

			if (keyPressed == (int)GameConfig::eMenuKeys::EXIT ||
				(keyPressed >= (int)GameConfig::eMenuKeys::START_H_VS_H && keyPressed <= (int)GameConfig::eMenuKeys::START_C_VS_C) ||
				(keyPressed >= (int)GameConfig::eMenuKeys::START_H_VS_H_WITOUT_COLORS && keyPressed <= (int)GameConfig::eMenuKeys::START_C_VS_C_WITOUT_COLORS))
			{
				break;
			}
			else if (keyPressed == (int)GameConfig::eMenuKeys::INSTRUCTIONS)
			{
				GameConfig::printInstructions();
				pauseMenu(true);
				clrscr();
				continueGame();
			}
			else // GameConfig::eMenuKeys::CONTINUE
				continueGame();
		}

		leftPLost = leftP->move();
		rightPLost = rightP->move();

		if (checkIfLost(leftPLost, rightPLost))
			break;

		leftP->setDefault();
		rightP->setDefault();
		Sleep(400);
	}
	gotoxy(0, 0);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)GameConfig::COLORS[0]);

	return keyPressed;
}

void Game::continueGame()
{
	drawBorder((int)GameConfig::ePlayerStartingPoint::L_PLAYER_START);
	drawBorder((int)GameConfig::ePlayerStartingPoint::R_PLAYER_START);

	leftP->printBoard();
	rightP->printBoard();
}

void Game::drawBorder(int playerDiff)
{
	for (int col = GameConfig::MIN_X + playerDiff; col < GameConfig::GAME_WIDTH + GameConfig::MIN_X + playerDiff; col++)
	{
		gotoxy(col, GameConfig::MIN_Y - 1);
		std::cout << "-";

		gotoxy(col, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y);
		std::cout << "-";
	}

	for (int row = GameConfig::MIN_Y - 1; row <= GameConfig::GAME_HEIGHT + GameConfig::MIN_Y; row++)
	{
		gotoxy(GameConfig::MIN_X + playerDiff - 1, row);
		std::cout << "|";

		gotoxy(GameConfig::GAME_WIDTH + GameConfig::MIN_X + playerDiff, row);
		std::cout << "|";
	}
}

void Game::menu(bool newRound)
{
	bool getKeyPressed = true;

	std::cout << "(1) Start a new game - Human vs Human" << std::endl << "(2) Start a new game - Human vs Computer" << std::endl << "(3) Start a new game - Computer vs Computer" <<
		std::endl << "(5) Start a new game - Human vs Human without colors" << std::endl << "(6) Start a new game - Human vs Computer without colors" << std::endl <<
		"(7) Start a new game - Computer vs Computer without colors" << std::endl << "(8) Present instructions and keys" << std::endl << "(9) EXIT";

	int keyPressed = _getch() - GameConfig::ZERO_CH;

	clrscr();
	gotoxy(0, 0);
	while (keyPressed != (int)GameConfig::eMenuKeys::EXIT)
	{
		switch (keyPressed)
		{
		case (int)GameConfig::eMenuKeys::START_H_VS_H:
			keyPressed = run(true, (int)GameConfig::ePlayersType::H_H);
			getKeyPressed = checkGetKeyPressed(keyPressed);
			break;

		case (int)GameConfig::eMenuKeys::START_H_VS_C:
			keyPressed = run(true, (int)GameConfig::ePlayersType::H_C);
			getKeyPressed = checkGetKeyPressed(keyPressed);
			break;

		case (int)GameConfig::eMenuKeys::START_C_VS_C:
			keyPressed = run(true, (int)GameConfig::ePlayersType::C_C);
			getKeyPressed = checkGetKeyPressed(keyPressed);
			break;

		case (int)GameConfig::eMenuKeys::START_H_VS_H_WITOUT_COLORS:
			keyPressed = run(false, (int)GameConfig::ePlayersType::H_H);
			getKeyPressed = checkGetKeyPressed(keyPressed);
			break;

		case (int)GameConfig::eMenuKeys::START_H_VS_C_WITOUT_COLORS:
			keyPressed = run(false, (int)GameConfig::ePlayersType::H_C);
			getKeyPressed = checkGetKeyPressed(keyPressed);
			break;

		case (int)GameConfig::eMenuKeys::START_C_VS_C_WITOUT_COLORS:
			keyPressed = run(false, (int)GameConfig::ePlayersType::C_C);
			getKeyPressed = checkGetKeyPressed(keyPressed);
			break;

		case (int)GameConfig::eMenuKeys::INSTRUCTIONS:
			GameConfig::printInstructions();
			pauseMenu(false);
			break;
		}

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[(int)GameConfig::eColors::BLACK]);

		if (getKeyPressed == true)
		{
			clrscr();
			std::cout << "(1) Start a new game - Human vs Human" << std::endl << "(2) Start a new game - Human vs Computer" << std::endl << "(3) Start a new game - Computer vs Computer" <<
				std::endl << "(5) Start a new game - Human vs Human without colors" << std::endl << "(6) Start a new game - Human vs Computer without colors" << std::endl <<
				"(7) Start a new game - Computer vs Computer without colors" << std::endl << "(8) Present instructions and keys" << std::endl << "(9) EXIT";

			keyPressed = _getch() - GameConfig::ZERO_CH;

			clrscr();
			gotoxy(0, 0);
		}
		else
			getKeyPressed = true;
	}
	if (keyPressed == (int)GameConfig::eMenuKeys::EXIT)
		exitGame();
}

bool Game::checkGetKeyPressed(int keyPressed)
{
	if (keyPressed == (int)GameConfig::eMenuKeys::EXIT ||
		(keyPressed >= (int)GameConfig::eMenuKeys::START_H_VS_H && keyPressed <= (int)GameConfig::eMenuKeys::START_C_VS_C) ||
		(keyPressed >= (int)GameConfig::eMenuKeys::START_H_VS_H_WITOUT_COLORS && keyPressed <= (int)GameConfig::eMenuKeys::START_C_VS_C_WITOUT_COLORS))
	{
		return false;
	}
	return true;
}

void Game::exitGame()
{
	clrscr();
	if (leftP->getScore() > rightP->getScore())
		std::cout << "Left player won!";
	else if (leftP->getScore() < rightP->getScore())
		std::cout << "Right player won!";
	else
		std::cout << "It's a tie!";
	std::cout << std::endl;

	std::cout << "Score: " << std::endl << "Left player: " << leftP->getScore() << " points" << std::endl << "Right player: " << rightP->getScore() << " points";

	gotoxy(0, 10);
}

bool Game::getKeyAndSetMove()
{
	leftP->saveShape();
	rightP->saveShape();

	int keyPressed = 0;
	int keyLeft = 0;
	int keyRight = 0;

	for (int i = 0; i < 20; i++) //in curr turn each player can do one turn 
	{


		if (keyLeft == 0)
			keyLeft = leftP->getKey(i);

		if (keyRight == 0)
			keyRight = rightP->getKey(i);

	}

	leftP->setMove(keyLeft);
	rightP->setMove(keyRight);
	if (keyLeft == (int)GameConfig::ESC || keyRight == (int)GameConfig::ESC)
		return true;
	return false;
}

bool Game::checkIfLost(bool leftPLost, bool rightPLost)
{
	if (leftPLost || rightPLost) //someone lost
	{
		gotoxy(0, GameConfig::GAME_HEIGHT + GameConfig::MIN_Y + 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), GameConfig::COLORS[(int)GameConfig::eColors::BLACK]);

		if (leftPLost && !rightPLost)
		{
			rightP->setScore();
			std::cout << "Right player won!";
		}
		else if (rightPLost && !leftPLost)
		{
			leftP->setScore();
			std::cout << "Left player won!";
		}
		else
			std::cout << "It's a tie!";
		std::cout << std::endl << std::endl << "Press any key to display the menu" << std::endl;

		_flushall();
		_getch(); //waits for a key
		Sleep(400);
		clrscr();

		return true;
	}
	return false;
}