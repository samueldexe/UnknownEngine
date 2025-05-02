
#include "include/UnknownEngine/ComponentManager.h"
#include "include/UnknownEngine/ecs/MeshComponent.h"

namespace UnknownEngine {
	ComponentManager::ComponentManager() {}

	ComponentManager::~ComponentManager() = default;

	void ComponentManager::Initialize(MeshManager* meshManager) {
		this->meshManager = meshManager;
	}
}