#pragma once

#include "SFML/Graphics.hpp"
#include "Shape.h"

class Circle : public Shape
{
private:
	float Radius;
	sf::CircleShape circle;

public:
	Circle(const sf::Vector2f& argScreenPos, const sf::Color& argColor, const float argRadius, const sf::Color argOutlineColour = sf::Color::Black, const float argOutlineThickness = 0.0f);
	
	// Game Mechanics
	void Resize(const float argNewRadius);
	
	// Overrided Game Mechanics
	void SetTexture(const sf::Texture* argTexture, bool argResetRect = false) override;
	void SetScreenPosition(const sf::Vector2f& argNewPosition) override;
	void Draw(sf::RenderWindow& window);

	// Overrided Get Functions
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
	
};

