#pragma once

#include "../ECS/Component.h"

enum class Tag
{
	player,
	enemy,
	player_projectile,
	enemy_projectile
};

struct Collider : ECS::Component
{
	Tag tag;
	bool active = false;
};

struct Collision : ECS::Component
{
	Collision(Tag tag, Tag from) : this_tag(tag), from_tag(from){}
	Tag this_tag;
	Tag from_tag;
};
