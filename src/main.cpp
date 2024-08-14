#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../include/Utils.hpp"
#include "../include/Window.hpp"
#include "../include/LifeManager.hpp"
#include "../include/InputManager.hpp"

void Render(Window& window, LifeManager& manager)
{
    window.ClearScreen();

    //draw
    manager.Render();

    window.Display();
}

void Update(Window& window, LifeManager& manager, InputManager& inputManager)
{
    manager.Tick(inputManager);
    Render(window, manager);
}

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL Failed to INIT. Error : " << SDL_GetError() << std::endl;
    }

    if (!IMG_Init(IMG_INIT_PNG))
    {
        std::cout << "IMG Failed to INIT. Error : " << SDL_GetError() << std::endl;
    }

    int width = 1280;
    int height = 720;

    int scale = 10;

    Window window("Game of Life", width, height);
    LifeManager manager(window, width, height, scale);

    InputManager inputManager;

    bool gameRunning = true;

    SDL_Event event;

    const float timeStep = 0.01f;
    float accumulator = 0.0f;
    float currentTime = Utils::HireTimeInSeconds();

    // for my clock
    int fps = 30;
    double timePerTick = 1000/fps;
    double delta = 0;
    long now;
    long lastTime = SDL_GetTicks();
    long timer = 0;
    int ticks = 0;

    while (gameRunning)
    {
        int startTicks = SDL_GetTicks();

        float newTime = Utils::HireTimeInSeconds();
        float frameTime = newTime - currentTime;

        currentTime = newTime;

        accumulator += frameTime;

        while (accumulator >= timeStep)
        {
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    gameRunning = false;
                }
                else if (event.type == SDL_MOUSEBUTTONDOWN)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        inputManager.leftDown = true;
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        inputManager.rightDown = true;
                    }
                }
                else if (event.type == SDL_MOUSEBUTTONUP)
                {
                    if (event.button.button == SDL_BUTTON_LEFT)
                    {
                        inputManager.leftDown = false;
                    }
                    if (event.button.button == SDL_BUTTON_RIGHT)
                    {
                        inputManager.rightDown = false;
                    }
                }
                else if (event.type == SDL_MOUSEMOTION)
                {
                    inputManager.mouseX = event.motion.x;
                    inputManager.mouseY = event.motion.y;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    if (!(event.key.keysym.sym == SDLK_SPACE))
                    {
                        inputManager.keys[event.key.keysym.sym] = true;
                    }
                }
                else if (event.type == SDL_KEYUP)
                {
                    if (!(event.key.keysym.sym == SDLK_SPACE))
                    {
                        inputManager.keys[event.key.keysym.sym] = false;
                    }
                    else
                    {
                        inputManager.keys[event.key.keysym.sym] = !inputManager.keys[event.key.keysym.sym];
                    }
                }
            }

            accumulator -= timeStep;
        }
        //my clock below

        now = SDL_GetTicks();
        delta += (now - lastTime) / timePerTick;
        timer += (now - lastTime);
        lastTime = now;

        if (delta >= 1)
        {
            //update here
            Update(window, manager, inputManager);
            //update above
            ticks++;
            delta--;
        }

        if (timer >= 1000)
        {
            std::cout << "Ticks and Frames : " << ticks << std::endl;
            ticks = 0;
            timer = 0;
        }

        //my clock above

        int frameTicks = SDL_GetTicks() - startTicks;

        if (frameTicks < 1000 / window.GetRefreshRate())
        {
            SDL_Delay(1000 / window.GetRefreshRate() - frameTicks);
        }
    }

    manager.CleanUp();
    window.CleanUp();

    SDL_Quit();

    return 0;
}
