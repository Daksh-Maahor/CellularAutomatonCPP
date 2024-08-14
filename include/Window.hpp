#ifndef WINDOW_H_
#define WINDOW_H_

#include <SDL2/SDL.h>

class Window
{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    int width, height;
public:
    Window(const char* title, int width, int height);
    int GetRefreshRate();
    void CleanUp();

    void ClearScreen();
    void Display();

    void FillRect(int x, int y, int w, int h, int r, int g, int b);
    void RenderTexture(SDL_Texture* texture, int x, int y, int w, int h);

    int GetWidth() { return width; }
    int GetHeight() { return height; }

    SDL_Texture* LoadTexture(const char* path);
};

#endif
