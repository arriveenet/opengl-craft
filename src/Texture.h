#pragma once
#include <cstdint>

class Texture {
public:
    Texture();
    ~Texture();

    uint32_t getWidth() const noexcept { return m_width; }
    uint32_t getHeight() const noexcept { return m_height; }

private:
    uint32_t m_width;
    uint32_t m_height;
};
