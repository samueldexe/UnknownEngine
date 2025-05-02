
#pragma once

#include "engine/resources/mesh/MeshManager.h"
#include "engine/ecs/component/Component.h"

#include <memory>
#include <unordered_map>
#include <typeindex>
#include <string>

namespace UnknownEngine {

	class ComponentManager {
	public:
		ComponentManager();
		~ComponentManager();

		void Initialize(MeshManager* meshManager);

		template<typename T>
		void RegisterComponent(uint32_t entityID, std::unique_ptr<T> component) {
			components[typeid(T)][entityID] = std::move(component);
		}

		template<typename T>
		std::unordered_map<uint32_t, std::shared_ptr<T>> GetComponents() { 
			std::unordered_map<uint32_t, std::shared_ptr<T>> result;

			auto it = components.find(typeid(T));
			if (it == components.end()) return result;

			for (auto& componentPair : it->second) {
				auto entityID = componentPair.first;
				auto& basePtr = componentPair.second;

				if (auto derivedPtr = std::dynamic_pointer_cast<T>(basePtr)) { 
					result[entityID] = derivedPtr;
				}
			}

			return result;
		}

	private:
		std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::shared_ptr<Component>>> components;
		MeshManager* meshManager;
	};
}