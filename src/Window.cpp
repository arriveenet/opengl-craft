#include "Window.h"

#include <stdio.h>

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}


std::unique_ptr<Window> Window::create(std::string_view title,
                                        int width,
                                        int height)
{
    std::unique_ptr<Window>result = std::make_unique<Window>(title, width, height);
    if (result->init()) {
        return result;
    }

    return nullptr;
}

Window::Window()
    : m_title("")
    , m_width(640)
    , m_height(480)
    , m_glfwWindow(nullptr)
{
}

Window::Window(std::string_view title, int width, int height)
    : m_title(title)
    , m_width(width)
    , m_height(height)
    , m_glfwWindow(nullptr)
{
}

Window::~Window()
{
    glfwDestroyWindow(m_glfwWindow);

    glfwTerminate();
}

void Window::setTitle(std::string_view title)
{
    glfwSetWindowTitle(m_glfwWindow, title.data());
}

bool Window::shouldClose()
{
    if (m_glfwWindow == nullptr)
        return false;

    return glfwWindowShouldClose(m_glfwWindow) == GLFW_TRUE;
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::swapBuffers()
{
    glfwSwapBuffers(m_glfwWindow);
}

bool Window::init()
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_glfwWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), nullptr, nullptr);
    if (!m_glfwWindow) {
        return false;
    }

    glfwSetKeyCallback(m_glfwWindow, key_callback);

    glfwMakeContextCurrent(m_glfwWindow);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    return true;
}
