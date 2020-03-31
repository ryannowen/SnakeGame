#include "Circle.h"


Circle::Circle(const sf::Vector2f& argScreenPos, const  sf::Color& argColor, const float argRadius, const sf::Color argOutlineColour, const float argOutlineThickness)
	: Shape(argScreenPos, argColor, argOutlineColour, argOutlineThickness, sf::Vector2f(0, 0)), Radius(argRadius)
{
	circle.setFillColor(fillColour);
	circle.setPosition(screenPosition);
	circle.setOutlineColor(outlineColour);
	circle.setOutlineThickness(outlineThickness);
	circle.setRadius(Radius);
}

// Changes the circles size to a new radius
void Circle::Resize(const float argNewRadius)
{
	circle.setRadius(argNewRadius);
}

// Updates the circles texture and changes the fill colour so that it is fully lit
void Circle::SetTexture(const sf::Texture* argTexture, bool argResetRect)
{
	circle.setTexture(argTexture, argResetRect);
	circle.setFillColor(sf::Color::White);
}

// Sets the screen position variable and then updates the circles position to match
void Circle::SetScreenPosition(const sf::Vector2f& argNewPosition)
{
	screenPosition = argNewPosition;
	circle.setPosition(screenPosition);
}

// Draws the circle to the window
void Circle::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
}

//
// Overrided Get Functions
//

sf::FloatRect Circle::GetLocalBounds() const
{
	return circle.getLocalBounds();
}

sf::FloatRect Circle::GetGlobalBounds() const
{
	return circle.getGlobalBounds();
}



