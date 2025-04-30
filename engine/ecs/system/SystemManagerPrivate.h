
#pragma once

#include <unordered_map>
#include <memory>
#include <vector>

#include "include/UnknownEngine/SystemManager.h" 
#include "System.h"

namespace UnknownEngine {
	struct SystemManager::Impl {
	public:
		Impl();
		~Impl();

		template<typename T>
		void RegisterUserSystem(std::function<std::shared_ptr<T>()> factory) {
			UserSystems.push_back(std::static_pointer_cast<System>(factory()));  
		}

		template<typename T>
		void RegisterEngineSystem(std::function<std::shared_ptr<T>()> factory) {
			EngineSystems.push_back(std::static_pointer_cast<System>(factory()));
		}

		void UpdateEngineSystemsInternal();
		void UpdateUserSystemsInternal();

		std::vector<std::shared_ptr<System>> UserSystems;
		std::vector<std::shared_ptr<System>> EngineSystems;
	};
}
