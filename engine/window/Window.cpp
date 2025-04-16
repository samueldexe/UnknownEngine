
#include "Window.h"

using namespace UnknownEngine;

Window::Window(int width, int height, const char* title)
    : width(width), height(height), title(title), window(nullptr)
{
    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

Window::~Window()
{
    if (window)
    {
        glfwDestroyWindow(window);
    }
    glfwTerminate();
}

void Window::createWindow() 
{
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (window == nullptr) 
    {
        std::cout << "Failed to create GLFW window" << std::endl; 
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(EXIT_FAILURE); 
    }

    // Set viewport size callback
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
