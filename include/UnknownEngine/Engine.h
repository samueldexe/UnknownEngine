
#pragma once

#include <memory>

namespace UnknownEngine { 

	class InputSystem;
	class ComponentManager;
	class EntityManager;
	class SystemManager;

	class Engine {
	public:
		Engine();
		~Engine();

		void Run();  

		InputSystem& getInputSystem(); 
		ComponentManager& getComponentManager();
		EntityManager& getEntityManager();
		SystemManager& getSystemManager();

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;  
	};
}