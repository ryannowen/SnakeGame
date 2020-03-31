#include "BaseSnake.h"

#include "Circle.h"
#include "Game.h"
#include "SpawnManager.h"



BaseSnake::BaseSnake(const Game* argGame, sf::Keyboard::Key* argKeys, sf::Color argSnakeColor, EDirection argFacingDirection, int argRemainingAir, unsigned short argTailGrowth)
	: isDead(false), score(0), keys(argKeys), snakeColor(argSnakeColor), facingDirection(argFacingDirection), remainingBreath(argRemainingAir), maxBreath(250), tailGrowth(argTailGrowth)
{
	// Loads snake death sound from resources
	snakeDeathSoundBuffer = argGame->GetGameResources()->LoadSoundBuffer("Snake_Death.wav");
}

// Deletes the snake body (Tail first) by popping back on the list
BaseSnake::~BaseSnake()
{
	for (unsigned int i = 0; i < snakeBody.Size(); i++)
	{
		snakeBody.PopBack();
	}
}

// Plays the snake death sound, outputs error if no sound is loaded
void BaseSnake::PlaySnakeDeathSound()
{
	if (!isDead)
	{
		if (snakeDeathSoundBuffer != nullptr)
		{
			snakeDeathSound.setBuffer(*snakeDeathSoundBuffer);
			snakeDeathSound.setVolume(15.0f);
			snakeDeathSound.play();

		} 
		else
			std::cerr << "ERROR: Trying to play snake death sound when it isn't loaded" << std::endl;
	}
}

// Redirects snake if above water (down or towards center of screen)
void BaseSnake::RedirectSnakeFromWater(const sf::Vector2f* argNextHeadLocation, const Game* argGame)
{
	
	if (isAboveWater && facingDirection == BaseSnake::EDirection::North)
	{
		(argNextHeadLocation->x > argGame->GetScreenDimensions().x / 2) ? facingDirection = BaseSnake::EDirection::West : facingDirection = BaseSnake::EDirection::East;
	} 
	else if (isAboveWater && facingDirection != BaseSnake::EDirection::North)
	{
		if (argNextHeadLocation->y < argGame->GetWaterLevel() - argGame->GetScale())
			facingDirection = BaseSnake::EDirection::South;
	}
}

// Updates Next location depending on current direction
void BaseSnake::UpdateNextHeadLocation(sf::Vector2f* argNextHeadLocation, const Game* argGame)
{
	
	switch (facingDirection)
	{
	case BaseSnake::EDirection::North:
		argNextHeadLocation->y -= argGame->GetScale();
		break;
	case BaseSnake::EDirection::East:
		argNextHeadLocation->x += argGame->GetScale();
		break;
	case BaseSnake::EDirection::South:
		argNextHeadLocation->y += argGame->GetScale();
		break;
	case BaseSnake::EDirection::West:
		argNextHeadLocation->x -= argGame->GetScale();
		break;
	default:
		std::cerr << "ERORR: Unknown snake movement Direction" << std::endl;
		break;
	}
}

// Changes air depending on water level and remaining breath, and removes segments if the snake has no breath, or kills it if they have no segments
void BaseSnake::WaterCheck(const float argNextHeadLocationY, const Game* argGame)
{
	// Resets Remaining air as play is above water level
	if (argNextHeadLocationY < argGame->GetWaterLevel())
	{
		remainingBreath = 250;
		isAboveWater = true;
	} 
	else
	{
		isAboveWater = false;

		if (remainingBreath <= 0) // Player is underwater and then checks if has any air, if they don't they loose a segment and score
		{
			snakeBody.PopBack();

			if (snakeBody.Size() == 0) // if they dont have any segments left they die,
			{
				Death();
				return;
			} 
			else
			{
				score -= score / snakeBody.Size();
			}
		} 
		else // otherwise if they have air remaining it they loose one air
		{
			remainingBreath--;
		}
	}
}

// Adds to the tail growth, to increase the tail when moving
void BaseSnake::IncreaseTailGrowth(const unsigned short argTailGrowth)
{
	tailGrowth += argTailGrowth;
}

// Adds to the score for highscore and winning
void BaseSnake::IncreaseScore(const int argScore)
{
	score += argScore;
}

