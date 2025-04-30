
#include "EntityManagerPrivate.h"

namespace UnknownEngine {
	EntityManager::EntityManager(): impl(std::make_unique<Impl>()) {}

	EntityManager::~EntityManager() = default;

	int EntityManager::CreateEntity() { return impl->CreateEntityInternal(); }

	EntityManager::Impl::Impl() {}

	EntityManager::Impl::~Impl() {}

	int EntityManager::Impl::CreateEntityInternal() {
		return nextEntityID++;
	}
}