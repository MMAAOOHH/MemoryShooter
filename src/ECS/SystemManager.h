#pragma once

#include <cassert>
#include <map>
#include <unordered_map>

#include "System.h"
#include "Types.h"

namespace ECS
{
	class SystemManager
	{
	public:
		template<typename T>
		std::shared_ptr<T> register_system()
		{
			static_assert((std::is_base_of<System, T>::value && !std::is_same<System, T>::value), "INVALID TEMPLATE TYPE");

			const char* type = typeid(T).name();
			assert(registered_systems.find(type) == registered_systems.end() && "System already registered!");

			auto system = std::make_shared<T>();
			registered_systems.insert({ type, system });
			return system;
		}

		template<typename T>
		void set_system_signature(const Signature signature)
		{
			const char* type = typeid(T).name();
			assert(registered_systems.find(type) != registered_systems.end() && "System not registered.");
			registered_signatures.insert({ type, signature });
		}

		void remove_entity(const Entity_ID entity)
		{
			for (auto const& pair : registered_systems)
			{
				// Remove entity from system
				auto const& system = pair.second;
				system->entities.erase(entity);
			}
		}

		void entity_signature_changed(const Entity_ID entity, const Signature entity_signature)
		{
			for (auto const& pair : registered_systems)
			{
				auto const& type = pair.first;
				auto const& system = pair.second;
				auto const& system_signature = registered_signatures[type];

				/* Checks if entity belongs to system
				compares bitwise AND-result with system_signature bits
				( & = multiplying the bits )	*/
				if ((entity_signature & system_signature) == system_signature)
				{
					// Add entity to system
					system->entities.insert(entity);
				}
				else
				{
					// Remove entity from system
					system->entities.erase(entity);
				}
			}
		}

	private:
			std::unordered_map<const char*, std::shared_ptr<System>> registered_systems;
			std::unordered_map<const char*, Signature> registered_signatures;
		};
}