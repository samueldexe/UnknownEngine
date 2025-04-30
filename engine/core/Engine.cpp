
#include "EnginePrivate.h"

namespace UnknownEngine {

	Engine::Engine() : impl(std::make_unique<Impl>()) {}
	Engine::~Engine() = default; 

	InputSystem& Engine::getInputSystem() { return *impl->inputSystem; }
	ComponentManager& Engine::getComponentManager() { return *impl->componentManager; } 
	EntityManager& Engine::getEntityManager() { return *impl->entityManager; }
	SystemManager& Engine::getSystemManager() { return *impl->systemManager; }

	//Function that gets called when you start the engine
	void Engine::Run() { 

		impl->InitializeInternal(); 
		impl->RunInternal(); 
		impl->ShutdownInternal();  
	}

	//Function that initializes every subsystem
	void Engine::Impl::InitializeInternal() {
		window = std::make_unique<Window>(1280, 720, "Test");  
		inputSystem = std::make_unique<InputSystem>(); 

		window->Initialize();
		inputSystem->impl->Initialize(window->getWindow()); 

		componentManager = std::make_unique<ComponentManager>(); 
		entityManager = std::make_unique<EntityManager>();
		systemManager = std::make_unique<SystemManager>();

		systemManager->impl->RegisterEngineSystem<RenderSystem>([&]() {
			auto& meshComponents = componentManager->GetComponents<MeshComponent>();
			return std::make_shared<RenderSystem>(meshComponents);
			});
	}

	//Main loop
	void Engine::Impl::RunInternal() const { 
		while (!window->ShouldClose()) {
			glfwPollEvents(); 

			glfwSwapBuffers(window->getWindow());
		}
	}

	//Cleanup
	void Engine::Impl::ShutdownInternal() {
		window.reset();
		inputSystem.reset(); 
	}
}

