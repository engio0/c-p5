#include <SDL.h>

int main(int argc, char *args[])
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Surface *surface;
    SDL_Event e;
    bool quit = false;

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               640, 480, SDL_WINDOW_SHOWN);
    surface = SDL_LoadBMP("./x.bmp");

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        SDL_BlitSurface(surface, NULL, SDL_GetWindowSurface(window), NULL);
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);

    return 0;
}
