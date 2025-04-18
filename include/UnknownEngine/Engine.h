
#pragma once
#include <memory> 
#include "InputSystem.h" 

namespace UnknownEngine { 

	class Engine {
	public:
		Engine();
		~Engine();

		void Run(); 

		InputSystem& getInputSystem(); 

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;  
	};
}