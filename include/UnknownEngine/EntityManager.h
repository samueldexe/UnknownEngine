
#pragma once

#include <memory>

namespace UnknownEngine {
	class EntityManager {
	public:
		EntityManager(); 
		~EntityManager();

		int CreateEntity();
	private:
		struct Impl;
		std::unique_ptr<Impl> impl;
	};
}