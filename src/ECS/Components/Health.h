#pragma once
#include "../Component.h"

struct Health : ECS::Component
{
	int current_health = 1;
};
