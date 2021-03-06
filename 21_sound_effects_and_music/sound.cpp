#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <cstdio>
#include <string>
#include <windows.h>

class LTexture
{
    public:
        ~LTexture() { if (mTexture) free(); }
        void free();
        bool loadFromFile(std::string path);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        void render(int x, int y, SDL_Rect *clip = NULL);
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

Mix_Music *gMusic = NULL;
Mix_Chunk *gScratch = NULL;
Mix_Chunk *gHigh = NULL;
Mix_Chunk *gMedium = NULL;
Mix_Chunk *gLow = NULL;
LTexture gPromptTexture;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;


void LTexture::free()
{
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::loadFromFile(std::string path)
{
    free();
    SDL_Surface *tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        MessageBoxA(NULL, "IMG_Load failed!", "Error", MB_OK);
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        printf("Error SDL_CreateTextureFromSurface in LTexture::loadFromFile\n");
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return true;
//    return (mTexture ? true : false);
}

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &destRect);
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        printf("SDL_CreateWindow failed! in init\n");
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        printf("SDL_CreateRenderer failed in init\n");
        return false;
    }
    return true;
}

bool loadMedia()
{
    if (!gPromptTexture.loadFromFile("./prompt.png")) {
        printf("Failed to load prompt texture!\n");
        return false;
    }

    gMusic = Mix_LoadMUS("./beat.wav");
    if (!gMusic) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    gScratch = Mix_LoadWAV("./scratch.wav");
    if (!gScratch) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    gHigh = Mix_LoadWAV("./high.wav");
    if (!gHigh) {
        printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    gMedium = Mix_LoadWAV("./medium.wav");
    if (!gHigh) {
        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }
    
    gLow = Mix_LoadWAV("./low.wav");
    if (!gHigh) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        return false;
    }

    return true;
}

void close()
{
    gPromptTexture.free();

    Mix_FreeChunk(gScratch);
    Mix_FreeChunk(gHigh);
    Mix_FreeChunk(gMedium);
    Mix_FreeChunk(gLow);

    Mix_FreeMusic(gMusic);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int, char*[])
{
    if (!init()) {
        printf("main::init() failed!\n");
        return 1;
    }
    if (!loadMedia()) {
        printf("main::loadMedia() failed!\n");
        return 1;
    }

    printf("init and loadMedia success!!!\n");

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_q:
                            quit = true;
                            break;
                        case SDLK_1:
                            Mix_PlayChannel(-1, gHigh, 0);
                            break;
                        case SDLK_2:
                            Mix_PlayChannel(-1, gMedium, 0);
                            break;
                        case SDLK_3:
                            Mix_PlayChannel(-1, gLow, 0);
                            break;
                        case SDLK_4:
                            Mix_PlayChannel(-1, gScratch, 0);
                            break;
                        case SDLK_9:
                            if (Mix_PlayingMusic() == 0) {
                                Mix_PlayMusic(gMusic, -1);
                            } else {
                                if (Mix_PausedMusic() == 1) {
                                    Mix_ResumeMusic();
                                } else {
                                    Mix_PauseMusic();
                                }
                            }
                            break;
                        case SDLK_0:
                            Mix_HaltMusic();
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);
        gPromptTexture.render(0, 0);
        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
