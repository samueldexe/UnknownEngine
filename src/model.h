
#ifndef MODEL_H
#define MODEL_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "shader.h"
#include "mesh.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <memory>

unsigned int TextureFromFile(const char *path, const std::string &directory);

// An model class that holds all the meshes of a model
class Model
{
public:
    // Model data
    std::vector<Texture> textures_loaded; // we store all the currently loaded textures, so that we wont load the same texture twice
    std::vector<std::unique_ptr<Mesh>> meshes;
    std::string directory;

    Model(std::string const &path)
    {
        LoadModel(path);
    }

    ~Model() {}

    // Function to draw model
    void Draw(Shader &shader)
    {
        for (int i = 0; i < meshes.size(); i++)
        {
            meshes[i]->Draw(shader);
        }
    }

private:
    // Function to load a model from assimp format into custom meshes for opengl
    void LoadModel(std::string const &path)
    {
        // Read file from assimp
        Assimp::Importer importer;
        const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
        // Check for errors
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
            return;
        }

        // Get the directory of the filepath
        directory = path.substr(0, path.find_last_of('/'));

        // Process the assimp rootnode recursively
        ProcessNode(scene->mRootNode, scene);
    }

    // Function to process a node in recursive fashion. Each node creates its own mesh and then checks all its childnodes
    void ProcessNode(aiNode *node, const aiScene *scene)
    {
        // Process each mess in the current node
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
            meshes.push_back(ProcessMesh(mesh, scene));
        }

        // We now recursively check all the childnodes
        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    // Function to create a custom mesh from the assimp mesh format
    std::unique_ptr<Mesh> ProcessMesh(aiMesh *mesh, const aiScene *scene)
    {
        // Data to fill
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        // Go through all of the vertices in the mesh
        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            glm::vec3 vector;

            // Position
            vector.x = mesh->mVertices[i].x;
            vector.y = mesh->mVertices[i].y;
            vector.z = mesh->mVertices[i].z;
            vertex.Position = vector;

            // Normal
            if (mesh->HasNormals())
            {
                vector.x = mesh->mNormals[i].x;
                vector.y = mesh->mNormals[i].y;
                vector.z = mesh->mNormals[i].z;
                vertex.Normal = vector;
            }

            // Texcoord
            if (mesh->mTextureCoords[0])
            {
                glm::vec2 vec;

                // Note that a vertex can contain 8 different texture coordinates
                vec.x = mesh->mTextureCoords[0][i].x;
                vec.y = mesh->mTextureCoords[0][i].y;
                vertex.TexCoord = vec;
            }
            else
                vertex.TexCoord = glm::vec2(0.0f);

            vertices.push_back(vertex);
        }

        // Now go through all of the faces of the mesh
        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int k = 0; k < face.mNumIndices; k++)
            {
                indices.push_back(face.mIndices[k]);
            }
        }

        // Now we process material
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];

        /*
            We assume that we have an standard sampler name convention.
            Each texture sampler should be named as follow (where N ranges from 1 to the maximum samplers):
            diffuse: texture_diffuseN
            specular: texture_specularN
        */

        // Diffuse maps
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // Specular maps
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

        return std::make_unique<Mesh>(vertices, indices, textures);
    }

    // Function to check all material textures and load them if they haven't already
    std::vector<Texture> LoadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName)
    {
        std::vector<Texture> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            // We check if this texture has been loaded before
            bool skip = false;
            for (unsigned int k = 0; k < textures_loaded.size(); k++)
            {
                if (std::strcmp(textures_loaded[k].path.data(), str.C_Str()) == 0)
                {
                    textures.push_back(textures_loaded[k]);
                    skip = true;
                    break;
                }
            }

            // Texture hasn't been loaded before
            if (!skip)
            {
                Texture texture;
                texture.id = TextureFromFile(str.C_Str(), this->directory);
                texture.type = typeName;
                texture.path = str.C_Str();
                textures.push_back(texture);
                textures_loaded.push_back(texture);
            }
        }
        return textures;
    }

    // Function to read a texture from a file
    unsigned int TextureFromFile(const char *path, const std::string &directory)
    {
        std::string filename = std::string(path);
        filename = directory + '/' + filename;

        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }
};

#endif