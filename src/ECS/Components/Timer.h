#pragma once

#include "../Component.h"

struct Timer : ECS::Component
{
	bool running = false;
	float time = 0;
	float elapsed = 0;

	void update(const float delta_time)
	{
		elapsed += delta_time;
	}

	void reset()
	{
		elapsed = 0;
	}
};
