
#include "InputSystemPrivate.h"

using namespace UnknownEngine;

InputSystem::InputSystem() : impl(std::make_unique<Impl>()) {}

InputSystem::~InputSystem() = default;

void InputSystem::BindAction(const std::string& action, const std::string& keyName) {
    impl->BindActionInternal(action, keyName);
}

void InputSystem::BindAction(const std::string& action, const std::vector<std::string>& keyNames) {
    impl->BindActionInternal(action, keyNames);
}

bool InputSystem::IsActionPressed(const std::string& action) const {
    return impl->IsActionPressedInternal(action);
}

InputSystem::Impl::Impl() {
    keyNames["space"] = GLFW_KEY_SPACE; 
    keyNames["w"] = GLFW_KEY_W;
    keyNames["a"] = GLFW_KEY_A;
    keyNames["s"] = GLFW_KEY_S;
    keyNames["d"] = GLFW_KEY_D;
    keyNames["escape"] = GLFW_KEY_ESCAPE;
}

InputSystem::Impl::~Impl() {}

void InputSystem::Impl::UpdateInternal(GLFWwindow* window) {
    glfwPollEvents();

    for (int key = 0; key < 512; key++) {
        keys[key] = glfwGetKey(window, key) == GLFW_PRESS;  // Update key states
    }
}

void InputSystem::Impl::BindActionInternal(const std::string& action, const std::string& keyName) {
    auto it = keyNames.find(keyName);
    if (it != keyNames.end()) {
        actionBindings[action] = { it->second };  // Bind action to the GLFW key code
    }
    else {
        // Handle invalid key name
        std::cerr << "Invalid key name: " << keyName << std::endl;
    }
}

void InputSystem::Impl::BindActionInternal(const std::string& action, const std::vector<std::string>& keyNames) {
    for (auto& keyName : keyNames) {
        auto it = this->keyNames.find(keyName);
        if (it != this->keyNames.end()) {
            actionBindings[action] = { it->second };  // Bind action to the GLFW key code
        }
        else {
            // Handle invalid key name
            std::cerr << "Invalid key name: " << keyName << std::endl;
        }
    }
}

bool InputSystem::Impl::IsActionPressedInternal(const std::string& action) const {
    auto it = actionBindings.find(action);
    if (it != actionBindings.end()) {
        // Check if a binding is pressed
        for (int key : it->second) {
            if (keys[key]) {
                return true;
            }
        }
    }
    return false;
}