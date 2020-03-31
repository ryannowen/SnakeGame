#include "Shape.h"

#include <iostream>

Shape::Shape(const sf::Vector2f argScreenPos, const sf::Color& argColor, const sf::Color argOutlineColour, const float argOutlineThickness, const sf::Vector2f argSpeed)
	: screenPosition(argScreenPos), fillColour(argColor), outlineColour(argOutlineColour), outlineThickness(argOutlineThickness), speed(argSpeed)  {}

// Moves shape in the speed direction, reverses direction if hits wall
void Shape::MoveShape(sf::Vector2f argScreenDimensions)
{
	screenPosition += speed;

	if (screenPosition.x > argScreenDimensions.x || screenPosition.x < 0)
		speed.x = -speed.x;

	if (screenPosition.y > argScreenDimensions.y || screenPosition.y < 0)
		speed.y = -speed.y;
}