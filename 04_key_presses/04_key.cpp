#include <SDL.h>
#include <string>
#include <windows.h>
#include <cstdio>

enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

bool init();
bool loadMedia();
void close();
SDL_Surface *loadSurface(std::string path);

SDL_Window *gWindow = NULL;
SDL_Surface *gScreenSurface = NULL;
SDL_Surface *gKeyPressSurface[KEY_PRESS_SURFACE_TOTAL];
SDL_Surface *gCurrentSurface = NULL;
char gBuffer[81];
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO)) {
        snprintf(gBuffer, 80, "SDL initialization failed! SDL Error: %s\n", SDL_GetError());
        MessageBox(NULL, gBuffer, "Error", MB_OK);
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        snprintf(gBuffer, 80, "Failed to create window! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, gBuffer, "Error", MB_OK);
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);

    return true;
}

SDL_Surface *loadSurface(std::string path)
{
    SDL_Surface *loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == NULL) {
        snprintf(gBuffer, 80, "Unable to load image %s! SDL error: %s\n", path.c_str(), SDL_GetError());
        MessageBox(NULL, gBuffer, "Error", MB_OK);
    }
    return loadedSurface;
}

bool loadMedia()
{
    gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("./press.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
        MessageBox(NULL, "Failed to load default image", "Error", MB_OK);
        return false;
    }

    gKeyPressSurface[KEY_PRESS_SURFACE_UP] = loadSurface("./up.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_UP] == NULL) {
        MessageBox(NULL, "Failed to load up image", "Error", MB_OK);
        return false;
    }

    gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] = loadSurface("./down.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_DOWN] == NULL) {
        MessageBox(NULL, "Failed to load down image", "Error", MB_OK);
        return false;
    }

    gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] = loadSurface("./left.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_LEFT] == NULL) {
        MessageBox(NULL, "Failed to load left image", "Error", MB_OK);
        return false;
    }

    gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] = loadSurface("./right.bmp");
    if (gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT] == NULL) {
        MessageBox(NULL, "Failed to load right image", "Error", MB_OK);
        return false;
    }

    return true;
}

void close()
{
    for (auto i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        SDL_FreeSurface(gKeyPressSurface[i]);
    }
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
}

int main(int argc, char *args[])
{
    if (!init()) {
        MessageBox(NULL, "Initialization Failed!", "Erro", MB_OK);
        return 1;
    }
    if (!loadMedia()) {
        MessageBox(NULL, "Loading Media Failed!", "Error", MB_OK);
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    case SDLK_q:
                        gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
                        quit = true;
                        break;
                    default:
                        gCurrentSurface = gKeyPressSurface[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
        }
        SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
    }

    close();

    return 0;
}
