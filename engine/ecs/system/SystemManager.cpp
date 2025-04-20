
#include "SystemManagerPrivate.h"

namespace UnknownEngine {
	SystemManager::SystemManager() : impl(std::make_unique<Impl>()) {}

	SystemManager::~SystemManager() = default;

	SystemManager::Impl::Impl() {}

	SystemManager::Impl::~Impl() {}

	void SystemManager::Impl::UpdateEngineSystemsInternal() { 
		for (const auto& EngineSystem : EngineSystems) {
			EngineSystem->Update();
		}
	}

	void SystemManager::Impl::UpdateUserSystemsInternal() {
		for (const auto& UserSystem : UserSystems) {
			UserSystem->Update();
		}
	}
}
