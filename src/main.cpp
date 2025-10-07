
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"
#include "shader.h"
#include "model.h"

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>

// Declare callback functions
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *windpw, double xoffset, double yoffset);
void processInput(GLFWwindow *window);

// Window settings
const unsigned int SCREEN_WIDTH = 1280;
const unsigned int SCREEN_HEIGHT = 720;

// Camera object
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing
float deltaTime{};

int main()
{
    // glfw: initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    GLFWwindow *window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "UnknownEngine", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // Tell glfw to capture mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Tell stb_image.h to flip loaded textures on the y-axis, as opengl expects texcoord starting at the bottom left corner
    // while assimp saves them starting at top left corner
    stbi_set_flip_vertically_on_load(true);

    // Configure global OpenGL state
    glEnable(GL_DEPTH_TEST);

    // Build and compile our shader program
    Shader lightingShader("shaders/lighting_vs.glsl", "shaders/lighting_fs.glsl");
    Shader lightSourceShader("shaders/light_source_vs.glsl", "shaders/light_source_fs.glsl");

    // Load our model
    Model ourModel("resources/backpack/backpack.obj");

    // Vertex data for a cube light source
    float vertices[] = {
        // positions
        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,

        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,

        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,

        -0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, -0.5f,
        0.5f, -0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, -0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, 0.5f,
        -0.5f, 0.5f, -0.5f};

    // Positions of the point lights
    glm::vec3 pointLightPosition(1.0f, 1.0f, 5.0f);

    // Create our VAO for the cube light source
    unsigned int VBO, cubeLightSourceVAO;
    glGenVertexArrays(1, &cubeLightSourceVAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(cubeLightSourceVAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0); 
    glEnableVertexAttribArray(0);

    float fps = 60;
    float updateTime = (1.0 / fps);
    float previousTime = static_cast<float>(glfwGetTime());

    // Render loop
    while (!glfwWindowShouldClose(window))
    {
        deltaTime = static_cast<float>(glfwGetTime()) - previousTime;
        if (deltaTime > updateTime)
        {
            previousTime = static_cast<float>(glfwGetTime()); 

            // Input
            processInput(window);

            // Render
            glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            // Active shader
            lightingShader.Use();
            lightingShader.SetVec3("viewPos", camera.Position);
            lightingShader.SetFloat("material.shininess", 32.0f);

            // Directional light
            glm::vec3 dirLightColor = glm::vec3(0.0f, 0.4f, 0.0f);
            lightingShader.SetVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
            lightingShader.SetVec3("dirLight.ambient", 0.1f * dirLightColor);
            lightingShader.SetVec3("dirLight.diffuse", dirLightColor);
            lightingShader.SetVec3("dirLight.specular", glm::vec3(1.0f) * 0.95f + 0.05f * dirLightColor);
            // Point Light source colors
            glm::vec3 pointLightColor(0.9f, 0.9f, 0.9f);
            // point light 1
            lightingShader.SetVec3("pointLights[0].position", pointLightPosition);
            lightingShader.SetVec3("pointLights[0].ambient", 0.1f * pointLightColor);
            lightingShader.SetVec3("pointLights[0].diffuse", pointLightColor);
            lightingShader.SetVec3("pointLights[0].specular", glm::vec3(1.0f) * 0.95f + 0.05f * pointLightColor);
            lightingShader.SetFloat("pointLights[0].constant", 1.0f);
            lightingShader.SetFloat("pointLights[0].linear", 0.02f);
            lightingShader.SetFloat("pointLights[0].quadratic", 0.008f);
            // spotLight
            glm::vec3 spotLightColor = glm::vec3(0.7f, 0.7f, 0.0f);
            lightingShader.SetVec3("spotLight.position", camera.Position);
            lightingShader.SetVec3("spotLight.direction", camera.Front);
            lightingShader.SetVec3("spotLight.ambient", glm::vec3(0.0f));
            lightingShader.SetVec3("spotLight.diffuse", spotLightColor);
            lightingShader.SetVec3("spotLight.specular", glm::vec3(1.0f) * 0.95f + 0.05f * spotLightColor);
            lightingShader.SetFloat("spotLight.constant", 1.0f);
            lightingShader.SetFloat("spotLight.linear", 0.09f);
            lightingShader.SetFloat("spotLight.quadratic", 0.032f);
            lightingShader.SetFloat("spotLight.innerCutOffAngle", glm::cos(glm::radians(10.0f)));
            lightingShader.SetFloat("spotLight.outerCutOffAngle", glm::cos(glm::radians(12.5f)));

            // Projection / View transformations
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
            model = glm::scale(model, glm::vec3(1.0f));
            lightingShader.SetMat4("projection", projection);
            lightingShader.SetMat4("view", view);
            lightingShader.SetMat4("model", model);

            // Draw model
            ourModel.Draw(lightingShader);

            // also draw the lamp object(s)
            lightSourceShader.Use();
            lightSourceShader.SetMat4("projection", projection);
            lightSourceShader.SetMat4("view", view);

            // we now draw as many light bulbs as we have point lights.
            glBindVertexArray(cubeLightSourceVAO);
            model = glm::mat4(1.0f);
            model = glm::translate(model, pointLightPosition);
            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
            lightSourceShader.SetMat4("model", model);
            lightSourceShader.SetVec3("lightColor", pointLightColor);
            glDrawArrays(GL_TRIANGLES, 0, 36);

            // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
            glfwSwapBuffers(window);
            glfwPollEvents();
        }

        // Prevent cpu hog
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // De-allocate resources for vao and vbo
    glDeleteVertexArrays(1, &cubeLightSourceVAO);
    glDeleteBuffers(1, &VBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

// Process all input
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

// Window change callback function
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Mouse move callback function
void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // We reverse because y go from top to bottom

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// Mouse scroll callback function
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}
