#pragma once

#include "Entity.h"
#include "Rectangle.h"
#include "Game.h"

#include "SFML/Audio.hpp"
#include "SFML/Window/Mouse.hpp"


class Button
{
private:
	enum class EState
	{
		Normal,
		Hover,
		Pressed
	};

	sf::SoundBuffer* hoverSoundBuffer;
	sf::SoundBuffer* pressedSoundBuffer;
	sf::Sound hoverSound;
	sf::Sound pressedSound;

	sf::Texture* buttonNormalTexture;
	sf::Texture* buttonHoveredTexture;
	sf::Texture* buttonPressedTexture;

	sf::Texture* currentTexture;

	Game::EGameState buttonShowState;
	EState buttonState;
	Rectangle button;
	sf::Text buttonLabel;

	// Game Mechanics
	void MouseHoverCheck(Game* argGame, sf::RenderWindow& window);
	void PlayPressedSound(const bool argLoop = false);
	void PlayHoveredSound(const bool argLoop = true);
	void EndPressedSound();
	void EndHoveredSound();

	// Overridable Game Mechanics (Pure)
	virtual void OnBeginHover(Game* argGame) = 0;
	virtual void OnEndHover(Game* argGame) = 0;
	virtual void OnBeginClick(Game* argGame) = 0;
	virtual void OnEndClick(Game* argGame) = 0;



public:
	enum class EButtonType
	{
		StartGame,
		MainMenu,
		HighScoreSubmittion,
		HighScore,
		QuitGame
	};

	Button(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition = sf::Vector2f(0, 0), const sf::Vector2f argButtonSize = sf::Vector2f(20, 20), const std::string argLabelText = "No Inputed Label Text", const unsigned int argLabelSize = 10, const sf::Color argFillColour = sf::Color::Green, const float argOutlineSize = 0.0f, const sf::Color argOutlineColour = sf::Color::Black, const std::string argNormalTexture = "", const std::string argHoveredTexture = "", const std::string argPressedTexture = "", const std::string argHoverSoundBufferName = "", const std::string argPressedSoundBufferName = "");
	~Button();

	// Game Mechanics
	void LoadButtonTextures(const Game* argGame, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture);
	void LoadSoundBuffers(const Game* argGame, const std::string argHoverSound, const std::string argPressedSound);
	void ChangeButtonSize(const sf::Vector2f argNewSize);
	void ChangeLabelText(const unsigned int, const std::string argNewText, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour);
	void ChangeLabelSize(const unsigned int argNewLabelSize);
	bool CheckIfMouseClicked(Game* argGame, sf::RenderWindow& window, const bool argIsPressed);
	void Draw(Game* argGame, sf::RenderWindow& window);

	// Get Functions
	Game::EGameState GetShowState();
};

