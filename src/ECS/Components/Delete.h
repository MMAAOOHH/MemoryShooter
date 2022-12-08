#pragma once

#include "../Component.h"

struct Delete : ECS::Component
{
	// Used to tag entities for deletion
	int hello = 0;
};
