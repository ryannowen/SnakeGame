#include "Entity.h"



Entity::Entity() : isEnabled(true)
{
}


Entity::~Entity()
{
}

// Changes the enabled status of the entity
void Entity::SetIsEnabled(bool argIsEnabled)
{
	isEnabled = argIsEnabled;
}

//
// Get Functions
//

bool Entity::GetIsEnabled()
{
	return isEnabled;
}
