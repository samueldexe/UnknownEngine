
#include "include/UnknownEngine/Engine.h"

namespace UnknownEngine {

	Engine::Engine() {}
	Engine::~Engine() = default; 

	EngineContext& Engine::getContext() { return context; }

	InputSystem& Engine::getInputSystem() { return *inputSystem; }
	ComponentManager& Engine::getComponentManager() { return *componentManager; } 
	EntityManager& Engine::getEntityManager() { return *entityManager; }
	SystemManager& Engine::getSystemManager() { return *systemManager; }
	MeshManager& Engine::getMeshManager() { return *meshManager; }

	//Function that initializes every subsystem
	void Engine::Initialize() {
		window = std::make_unique<Window>(1280, 720, "Test");  
		inputSystem = std::make_unique<InputSystem>(); 

		window->Initialize();
		inputSystem->Initialize(window->getWindow()); 

		entityManager = std::make_unique<EntityManager>();
		componentManager = std::make_unique<ComponentManager>(); 

		systemManager = std::make_unique<SystemManager>(); 
		systemManager->Initialize(componentManager.get()); 

		meshManager = std::make_unique<MeshManager>(); 

		context.meshManager = meshManager.get();
	}

	//Function that gets called when you start the engine
	void Engine::Start() {
		Run();
		Shutdown();
	}

	//Main loop
	void Engine::Run() { 
		while (!window->ShouldClose()) {
			glfwPollEvents(); 

			systemManager->UpdateSystems(); 

			glfwSwapBuffers(window->getWindow());
		}
	}

	//Cleanup
	void Engine::Shutdown() {
		window.reset();
		inputSystem.reset(); 
	}
}

