
#pragma once

#include "../../ecs/system/System.h
#include "../../ecs/component/default_components/MeshComponent.h"
#include "Shader.h"

#include <unordered_map>
#include <memory>

namespace UnknownEngine {
	class RenderSystem : System {
	public:
		RenderSystem();
		~RenderSystem();

		void Update() override;
		
	private:
		std::unordered_map < uint32_t, std::shared_ptr<Component>>* TransformComponents; 
		std::unordered_map < uint32_t, std::shared_ptr<MeshComponent>>* MeshComponents;

		std::unordered_map < std::string, std::unique_ptr<Shader>> shaders;
	}; 
}
