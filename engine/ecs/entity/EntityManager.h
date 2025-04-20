
#pragma once

class EntityManager {
public:
	uint32_t nextEntityID;

	int CreateEntity() { return nextEntityID++;  }
};