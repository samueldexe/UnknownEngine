
#pragma once

#include "../Component.h"
#include "../../resources/mesh/Mesh.h"
#include "../../resources/mesh/MeshManager.h"

#include <string>
#include <memory>
#include <iostream>

namespace UnknownEngine {
	struct MeshComponent : Component {
	public:
		MeshComponent(const std::string& meshName, const std::unique_ptr<MeshManager>& meshManager);
		~MeshComponent();

		void Draw() const;
	private:
		unsigned int vao, vbo, ebo;

		std::string meshName;
		Mesh* mesh = nullptr; 

		void setupMesh(); 
	};
}