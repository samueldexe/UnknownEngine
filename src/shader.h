#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader 
{
public:
    unsigned int ID {};

    // Constructor generates our shader
    Shader(const char* vertexPath, const char* fragmentPath)
    {
        std::string vertexCode {};
        std::string fragmentCode {};
        std::ifstream vShaderFile {};
        std::ifstream fShaderFile {};

        // Enable exceptions for ifstream objects
        vShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        fShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // Open files
            vShaderFile.open(vertexPath);
            fShaderFile.open(fragmentPath);
            std::stringstream vShaderStream, fShaderStream;

            // Read file data into stringstream
            vShaderStream << vShaderFile.rdbuf();
            fShaderStream << fShaderFile.rdbuf(); 

            // Close the file
            vShaderFile.close();
            fShaderFile.close();

            // Convert our stream into string
            vertexCode = vShaderStream.str();
            fragmentCode = fShaderStream.str(); 
        }
        catch (std::ifstream::failure& e)
        {
            std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << std::endl;
        }

        const char* vShaderCode = vertexCode.c_str();
        const char* fShaderCode = fragmentCode.c_str();

        // Compile shaders
        unsigned int vertex, fragment;

        // Vertex shader
        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vShaderCode, NULL);
        glCompileShader(vertex);
        CheckCompileErrors(vertex, "VERTEX");

        // Fragment shader
        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fShaderCode, NULL);
        glCompileShader(fragment);
        CheckCompileErrors(fragment, "FRAGMENT");

        // Shader program
        ID = glCreateProgram();
        glAttachShader(ID, vertex); 
        glAttachShader(ID, fragment);
        glLinkProgram(ID);
        CheckCompileErrors(ID, "PROGRAM"); 

        // Delete shaders as they have been linked to the program
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }

    // Clean up opengl resources
    ~Shader()
    {
        glDeleteProgram(ID);
    }

    // Setting the current active glProgram
    void Use() const
    {
        glUseProgram(ID); 
    }

    // Utility uniform functions
    void SetInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void SetMat4(const std::string &name, const glm::mat4 &mat)
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }

private:

    // Utility function to check shader compilation/linking errors
    void CheckCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];

        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }

        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
                std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << std::endl;
            }
        }
    }
};

#endif
