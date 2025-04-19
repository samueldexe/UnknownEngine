
#pragma once

#include "../ecs/System.h"
#include "../ecs/Component.h" 
#include "Shader.h"

#include <unordered_map>
#include <memory>

namespace UnknownEngine {
	class RenderSystem : System {
	public:
		RenderSystem();
		~RenderSystem();

		void Initialize();
		void Update() override;
		
	private:
		std::unordered_map < uint32_t, std::shared_ptr<Component>>* TransformComponents; 
		std::unordered_map < uint32_t, std::shared_ptr<Component>>* MeshComponents; 

		std::unordered_map < std::string, std::unique_ptr<Shader>> shaders;
	}; 
}
