#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>

int main(int, char*[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;

    SDL_Window* hWindow = NULL;
    SDL_Renderer* hRenderer = NULL;
    const int WALKING_ANIMATION_FRAMES = 4;
    SDL_Rect hSpriteClips[WALKING_ANIMATION_FRAMES];
    SDL_Texture* hSpriteSheetTexture = NULL;

    hWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               0);
    hRenderer = SDL_CreateRenderer(hWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    {
        SDL_Surface* tmpSurface = NULL;
        tmpSurface = IMG_Load("./foo.png");
        hSpriteSheetTexture = SDL_CreateTextureFromSurface(hRenderer, tmpSurface);
        SDL_FreeSurface(tmpSurface);
    }

    for (int i = 0; i < 4; ++i) {
        hSpriteClips[i].x = 64 * i;
        hSpriteClips[i].y = 0;
        hSpriteClips[i].w = 64;
        hSpriteClips[i].h = 206;
    }

    SDL_Event evt;
    bool quit = false;
    int frame = 0;
    SDL_Rect* currentClip;
    while (!quit) {
        while (SDL_PollEvent(&evt)) {
            switch (evt.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (evt.key.keysym.sym) {
                        case SDLK_q:
                            quit = true;
                            break;
                        default:
                            break;
                    }
            }
        }
        currentClip = &hSpriteClips[frame / 4];
        SDL_RenderCopy(hRenderer, hSpriteSheetTexture, currentClip, NULL);
        SDL_RenderPresent(hRenderer);

        ++frame;
        if ((frame/4) >= WALKING_ANIMATION_FRAMES) {
            frame = 0;
        }
    }

    SDL_DestroyTexture(hSpriteSheetTexture);
    SDL_DestroyRenderer(hRenderer);
    SDL_DestroyWindow(hWindow);

    SDL_Quit();

    return 0;
} 
