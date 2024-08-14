#ifndef LIFE_MANAGER_H_
#define LIFE_MANAGER_H_

#include "Window.hpp"
#include "InputManager.hpp"

class LifeManager
{
private:
    Window& window;
    SDL_Texture* aliveCell;

    int extraTimes = 3;
    int width, height;
    int scale;

    bool* cells;
    bool* next;

    int xOffset;
    int yOffset;

    int scrollSpeed = 10;
public:
    LifeManager(Window& window, int width, int height, int scale);
    void Clear();
    void Tick(InputManager& manager);
    void CheckInput(InputManager& manager);
    void Render();
    void CleanUp();
};

#endif
