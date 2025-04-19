
#include "RenderSystem.h"

namespace UnknownEngine{
	RenderSystem::RenderSystem() {}

	RenderSystem::~RenderSystem() {}

	RenderSystem::Initialize() {
		shaders["basic_shader_program"] = std::make_unique<Shader>("shaders/basic_vertex_shader.glsl", "shaders/basic_fragment_shader.glsl"); 
	}

	RenderSystem::Update() {
		shaders["basic_shader_program"]->Run(); 
	}
}
