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
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return (mTexture ? true : false);
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
    return true;
}

bool loadMedia()
{
    if (!gPromptTexture->loadFromFile("./prompt.png")) {
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
        printf("main::init failed!");
        return 1;
    }
    return 0;
}
