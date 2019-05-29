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


bool loadMedia()
{
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
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }

            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_LEFT:
                        break;
                    case SDLK_RIGHT:
                        break;
                    case SDLK_q:
                        quit = true;
                        break;
                    default:
                        break;
                }
            }
        }

        SDL_RenderSetViewport(gRenderer, NULL);

        // Clear screen
        SDL_SetRenderDrawColor(gRenderer, 0x66, 0x66, 0x66, 0x66);
        SDL_RenderClear(gRenderer);

        // Render red filled rectangle
        SDL_Rect fillRect = { SCREEN_WIDTH/4, SCREEN_HEIGHT/4, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 };
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
        SDL_RenderFillRect(gRenderer, &fillRect);

        SDL_Rect clip = {100, 50, 400, 300};
        SDL_RenderSetViewport(gRenderer, &clip);

        // Render green outlined rectangle
        SDL_Rect outlineRect = { SCREEN_WIDTH/6, SCREEN_HEIGHT/6, SCREEN_WIDTH*2/3, SCREEN_HEIGHT*2/3 };
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        // Draw blue horizontal line
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
        SDL_RenderDrawLine(gRenderer, 0, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT/2);

        // Draw vertical line of yellow dots
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0x00, 0xff);
        for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH/2, i);
        }

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
