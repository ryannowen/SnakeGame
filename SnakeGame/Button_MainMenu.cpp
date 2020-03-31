#include "Button_MainMenu.h"



Button_MainMenu::Button_MainMenu(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
	: Button(argGame, argButtonShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName)
{
}


Button_MainMenu::~Button_MainMenu()
{
}

void Button_MainMenu::OnBeginHover(Game* argGame)
{
}

void Button_MainMenu::OnEndHover(Game* argGame)
{
}

void Button_MainMenu::OnBeginClick(Game* argGame)
{
}

// Changes the game state to MainMenu (Which in turn resets the game and draws the main menu)
void Button_MainMenu::OnEndClick(Game* argGame)
{
	argGame->SetGameState(Game::EGameState::MainMenu);
}
