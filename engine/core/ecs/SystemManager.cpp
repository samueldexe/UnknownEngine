
#include "SystemManagerPrivate.h"

namespace UnknownEngine {
	SystemManager::SystemManager() : impl(std::make_unique<Impl>()) {}

	SystemManager::~SystemManager() = default;

	SystemManager::Impl::Impl() {}

	SystemManager::Impl::~Impl() {}

	SystemManager::Impl::UpdateEngineSystemsInternal() {
		for (const auto& EngineSystem : EngineSystems) {
			EngineSystem->Update();
		}
	}

	SystemManager::Impl::UpdateUserSystemsInternal() {
		for (const auto& UserSystem : UserSystems) {
			UserSystem->Update();
		}
	}
}
