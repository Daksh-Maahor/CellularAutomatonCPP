#ifndef INPUT_MANAGER_H_
#define INPUT_MANAGER_H_

#include <SDL2/SDL.h>

struct InputManager
{
    bool keys[256];
    bool leftDown = false;
    bool rightDown = false;
    int mouseX, mouseY;

    InputManager()
    {
        for (int i=0; i<256; i++)
        {
            keys[i] = false;
        }
        keys[SDLK_SPACE] = true;
    }
};

#endif
