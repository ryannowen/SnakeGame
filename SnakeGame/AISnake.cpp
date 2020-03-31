#include "AISnake.h"

#include "Game.h"
#include "SpawnManager.h"

// Finds a collectable with the desired type and returns it, if no collectable can be found then it will return 0,0
sf::Vector2f AISnake::FindTarget(const Collectable::ECollectableType argTargetType, const Game* argGame) const
{
	for (Collectable* collectable : argGame->GetGameSpawnManager()->GetCollectables())
	{
		if (collectable->GetType() == argTargetType && collectable->GetIsEnabled())
		{
			if (rand() % 2 == 0)

			{
				return collectable->GetScreenPosition();
			}
		}
	}

	return sf::Vector2f(0, 0);
}

// Checks if AI target is still available to be eaten, returns true if it is
bool AISnake::CheckTarget(const sf::Vector2f argTargetLocation, const Game* argGame) const
{
	for (Collectable* collectable : argGame->GetGameSpawnManager()->GetCollectables())
	{
		if (collectable->GetScreenPosition() == argTargetLocation)
		{
			if (collectable->GetIsEnabled())
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	}

	return false;
}

void AISnake::CalculateNextDirection(const sf::Vector2f& argCurrentHeadLocation, const Game* argGame)
{
	/// Finds some sort of target for the snake to move to
	// Checks if any target is still active
	if (!CheckTarget(targetLocation, argGame)) 
	{
		// If air is low will choose bubbles over food
		if (remainingBreath < (maxBreath / 3))
		{
			// Finds Air Bubbles
			targetLocation = FindTarget(Collectable::ECollectableType::Bubble, argGame);

			// Checks if no bubble was found preventing division by 0
			if (targetLocation != sf::Vector2f(0, 0))
			{
				// if surface is closer than the target bubble and not full then target the top of the water
				if ((argGame->GetWaterLevel() / argGame->GetScale() < (targetLocation.x / argGame->GetScale() + targetLocation.y / argGame->GetScale())) && argGame->GetWaterLevel() != 0)
				{
					targetLocation = sf::Vector2f(argCurrentHeadLocation.x, argGame->GetWaterLevel());
				}
			}
		}
		else
		{
			// Finds Food
			targetLocation = FindTarget(Collectable::ECollectableType::Food, argGame);

			// if no food is found find any remaining bubbles
			if (targetLocation == sf::Vector2f(0, 0))
			{
				targetLocation = FindTarget(Collectable::ECollectableType::Bubble, argGame);
			}
		}

		// If nothing is found will go to surface for air
		if (targetLocation == sf::Vector2f(0, 0))
		{
			targetLocation = sf::Vector2f(argCurrentHeadLocation.x, argGame->GetWaterLevel());
		}
	}
	

	// Changes direction towards target, but wont ever face towards the opposite direction (full 180)
	if(targetLocation.y < argCurrentHeadLocation.y && facingDirection != BaseSnake::EDirection::South && !isAboveWater)
		facingDirection = BaseSnake::EDirection::North;
	else if (targetLocation.x > argCurrentHeadLocation.x && facingDirection != BaseSnake::EDirection::West)
		facingDirection = BaseSnake::EDirection::East;
	else if (targetLocation.y > argCurrentHeadLocation.y && facingDirection != BaseSnake::EDirection::North)
		facingDirection = BaseSnake::EDirection::South;
	else if (targetLocation.x < argCurrentHeadLocation.x && facingDirection != BaseSnake::EDirection::East)
		facingDirection = BaseSnake::EDirection::West;

}

AISnake::AISnake(const Game* argGame, sf::Color argSnakeColor, EDirection argFacingDirection, int argRemainingAir)
	: BaseSnake(argGame, nullptr, argSnakeColor, argFacingDirection, argRemainingAir), targetLocation(0, 0)
{
}


AISnake::~AISnake()
{
}

void AISnake::MoveSnake(const Game* argGame)
{
	// Current Location of head
	sf::Vector2f* nextHeadLocation = new sf::Vector2f(snakeBody[0]->data);

	/// Snake AI to ge the next direction
	CalculateNextDirection(*nextHeadLocation, argGame);

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
