
#pragma once

#include <memory>

namespace UnknownEngine {
	class EntityManager {
	public:
		EntityManager(); 
		~EntityManager();

		int CreateEntity(); 
	private:
		uint32_t nextEntityID;
	};
}