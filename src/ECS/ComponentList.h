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

		// TODO: make more memory oriented structure. 
		void insert(const T& component)
		{
			// check list, if component id matches existing id, if not add to list
			auto comp = std::find_if(data.begin(), data.end(), [&](const T& c) { return c.get_id() == component.get_id(); });
			if (comp == data.end())
			{

				data.push_back(component);
			}
		}

		T& get(const Entity_ID entity)
		{
			// check list, if component id matches entity id (if entity has component)
			auto comp = std::find_if(data.begin(), data.end(), [&](const T& c) { return c.get_id() == entity; });
			assert(comp != data.end() && "Trying to get non-existing component!");
			return *comp;
		}

		// TODO: make more memory oriented structure
		void erase(const Entity_ID entity) override final
		{
			// check list, if component id matches entity id (if entity has component)
			auto comp = std::find_if(data.begin(), data.end(), [&](const T& c) { return c.get_id() == entity; });
			if (comp != data.end())
			{
				// TODO: might be a slow operation. Just erasing the data at the index also fragments the list.
				data.erase(comp);
			}
		}

		std::vector<T> data;
	};
}