// Adds to breath so the snake doesnt drown, but is capped at the max breath
void BaseSnake::IncreaseBreath(const int argBreath)
{
	remainingBreath += argBreath;

	if (remainingBreath > maxBreath)
		remainingBreath = maxBreath;
}

void BaseSnake::SetFacingDirection(const EDirection argNewDirection)
{
	facingDirection = argNewDirection;
}

void BaseSnake::MoveSnake(const Game* argGame)
{
	// Current Location of head
	sf::Vector2f* nextHeadLocation = new sf::Vector2f(snakeBody[0]->data);

	// Redirects snake if above water (down or towards center of screen)
	RedirectSnakeFromWater(nextHeadLocation, argGame);

	// Updates Next location depending on current direction
	UpdateNextHeadLocation(nextHeadLocation, argGame);

	// Changes air depending on water level and remaining breath, and removes segments if the snake has no breath, or kills it if they have no segments
	WaterCheck(nextHeadLocation->y, argGame);


	/// Movement and Growth
	// If player is able to grow then pushes a new head and minuses from growth, 
	if (tailGrowth > 0)
	{
		snakeBody.PushFront(nextHeadLocation);
		tailGrowth--;
	} 
	else // otherwise if they have more than 1 segment removes on from the end and adds new to the front, if they only have 1 segment moves it to the next location
	{
		if (snakeBody.Size() > 1)
		{
			snakeBody.PopBack();
			snakeBody.PushFront(nextHeadLocation);
		} 
		else
		{
			snakeBody[snakeBody.Size()]->data = *nextHeadLocation;
		}
	}
}

// Plays the snake death sound and sets isDead to true (wont be draw or able to recieve input)
void BaseSnake::Death()
{
	PlaySnakeDeathSound();

	isDead = true;
}

// Cycles through all segments and draws them as circles
void BaseSnake::Draw(sf::RenderWindow& window, const Game* argGame)
{
	for (unsigned int i = 0; i < snakeBody.Size(); i++)
	{
		Circle tempCircle(snakeBody[i]->data, snakeColor, (float)argGame->GetScale() / 2, sf::Color::Black, 2.0f);
		tempCircle.Draw(window);
	}
}

// Checks if snake is colliding with the tank walls, collectables and other snakes by cycling through them
bool BaseSnake::CheckCollisions(const Game* argGame)
{
	// Checks if snake has gone off the edges of the screen (the tank) and kills self if they have
	if (snakeBody[0]->data.x < 0 || snakeBody[0]->data.y < 0 || snakeBody[0]->data.x > argGame->GetScreenDimensions().x - argGame->GetScale() || snakeBody[0]->data.y > argGame->GetScreenDimensions().y - argGame->GetScale())
	{
		Death();
		return true;
	}

	// Cycles through all the collectables triggering their collection virtual function if the snake has collided with it
	for (Collectable* collectable : argGame->GetGameSpawnManager()->GetCollectables())
	{
		if (snakeBody[0]->data == collectable->GetScreenPosition())
		{
			collectable->Collect(this);
			return false;
		}
	}

	// Checks if snake has hit another snake, kills self if they have
	for (unsigned i = 0; i < argGame->GetGameSpawnManager()->GetSnakes().size(); i++)
	{
		if (argGame->GetGameSpawnManager()->GetSnakes()[i]->GetIsEnabled())
		{
			for (unsigned int j = ((argGame->GetGameSpawnManager()->GetSnakes()[i] == this) ? 1 : 0); j < argGame->GetGameSpawnManager()->GetSnakes()[i]->snakeBody.Size(); j++)
			{
				if (snakeBody[0]->data == argGame->GetGameSpawnManager()->GetSnakes()[i]->snakeBody[j]->data)
				{
					Death();
					return true;
				}
			}
		}
	}

	return false;
}

//
// Get Functions
//

bool BaseSnake::GetIsDead() const
{
	return isDead;
}

sf::Keyboard::Key* BaseSnake::GetKeys() const
{
	return keys;
}

BaseSnake::EDirection BaseSnake::GetFacingDirection() const
{
	return facingDirection;
}

unsigned short BaseSnake::GetTailGrowth() const
{
	return tailGrowth;
}

int BaseSnake::GetRemainingAir() const
{
	return remainingBreath;
}

bool BaseSnake::GetIsAboveWater() const
{
	return isAboveWater;
}

int BaseSnake::GetScore() const
{
	return score;
}
