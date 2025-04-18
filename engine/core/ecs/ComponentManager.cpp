
#include "ComponentManagerPrivate.h"

namespace UnknownEngine {
	ComponentManager::ComponentManager() : impl(std::make_unique<Impl>()) {}

	ComponentManager::~ComponentManager() = default;

	ComponentManager::Impl::Impl() {}

	ComponentManager::Impl::~Impl() {}
}