#pragma once

class Engine {
public:
    static Engine* getInstance();
    static void destroyInstance();

    ~Engine();

    void mainLoop();

private:
    bool init();

    void update(float deltaTime);

    void draw();

private:
    static Engine* s_sharedEngine;
};