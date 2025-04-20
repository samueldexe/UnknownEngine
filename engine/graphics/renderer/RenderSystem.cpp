
#include "RenderSystem.h"

#include "glad/glad.h"
#include "glfw/glfw3.h"

namespace UnknownEngine{
	RenderSystem::RenderSystem() {
		shaders["basic_shader_program"] = std::make_unique<Shader>("shaders/basic_vertex_shader.glsl", "shaders/basic_fragment_shader.glsl");
	}

	RenderSystem::~RenderSystem() {}

	RenderSystem::Update() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); 
		glClear(GL_COLOR_BUFFER_BIT); 

		shaders["basic_shader_program"]->Run();

		for (MeshComponent& meshComponent : meshComponents) {
			meshComponent.Draw();
		}
			
		glfwSwapBuffers(window);
	}
}
