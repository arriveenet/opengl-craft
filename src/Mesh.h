#pragma once
#include <glm/glm.hpp>
#include <vector>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};

class Mesh {
public:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned short> m_indices;

    Mesh();
    virtual ~Mesh();
};