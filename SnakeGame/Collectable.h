#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Entity.h"
#include "BaseSnake.h"

class Collectable : public Entity
{
public:
	enum class ECollectableType
	{
		Food,
		Bubble
	};

private:
	int score;
	sf::Vector2f screenPosition;
	int tailGrowthAmount;
	ECollectableType collectableType;

	sf::Texture* bubbleTexture;
	sf::Texture* seaweed1Texture;
	sf::Texture* seaweed2Texture;
	sf::Texture* seaweed3Texture;

	sf::Sound collectionSound;

	sf::SoundBuffer* bubbleCollectSoundBuffer;
	sf::SoundBuffer* seaweedCollectSoundBuffer;

	// Game Mechanics
	void PlayCollectionSound();

public:
	Collectable(const Game* argGame);
	~Collectable();

	// Game Mechanics
	void SpawnAndReset(const Game* argGame);

	// Overridable Game Mechanics
	virtual void Collect(BaseSnake* argSnake);

	// Overrided Game Mechanics
	void Draw(sf::RenderWindow& window, const Game* argGame) override final;
	bool CheckCollisions(const Game* argGame) override final;

	// Get Functions
	int GetScore() const;
	sf::Vector2f GetScreenPosition() const;
	int GetTailGrowthAmount() const;
	Collectable::ECollectableType GetType() const;
};

