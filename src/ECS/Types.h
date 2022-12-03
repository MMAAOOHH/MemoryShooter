#pragma once
#include <bitset>
#include <set>
#include <iostream>

namespace ECS
{
	class System;
	struct Component;

	const size_t MAX_ENTITY_COUNT = 20000;
	const size_t MAX_COMPONENT_COUNT = 16;

	using Entity_ID = size_t;
	using System_Type = size_t;
	using Component_Type = size_t;

	using Entity_Signature = std::set<Component_Type>;
	using Signature = std::bitset<MAX_COMPONENT_COUNT>;




	inline static const Component_Type get_runtime_comp_type_id()
	{
		static Component_Type type_id = 0u;
		return type_id++;
	}

	inline static const System_Type get_runtime_system_type_id()
	{
		static System_Type type_id = 0u;
		return type_id++;
	}

	// Attach type ID to component class and return it
	template<typename T>
	const static Component_Type component_type() noexcept
	{
		static_assert((std::is_base_of<Component, T>::value && !std::is_same<Component, T>::value), "INVALID TEMPLATE TYPE");
		static const Component_Type type_id = get_runtime_comp_type_id();
		return type_id;
	}

	// Attach type ID to system class and return it
	template<typename T>
	const static System_Type system_type() noexcept
	{
		static_assert((std::is_base_of<System, T>::value && !std::is_same<System, T>::value), "INVALID TEMPLATE TYPE");
		static const System_Type type_id = get_runtime_system_type_id();
		return type_id;
	}
}
