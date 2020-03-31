#include "SpawnManager.h"

#include "AISnake.h"
#include "PlayerSnake.h"

#include "Button_StartGame.h"
#include "Button_MainMenu.h"
#include "Button_HighScoreSubmittion.h"
#include "Button_Highscore.h"
#include "Button_QuitGame.h"

#include <iostream>
#include <string>

SpawnManager::SpawnManager() {}

// Cleans up all the objects that have been spawned
SpawnManager::~SpawnManager()
{
	ClearObjects();
}

// This deletes all the objects that have been spawned and clears the container
void SpawnManager::ClearObjects()
{
	for (BaseSnake* snake : snakes)
	{
		delete snake;
	}

	snakes.clear();

	for (Collectable* collectable : collectables)
	{
		delete collectable;
	}

	collectables.clear();
}

// Searches for a location on screen that is below the water level and also matches the game scale
sf::Vector2f SpawnManager::GetRandomScreenLocation(const Game* argGame)
{
	int randCol, randRow;
	do
	{
		randCol = (rand() % ((int)(argGame->GetScreenDimensions().x / argGame->GetScale()))) * argGame->GetScale();
		randRow = (rand() % ((int)(argGame->GetScreenDimensions().y / argGame->GetScale()))) * argGame->GetScale();
	} while (randRow < argGame->GetWaterLevel());


	return sf::Vector2f((float)randCol, (float)randRow);
}

// Spawns a snake at a random location facing towards the center of the screen, Spawns players or AI depending on the inputted game values, also adds 2 body length
void SpawnManager::SpawnSnake(const Game* argGame, const bool argPlayerSnake, unsigned short argSnakeID)
{
	sf::Vector2f* screenLocation = new sf::Vector2f(GetRandomScreenLocation(argGame));
	BaseSnake::EDirection snakeDirection;

	if (screenLocation->x > argGame->GetScreenDimensions().x / 2)
		snakeDirection = BaseSnake::EDirection::West;
	else
		snakeDirection = BaseSnake::EDirection::East;

	if (argPlayerSnake)
		snakes.push_back(new PlayerSnake(argGame, snakeInfo.snakeKeys[argSnakeID], snakeInfo.snakeColors[argSnakeID], snakeDirection, (int)argGame->GetGameDifficulty() * 80));
	else
		snakes.push_back(new AISnake(argGame, snakeInfo.snakeColors[argSnakeID], BaseSnake::EDirection(rand() % 4), (int)argGame->GetGameDifficulty() * 65));

	// Adds Head and initial body segments
	snakes[argSnakeID]->snakeBody.PushFront(screenLocation);
	snakes[argSnakeID]->IncreaseTailGrowth(2);
}

// Adds a new collectable to the container
void SpawnManager::SpawnCollectable(const Game* argGame)
{
	collectables.push_back(new Collectable(argGame));
}

// Loads the water textures, spawns rectangles for them and then updates the texture, this also saves the rectangle pointers for later use
void SpawnManager::SpawnWater(const Game* argGame)
{
	waterTexture = argGame->GetGameResources()->LoadTexture("water.png");
	tankBackgroundTexture = argGame->GetGameResources()->LoadTexture("TankBackground.png");

	tankBackground = new Rectangle(sf::Vector2f(0, 0), sf::Color::White, argGame->GetScreenDimensions());
	water = new Rectangle(sf::Vector2f(0, argGame->GetWaterLevel()), sf::Color(255,255,255, 100), argGame->GetScreenDimensions());

	water->SetTexture(waterTexture);
	tankBackground->SetTexture(tankBackgroundTexture);
}

// Spawns a text onto the screen which only will be draw depending on the inputted gamestate will output error to console if gamestate is not supported
void SpawnManager::SpawnText(const Game::EGameState argState, const Game* argGame, const std::string argText, const unsigned int argFontSize, const sf::Color argFillColour, const sf::Vector2f argPosition, const sf::Text::Style argStyle, const float argOutlineSize, const sf::Color argOutlineColour)
{
	sf::Text* newText = new sf::Text;

	newText->setFont(*argGame->GetGameFont());
	newText->setString(argText);
	newText->setCharacterSize(argFontSize);
	newText->setFillColor(argFillColour);
	newText->setPosition(sf::Vector2f(argPosition.x - newText->getLocalBounds().width / 2, argPosition.y));
	newText->setStyle(argStyle);
	newText->setOutlineThickness(argOutlineSize);
	newText->setOutlineColor(argOutlineColour);

	switch (argState)
	{
	case Game::EGameState::MainMenu:
		mainMenuTextList.PushBack(newText);
		break;

	case Game::EGameState::InGame:
		inGameTextList.PushBack(newText);
		break;

	case Game::EGameState::HighScoreTable:
		highScoreTextList.PushBack(newText);
		break;

	case Game::EGameState::PauseMenu:
		pauseMenuTextList.PushBack(newText);
		break;

	default:
		std::cerr << "ERROR: Trying to spawn text in a invalid GameState" << std::endl;
		break;
	}
}

