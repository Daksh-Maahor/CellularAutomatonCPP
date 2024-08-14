#include "../include/LifeManager.hpp"

LifeManager::LifeManager(Window& win, int w, int h, int sc) : window(win), scale(sc)
{
    width = (w * extraTimes) / scale;
    height = (h * extraTimes) / scale;

    cells = new bool[width * height];
    next = new bool[width * height];

    xOffset = 0;
    yOffset = 0;

    aliveCell = window.LoadTexture("D:/Programming/CPP_PROJECTS/GameOfLifeV2/res/cell.png");

    Clear();
}

void LifeManager::Clear()
{
    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            cells[x + y * width] = false;
            next[x + y * width] = false;
        }
    }
}

void LifeManager::Tick(InputManager& manager)
{
    CheckInput(manager);
    if (!manager.keys[SDLK_SPACE])
    {
        for (int x=0; x < width; x++)
        {
            for (int y=0; y < height; y++)
            {
                next[x + y * width] = cells[x + y * width];
            }
        }

        for (int x=0; x<width; x++)
        {
            for (int y=0; y<height; y++)
            {
                bool currentCell = cells[x + y * width];
                int aliveNeighbours = 0;

                for (int dx = -1; dx <= 1; dx++)
                {
                    int tx = x + dx;
                    for (int dy = -1; dy <= 1; dy++)
                    {
                        if (dx == 0 && dy == 0)
                        {
                            continue;
                        }

                        int ty = y + dy;

                        if (tx < 0 || ty < 0)
                        {
                            continue;
                        }

                        if (tx >= width || ty >= height)
                        {
                            continue;
                        }

                        aliveNeighbours += cells[tx + ty * width] ? 1 : 0;
                    }
                }

                if (currentCell && (aliveNeighbours < 2 || aliveNeighbours > 3))
                {
                    next[x + y * width] = !currentCell;
                }

                if (!currentCell && aliveNeighbours == 3)
                {
                    next[x + y * width] = !currentCell;
                }
            }
        }

        for (int x=0; x < width; x++)
        {
            for (int y=0; y < height; y++)
            {
                cells[x + y * width] = next[x + y * width];
            }
        }
    }
}

void LifeManager::CheckInput(InputManager& manager)
{
    if (manager.keys[SDLK_SPACE])
    {
        if (manager.leftDown)
        {
            int x = (manager.mouseX + xOffset) / scale;
            int y = (manager.mouseY + yOffset) / scale;

            cells[x + y * width] = true;
        }
        if (manager.rightDown)
        {
            int x = (manager.mouseX + xOffset) / scale;
            int y = (manager.mouseY + yOffset) / scale;

            cells[x + y * width] = false;
        }
        if (manager.keys[SDLK_c])
        {
            Clear();
        }
    }
    if (manager.keys[SDLK_w])
    {
        yOffset -= scrollSpeed;
    }
    if (manager.keys[SDLK_s])
    {
        yOffset += scrollSpeed;
    }
    if (manager.keys[SDLK_a])
    {
        xOffset -= scrollSpeed;
    }
    if (manager.keys[SDLK_d])
    {
        xOffset += scrollSpeed;
    }
    if (xOffset < 0)
    {
        xOffset = 0;
    }
    if (xOffset >= width * scale - window.GetWidth())
    {
        xOffset = width * scale - window.GetWidth();
    }
    if (yOffset < 0)
    {
        yOffset = 0;
    }
    if (yOffset >= height * scale - window.GetHeight())
    {
        yOffset = height * scale - window.GetHeight();
    }
    if (manager.keys[SDLK_o])
    {
        xOffset = width * scale / 2;
        yOffset = height * scale / 2;
    }
    if (manager.keys[SDLK_i])
    {
        xOffset = 0;
        yOffset = 0;
    }
}

void LifeManager::Render()
{
    for (int x=0; x<width; x++)
    {
        for (int y=0; y<height; y++)
        {
            bool cell = cells[x + y * width];
            if (cell)
            {
                window.RenderTexture(aliveCell, x * scale - xOffset, y * scale - yOffset, scale, scale);
            }
        }
    }
}

void LifeManager::CleanUp()
{
    SDL_DestroyTexture(aliveCell);
    delete[] cells;
    delete[] next;
}
