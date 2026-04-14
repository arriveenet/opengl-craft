#include "Application.h"
#include <GLFW/glfw3.h>

void Application::run()
{
    GLFWwindow* window;

    if (!glfwInit()) {
        return;    
    }

    window = glfwCreateWindow(640, 480, "OpenGL Craft", nullptr, nullptr);
    if (!window) {
        return;
    }

    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents(); 

        update(0.0f);
        draw();
    
        glfwSwapBuffers(window);
    }

    glfwDestroyWindow(window);

    glfwTerminate();

}

void Application::update(float deltaTime)
{
}

void Application::draw()
{
}
