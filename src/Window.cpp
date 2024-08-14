#include "../include/Window.hpp"

#include <iostream>
#include <SDL2/SDL_image.h>

Window::Window(const char* title, int w, int h) : window(NULL), width(w), height(h)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS);

    if (window == NULL)
    {
        std::cout << "Window failed to init. Error : " << SDL_GetError() << std::endl;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

int Window::GetRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);

    SDL_DisplayMode mode;

    SDL_GetDisplayMode(displayIndex, 0, &mode);

    return mode.refresh_rate;
}

void Window::CleanUp()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

void Window::ClearScreen()
{
    SDL_RenderClear(renderer);
    FillRect(0, 0, width, height, 0, 0, 0);
}

void Window::Display()
{
    SDL_RenderPresent(renderer);
}

void Window::FillRect(int x, int y, int w, int h, int r, int g, int b)
{
    SDL_Rect fillRect = {x, y, w, h};

    SDL_SetRenderDrawColor(renderer, r, g, b, 1);

    SDL_RenderFillRect(renderer, &fillRect);
}

void Window::RenderTexture(SDL_Texture* texture, int x, int y, int w, int h)
{
    SDL_Rect destRect = {x, y, w, h};

    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

SDL_Texture* Window::LoadTexture(const char* path)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, path);

    if (texture == NULL)
    {
        std::cout << "Failed to load texture " << path << ". Error : " << SDL_GetError() << std::endl;
    }

    return texture;
}
