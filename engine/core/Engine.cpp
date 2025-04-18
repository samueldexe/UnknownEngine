
#include "EnginePrivate.h"

namespace UnknownEngine {

	Engine::Engine() : impl(std::make_unique<Impl>()) {}
	Engine::~Engine() = default; 

	InputSystem& Engine::getInputSystem() { return *impl->inputSystem; }

	void Engine::Run() { 

		impl->InitializeInternal(); 
		impl->RunInternal(); 
		impl->ShutdownInternal();  
	}

	void Engine::Impl::InitializeInternal() {
		window = std::make_unique<Window>(1280, 720, "Test"); 
		inputSystem = std::make_unique<InputSystem>(); 

		window->Initialize();
		inputSystem->impl->Initialize(window->getWindow()); 
	}

	void Engine::Impl::RunInternal() { 
		while (!window->ShouldClose()) {
			glfwPollEvents(); 

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window->getWindow()); 
		}
	}

	void Engine::Impl::ShutdownInternal() {
		window.reset();
		inputSystem.reset(); 
	}
}

