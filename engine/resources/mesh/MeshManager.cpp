
#include "MeshManager.h"

namespace UnknownEngine {
	MeshManager::MeshManager() {}

	MeshManager::~MeshManager() {}

	MeshManager::getMesh(const std::string& meshName) {
		if (meshes.find(meshName) == meshes.end()) {
			loadMesh(meshName, "path to meshes" + meshName + ".något");
		}
		else {
			return &meshes[meshName];
		}
	}

	MeshManager::loadMesh(const std::string& meshName, const std::string& fileName) {
		Mesh mesh;
		mesh.LoadFromFile(fileName);
		meshes[meshName] = mesh; 
	}
}