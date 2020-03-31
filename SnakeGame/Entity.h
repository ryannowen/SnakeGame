#pragma once

#include "SFML/Graphics.hpp"
class Game;

class Entity
{
protected:
	bool isEnabled;

public:
	Entity();
	~Entity();

	// Game Mechanics
	void SetIsEnabled(bool argIsEnabled);

	// Get Functions
	bool GetIsEnabled();

	// Overridable Game Mechanics
	virtual void Draw(sf::RenderWindow& window, const Game* argGame) = 0;
	virtual bool CheckCollisions(const Game* argGame) = 0;
};

