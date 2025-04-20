
#pragma once

#include "include/UnknownEngine/ComponentManager.h" 
#include "Component.h"

namespace UnknownEngine {
	struct ComponentManager::Impl {
	public:
		Impl();
		~Impl();

		template<typename T>
		void RegisterComponentInternal(uint32_t entityID, std::shared_ptr<T> component) { 
			components[typeid(T)][entityID] = component;
		}

		template<typename T>
		std::unordered_map< uint32_t, std::shared_ptr<T>> GetComponentsInternal() {
			std::unordered_map < uint32_t, std::shared_ptr<T>> result;

			auto TypeIt = components.find(typeid(T));

			for (const auto& [entityID, basePtr] : TypeIt->second) {
				std::shared_ptr<T>  derivedPtr = std::dynamic_pointer_cast<T>(basePtr);
				if (derivedPtr) {
					result[entityID] = derivedPtr;
				}
			}

			return result;
		}

		std::unordered_map < std::type_index, std::unordered_map<uint32_t, std::shared_ptr<Component>>> components;
	};
}
