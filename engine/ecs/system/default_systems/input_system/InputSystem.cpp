
#include "include/UnknownEngine/InputSystem.h"

namespace UnknownEngine {
    InputSystem::InputSystem(GLFWwindow* window) {
        this->window = window;

        keyNames["space"] = GLFW_KEY_SPACE;
        keyNames["w"] = GLFW_KEY_W;
        keyNames["a"] = GLFW_KEY_A;
        keyNames["s"] = GLFW_KEY_S;
        keyNames["d"] = GLFW_KEY_D;
        keyNames["escape"] = GLFW_KEY_ESCAPE;
    }

    InputSystem::~InputSystem() = default;

    bool InputSystem::isKeyPressed(std::string key) { 
        return glfwGetKey(window, keyNames[key]) == GLFW_PRESS;
    }
}

