
#pragma once

#include <memory>
#include <unordered_map>
#include <typeindex>

namespace UnknownEngine {

	class ComponentManager {
	public:
		ComponentManager();
		~ComponentManager();

		template<typename T>
		void RegisterComponent(uint32_t entityID, std::shared_ptr<T> component) { impl->RegisterComponentInternal(entityID, component); }

		template<typename T>
		std::unordered_map<uint32_t, std::shared_ptr<T>> GetComponents() { return impl->GetComponentsInternal(); }

	private:
		struct Impl;
		std::unique_ptr<Impl> impl;
	};

}