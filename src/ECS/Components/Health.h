#pragma once
#include "../Component.h"

struct Damageable : ECS::Component
{

};

struct Health : ECS::Component
{
	int max_health;
	int current_health = 1;

	bool alive = true;
};
