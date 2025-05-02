
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
		window->Initialize();

		inputSystem = std::make_unique<InputSystem>(); 
		inputSystem->Initialize(window->getWindow()); 

		meshManager = std::make_unique<MeshManager>();
		entityManager = std::make_unique<EntityManager>();

		componentManager = std::make_unique<ComponentManager>(); 
		componentManager->Initialize(meshManager.get()); 

		context.meshManager = meshManager.get();
	}

	//Function that gets called when you start the engine
	void Engine::Start() {
		systemManager = std::make_unique<SystemManager>();
		systemManager->Initialize(componentManager.get());

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

