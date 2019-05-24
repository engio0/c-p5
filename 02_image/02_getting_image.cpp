#include <SDL.h>
#include <cstdio>

// Starts up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Frees media and shuts down SDL
void close();

// The window we'll be rendering to
SDL_Window *gWindow = NULL;

// The surface contained by the window, and the image we will load and show on the screen
SDL_Surface *gScreenSurface = NULL, *gHelloWorld = NULL;
const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL initialize failed! SDL_Error : %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window create failed! SDL_Error : %s\n", SDL_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

bool loadMedia()
{
//    gHelloWorld = SDL_LoadBMP("./hello_world.bmp");
    gHelloWorld = SDL_LoadBMP("./02_hello_world.bmp");
    if (gHelloWorld == NULL) {
        printf("Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError());
        return false;
    }
    return true;
}

void close()
{
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    SDL_Quit();
}

int main(int argc, char *argv[])
{
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    if (!loadMedia()) {
        printf("Failed to load media!\n");
        return 1;
    }

    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);
    SDL_UpdateWindowSurface(gWindow);
    SDL_Delay(2000);

    close();

    return 0;
}
