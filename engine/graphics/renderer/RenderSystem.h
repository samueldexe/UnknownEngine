
#pragma once

#include "engine/ecs/system/System.h"
#include "include/UnknownEngine/ecs/MeshComponent.h"
#include "include/UnknownEngine/ecs/TransformComponent.h"
#include "Shader.h"

#include <unordered_map>
#include <memory>
#include <type_traits>
#include <iostream>

namespace UnknownEngine {
	class RenderSystem : public System {
	public:

		RenderSystem(const std::unordered_map < uint32_t, std::shared_ptr <MeshComponent>>& meshComponents, const std::unordered_map < uint32_t, std::shared_ptr <TransformComponent>>& transformComponents);
		~RenderSystem();

		void Update() override;
		
	private:
		std::unordered_map < uint32_t, std::shared_ptr<TransformComponent>> TransformComponents; 
		std::unordered_map < uint32_t, std::shared_ptr<MeshComponent>> MeshComponents; 

		std::unordered_map < std::string, std::unique_ptr<Shader>> shaders;
	}; 
}