// Spawns a Button onto the screen which only will be draw depending on the inputted gamestate will output error to console if gamestate is not supported, the buttontype determines the click events
void SpawnManager::SpawnButton(const Button::EButtonType argButtonType, const Game* argGame, const Game::EGameState argShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
{
	Button* newButton;

	switch (argButtonType) 
	{
	case Button::EButtonType::StartGame:
		newButton = new Button_StartGame(argGame, argShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName);
		break;

	case Button::EButtonType::MainMenu:
		newButton = new Button_MainMenu(argGame, argShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName);
		break;

	case Button::EButtonType::HighScoreSubmittion:
		newButton = new Button_HighScoreSubmittion(argGame, argShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName);
		break;

	case Button::EButtonType::HighScore:
		newButton = new Button_Highscore(argGame, argShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName);
		break;

	case Button::EButtonType::QuitGame:
		newButton = new Button_QuitGame(argGame, argShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName);
		break;

	default:
		std::cerr << "ERROR: Trying to spawn button in a invalid GameState" << std::endl;
		break;
	}

	buttons.push_back(newButton);
}

// Updates water rectagle position 
void SpawnManager::UpdateWaterPosition(const sf::Vector2f& argNewPosition)
{
	water->SetScreenPosition(argNewPosition);
}

// Draws water if it is spawned, otherwise throw error
void SpawnManager::DrawWater(sf::RenderWindow& window)
{
	if (water != nullptr)
	{
		tankBackground->Draw(window);
		water->Draw(window);
	}
	else
		std::cerr << "ERROR: Trying to draw water, which is nullptr!" << std::endl;
}

// Draws Interface depending on current game state (Text and buttons)
void SpawnManager::DrawInterface(sf::RenderWindow& window, Game* argGame)
{
	switch (argGame->GetGameState())
	{
	case Game::EGameState::MainMenu:
		DrawMainMenu(window, argGame);
		break;

	case Game::EGameState::InGame:
		DrawInGame(window, argGame);
		break;

	case Game::EGameState::HighScoreSubmittion:
		DrawHighScoreSubmittion(window, argGame);
		break;

	case Game::EGameState::HighScoreTable:
		DrawHighScore(window, argGame);
		break;

	case Game::EGameState::PauseMenu:
		DrawPauseMenu(window, argGame);
		break;

	case Game::EGameState::Quit:
		break;

	default:
		std::cerr << "ERORR: Interface Enum in Game not set" << std::endl;
		break;
	}

	for (Button* button : buttons)
	{
		if(button->GetShowState() == argGame->GetGameState())
			button->Draw(argGame, window);
	}
}

void SpawnManager::DrawMainMenu(sf::RenderWindow& window, const Game* argGame)
{
	// Draws MainMenuTexts
	for (unsigned int i = 0; i < mainMenuTextList.Size(); i++)
	{
		window.draw(mainMenuTextList[i]->data);
	}
}

void SpawnManager::DrawInGame(sf::RenderWindow& window, const Game* argGame)
{
	// Updates String before drawing instead of creating sf::text due to it being expensive
	inGameTextList[0]->data.setString("Player 1 \nBreath: " + std::to_string(snakes[0]->GetRemainingAir()) + "\nScore: " + std::to_string(snakes[0]->GetScore()));
	(snakes.size() > 1) ? inGameTextList[1]->data.setString(std::string(argGame->GetNumberOfPlayers() >= snakes.size() ? "Player 2 " : "AI 1 ") + "\nBreath: " + std::to_string(snakes[1]->GetRemainingAir()) + "\nScore: " + std::to_string(snakes[1]->GetScore())) : inGameTextList[1]->data.setString("");
	(snakes.size() > 2) ? inGameTextList[2]->data.setString(std::string(argGame->GetNumberOfPlayers() >= snakes.size() ? "Player 3 " : "AI 2 ") + "\nBreath: " + std::to_string(snakes[2]->GetRemainingAir()) + "\nScore: " + std::to_string(snakes[2]->GetScore())) : inGameTextList[2]->data.setString("");
	(snakes.size() > 3) ? inGameTextList[3]->data.setString(std::string(argGame->GetNumberOfPlayers() >= snakes.size() ? "Player 4 " : "AI 3 ") + "\nBreath: " + std::to_string(snakes[3]->GetRemainingAir()) + "\nScore: " + std::to_string(snakes[3]->GetScore())) : inGameTextList[3]->data.setString("");
	
	inGameTextList[4]->data.setString("Remaining Time: " + std::to_string((int)argGame->GetWaterRemainingTime()) + " Seconds");

	// Draws InGameTexts
	for (unsigned int i = 0; i < inGameTextList.Size(); i++)
	{
		window.draw(inGameTextList[i]->data);
	}
}

void SpawnManager::DrawHighScoreSubmittion(sf::RenderWindow& window, const Game* argGame)
{
	// Updates String before drawing instead of creating sf::text due to it being expensive
	highScoreTextList[0]->data.setString("The Winner is: " + argGame->GetWinningSnakeName() + "\nwith the score " + std::to_string(argGame->GetWinningSnakeScore()));

	// Draws HighScoreSubmittion Texts
	for (unsigned int i = 0; i < highScoreSubmittionTextList.Size(); i++)
	{
		window.draw(highScoreSubmittionTextList[i]->data);
	}
}

void SpawnManager::DrawHighScore(sf::RenderWindow& window, const Game* argGame)
{
	std::vector<Game::SHighScore> highScores{ argGame->GetHighScores() };

	// Updates String before drawing instead of creating sf::text due to it being expensive
	highScoreTextList[0]->data.setString("The Winner is: " + argGame->GetWinningSnakeName() + " with the score " + std::to_string(argGame->GetWinningSnakeScore()));
	highScoreTextList[2]->data.setString("1: " + highScores[0].name + " with the score " + std::to_string(highScores[0].score));
	highScoreTextList[3]->data.setString("2: " + highScores[1].name + " with the score " + std::to_string(highScores[1].score));
	highScoreTextList[4]->data.setString("3: " + highScores[2].name + " with the score " + std::to_string(highScores[2].score));
	highScoreTextList[5]->data.setString("4: " + highScores[3].name + " with the score " + std::to_string(highScores[3].score));
	highScoreTextList[6]->data.setString("5: " + highScores[4].name + " with the score " + std::to_string(highScores[4].score));
	highScoreTextList[7]->data.setString("6: " + highScores[5].name + " with the score " + std::to_string(highScores[5].score));
	highScoreTextList[8]->data.setString("7: " + highScores[6].name + " with the score " + std::to_string(highScores[6].score));
	highScoreTextList[9]->data.setString("8: " + highScores[7].name + " with the score " + std::to_string(highScores[7].score));
	highScoreTextList[10]->data.setString("9: " + highScores[8].name + " with the score " + std::to_string(highScores[8].score));
	highScoreTextList[11]->data.setString("10: " + highScores[9].name + " with the score " + std::to_string(highScores[9].score));

	// Draws HighScoreTexts
	for (unsigned int i = 0; i < highScoreTextList.Size(); i++)
	{
		window.draw(highScoreTextList[i]->data);
	}
}

void SpawnManager::DrawPauseMenu(sf::RenderWindow& window, const Game* argGame)
{
	// Draws PauseMenuTexts
	for (unsigned int i = 0; i < pauseMenuTextList.Size(); i++)
	{
		window.draw(pauseMenuTextList[i]->data);
	}
}

void SpawnManager::DrawEntities(sf::RenderWindow& window, const Game* argGame)
{
	// Draws all enabled collectables
	for (Collectable* collectable : collectables)
	{
		if (collectable->GetIsEnabled())
			collectable->Draw(window, argGame);
	}

	// Draws all enabled and snakes that are not dead
	for (BaseSnake* snake : snakes)
	{
		if (!snake->GetIsDead() && snake->GetIsEnabled())
			snake->Draw(window, argGame);
	}
}

//
// Get Functions
//

std::vector<BaseSnake*> SpawnManager::GetSnakes() const
{
	return snakes;
}

std::vector<Collectable*> SpawnManager::GetCollectables() const
{
	return collectables;
}

std::vector<Button*> SpawnManager::GetButtons() const
{
	return buttons;
}

Rectangle* SpawnManager::GetWater() const
{
	return water;
}

int SpawnManager::GetSnakeID(BaseSnake* argSnake) const
{
	for (int i = 0; i < snakes.size(); i++)
	{
		if (snakes[i] == argSnake)
		{
			return i;
		}
	}

	return -1;
}
