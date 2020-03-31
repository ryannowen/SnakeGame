#include "Button_QuitGame.h"



Button_QuitGame::Button_QuitGame(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
	: Button(argGame, argButtonShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName)
{
}


Button_QuitGame::~Button_QuitGame()
{
}

void Button_QuitGame::OnBeginHover(Game* argGame)
{
}

void Button_QuitGame::OnEndHover(Game* argGame)
{
}

void Button_QuitGame::OnBeginClick(Game* argGame)
{
}

// Changes the game state to Quit (Which in turn Closes the game)
void Button_QuitGame::OnEndClick(Game* argGame)
{
	argGame->QuitGame();
}
