#pragma once
#include <set>

namespace ECS
{
	class System;
	struct Component;

	const size_t MAX_ENTITY_COUNT = 1000;
	const size_t MAX_COMPONENT_COUNT = 16;

	using Entity_ID = size_t;
	using System_Type_ID = size_t;
	using Component_Type_ID = size_t;

	// set does not allow for duplicated values (an entity can only have one component of type))
	using Entity_Signature = std::set<Component_Type_ID>;

	inline static const Component_Type_ID get_runtime_comp_type_id()
	{
		static Component_Type_ID type_id = 0u;
		return type_id++;
	}

	inline static const System_Type_ID get_runtime_system_type_id()
	{
		static System_Type_ID type_id = 0u;
		return type_id++;
	}

	// Attach type ID to component class and return it
	template<typename T>
	inline static const Component_Type_ID component_type() noexcept
	{
		static_assert((std::is_base_of<Component, T>::value && !std::is_same<Component, T>::value), "INVALID TEMPLATE TYPE");
		static const Component_Type_ID type_id = get_runtime_comp_type_id();
		return type_id;
	}

	// Attach type ID to system class and return it
	template<typename T>
	inline static const System_Type_ID system_type() noexcept
	{
		static_assert((std::is_base_of<System, T>::value && !std::is_same<System, T>::value), "INVALID TEMPLATE TYPE");
		static const System_Type_ID type_id = get_runtime_system_type_id();
		return type_id;
	}
}
