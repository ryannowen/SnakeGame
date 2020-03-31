#pragma once

#include "SFML/Graphics.hpp"

#include <vector>

class Shape
{
protected:
	sf::Vector2f screenPosition;
	sf::Color fillColour;
	sf::Color outlineColour;

	sf::Vector2f speed;
	float sizeMultiplier = 3.0f;
	float outlineThickness = 0.0f;

public:
	Shape(const sf::Vector2f argScreenPos, const sf::Color& argcolor, const sf::Color argOutlineColour = sf::Color::Black, const float argOutlineThickness = 0.0f, const sf::Vector2f Argspeed = sf::Vector2f(0, 0));
	
	// Game Mechanics
	void MoveShape(sf::Vector2f argScreenDimensions);

	// Overridable Game Mechanics (Pure)
	virtual void Draw(sf::RenderWindow& window) = 0;
	virtual void SetTexture(const sf::Texture* argTexture, bool argResetRect = false) = 0;
	virtual void SetScreenPosition(const sf::Vector2f& argNewPosition) = 0;

	virtual sf::FloatRect GetLocalBounds() const = 0;
	virtual sf::FloatRect GetGlobalBounds() const = 0;
};
