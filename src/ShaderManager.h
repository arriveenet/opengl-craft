#pragma once
#include <cstdint>
#include <unordered_map>

class Shader;

enum class ShaderType : uint32_t {
    Basic,
    Max,
};

class ShaderManager {
public:
    static ShaderManager* getInstance();
    static void destroyInstance();

    ShaderManager(const ShaderManager&) = delete;
    ShaderManager& operator=(const ShaderManager&) = delete;
    ShaderManager(ShaderManager&&) = delete;
    ShaderManager&& operator==(ShaderManager&&) = delete;

    ~ShaderManager();

    Shader* getShader(ShaderType type);

private:
    ShaderManager();
    bool init();

private:
    static ShaderManager* s_sharedShaderManager;

    std::unordered_map<ShaderType, Shader*> m_shaderMap;
};
