
#pragma once
#include "../../include/UnknownEngine/Engine.h" 
#include "../ecs/system/default_systems/input_system/InputSystemPrivate.h"
#include "../graphics/window/Window.h"

#include "../ecs/component/ComponentManagerPrivate.h"
#include "../ecs/system/SystemManagerPrivate.h"

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