#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Texture *gTexture = NULL;
int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;


bool init()
{
    char szBuffer[81]; 

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        wsprintf(szBuffer, "SDL Init failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        wsprintf(szBuffer, "CreateWindow failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        wsprintf(szBuffer, "CreateRendere failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        wsprintf(szBuffer, "SDL_image init failed! SDL Error: %s", IMG_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    return true;
}


SDL_Texture *loadTexture(std::string path)
{
    char szBuffer[81];
    SDL_Texture *newTexture = NULL;

    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        wsprintf(szBuffer, "IMG_Load failed! SDL_image Error: %s", IMG_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (!newTexture) {
        wsprintf(szBuffer, "SDL_CreateTextureFromSurface failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
    }

    SDL_FreeSurface(loadedSurface);

    return newTexture;
}


bool loadMedia()
{
    char szBuffer[81];

    gTexture = loadTexture("texture.png");
    if (!gTexture) {
        wsprintf(szBuffer, "loadTexture failed!", "Error", MB_OK);
        return false;
    }
    return true;
}


void close()
{
    SDL_DestroyTexture(gTexture);
    gTexture = NULL;
    SDL_DestroyRenderer(gRenderer);
    gRenderer = NULL;
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[])
{
    bool quit = false;
    SDL_Event e;

    if (!init()) {
        MessageBox(NULL, "main::init failed!", "Error", MB_OK);
        return 1;
    }
    
    if (!loadMedia()) {
        MessageBox(NULL, "main::loadMedia failed!", "Error", MB_OK);
        return 2;
    }

    while (!quit) {
        while (!SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);

        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
