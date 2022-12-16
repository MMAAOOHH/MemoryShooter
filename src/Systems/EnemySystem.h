#pragma once

#include "../ECS/System.h"
#include "../Components/Enemy.h"


struct EnemySystem : ECS::System
{
	EnemySystem()
	{
		std::cout << "EnemySystem created" << std::endl;
	}

	void init();
	void update(const float delta_time);

private:
	// wave stuff
	void create_grid_locations(int rows, int cols);
	void start_wave();
	void spawn_enemy(Vec2 spawn_pos, Vec2 start_pos);

	float wave_time = 0;
	int wave_index = 0;
	std::vector<Vec2> start_locations;

};