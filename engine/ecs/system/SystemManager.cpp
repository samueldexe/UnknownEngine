
#include "include/UnknownEngine/SystemManager.h"

namespace UnknownEngine {
	SystemManager::SystemManager() {}

	SystemManager::~SystemManager() = default;

	void SystemManager::Initialize(ComponentManager* componentManager) {
		this->componentManager = componentManager;

		renderingSystem = std::make_unique<RenderSystem>(
			componentManager->GetComponents<MeshComponent>(),
			componentManager->GetComponents<TransformComponent>()
		);
	}

	void SystemManager::UpdateSystems() { 
		//Upddate engine systems
		for (const auto& EngineSystem : EngineSystems) { 
			EngineSystem->Update();
		}

		//Update user definied systems
		for (const auto& UserSystem : UserSystems) {
			UserSystem->Update();
		}

		//Render the screen
		renderingSystem->Update();
	}
}
