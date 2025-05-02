
#pragma once

#include "componentManager.h"
#include "engine/ecs/system/System.h"
#include "engine/graphics/renderer/RenderSystem.h"

#include <memory>
#include <unordered_map>
#include <functional>

namespace UnknownEngine {
	class SystemManager {
	public:
		SystemManager();
		~SystemManager();

		void Initialize(ComponentManager* componentManager);

		template<typename T>
		void RegisterUserSystem(std::function<std::shared_ptr<T>()> factory) {
			UserSystems.push_back(std::static_pointer_cast<System>(factory())); 
		}

		template<typename T>
		void RegisterEngineSystem(std::function<std::shared_ptr<T>()> factory) {
			EngineSystems.push_back(std::static_pointer_cast<System>(factory()));
		}

		void UpdateSystems();

	private:
		std::vector<std::shared_ptr<System>> UserSystems;
		std::vector<std::shared_ptr<System>> EngineSystems;
		std::unique_ptr<RenderSystem> renderingSystem;

		ComponentManager* componentManager;
	};
}
