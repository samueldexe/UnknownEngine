
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.h"

#include <vector>
#include <string>

// Struct for a single vertex
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

// Struct for a single texture
struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

// An mesh class that holds the data for a single mesh that is drawn by the gpu
class Mesh {
public:
    // Mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    unsigned int VAO;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) : vertices(vertices), indices(indices), textures(textures) 
    {
        // Setup mesh
        SetupMesh();
    }

    ~Mesh()
    {
        // Cleanup vertex data 
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        // Cleanup texture data
        for (int i = 0; i < textures.size(); i++) {
            glDeleteTextures(1, &textures[i].id);
        }
    }

    // Draw function to render mesh
    void Draw(Shader &shader)
    {
        // Bind appropriate textures
        unsigned int diffuseNr = 1; 
        unsigned int specularNr = 1;

        for (unsigned int i = 0; i < textures.size(); i++) {
            glActiveTexture(GL_TEXTURE0 + i);

            std::string number;
            std::string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++);

            // Add "material." to the name as the textures are stored in a material struct in the shader
            name = "material." + name;

            // Now we set the sampler for this texture
            GLint loc = glGetUniformLocation(shader.ID, (name + number).c_str());
            if (loc == -1) {
                std::cout << "TEXTURE::SAMPLER::" << name << "NOT::FOUND" << std::endl;
            }
            glUniform1i(loc, i);
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    }   
private:
    // Render data variables
    unsigned int VBO, EBO;

    // Initialize the VBO and EBO
    void SetupMesh()
    {
        // Create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW); 
        
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // Setup vertex attribute pointers
        // vertex position
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0); 
        // vertex normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));
        // vertex texcoord
        glEnableVertexAttribArray(2);   
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoord)));
    }
}; 

#endif