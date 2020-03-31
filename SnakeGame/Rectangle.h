#pragma once

#include "SFML/Graphics.hpp"
#include "Shape.h"

class Rectangle : public Shape
{
private:
	float rotateSpeed, currentRotation;
	sf::Vector2f RectangleSize;
	sf::RectangleShape rectangle;

public:
	Rectangle(const sf::Vector2f argScreenPos = sf::Vector2f(0, 0), const sf::Color& argColour = sf::Color::Blue, const sf::Vector2f argRectangleSize = sf::Vector2f(10, 10), const sf::Color argOutlineColour = sf::Color::Black, const float argOutlineThickness = 0.0f, const float argRotateSpeed = 0.0f, const float argCurrentRotation = 0.0f, const sf::Vector2f argSpeed = sf::Vector2f(0, 0));
	
	// Game Mechanics
	void Resize(const sf::Vector2f argNewSize);
	
	// Overrided Game Mechanics
	void SetTexture(const sf::Texture* argTexture, bool argResetRect = false) override;
	void SetScreenPosition(const sf::Vector2f& argNewPosition) override;
	void Draw(sf::RenderWindow& window) override;
	
	// Get Functions
	sf::Vector2f GetRectangleSize() const;

	// Overrided Get Functions
	sf::FloatRect GetLocalBounds() const override;
	sf::FloatRect GetGlobalBounds() const override;
};

