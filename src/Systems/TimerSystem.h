#pragma once

#include "../ECS/System.h"
#include "../ECS//ECS.h"
#include "../Components/Timer.h"


struct TimerSystem : ECS::System
{
	TimerSystem()
	{
		std::cout << "TimerSystem created" << std::endl;
	}

	void init()
	{
		auto& manager = ECS::ECSManager::get_instance();

		ECS::Signature signature;
		signature.set(manager.get_component_type<Timer>());
	}
	void update(const float delta_time)
	{
		/*
		auto& manager = ECS::ECSManager::get_instance();
		for (auto entity : entities)
		{
			auto& timer = manager.get_component<Timer>(entity);
			timer.elapsed += delta_time;
			timer_list.push_back(timer);
		}

		for (auto& timer : timer_list)
		{
		}
		*/
	}


	std::vector<Timer> timer_list;
};
