#pragma once

#include <algorithm>
#include <cassert>
#include <vector>

#include "Types.h"

namespace ECS
{
	class IComponentList
	{
	public:
		IComponentList() = default;
		virtual ~IComponentList() = default;
		virtual void erase(const Entity_ID entity){}
	};

	template<typename T>
	class ComponentList : public IComponentList
	{
	public:
		ComponentList() = default;
		~ComponentList() = default;


		void insert(const T& component)
		{
			auto comp = std::find_if(data.begin(), data.end(), [&](const T& c) { return c.get_id() == component.get_id(); });
			if (comp == data.end())
			{
				data.push_back(component);
			}
		}

		T& get(const Entity_ID entity)
		{
			auto comp = std::find_if(data.begin(), data.end(), [&](const T& c) { return c.get_id() == entity; });
			assert(comp != data.end() && "Trying to get non-existing component!");
			return *comp;
		}

		void erase(const Entity_ID entity) override final
		{
			auto comp = std::find_if(data.begin(), data.end(), [&](const T& c) { return c.get_id() == entity; });
			if (comp != data.end())
			{
				data.erase(comp);
			}
		}

		// Use array instead?
		std::vector<T> data;
	};
}
