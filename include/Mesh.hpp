#pragma once
#ifndef MESH_H_
#define MESH_H_

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <Shader.hpp>

struct Vertex{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 texCoord;
};

struct Texture {
    unsigned int id;
    std::string type;
};

class Mesh {
public:
    std::vector <Vertex> vertices;
    std::vector <unsigned int>indices;
    std::vector <Texture> textures;

    Mesh(std::vector<Vertex>vertices, std::vector<unsigned int>indices, std::vector<Texture>textures);
    void Draw(Shader shader);

private:
    unsigned int VAO, VBO, EBO;
    void setupMesh();
};

#endif