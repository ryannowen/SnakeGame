#include "Game.h"

#include <iostream>
#include "BaseSnake.h"
#include "SpawnManager.h"
#include "Button.h"

#include <fstream>
#include <iostream>
#include <sstream>

Game::Game(const unsigned short argScale, const float argWaterMaxTime, const Game::EDifficulty argDifficulty)
	: waterLevel(0), pausedTime(0.0f), scale(argScale), gameSpawnManager(new SpawnManager), gameResourceHolder(new GameResources), waterMaxTime(argWaterMaxTime), waterRemainingTime(argWaterMaxTime), gameState(EGameState::MainMenu), gameDifficulty(argDifficulty), maxHighscores(10)
{
	// Spawns water which will be used throughout the game
	gameSpawnManager->SpawnWater(this);

	// Loads game font
	if (!gameFont.loadFromFile("arial.ttf"))
		std::cout << "Couldn't load font" << std::endl;

	// Begins spawning UI
	SpawnUI();

	// Creates Highscores for Loading/Saving
	for (int i = 0; i < maxHighscores; i++)
	{
		AddHighScore();
	}

	LoadHighScores();
}

// Cleans up spawn manager and the game resources (Textures/Sounds)
Game::~Game()
{
	delete gameSpawnManager;
	delete gameResourceHolder;
}

// Spawns UI Text and Buttons at begining due to being expensive (only updates variables as needed during draw)
void Game::SpawnUI()
{
	// Main Menu Elements
	// Text
	gameSpawnManager->SpawnText(EGameState::MainMenu, this, "Ryan Robson - T7091365 \n SnakeGame ICA", 40, sf::Color::Green, sf::Vector2f(ScreenDimensions.x / 2, 0), sf::Text::Regular, 3.0f);
	gameSpawnManager->SpawnText(EGameState::MainMenu, this, "Snakes have discovered the best food to be \nunderwater but must periodically come to the surface for air.\nThe snakes in this game live in a water tank, which unfortunately has a leak, \nand the water level is dropping...", 35, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 200), sf::Text::Regular, 2.0f);

	// Buttons
	gameSpawnManager->SpawnButton(Button::EButtonType::StartGame, this, Game::EGameState::MainMenu, sf::Vector2f(400, 750), sf::Vector2f(400, 150), "Start Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::QuitGame, this, Game::EGameState::MainMenu, sf::Vector2f(800, 750), sf::Vector2f(400, 150), "Quit Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");

	// InGame Elements
	// Text
	gameSpawnManager->SpawnText(EGameState::InGame, this, "Player 1 Info ", 25, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 5, 0), sf::Text::Regular, 3.0f);
	gameSpawnManager->SpawnText(EGameState::InGame, this, "Player 2 Info ", 25, sf::Color::Cyan, sf::Vector2f(ScreenDimensions.x / 5 * 2, 0), sf::Text::Regular, 3.0f);
	gameSpawnManager->SpawnText(EGameState::InGame, this, "Player 3 Info ", 25, sf::Color::Yellow, sf::Vector2f(ScreenDimensions.x / 5 * 3, 0), sf::Text::Regular, 3.0f);
	gameSpawnManager->SpawnText(EGameState::InGame, this, "Player 4 Info ", 25, sf::Color::Magenta, sf::Vector2f(ScreenDimensions.x / 5 * 4, 0), sf::Text::Regular, 3.0f);
	gameSpawnManager->SpawnText(EGameState::InGame, this, "Remaining Time: ", 25, sf::Color::Green, sf::Vector2f(ScreenDimensions.x / 2, ScreenDimensions.y / 2), sf::Text::Regular, 3.0f);

	// Pause Menu Elements
	// Text
	gameSpawnManager->SpawnText(EGameState::PauseMenu, this, "Controls!\nPlayer 1 - W, A, S, D\nPlayer 2 - Arrow Keys\nPlayer 3 - Num8, Num4, Num5, Num6\nPlayer 4 - I, J, K, L\nPause Game - Escape or P", 50, sf::Color::White, sf::Vector2f(ScreenDimensions.x - ScreenDimensions.x / 2.1f, ScreenDimensions.y / 10), sf::Text::Regular, 2.0f);

	// Buttons
	gameSpawnManager->SpawnButton(Button::EButtonType::MainMenu, this, Game::EGameState::PauseMenu, sf::Vector2f(0, 0), sf::Vector2f(400, 150), "Return to Main Menu", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::StartGame, this, Game::EGameState::PauseMenu, sf::Vector2f(0, 150), sf::Vector2f(400, 150), "Restart Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::QuitGame, this, Game::EGameState::PauseMenu, sf::Vector2f(0, 300), sf::Vector2f(400, 150), "Quit Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");

	// HighScoreSubmittion Elements
	// Text
	gameSpawnManager->SpawnText(EGameState::HighScoreSubmittion, this, "Winner Text", 25, sf::Color::Green, sf::Vector2f(ScreenDimensions.x / 2, ScreenDimensions.y / 2), sf::Text::Regular, 2.0f);

	// Buttons
	gameSpawnManager->SpawnButton(Button::EButtonType::HighScoreSubmittion, this, Game::EGameState::HighScoreSubmittion, sf::Vector2f(600, 600), sf::Vector2f(400, 150), "Submit High Score!", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::MainMenu, this, Game::EGameState::HighScoreSubmittion, sf::Vector2f(200, 750), sf::Vector2f(400, 150), "Return to Main Menu", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::StartGame, this, Game::EGameState::HighScoreSubmittion, sf::Vector2f(600, 750), sf::Vector2f(400, 150), "Restart Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::QuitGame, this, Game::EGameState::HighScoreSubmittion, sf::Vector2f(1000, 750), sf::Vector2f(400, 150), "Quit Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");

	// HighScore Elements
	// Text
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text", 25, sf::Color::Green, sf::Vector2f(ScreenDimensions.x / 2, ScreenDimensions.y / 2), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "High Score Table:", 25, sf::Color::Green, sf::Vector2f(ScreenDimensions.x / 2, 0), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 1", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 40), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 2", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 60), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 3", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 80), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 4", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 100), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 5", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 120), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 6", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 140), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 7", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 160), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 8", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 180), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 9", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 200), sf::Text::Regular, 2.0f);
	gameSpawnManager->SpawnText(EGameState::HighScoreTable, this, "Winner Text 10", 15, sf::Color::Red, sf::Vector2f(ScreenDimensions.x / 2, 220), sf::Text::Regular, 2.0f);


	// Buttons
	gameSpawnManager->SpawnButton(Button::EButtonType::MainMenu, this, Game::EGameState::HighScoreTable, sf::Vector2f(200, 750), sf::Vector2f(400, 150), "Return to Main Menu", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::StartGame, this, Game::EGameState::HighScoreTable, sf::Vector2f(600, 750), sf::Vector2f(400, 150), "Restart Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
	gameSpawnManager->SpawnButton(Button::EButtonType::QuitGame, this, Game::EGameState::HighScoreTable, sf::Vector2f(1000, 750), sf::Vector2f(400, 150), "Quit Game", 25, sf::Color::White, 2.0f, sf::Color::Black, "Button_Normal.png", "Button_Hovered.png", "Button_Pressed.png", "Button_Hover.wav", "Button_Pressed.wav");
}


