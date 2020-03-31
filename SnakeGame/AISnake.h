#pragma once

#include "BaseSnake.h"
#include "Collectable.h"

class AISnake : public BaseSnake
{
protected:
	sf::Vector2f targetLocation;
	
	// Game Mechanics
	sf::Vector2f FindTarget(const Collectable::ECollectableType argTargetType, const Game* argGame) const;
	bool CheckTarget(const sf::Vector2f argTargetLocation, const Game* argGame) const;
	void CalculateNextDirection(const sf::Vector2f& argCurrentHeadLocation, const Game* argGame);

public:
	AISnake(const Game* argGame, sf::Color argSnakeColor = sf::Color::White, EDirection argFacingDirection = EDirection::North, int argRemainingAir = 250);
	~AISnake();

	// Game Mechanics
	void MoveSnake(const Game* argGame) override;
};

