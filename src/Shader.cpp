#include "Shader.h"

#include <fstream>
#include <iostream>
#include <vector>

Shader* Shader::create(std::string_view vert, std::string_view frag)
{
    Shader* shader = new Shader();
    if (shader->createProgram(vert, frag)) {
        return shader;
    }

    delete shader;
    return nullptr;
}

Shader::Shader()
    : m_program(0)
{
}

Shader::~Shader()
{
}

bool Shader::createProgram(std::string_view vert, std::string_view frag)
{
    GLuint vertexShader = loadShader(vert, GL_VERTEX_SHADER);
    GLuint fragmentShader = loadShader(frag, GL_FRAGMENT_SHADER);

    if (vertexShader == 0 || fragmentShader == 0) {
        return false;
    }

    glCompileShader(vertexShader);
    if (!checkCompileError(vertexShader)) {
        return false;
    }

    glCompileShader(fragmentShader);
    if (!checkCompileError(fragmentShader))
        return false;

    m_program = glCreateProgram();

    glAttachShader(m_program, vertexShader);
    glAttachShader(m_program, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(m_program);
    if (!checkLinkError(m_program))
        return false;

    return true;
}

GLuint Shader::loadShader(std::string_view fileName, GLenum type)
{
    GLuint shader = 0;

    std::ifstream file(fileName.data(), std::ios::ate | std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "[Shader] " << fileName << "open failed!\n";
        return shader;
    }

    std::cout << "[Shader] " << fileName << "open suceeded.\n";

    const size_t fileSize = static_cast<size_t>(file.tellg());
    std::vector<char> buffer(fileSize);
    file.seekg(0).read(buffer.data(), fileSize);
    file.close();

    shader = glCreateShader(type);
    const GLchar* source = buffer.data();
    const GLint length = static_cast<GLint>(fileSize);
    glShaderSource(shader, 1, &source, &length);

    return shader;
}

bool Shader::checkCompileError(GLuint shader)
{
    GLint compiled;
    int size;
    int length;
    char* str;
    bool result = true;

    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled == GL_FALSE) {
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &size);
        if (size > 0) {
            str = (char*)malloc(size);
            glGetShaderInfoLog(shader, size, &length, str);
            printf("[Shader] Compile error: %s!\n", str);
            free(str);
            result = false;
        }
    }

    return result;
}

bool Shader::checkLinkError(GLuint program)
{
    GLint linked;
    int size;
    int length;
    char* str;
    bool result = true;

    glGetShaderiv(program, GL_LINK_STATUS, &linked);
    if (linked == GL_FALSE) {
        glGetShaderiv(program, GL_INFO_LOG_LENGTH, &size);
        if (size > 0) {
            str = (char*)malloc(size);
            glGetShaderInfoLog(program, size, &length, str);
            printf("[Shader] Link error: %s!\n", str);
            free(str);
            result = false;
        }
    }

    return result;
}