// Checks what state the game is in, and then checks if the keys can trigger anything, if so it triggers otherwise continues with the game loop
void Game::HandleKeyboardPressedInput(const sf::Keyboard::Key& argKey)
{
	switch (gameState)
	{
	case Game::EGameState::MainMenu:
		break;

	case Game::EGameState::InGame:
		if (argKey == sf::Keyboard::Key::P || argKey == sf::Keyboard::Key::Escape) // Switches game from Ingame to Paused
			gameState = EGameState::PauseMenu;

		// Cycles through snakes checking if their key matches the pressed one, if it does changes their direction
		for (BaseSnake* snake : GetGameSpawnManager()->GetSnakes()) 
		{
			if (!snake->GetIsDead())
			{
				for (unsigned short i = 0; i < 4; i++)
				{
					if (snake->GetKeys() != nullptr)
					{
						if (argKey == snake->GetKeys()[i])
						{
							switch (i)
							{
							case 0:
								if ((snake->GetFacingDirection() != BaseSnake::EDirection::South || snake->snakeBody.Size() == 1) && !snake->GetIsAboveWater())
									snake->SetFacingDirection(BaseSnake::EDirection::North);
								return;
								break;
							case 1:
								if (snake->GetFacingDirection() != BaseSnake::EDirection::West || snake->snakeBody.Size() == 1)
									snake->SetFacingDirection(BaseSnake::EDirection::East);
								return;
								break;
							case 2:
								if (snake->GetFacingDirection() != BaseSnake::EDirection::North || snake->snakeBody.Size() == 1)
									snake->SetFacingDirection(BaseSnake::EDirection::South);
								return;
								break;
							case 3:
								if (snake->GetFacingDirection() != BaseSnake::EDirection::East || snake->snakeBody.Size() == 1)
									snake->SetFacingDirection(BaseSnake::EDirection::West);
								return;
								break;
							}
						}
					}
				}
			}
		}
		break;

	case Game::EGameState::HighScoreTable:
		break;

	case Game::EGameState::PauseMenu:
		if (argKey == sf::Keyboard::Key::P || argKey == sf::Keyboard::Key::Escape) // Switches game from Paused to Ingame
			gameState = EGameState::InGame;
		break;

	default:
		break;

	}
}

