#include "Button_HighScoreSubmittion.h"

Button_HighScoreSubmittion::Button_HighScoreSubmittion(const Game* argGame, const Game::EGameState argButtonShowState, const sf::Vector2f argScreenPosition, const sf::Vector2f argButtonSize, const std::string argLabelText, const unsigned int argLabelSize, const sf::Color argFillColour, const float argOutlineSize, const sf::Color argOutlineColour, const std::string argNormalTexture, const std::string argHoveredTexture, const std::string argPressedTexture, const std::string argHoverSoundBufferName, const std::string argPressedSoundBufferName)
	: Button(argGame, argButtonShowState, argScreenPosition, argButtonSize, argLabelText, argLabelSize, argFillColour, argOutlineSize, argOutlineColour, argNormalTexture, argHoveredTexture, argPressedTexture, argHoverSoundBufferName, argPressedSoundBufferName)
{
}


Button_HighScoreSubmittion::~Button_HighScoreSubmittion()
{
}

void Button_HighScoreSubmittion::OnBeginHover(Game* argGame)
{
}

void Button_HighScoreSubmittion::OnEndHover(Game* argGame)
{
}

void Button_HighScoreSubmittion::OnBeginClick(Game* argGame)
{
}

// Submits the current highscore
void Button_HighScoreSubmittion::OnEndClick(Game* argGame)
{
	argGame->SubmitHighScore();
}
