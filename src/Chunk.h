#pragma once
#include "Mesh.h"

constexpr int CHUNK_SIZE = 16;

class Chunk {
public:
    Chunk();
    virtual ~Chunk();

    void update();

    void draw();

private:
    Mesh m_mesh;
};
