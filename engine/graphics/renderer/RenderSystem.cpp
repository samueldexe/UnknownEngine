
#include "RenderSystem.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace UnknownEngine{
	RenderSystem::RenderSystem(const std::unordered_map < uint32_t, std::shared_ptr <MeshComponent>>& meshComponents, const std::unordered_map < uint32_t, std::shared_ptr <TransformComponent>>& transformComponents)
		: TransformComponents(transformComponents), MeshComponents(meshComponents) {
		shaders["basic_shader_program"] = std::make_unique<Shader>("engine/graphics/renderer/shaders/basic_vertex_shader.glsl", "engine/graphics/renderer/shaders/basic_fragment_shader.glsl");
	}

	RenderSystem::~RenderSystem() {} 

	void RenderSystem::Update() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 

		shaders["basic_shader_program"]->Run();  

		for (auto& it : MeshComponents) {
			if (it.second) {
				it.second->Draw(); 
			}
		}
	}
}
