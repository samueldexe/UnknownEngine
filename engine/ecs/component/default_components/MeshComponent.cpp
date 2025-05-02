
#include "include/UnknownEngine/ecs/MeshComponent.h"
#include "glad/glad.h"

namespace UnknownEngine {
	MeshComponent::MeshComponent(const std::string& meshName, EngineContext& context) : meshName(meshName), context(context) {
		
		//mesh = context.meshManager->getMesh(meshName); 

		mesh = std::make_shared<Mesh>();

		mesh->vertices = { 0.5f, 0.5f, 0.0f,  // top right
			0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f, 0.5f, 0.0f };
		mesh->indices = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
		}; 

		if (mesh) {
			setupMesh();
		}
		else {
			std::cout << "ERROR::MESH::NOT_FOUND::" + meshName << std::endl;
		}
	}

	MeshComponent::~MeshComponent() {}

	void MeshComponent::setupMesh() {
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo);
		glGenBuffers(1, &ebo);

		glBindVertexArray(vao);

		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, mesh->vertices.size() * sizeof(float), mesh->vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->indices.size() * sizeof(unsigned int), mesh->indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}


	void MeshComponent::Draw() const { 
		glBindVertexArray(vao); 

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}