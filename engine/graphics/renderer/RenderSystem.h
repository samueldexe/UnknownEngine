
#pragma once

#include "engine/ecs/system/System.h"
#include "include/UnknownEngine/ecs/MeshComponent.h"
#include "Shader.h"

#include <unordered_map>
#include <memory>
#include <type_traits>

namespace UnknownEngine {
	class RenderSystem : public System {
	public:

		template<typename T>
		RenderSystem(std::unordered_map < uint32_t, std::shared_ptr <T>> components) : TransformComponents(nullptr), MeshComponents(nullptr) {
			shaders["basic_shader_program"] = std::make_unique<Shader>("shaders/basic_vertex_shader.glsl", "shaders/basic_fragment_shader.glsl");

			if constexpr (std::is_same_v < T, MeshComponent>) {
				MeshComponents = &components;
			}
			else {
				TransformComponents = &components;
			}
		}

		~RenderSystem();

		void Update() override;
		
	private:
		std::unordered_map < uint32_t, std::shared_ptr<Component>>* TransformComponents; 
		std::unordered_map < uint32_t, std::shared_ptr<MeshComponent>>* MeshComponents; 

		std::unordered_map < std::string, std::unique_ptr<Shader>> shaders;
	}; 
}
