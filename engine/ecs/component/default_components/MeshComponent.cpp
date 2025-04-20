
#include "MeshComponent.h"
#include "glad/glad.h"
//#include "thirdparty/glad/include/glad/glad.h"

namespace UnknownEngine {
	MeshComponent::MeshComponent(const std::string& meshName, const std::unique_ptr<MeshManager>& meshManager) : meshName(meshName) {
		mesh = meshManager->getMesh(meshName);

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
		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices), mesh->vertices.data(), GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->indices), mesh->indices.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(0);
	}

	void MeshComponent::Draw() const {
		glBindVertexArray(vao); 

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}
}