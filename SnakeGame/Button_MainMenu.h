#pragma once

#include "Button.h"

class Button_MainMenu : public Button
{
public:
	Button_MainMenu(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition = sf::Vector2f(0, 0), const sf::Vector2f argButtonSize = sf::Vector2f(20, 20), const std::string argLabelText = "No Inputed Label Text", const unsigned int argLabelSize = 10, const sf::Color argFillColour = sf::Color::Green, const float argOutlineSize = 0.0f, const sf::Color argOutlineColour = sf::Color::Black, const std::string argNormalTexture = "", const std::string argHoveredTexture = "", const std::string argPressedTexture = "", const std::string argHoverSoundBufferName = "", const std::string argPressedSoundBufferName = "");
	~Button_MainMenu();

	// Overrided Game Mechanics
	void OnBeginHover(Game* argGame) override final;
	void OnEndHover(Game* argGame) override final;
	void OnBeginClick(Game* argGame) override final;
	void OnEndClick(Game* argGame) override final;
};

