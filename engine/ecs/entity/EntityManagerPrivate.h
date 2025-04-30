
#pragma once

#include "include/UnknownEngine/EntityManager.h"

namespace UnknownEngine{
	struct EntityManager::Impl {
	public:
		Impl();
		~Impl();

		int CreateEntityInternal();

		uint32_t nextEntityID;
	};
}