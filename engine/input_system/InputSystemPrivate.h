
#pragma once
#include "../../include/UnknownEngine/InputSystem.h" 
#include "../window/window.h"
#include <unordered_map>

namespace UnknownEngine {
    // Implementation class
    struct InputSystem::Impl {
        Impl();
        ~Impl(); 

        void UpdateInternal(GLFWwindow* window);  
        void BindActionInternal(const std::string& action, const std::string& keyName);
        void BindActionInternal(const std::string& action, const std::vector<std::string>& keyNames);
        bool IsActionPressedInternal(const std::string& action) const;

        bool keys[512] = { false };
        std::unordered_map<std::string, std::vector<int>> actionBindings;
        std::unordered_map<std::string, int> keyNames; 
    };
}