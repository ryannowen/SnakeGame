#include "Collectable.h"

#include "Circle.h"
#include "Game.h"
#include "SpawnManager.h"


// Plays the collection sound but switches depending on the type of collectable (Food or Bubble), also makes sure sound is loaded and outputs error if it isn't
void Collectable::PlayCollectionSound()
{
	switch (collectableType)
	{
	default:
	case Collectable::ECollectableType::Food:
		if (seaweedCollectSoundBuffer != nullptr)
		{
			collectionSound.setBuffer(*seaweedCollectSoundBuffer);
			collectionSound.setVolume(25.0f);
			collectionSound.play();
		} else
			std::cerr << "ERROR: Trying to play collectable seaweed collection sound when it isn't loaded" << std::endl;
		break;


	case Collectable::ECollectableType::Bubble:
		if (bubbleCollectSoundBuffer != nullptr)
		{
			collectionSound.setBuffer(*bubbleCollectSoundBuffer);
			collectionSound.setVolume(25.0f);
			collectionSound.play();
		} 
		else
			std::cerr << "ERROR: Trying to play collectable bubble collection sound when it isn't loaded" << std::endl;
		break;
	}
}

Collectable::Collectable(const Game* argGame)
{
	// Loads the required Textures
	seaweed1Texture = argGame->GetGameResources()->LoadTexture("Seaweed_1.png");
	seaweed2Texture = argGame->GetGameResources()->LoadTexture("Seaweed_2.png");
	seaweed3Texture = argGame->GetGameResources()->LoadTexture("Seaweed_3.png");
	bubbleTexture = argGame->GetGameResources()->LoadTexture("Bubble.png");

	// Loads the required Sounds
	bubbleCollectSoundBuffer = argGame->GetGameResources()->LoadSoundBuffer("Snake_Eat_Bubble.wav");
	seaweedCollectSoundBuffer = argGame->GetGameResources()->LoadSoundBuffer("Snake_Eat_Food.wav");

	// Spawns the collectable with new values
	SpawnAndReset(argGame);
}

Collectable::~Collectable() {}

// Randomises the position of the collectable in the screen and by the scale, also changes the values and type to become different, finally gets enabled again so it can be drawn and collected
void Collectable::SpawnAndReset(const Game* argGame)
{
	do
	{
		screenPosition = argGame->GetGameSpawnManager()->GetRandomScreenLocation(argGame);
	} while (CheckCollisions(argGame));

	tailGrowthAmount = rand() % 3 + 1 + ((screenPosition.y > argGame->GetScreenDimensions().y / 2) ? 1 : 0);
	score = (rand() % 76) + 25;
	collectableType = (ECollectableType)(rand() % 2);
	SetIsEnabled(true);
}

// Increases snake values depending on collectable type (TailGrowth or Breath) if type isn't set outputs an error, It then plays the desired sound, increases the snakes score and then disables itself from being drawn and collected again
void Collectable::Collect(BaseSnake* argSnake)
{
	switch (collectableType)
	{
	case Collectable::ECollectableType::Food:
		argSnake->IncreaseTailGrowth(tailGrowthAmount);
		break;

	case Collectable::ECollectableType::Bubble:
		argSnake->IncreaseBreath(tailGrowthAmount * 20);
		break;

	default:
		std::cerr << "ERROR: Trying to collect collectable but type collection has been specified" << std::endl;
		break;
	}

	PlayCollectionSound();
	argSnake->IncreaseScore(score);
	isEnabled = false;
}

// Updates the collectable texture depending on value and type, and then draws it to the window
void Collectable::Draw(sf::RenderWindow& window, const Game* argGame)
{
	Circle tempCollectable(screenPosition, sf::Color::White, argGame->GetScale() / 2.0f);

	switch (collectableType)
	{
	default:
	case Collectable::ECollectableType::Food:
		switch (tailGrowthAmount)
		{
		default:
		case 1:
			tempCollectable.SetTexture(seaweed1Texture);
			break;
		case 2:
			tempCollectable.SetTexture(seaweed2Texture);
			break;
		case 3:
			tempCollectable.SetTexture(seaweed3Texture);
			break;
		}
		break;
	case Collectable::ECollectableType::Bubble:
		tempCollectable.SetTexture(bubbleTexture);
		break;
	}

	tempCollectable.Draw(window);
}

// Used in place of movement collision, but instead is used for detecting if the collectable spawned on any other object 
bool Collectable::CheckCollisions(const Game* argGame)
{
	for (unsigned i = 0; i < argGame->GetGameSpawnManager()->GetSnakes().size(); i++)
	{
		if (!argGame->GetGameSpawnManager()->GetSnakes()[i]->GetIsDead() && argGame->GetGameSpawnManager()->GetSnakes()[i]->GetIsEnabled())
		{
			for (unsigned int j = i + 1; j < argGame->GetGameSpawnManager()->GetSnakes()[i]->snakeBody.Size(); j++)
			{
				if (screenPosition == argGame->GetGameSpawnManager()->GetSnakes()[i]->snakeBody[j]->data)
				{
					return true;
				}
			}
		}
	}

	for (Collectable* collectable : argGame->GetGameSpawnManager()->GetCollectables())
	{
		if (screenPosition == collectable->GetScreenPosition() && collectable->GetIsEnabled())
		{
			return true;
		}
	}

	return false;
}

//
// Get Functions
//

int Collectable::GetScore() const
{
	return score;
}

sf::Vector2f Collectable::GetScreenPosition() const
{
	return screenPosition;
}

int Collectable::GetTailGrowthAmount() const
{
	return tailGrowthAmount;
}

Collectable::ECollectableType Collectable::GetType() const
{
	return collectableType;
}