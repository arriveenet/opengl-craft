#pragma once
#include "Window.h"
#include <memory>

class Window;

class Application {
public:
    Application();
    ~Application();

    void run();

private:
    std::unique_ptr<Window> m_window;
};
