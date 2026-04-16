#include "Application.h"

#include "Engine.h"
#include "Window.h"

Application::Application()
{
}

Application::~Application()
{
}

void Application::run()
{
    m_window = Window::create("OpenGL Craft", 800, 600);

    Engine* engien = Engine::getInstance();

    while (!m_window->shouldClose()) {
        m_window->pollEvents();

        engien->mainLoop();

        m_window->swapBuffers();
    }

    Engine::destroyInstance();
}
