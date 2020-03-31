#include "Button_Highscore.h"



Button_Highscore::Button_Highscore(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
	: Button(argGame, argButtonShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName)
{
}


Button_Highscore::~Button_Highscore()
{
}

void Button_Highscore::OnBeginHover(Game* argGame)
{
}

void Button_Highscore::OnEndHover(Game* argGame)
{
}

void Button_Highscore::OnBeginClick(Game* argGame)
{
}

// Changes the game state to Highscore (Which in turn resets the game and draws the highscore)
void Button_Highscore::OnEndClick(Game* argGame)
{
	argGame->SetGameState(Game::EGameState::HighScoreTable);
}
