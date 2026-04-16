#pragma once
#include <glad/gl.h>
#include <string_view>

class Shader {
public:
    static Shader* create(std::string_view vert, std::string_view frag);

    Shader();
    ~Shader();

    GLuint getHandle() const { return m_program; }

protected:
    bool createProgram(std::string_view vert, std::string_view frag);
    GLuint loadShader(std::string_view fileName, GLenum type);
    bool checkCompileError(GLuint shader);
    bool checkLinkError(GLuint program);

private:
    GLuint m_program;
};