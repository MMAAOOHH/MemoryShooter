#include "EnemySystem.h"
#include "../Components/Weapon.h"

void EnemySystem::init()
{
	ECS::Signature signature;
	auto& manager = ECS::World::get_instance();
	signature.set(manager.get_component_type<Enemy>(), true);

	manager.set_system_signature<EnemySystem>(signature);

	create_grid_locations(4, 8);
}


void EnemySystem::update(const float delta_time)
{
	auto& manager = ECS::World::get_instance();

	if (entities.empty())
		start_wave();

	wave_time += delta_time;

	for (auto& e : entities)
	{
		auto& enemy = manager.get_component<Enemy>(e);
		auto& transform = manager.get_component<Transform>(e);
		auto& rb = manager.get_component<RigidBody>(e);
		auto& weapon = manager.get_component<Weapon>(e);

		if(enemy.state == EnemyState::entry)
		{
			if (wave_time < 2)
				transform.position = lerp(transform.position, { SCREEN_WIDTH * 0.5f ,50 }, delta_time / 0.5f);
			if (wave_time > 2)
				transform.position = lerp(transform.position, enemy.start_position, delta_time / 0.5f);
			if (wave_time >= 3)
				enemy.state = EnemyState::active;
		}

		if(enemy.state == EnemyState::active)
		{
			manager.get_component<Collider>(e).active = true;
			rb.velocity.y = 10;
			transform.position.x += sin(wave_time) * delta_time * 10;

			enemy.time += delta_time;
			if (enemy.time > 3)
			{
				weapon.shoot({ 0, 80 }, Tag::enemy_projectile);
				enemy.time = 0;
			}
		}
	} 
}


void EnemySystem::create_grid_locations(int rows, int cols)
{

	const float width = SCREEN_WIDTH / cols;
	const float height = SCREEN_HEIGHT / 3 / rows;

	start_locations.clear();

	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			const float x = width * j;
			const float y = height * i;

			Vec2 center;
			center.x = width * 0.5 + x;
			center.y = height * 0.5 + y;

			start_locations.push_back(center);
		}
	}
}

void EnemySystem::start_wave()
{
	wave_time = 0;
	wave_index++;

	for (int i = 0; i < 16; ++i)
	{
		const Vec2 spawn_pos = { SCREEN_WIDTH * 0.5f, -20 };
		spawn_enemy(spawn_pos, start_locations[i]);
	}
}


void EnemySystem::spawn_enemy(Vec2 spawn_pos, Vec2 start_pos)
{
	auto& manager = ECS::World::get_instance();
	auto id = manager.create_entity();
	manager.add_component<Enemy>(id);

	auto& enemy = manager.get_component<Enemy>(id);
	enemy.init();
	enemy.start_position = start_pos;
	enemy.state = EnemyState::entry;

	auto& t = manager.get_component<Transform>(id);
	auto& col = manager.get_component<Collider>(id);

	t.position = spawn_pos;
	col.active = false;
}
