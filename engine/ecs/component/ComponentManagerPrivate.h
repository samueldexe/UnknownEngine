#pragma once

#include "include/UnknownEngine/ComponentManager.h"
#include "Component.h"

#include <unordered_map>
#include <typeindex>
#include <memory>

namespace UnknownEngine {
	struct ComponentManager::Impl {
	public:
		Impl();
		~Impl();

		template<typename T>
		void RegisterComponent(uint32_t entityID, std::shared_ptr<T> component) {
			components[typeid(T)][entityID] = component;
		}

		template<typename T>
		std::unordered_map<uint32_t, std::shared_ptr<T>> GetComponents() {
			std::unordered_map<uint32_t, std::shared_ptr<T>> result;

			auto it = components.find(typeid(T));
			if (it == components.end()) return result;

			for (const auto& [entityID, basePtr] : it->second) {
				if (auto derivedPtr = std::dynamic_pointer_cast<T>(basePtr)) {
					result[entityID] = derivedPtr;
				}
			}
			return result; 
		}

		std::unordered_map<std::type_index, std::unordered_map<uint32_t, std::shared_ptr<Component>>> components;
	};
}
