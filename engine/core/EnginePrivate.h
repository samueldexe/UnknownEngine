
#pragma once
#include "../../include/UnknownEngine/Engine.h" 
#include "../input_system/InputSystemPrivate.h"
#include "../window/Window.h"
#include <memory> 

namespace UnknownEngine {

	struct Engine::Impl {

		std::unique_ptr<InputSystem> inputSystem; 
		std::unique_ptr<Window> window;

		void InitializeInternal();
		void UpdateInternal();
		void ShutdownInternal();
	};
}