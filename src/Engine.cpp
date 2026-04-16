#include "Engine.h"
#include "ShaderManager.h"

Engine* Engine::s_sharedEngine = nullptr;

Engine* Engine::getInstance()
{
    if (s_sharedEngine == nullptr) {
        s_sharedEngine = new Engine();
        s_sharedEngine->init();
    }
    return s_sharedEngine;
}

void Engine::destroyInstance()
{
    delete s_sharedEngine;
    s_sharedEngine = nullptr;
}

Engine::~Engine()
{
    ShaderManager::destroyInstance();
}

void Engine::mainLoop()
{
    update(0.0f);
    draw();
}

bool Engine::init()
{
    return true;
}

void Engine::update(float deltaTime)
{
}

void Engine::draw()
{
}
