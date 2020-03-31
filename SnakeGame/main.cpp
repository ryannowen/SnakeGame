/*
  Games Development with C++ GAV1031-N
  Snake ICA start project

  Set up to use the SFML 2.5.1 64-bit API
	SFML documentation: https://www.sfml-dev.org/learn.php
*/

#include <iostream>
#include <string>

#include "Game.h"

int main()
{
	srand((unsigned int)time(0));

	// Settings
	unsigned short aiSnakes{ 3 }, playerSnakes{ 1 }, gameScale{ 30 }, gameDifficulty{ 2 };
	float waterTime{ 90.0f };
	std::string defaults;

	std::cout << "Do you want to use default Settings? (Yes/No)" << std::endl;
	std::cin >> defaults;

	if (defaults == "No" || defaults == "no")
	{
		std::cout << "How Many Player Snakes do you want? (Default: 1)" << std::endl;
		std::cin >> playerSnakes;

		std::cout << "How Many Ai Snakes do you want? (Default: 3)" << std::endl;
		std::cin >> aiSnakes;

		std::cout << "What size do you want the scale to be (Default: 30)" << std::endl;
		std::cin >> gameScale;

		std::cout << "What size do you want the difficulty to be (1 - Hard, 2 - Medium, 3 - Easy) (Default: 2)" << std::endl;
		std::cin >> gameDifficulty;

		std::cout << "How long do you want the water to take in seconds? (Default: 90)" << std::endl;
		std::cin >> waterTime;
	}

	Game* mainGame = new Game(gameScale, waterTime, (Game::EDifficulty)gameDifficulty);

	// Starts the Game
	mainGame->Play(aiSnakes, playerSnakes);


	// Cleans up
	delete mainGame;
	std::cout << "SnakeGame: Finished" << std::endl;
	return 0;
}
