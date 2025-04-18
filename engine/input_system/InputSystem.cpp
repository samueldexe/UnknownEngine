
#include "InputSystemPrivate.h"

using namespace UnknownEngine;

InputSystem::InputSystem() : impl(std::make_unique<Impl>()) {}

InputSystem::~InputSystem() = default;

bool InputSystem::isKeyPressed(std::string key) { return impl->isKeyPressedInternal(key); }

InputSystem::Impl::Impl() {
    keyNames["space"] = GLFW_KEY_SPACE; 
    keyNames["w"] = GLFW_KEY_W;
    keyNames["a"] = GLFW_KEY_A;
    keyNames["s"] = GLFW_KEY_S;
    keyNames["d"] = GLFW_KEY_D;
    keyNames["escape"] = GLFW_KEY_ESCAPE;
}

InputSystem::Impl::~Impl() {}

void InputSystem::Impl::Initialize(GLFWwindow* window) { 
    this->window = window; 
}

bool InputSystem::Impl::isKeyPressedInternal(std::string key) {
    return glfwGetKey(window, keyNames[key]) == GLFW_PRESS;
}