
#pragma once

#include "engine/graphics/window/Window.h"
#include "engine/resources/mesh/MeshManager.h"
#include "engine/core/EngineContext.h"

#include "InputSystem.h"
#include "ComponentManager.h"
#include "EntityManager.h"
#include "SystemManager.h"

#include <memory>

namespace UnknownEngine { 

	class Engine {
	public:
		Engine();
		~Engine();

		void Initialize();
		void Start();

		EngineContext& getContext();

		InputSystem& getInputSystem(); 
		ComponentManager& getComponentManager();
		EntityManager& getEntityManager();
		SystemManager& getSystemManager();

		MeshManager& getMeshManager();

	private:
		void Run();
		void Shutdown();

		std::unique_ptr<InputSystem> inputSystem;
		std::unique_ptr<Window> window;
		std::unique_ptr<ComponentManager> componentManager;
		std::unique_ptr<EntityManager> entityManager;
		std::unique_ptr<SystemManager> systemManager;
		std::unique_ptr<MeshManager> meshManager;

		EngineContext context;
	};
}