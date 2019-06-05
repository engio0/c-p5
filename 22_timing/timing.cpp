#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <string>
#include <sstream>
#include <cstdio>
#include <windows.h>

class LTexture
{
    public:
        ~LTexture() { if (mTexture) free(); }
        void free();
        bool loadFromFile(std::string path);
        bool loadFromRenderedText(std::string text, SDL_Color color);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        void render(int x, int y, SDL_Rect *clip = NULL);
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
TTF_Font *gFont = NULL;
LTexture gPromptTexture;
LTexture gTimeTexture;


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

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (!textSurface) {
        printf("TTF_RenderText_Solid failed rendering \"%s\"", textureText.c_str());
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    if (!mTexture) {
        MessageBoxA(NULL, "SDL_CreateTextureFromSurface failed!", "Error", MB_OK);
        return false;
    }
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    return true;
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

bool loadMedia()
{
    gFont = TTF_OpenFont("./lazy.ttf", 28);
    if (!gFont) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
    SDL_Color textColor = {0, 0, 0, 255};
    if (!gPromptTexture.loadFromRenderedText("Press Enter to Reset Start Time.", textColor)) {
        printf("Unable to render prompt texture!\n");
        return false;
    }
    return true;
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

    if (TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
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

void close()
{
    gPromptTexture.free();

//    Mix_FreeChunk(gScratch);
//    Mix_FreeChunk(gHigh);
//    Mix_FreeChunk(gMedium);
//    Mix_FreeChunk(gLow);
//
//    Mix_FreeMusic(gMusic);

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

int main(int, char*[])
{
    if (!init()) {
        printf("main:init failed\n");
        return 1;
    }
    if (!loadMedia()) {
        printf("main::loadMedia failed\n");
        return 1;
    }

    bool quit = false;
    SDL_Event e;
    SDL_Color textColor = {0, 0, 0, 255};
    Uint32 startTime = 0;
    std::stringstream timeText;

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
                        case SDLK_RETURN:
                            startTime = SDL_GetTicks();
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }

        timeText.str("");
        timeText << "Milliseconds since start time " << SDL_GetTicks() - startTime;
        if (!gTimeTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
            printf("Unable to render time texture!\n");
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gPromptTexture.render((SCREEN_WIDTH - gPromptTexture.getWidth())/2, 0);
        gTimeTexture.render((SCREEN_WIDTH - gTimeTexture.getWidth())/2,
                            (SCREEN_HEIGHT - gPromptTexture.getHeight())/2);

        SDL_RenderPresent(gRenderer);
    }
    close();

    return 0;
}
