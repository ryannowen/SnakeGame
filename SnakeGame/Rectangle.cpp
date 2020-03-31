#include "Rectangle.h"

#include <math.h>
#include <iostream>


Rectangle::Rectangle(const sf::Vector2f argScreenPos, const sf::Color& argColour, const sf::Vector2f argRectangleSize, const sf::Color argOutlineColour, const float argOutlineThickness, const float argRotateSpeed, const float argCurrentRotation, const sf::Vector2f argSpeed)
	: Shape(argScreenPos, argColour, argOutlineColour, argOutlineThickness, argSpeed), RectangleSize(argRectangleSize), rotateSpeed(argRotateSpeed), currentRotation(argCurrentRotation)
{
	rectangle.setFillColor(fillColour);
	rectangle.setPosition(screenPosition);
	rectangle.setSize(RectangleSize);
	rectangle.setOutlineColor(outlineColour);
	rectangle.setOutlineThickness(outlineThickness);
}

// Changes the rectangles size
void Rectangle::Resize(const sf::Vector2f argNewSize)
{
	rectangle.setSize(argNewSize);
}

// Updates the rectangles texture and sets the fill colour to white so that it is fully lit
void Rectangle::SetTexture(const sf::Texture* argTexture, bool argResetRect)
{
	rectangle.setTexture(argTexture, argResetRect);
	rectangle.setFillColor(sf::Color::White);
}

// updates the saved value Changes the rectangles position with it 
void Rectangle::SetScreenPosition(const sf::Vector2f& argNewPosition)
{
	screenPosition = argNewPosition;
	rectangle.setPosition(screenPosition);
}

// Draws the rectangle to the window, and also rotates it depending on speed
void Rectangle::Draw(sf::RenderWindow& window)
{
	currentRotation += rotateSpeed;
	rectangle.rotate(currentRotation);
	window.draw(rectangle);
}

//
// Get Functions
//

sf::Vector2f Rectangle::GetRectangleSize() const
{
	return rectangle.getSize();
}

// Overrided Get Functions
sf::FloatRect Rectangle::GetLocalBounds() const
{
	return rectangle.getLocalBounds();
}

sf::FloatRect Rectangle::GetGlobalBounds() const
{
	return rectangle.getGlobalBounds();
}


