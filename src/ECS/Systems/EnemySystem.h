#pragma once

#include "../System.h"
#include "../Components/Enemy.h"


struct EnemySystem : ECS::System
{
	EnemySystem()
	{
		std::cout << "EnemySystem created" << std::endl;
	}

private: // temp for test
		Vec2 left = { -1, 0 };
		Vec2 right = { 1, 0 };
		Vec2 up = { 0, -1 };
		Vec2 down = { 0, 1 };
		Vec2 down_left = { -1, 1 };
		Vec2 down_right = { 1, 1 };
		Vec2 up_left = { -1, -1 };
		Vec2 up_right = { 1, -1 };

public:

	void init();
	void update(const float delta_time);

	float time = 0;
	std::vector<Enemy> enemies;


	// wave stuff
	void create_grid(int rows, int cols);
	void start_wave();
	void spawn_at_location(Vec2 position);

	std::vector<Vec2> start_locations;
	float wave_timer = 0;
	std::vector<ECS::Entity> wave_ids;

};