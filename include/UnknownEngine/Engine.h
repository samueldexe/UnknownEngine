
#pragma once

namespace UnknownEngine { 

	class InputSystem;
	class ComponentManager;
	class SystemManager;

	class Engine {
	public:
		Engine();
		~Engine();

		void Run(); 

		InputSystem& getInputSystem(); 
		ComponentManager& getComponentManager();
		SystemManager& getSystemManager();

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;  
	};
}