
#include "EnginePrivate.h"

namespace UnknownEngine {

	Engine::Engine() : impl(std::make_unique<Impl>()) {}
	Engine::~Engine() = default;

	void Engine::Initialize() { impl->InitializeInternal(); }

	void Engine::Update() { impl->UpdateInternal(); }

	void Engine::Shutdown() { impl->ShutdownInternal(); }

	InputSystem& Engine::getInputSystem() { return *impl->inputSystem; } 

	void Engine::Impl::InitializeInternal() {
		window = std::make_unique<Window>(1280, 720, "Test");
		inputSystem = std::make_unique<InputSystem>();
		//initialise window function here
	}

	void Engine::Impl::UpdateInternal() { 
		while (!window->ShouldClose()) {
			inputSystem->impl->UpdateInternal(window->getWindow()); 

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glfwSwapBuffers(window->getWindow());
		}
	}

	void Engine::Impl::ShutdownInternal() {
		//destroy window (glfw) function here
	}
}