// When the mouse is pressed or released this will cycle through the buttons checking if they are being/ending clicked
void Game::HandleMouseInput(sf::RenderWindow& window)
{
	for (Button* button : gameSpawnManager->GetButtons())
	{
		if (button->GetShowState() == gameState)
		{
			if (button->CheckIfMouseClicked(this, window, sf::Mouse::isButtonPressed(sf::Mouse::Left)))
				break;
		}
	}
}

void Game::Play(const unsigned short argNumOfAI, const unsigned short argNumOfPlayers)
{
	// Create an instance of the SFML RenderWindow type which represents the display and initialise its size and title text
	sf::RenderWindow window(sf::VideoMode((int)ScreenDimensions.x, (int)ScreenDimensions.y), "C++ Snake ICA : T7091365");

	// We can still output to the console window
	std::cout << "SnakeGame: Starting" << std::endl;

	numOfAISnakes = argNumOfAI;
	numOfPlayerSnakes = argNumOfPlayers;

	// Initial Game Start
	ResetGame(); 

	// Clocks for game loop
	sf::Clock frameDelay;
	sf::Clock waterFallRate;

	// Changes movement speed/spawn speed of objects within the game loop
	unsigned int gameLoopSpeed;
	switch (gameDifficulty)
	{
	case Game::EDifficulty::Hard:
		gameLoopSpeed = 80;
		break;
	case Game::EDifficulty::Medium:
		gameLoopSpeed = 125;
		break;
	case Game::EDifficulty::Easy:
		gameLoopSpeed = 160;
		break;
	default:
		break;
	}

	// Main loop that continues until we call window.close()
	while (window.isOpen())
	{
		// Handle any pending SFML events, These cover keyboard, mouse,joystick etc.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				gameState = EGameState::Quit;
				break;

			case sf::Event::KeyPressed:
				HandleKeyboardPressedInput(event.key.code);
				break;

			case sf::Event::MouseButtonPressed:
				HandleMouseInput(window);
				break;

			case sf::Event::MouseButtonReleased:
				HandleMouseInput(window);
				break;

			default:
				
				break;
			}
		}

		// If Game State is quit closes window
		if (gameState == EGameState::Quit)
			window.close();

		// We must clear the window each time around the loop
		window.clear();

		// Game Loop
		if (frameDelay.getElapsedTime().asMilliseconds() >= gameLoopSpeed)
		{
			if (gameState != EGameState::PauseMenu)
			{
				if (!CheckGameWinner())
				{
					// Cycles through all the snakes and moves them
					for (BaseSnake* snake : GetGameSpawnManager()->GetSnakes())
					{
						if (!snake->GetIsDead())
						{
							snake->MoveSnake(this);
						}
					}

					// Cycles through all the collectables, if disabled has a chance of re-spawning it (New position, value, etc)
					for (Collectable* collectable : GetGameSpawnManager()->GetCollectables())
					{
						if (!collectable->GetIsEnabled())
						{
							if (rand() % 101 < 5)
							{
								collectable->SpawnAndReset(this);
							}
						}
					}

					// Makes snakes check their collisions in their new location
					CheckSnakeCollisions();

					if (waterFallRate.getElapsedTime().asSeconds() >= GetWaterFallRate())
					{
						LowerWater();
						CheckCollectablesWithWaterHeight();
						waterFallRate.restart();
					}
				} 
				else // If a winner is found the game will reset, if the game is at the InGame state it will change to the highscore screen
				{
					std::cout << "Winner Found" << std::endl;

					if (gameState == EGameState::InGame)
					{
						gameState = EGameState::HighScoreTable;
					}



					ResetGame();
					gameTime.restart();
				}
			}
			else
			{
				pausedTime += frameDelay.getElapsedTime().asSeconds();
			}

			// Resets Move Delay
			frameDelay.restart();
		}
		
		// Updates Remaining Time
		waterRemainingTime = (waterMaxTime + pausedTime) - gameTime.getElapsedTime().asSeconds();

		// Draws My objects (Text, Entities, etc)
		DrawWindow(window);

		// Get the window to display its contents
		window.display();
	}
}

