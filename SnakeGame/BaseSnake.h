#pragma once

#include "SFML/Audio.hpp"
#include "sgList.h"
#include "Entity.h"

class BaseSnake : public Entity
{
private:
	bool isDead;

public:
	enum class EDirection
	{
		North,
		East,
		South,
		West
	};
protected:
	
	bool isAboveWater;
	int remainingBreath;
	int maxBreath;
	int score;
	unsigned short tailGrowth;

	sf::Sound snakeDeathSound;
	sf::SoundBuffer* snakeDeathSoundBuffer;

	EDirection facingDirection;
	sf::Color snakeColor;
	sf::Keyboard::Key* keys;

	// Game Mechanics
	void PlaySnakeDeathSound();
	void RedirectSnakeFromWater(const sf::Vector2f* argNextHeadLocation, const Game* argGame);
	void UpdateNextHeadLocation(sf::Vector2f* argNextHeadLocation, const Game* argGame);
	void WaterCheck(const float argNextHeadLocationY, const Game* argGame);

public:
	sgList<sf::Vector2f> snakeBody;

	BaseSnake(const Game* argGame, sf::Keyboard::Key* argKeys = nullptr, sf::Color argSnakeColor = sf::Color::White, EDirection argFacingDirection = EDirection::North, int argRemainingAir = 250, unsigned short argTailGrowth = 0);
	~BaseSnake();
	
	// Game Mechanics
	void IncreaseTailGrowth(const unsigned short argTailGrowth);
	void IncreaseScore(const int argScore);
	void IncreaseBreath(const int argBreath);

	void SetFacingDirection(const EDirection argNewDirection);
	virtual void MoveSnake(const Game* argGame);
	virtual void Death();

	void Draw(sf::RenderWindow& window, const Game* argGame) override final;
	bool CheckCollisions(const Game* argGame) override final;

	// Get Functions
	bool GetIsDead() const;
	sf::Keyboard::Key* GetKeys() const;
	EDirection GetFacingDirection() const;
	unsigned short GetTailGrowth() const;
	int GetRemainingAir() const;
	bool GetIsAboveWater() const;
	int GetScore() const;
};

