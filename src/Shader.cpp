#include "Shader.h"

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

    glCompileShader(vertexShader);
    if (!checkCompileError(vertexShader)) {
        return false;
    }

    glCompileShader(fragmentShader);
    checkCompileError(fragmentShader);
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
    FILE* pFile;
    int size;
    char* buf;
    GLuint shader = 0;

    fopen_s(&pFile, fileName.data(), "rb");
    if (!pFile) {
        printf("[Shader] %s open feiled!\n", fileName.data());
        return 0;
    }
    printf("[Shader] %s open succeeded.\n", fileName.data());
    fseek(pFile, 0, SEEK_END);
    size = ftell(pFile);

    buf = (char*)malloc(size);
    fseek(pFile, 0, SEEK_SET);

    if (buf != 0) {
        fread(buf, 1, size, pFile);

        shader = glCreateShader(type);
        glShaderSource(shader, 1, (const GLchar**)&buf, &size);
    }
    free(buf);
    fclose(pFile);

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
