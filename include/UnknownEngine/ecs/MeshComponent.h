
#pragma once

#include "Component.h"
#include "engine/resources/mesh/Mesh.h"
#include "engine/resources/mesh/MeshManager.h"
#include "engine/core/EngineContext.h"

#include <string>
#include <memory>
#include <iostream>

namespace UnknownEngine {
	struct MeshComponent : public Component {
	public:
		MeshComponent(const std::string& meshName, EngineContext& context);
		~MeshComponent();

		void Draw() const;
	private:
		unsigned int vao, vbo, ebo; 

		std::string meshName;
		std::shared_ptr<Mesh> mesh; 

		EngineContext& context; 

		void setupMesh(); 
	};
}