void Game::DrawWindow(sf::RenderWindow& window)
{
	// Draws water
	gameSpawnManager->DrawWater(window);

	// Draws Snakes and Collectables
	gameSpawnManager->DrawEntities(window, this);

	// Draws UI
	gameSpawnManager->DrawInterface(window, this);
}



void Game::LowerWater()
{
	waterLevel += scale;
	gameSpawnManager->UpdateWaterPosition(sf::Vector2f(0, waterLevel));
}

void Game::SaveHighScores()
{
	std::ofstream highScoreFile;
	highScoreFile.open("HighScores.SaveData");

	for (const Game::SHighScore& highScore : highScores)
	{
		highScoreFile << highScore.name << "." << highScore.score << "\n";
	}

	highScoreFile.close();
}

void Game::LoadHighScores()
{
	std::string currentHighScoreLine;
	std::ifstream highScoreFile("example.txt");

	if (highScoreFile.is_open())
	{
		for (Game::SHighScore& highScore : highScores)
		{
			std::getline(highScoreFile, currentHighScoreLine);

			highScore.name = currentHighScoreLine.substr(0, currentHighScoreLine.find("."));
			std::stringstream score(currentHighScoreLine.substr(currentHighScoreLine.find("."), INT_MAX));
			score >> highScore.score;
		}

		highScoreFile.close();
	}
	else 
		std::cout << "Unable to open HighScore file";
}

void Game::SubmitHighScore()
{
	for (int i = 0; i < highScores.size(); i++)
	{
		if (highScores[i].score < winningSnakeScore)
		{
			highScores[i].score = winningSnakeScore;
			highScores[i].name = " Not Enough Time to Implement: ";

			if (i + 1 < maxHighscores)
			{
				winningSnakeScore = highScores[i + 1].score;
			}
		}
	}

	SaveHighScores();
	gameState = Game::EGameState::HighScoreTable;
}

void Game::ResetGame()
{
	// Removes all COllectables and Snakes
	gameSpawnManager->ClearObjects();

	// Resets game values
	gameSpawnManager->UpdateWaterPosition(sf::Vector2f(0, 0));
	waterLevel = 0;
	pausedTime = 0.0f;
	gameTime.restart();

	// Spawns snakes depending on gamestate, if state is Ingame will spawn normal amount of snakes otherwise will spawn 4 AI snakes
	for (unsigned short i = 0; i < ((gameState == EGameState::InGame) ? numOfAISnakes + numOfPlayerSnakes : 4); i++)
	{
		gameSpawnManager->SpawnSnake(this, (gameState == EGameState::InGame) ? (i < numOfPlayerSnakes) : false, i);
	}

	// Spawns the desired amount of collectables
	for (unsigned short i = 0; i < 5; i++)
	{
		gameSpawnManager->SpawnCollectable(this);
	}
}

// Updates GameState with the new state then restarts the game
void Game::SetGameState(Game::EGameState argNewState)
{
	gameState = argNewState;
	ResetGame();
}

// Updates GameState to quit which will cycle then close the window
void Game::QuitGame()
{
	gameState = EGameState::Quit;
}

void Game::AddHighScore()
{
	highScores.push_back(Game::SHighScore());
	highScores[highScores.size() - 1].name = "NONE";
	highScores[highScores.size() - 1].score = 0;
}

// Cycles through snakes, checks if they're colliding with anything (E.g Collectable or snake part)
void Game::CheckSnakeCollisions()
{
	for (BaseSnake* snake : gameSpawnManager->GetSnakes())
	{
		snake->CheckCollisions(this);
	}
}

// Goes through all the collectables, and disables all the ones above the water
void Game::CheckCollectablesWithWaterHeight()
{
	for (Collectable* collectable : gameSpawnManager->GetCollectables())
	{
		if (collectable->GetScreenPosition().y < waterLevel)
			collectable->SetIsEnabled(false);
	}
}

