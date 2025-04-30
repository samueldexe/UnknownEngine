
#pragma once
#include "include/UnknownEngine/Engine.h"
#include "graphics/window/Window.h" 

#include "ecs/system/default_systems/input_system/InputSystemPrivate.h" 
#include "graphics/renderer/RenderSystem.h"

#include "ecs/component/ComponentManagerPrivate.h" 
#include "ecs/entity/EntityManagerPrivate.h"
#include "ecs/system/SystemManagerPrivate.h"

#include <memory> 
#include <iostream>

namespace UnknownEngine {

	struct Engine::Impl {

		std::unique_ptr<InputSystem> inputSystem; 
		std::unique_ptr<Window> window;
		std::unique_ptr<ComponentManager> componentManager; 
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<SystemManager> systemManager;

		void InitializeInternal();
		void RunInternal() const;
		void ShutdownInternal();
	};
}