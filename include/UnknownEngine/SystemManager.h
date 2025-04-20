
#pragma once

#include <memory>
#include <unordered_map>

namespace UnknownEngine {
	class SystemManager {
	public:
		SystemManager();
		~SystemManager();

		template<typename T>
		void RegisterSystemInternal(std::unordered_map < uint32_t, std::shared_ptr<T>> components) { impl->RegisterSystemInternal(components); }

	private:
		struct Impl;
		std::unique_ptr<Impl> impl; 
	};
}
