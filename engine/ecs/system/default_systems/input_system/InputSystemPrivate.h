
#pragma once
#include "../../../../include/UnknownEngine/InputSystem.h" 
#include "../../../graphics/window/Window.h"
#include <unordered_map>

namespace UnknownEngine {
    // Implementation class
    struct InputSystem::Impl {
        Impl();
        ~Impl(); 

        void Initialize(GLFWwindow* window);   
        bool isKeyPressedInternal(std::string key); 

        GLFWwindow* window;
        std::unordered_map<std::string, int> keyNames; 
    };
}