
#pragma once

#include <memory>
#include <unordered_map>
#include <functional>

namespace UnknownEngine {
	class SystemManager {
	public:
		SystemManager();
		~SystemManager();

		template<typename T>
		void RegisterUserSystem(std::function<std::shared_ptr<T>()> factory);

	private:
		struct Impl;
		friend class Engine;
		std::unique_ptr<Impl> impl; 
	};
}
