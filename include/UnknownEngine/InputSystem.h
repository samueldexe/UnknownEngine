
#pragma once

#include <string>
#include <vector>
#include <memory> 
#include <unordered_map>

#include "GLFW/glfw3.h"

namespace UnknownEngine { 
  
    class InputSystem {
    public:
        InputSystem();
        ~InputSystem();

        void Initialize(GLFWwindow* window); 

        bool isKeyPressed(std::string key); 

    private: 
        GLFWwindow* window; 
        std::unordered_map<std::string, int> keyNames;
    };
}