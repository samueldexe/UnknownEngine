
#include "include/UnknownEngine/EntityManager.h"

namespace UnknownEngine {
	EntityManager::EntityManager() : nextEntityID(0) {}

	EntityManager::~EntityManager() = default;

	int EntityManager::CreateEntity() { return nextEntityID++; }
}