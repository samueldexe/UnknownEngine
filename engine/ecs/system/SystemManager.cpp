
#include "include/UnknownEngine/SystemManager.h"

namespace UnknownEngine {
	SystemManager::SystemManager() {}

	SystemManager::~SystemManager() = default;

	void SystemManager::Initialize(ComponentManager* componentManager) {
		this->componentManager = componentManager;

		RegisterEngineSystem<RenderSystem>([&]() {
			auto& meshComponents = componentManager.GetComponents<MeshComponent>();
			return std::make_shared<RenderSystem>(meshComponents);
		)};
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
