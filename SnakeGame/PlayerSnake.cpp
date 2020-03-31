#include "PlayerSnake.h"
#include "Game.h"
#include "sgList.h"


PlayerSnake::PlayerSnake(const Game* argGame, sf::Keyboard::Key* argKeys, sf::Color argSnakeColor, EDirection argFacingDirection, int argRemainingAir) 
	: BaseSnake(argGame, argKeys, argSnakeColor, argFacingDirection, argRemainingAir)
{
}

PlayerSnake::~PlayerSnake()
{
}


