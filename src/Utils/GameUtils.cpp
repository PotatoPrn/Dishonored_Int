#include "Utils/GameUtils.h"

bool ValidateEntity(PlayerObject* Entity)
{
	if (Entity == nullptr)
		return false;

	if (Entity->Health <= 0 || Entity->Health >= 300)
		return false;

	return true;
}

