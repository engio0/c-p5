#include <SDL.h>

int main()
{
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window *window;
    SDL_Surface *surface;

    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               640, 480, SDL_WINDOW_SHOWN);


    SDL_Delay(2000);

    SDL_DestroyWindow(window);

    return 0;
}
