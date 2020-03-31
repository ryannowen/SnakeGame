#pragma once

#include "SFML/Graphics.hpp"
#include "BaseSnake.h"
#include "Collectable.h"
#include "Rectangle.h"
#include "Game.h"
#include "Button.h"

#include <vector>

class SpawnManager
{
private:
	struct SSnakeInformation
	{
		sf::Keyboard::Key snakeKeys[4][4]
		{
			{ sf::Keyboard::W, sf::Keyboard::D , sf::Keyboard::S, sf::Keyboard::A },
			{ sf::Keyboard::Up, sf::Keyboard::Right , sf::Keyboard::Down, sf::Keyboard::Left },
			{ sf::Keyboard::Num8, sf::Keyboard::Num6 , sf::Keyboard::Num2, sf::Keyboard::Num4 },
			{ sf::Keyboard::I, sf::Keyboard::L , sf::Keyboard::K, sf::Keyboard::J },
		};

		sf::Color snakeColors[4]
		{
			sf::Color::Red,
			sf::Color::Cyan,
			sf::Color::Yellow,
			sf::Color::Magenta
		};

	};

	SSnakeInformation snakeInfo;
	std::vector<BaseSnake*> snakes;
	std::vector<Collectable*> collectables;

	std::vector<Button*> buttons;

	sgList<sf::Text> mainMenuTextList;
	sgList<sf::Text> inGameTextList;
	sgList<sf::Text> highScoreSubmittionTextList;
	sgList<sf::Text> highScoreTextList;
	sgList<sf::Text> pauseMenuTextList;

	Rectangle* water; 
	Rectangle* tankBackground;

	sf::Texture* waterTexture;
	sf::Texture* tankBackgroundTexture;

	// Game Mechanics
	void DrawMainMenu(sf::RenderWindow& window, const Game* argGame);
	void DrawInGame(sf::RenderWindow& window, const Game* argGame);
	void DrawHighScoreSubmittion(sf::RenderWindow& window, const Game* argGame);
	void DrawHighScore(sf::RenderWindow& window, const Game* argGame);
	void DrawPauseMenu(sf::RenderWindow& window, const Game* argGame);

public:
	SpawnManager();
	~SpawnManager();

	// Game Mechanics
	void ClearObjects();

	void SpawnSnake(const Game* argGame, const bool argPlayerSnake, unsigned short argSnakeID);
	void SpawnCollectable(const Game* argGame);
	void SpawnWater(const Game* argGame);
	void SpawnText(const Game::EGameState argState, const Game* argGame, const std::string argText, const unsigned int argFontSize, const sf::Color argFillColour = sf::Color::Green, const sf::Vector2f argPosition = sf::Vector2f(0, 0), const sf::Text::Style argStyle = sf::Text::Regular, const float argOutlineSize = 0, const sf::Color argOutlineColour = sf::Color::Black);
	void SpawnButton(const Button::EButtonType argButtonType, const Game* argGame, const Game::EGameState argShowState, const sf::Vector2f argScreenPosition = sf::Vector2f(0, 0), const sf::Vector2f argButtonSize = sf::Vector2f(20, 20), const std::string argLabelText = "No Inputed Label Text", const unsigned int argLabelSize = 10, const sf::Color argFillColour = sf::Color::Green, const float argOutlineSize = 0.0f, const sf::Color argOutlineColour = sf::Color::Black, const std::string argNormalTexture = "", const std::string argHoveredTexture = "", const std::string argPressedTexture = "", const std::string argHoverSoundBufferName = "", const std::string argPressedSoundBufferName = "");

	void UpdateWaterPosition(const sf::Vector2f& argNewPosition);

	void DrawInterface(sf::RenderWindow& window, Game* argGame);
	void DrawWater(sf::RenderWindow& window);
	void DrawEntities(sf::RenderWindow& window, const Game* argGame);

	// Get Functions
	sf::Vector2f GetRandomScreenLocation(const Game* argGame);
	std::vector<BaseSnake*> GetSnakes() const;
	std::vector<Collectable*> GetCollectables() const;
	std::vector<Button*> GetButtons() const;
	Rectangle* GetWater() const;
	int GetSnakeID(BaseSnake* argSnake) const;
};

