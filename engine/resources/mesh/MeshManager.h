
#pragma once

#include "Mesh.h"

#include <unordered_map>
#include <string>

namespace UnknownEngine {
	class MeshManager {
	public:
		MeshManager();
		~MeshManager();

		Mesh* getMesh(const std::string& meshName);
	private:
		void loadMesh(const std::string& meshName, const std::string& fileName);
		std::unordered_map < std::string, Mesh> meshes;
	};
}