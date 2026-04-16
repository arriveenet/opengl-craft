#pragma once
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <string>
#include <memory>

class Window {
public:
    static std::unique_ptr<Window> create(std::string_view title, int width, int height);

    Window();
    Window(std::string_view title, int width, int height);
    ~Window();

    std::string getTitle() const { return m_title; }

    void setTitle(std::string_view title);

    int getWidth() const { return m_width; }

    int getHeight() const { return m_height; }

    bool shouldClose();

    void pollEvents();

    void swapBuffers();

protected:
    bool init();

private:
    std::string m_title;
    int m_width;
    int m_height;
    GLFWwindow* m_glfwWindow;
};