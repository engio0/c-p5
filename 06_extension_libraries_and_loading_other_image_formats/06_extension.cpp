#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <cstdio>
#include <string>

int main(int argc, char *argv[])
{
    char strBuffer[81];

    // SDL Initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        snprintf(strBuffer, 80, "SDL Init failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, strBuffer, "Error", MB_OK);
        return false;
    }

    // Create Window
    SDL_Window *window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          640, 480, SDL_WINDOW_SHOWN);
    if (!window) {
        snprintf(strBuffer, 80, "CreateWindow failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, strBuffer, "Error", MB_OK);
        return false;
    }

    // Initialize PNG
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        snprintf(strBuffer, 80, "SDL_image initialization failed! SDL Error: %s", IMG_GetError());
        MessageBox(NULL, strBuffer, "Error", MB_OK);
        return false;
    }

    // Load & optimize PNG
    SDL_Surface *loadedSurface = IMG_Load("loaded.png");
    if (!loadedSurface) {
        snprintf(strBuffer, 80, "Loading PNG failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, strBuffer, "Error", MB_OK);
        return false;
    }
    SDL_Surface *scrSurface = SDL_GetWindowSurface(window);
    SDL_Surface *optimizedSurface = SDL_ConvertSurface(loadedSurface, scrSurface->format, 0);
    if (!optimizedSurface) {
        snprintf(strBuffer, 80, "Optimization failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, strBuffer, "Error", MB_OK);
        return false;
    }
    SDL_FreeSurface(loadedSurface);
    
    // Main loop
    int quit = false;
    SDL_Event evt;

    while (!quit) {
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_BlitScaled(optimizedSurface, NULL, scrSurface, NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_FreeSurface(optimizedSurface);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