// Checks if a snake has won by being the last one or by having the heighest score
bool Game::CheckGameWinner()
{
	if (waterLevel >= ScreenDimensions.y) // Resets game if water is off screeen
		return true;

	std::vector<BaseSnake*> snakesThatDied;
	unsigned int previouslyDied{ 0 };

	for (BaseSnake* snake : gameSpawnManager->GetSnakes()) // Gets values for remaining snake calculation and also disables dead snakes
	{
		if (!snake->GetIsEnabled())
		{
			previouslyDied++;
		}
		else if (snake->GetIsDead())
		{
			snakesThatDied.push_back(snake);
			snake->SetIsEnabled(false);
		}
	}

	int winnerSnakeID;

	if (snakesThatDied.size() == 0)
		return false;
	else if ((gameSpawnManager->GetSnakes().size() - previouslyDied) - snakesThatDied.size() == 1) // Checks if only one snake is alive
	{
		// Finds single winner snake
		for (int i = 0; i < gameSpawnManager->GetSnakes().size(); i++)
		{
			if (!gameSpawnManager->GetSnakes()[i]->GetIsDead())
			{
				winnerSnakeID = i;
				break;
			}
		}

		// Only updates winner if game loop is InGame
		if (gameState == Game::EGameState::InGame)
		{
			winningSnakeName = ((winnerSnakeID < numOfPlayerSnakes) ? ("Player " + std::to_string(winnerSnakeID + 1)) : ("AI " + std::to_string(winnerSnakeID)));
			winningSnakeScore = gameSpawnManager->GetSnakes()[winnerSnakeID]->GetScore();

			//if(winnerSnakeID < numOfPlayerSnakes)
				CheckIsHighScore(gameSpawnManager->GetSnakes()[winnerSnakeID]->GetScore());
		}
		
		return true;
	}
	else if ((gameSpawnManager->GetSnakes().size() - previouslyDied) - snakesThatDied.size() == 0) // Checks if both snakes died in head-on collision
	{
		// Checks if two snakes actually hit each other or only a single snake was in-game
		if (snakesThatDied.size() > 1) 
		{
			winnerSnakeID = (snakesThatDied[0]->GetScore() > snakesThatDied[1]->GetScore()) ? gameSpawnManager->GetSnakeID(snakesThatDied[0]) : gameSpawnManager->GetSnakeID(snakesThatDied[1]);
		}
		else
		{
			winnerSnakeID = gameSpawnManager->GetSnakeID(snakesThatDied[0]);
		}

		// Only updates winner if game loop is InGame
		if (gameState == Game::EGameState::InGame)
		{
			winningSnakeName = ((winnerSnakeID < numOfPlayerSnakes) ? ("Player " + std::to_string(winnerSnakeID + 1)) : ("AI " + std::to_string(winnerSnakeID)));
			winningSnakeScore = gameSpawnManager->GetSnakes()[winnerSnakeID]->GetScore();
			//if (winnerSnakeID < numOfPlayerSnakes)
				CheckIsHighScore(gameSpawnManager->GetSnakes()[winnerSnakeID]->GetScore());
		}
		
		return true;
	}

	return false;
}

void Game::CheckIsHighScore(const unsigned int& argScore)
{
	for (Game::SHighScore& highScore : highScores)
	{
		if (highScore.score < argScore)
		{
			gameState = Game::EGameState::HighScoreSubmittion;
			return;
		}
	}

	gameState = Game::EGameState::HighScoreTable;
}

// Returns the rate at which the water is falling in seconds
float Game::GetWaterFallRate() const
{
	return waterMaxTime / (ScreenDimensions.y / scale);
}

// Returns the time remaining
float Game::GetWaterRemainingTime() const
{
	return waterRemainingTime;
}

//
// Get functions (returns a value)
//

int Game::GetNumberOfAI() const
{
	return numOfAISnakes;
}

int Game::GetNumberOfPlayers() const
{
	return numOfPlayerSnakes;
}

std::string Game::GetWinningSnakeName() const
{
	return winningSnakeName;
}

int Game::GetWinningSnakeScore() const
{
	return winningSnakeScore;
}

int Game::GetWaterLevel() const
{
	return waterLevel;
}

sf::Vector2f Game::GetScreenDimensions() const
{
	return ScreenDimensions;
}

unsigned short Game::GetScale() const
{
	return scale;
}

SpawnManager* Game::GetGameSpawnManager() const
{
	return gameSpawnManager;
}

GameResources* Game::GetGameResources() const
{
	return gameResourceHolder;
}

Game::EDifficulty Game::GetGameDifficulty() const
{
	return gameDifficulty;
}

Game::EGameState Game::GetGameState() const
{
	return gameState;
}

sf::Font* Game::GetGameFont() const
{
	return new sf::Font(gameFont);
}

std::vector<Game::SHighScore> Game::GetHighScores() const
{
	return highScores;
}
