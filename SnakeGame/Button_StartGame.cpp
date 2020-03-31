#include "Button_StartGame.h"

#include "Game.h"


Button_StartGame::Button_StartGame(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
	: Button(argGame, argButtonShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName)
{
}


Button_StartGame::~Button_StartGame()
{
}

void Button_StartGame::OnBeginHover(Game* argGame)
{

}

void Button_StartGame::OnEndHover(Game* argGame)
{

}

void Button_StartGame::OnBeginClick(Game* argGame)
{

}

// Changes the game state to InGame (Which in turn resets the game)
void Button_StartGame::OnEndClick(Game* argGame)
{
	argGame->SetGameState(Game::EGameState::InGame);
}
