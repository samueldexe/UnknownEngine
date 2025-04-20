
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
		void RegisterSystemInternal(std::unordered_map < uint32_t, std::shared_ptr<T>> components) {
			UserSystems.push_back(std::make_shared<T>(components));
		}

		void UpdateEngineSystemsInternal();
		void UpdateUserSystemsInternal();

		std::vector<std::shared_ptr<System>> UserSystems;
		std::vector<std::shared_ptr<System>> EngineSystems;
	};
}
