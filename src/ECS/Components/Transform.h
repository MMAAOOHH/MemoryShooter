#pragma once

#include "../Component.h"

namespace ECS
{
	struct vec2
	{
		int x, y;
	};

	struct Transform : Component
	{
		vec2 position;
		float rotation = 0.f;
		float scale = 1.f;
	};
}
