
#pragma once
#include "../../include/UnknownEngine/Engine.h" 
#include "../systems/input_system/InputSystemPrivate.h"
#include "window/Window.h"

#include "ecs/ComponentManagerPrivate.h"
#include "ecs/SystemManagerPrivate.h" 

#include <memory> 
#include <iostream>

namespace UnknownEngine {

	struct Engine::Impl {

		std::unique_ptr<InputSystem> inputSystem; 
		std::unique_ptr<Window> window;
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<SystemManager> systemManager;

		void InitializeInternal();
		void RunInternal();
		void ShutdownInternal();
	};
}