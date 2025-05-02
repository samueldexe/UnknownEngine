
#pragma once
 
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <iostream>

namespace UnknownEngine {
    class Window
    {
    public:
        Window(int width, int height, const char* title);
        ~Window();

        void Initialize();
        GLFWwindow* getWindow() const { return window; }
        bool ShouldClose() { return glfwWindowShouldClose(window) == 1; } 

    private: 
        int width, height;
        const char* title;
        GLFWwindow* window;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height); // static callback
    };
}

