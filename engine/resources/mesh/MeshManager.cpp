
#include "MeshManager.h"

namespace UnknownEngine {
	MeshManager::MeshManager() {}

	MeshManager::~MeshManager() {}

	Mesh* MeshManager::getMesh(const std::string& meshName) {
		if (meshes.find(meshName) == meshes.end()) {
			loadMesh(meshName, "path to meshes" + meshName + ".något");
			return &meshes[meshName];
		}
		else {
			return &meshes[meshName];
		}
	}

	void MeshManager::loadMesh(const std::string& meshName, const std::string& fileName) {
		Mesh mesh; 
		mesh.LoadFromFile(fileName);
		meshes[meshName] = mesh; 
	}
}