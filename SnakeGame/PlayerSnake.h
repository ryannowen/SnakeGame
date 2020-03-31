#pragma once

#include "BaseSnake.h"

class PlayerSnake : public BaseSnake
{
public:
	PlayerSnake(const Game* argGame, sf::Keyboard::Key* argKeys, sf::Color argSnakeColor = sf::Color::White, EDirection argFacingDirection = EDirection::North, int argRemainingAir = 250);
	~PlayerSnake();

	// Empty due to player not needing anything else other than from basesnake, however is here for the future in case of needing it
};

