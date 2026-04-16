#include "ShaderManager.h"
#include "Shader.h"

ShaderManager* ShaderManager::s_sharedShaderManager = nullptr;

ShaderManager* ShaderManager::getInstance()
{
    if (s_sharedShaderManager == nullptr) {
        s_sharedShaderManager = new ShaderManager();
        s_sharedShaderManager->init();
    }

    return s_sharedShaderManager;
}

void ShaderManager::destroyInstance()
{
    delete s_sharedShaderManager;
    s_sharedShaderManager = nullptr;
}

ShaderManager::ShaderManager()
{
}

ShaderManager::~ShaderManager()
{
    for (auto& program : m_shaderMap) {
        delete program.second;
        program.second = nullptr;
    }

    m_shaderMap.clear();
}

Shader* ShaderManager::getShader(ShaderType type)
{
    const auto& iter = m_shaderMap.find(type);
    if (iter != m_shaderMap.end()) {
        return iter->second;
    }

    return nullptr;
}

bool ShaderManager::init()
{
    Shader* shader = Shader::create("basic.vert", "basic.frag");
    m_shaderMap.emplace(ShaderType::Basic, shader);

    return true;
}
