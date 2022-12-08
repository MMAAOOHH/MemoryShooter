#pragma once

#include "Types.h"

namespace ECS
{
	class System
	{

	protected:
		friend class SystemManager;
		std::set<Entity> entities;
		//Entity_Signature signature;
	};
}
