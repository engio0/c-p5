#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

class LTexture
{
    public:
        ~LTexture() { free(); }
        void free();
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        bool loadFromFile(std::string path);
#ifdef SDL_TTF_H_
        bool loadFromRenderedText(std::string text, SDL_Color color);
#endif
        void setColor(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(mTexture, r, g, b); }
        void setBlendMode(SDL_BlendMode blending) { SDL_SetTextureBlendMode(mTexture, blending); }
        void setAlpha(Uint8 alpha) { SDL_SetTextureAlphaMod(mTexture, alpha); }
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        // Pixel manipulators
        bool lockTexture();
        bool unlockTexture();
        void* getPixels();
        int getPitch();
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0, mHeight = 0;
        void* mPixels = NULL;
        int mPitch = 0;
};

bool init();
bool loadMedia();
void close();
bool checkCollision(SDL_Rect &a, SDL_Rect &b);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

int main(int, char**)
{
    setvbuf(stdout, NULL, _IONBF, 0);

    printf("entering main...\n");
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }
#ifdef _LOG_
    printf("main::init successful!\n");
#endif

    if (!loadMedia()) {
        printf("main::loadMedia failed!\n");
        return 2;
    }
#ifdef _LOG_
    printf("main::loadMedia successful!\n");
#endif

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
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}

void LTexture::free()
{
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::loadFromFile(std::string path)
{
    free();
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        printf("IMG_Load failed opening file %s! IMG_Error: %s\n", path.c_str(), IMG_GetError());
        return false;
    }
    SDL_Surface *formattedSurface = SDL_ConvertSurfaceFormat(loadedSurface, SDL_GetWindowPixelFormat(gWindow), 0);
    if (!formattedSurface) {
        printf("Unable to convert loaded surface to display format! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        printf("SDL_CreateTextureFromSurface failed!\n");
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(formattedSurface);
    SDL_FreeSurface(loadedSurface);
    return true;
}

#ifdef SDL_TTF_H_
bool LTexture::loadFromRenderedText(std::string text, SDL_Color color)
{
    free();
    SDL_Surface *tmpSurface =  TTF_RenderText_Solid(gFont, text.c_str(), color);
    if (!tmpSurface) {
        printf("TTF_RenderText_Solid failed!\n");
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        printf("SDL_CreateTextureFromSurface failed rendering from text\n");
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return true;
}
#endif

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &destRect, angle, center, flip);
}

bool init()
{
#ifdef _LOG_
    printf("entering init...\n");
#endif
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::SDL_Init successful!\n");
#endif

#ifdef SDL_IMG_H_
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::IMG_Init successful!\n");
#endif
#endif

#ifdef SDL_TTF_H_
    if (TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::TTF_Init successful!\n");
#endif
#endif

#ifdef SDL_MIX_H_
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::Mix_OpenAudio successful!\n");
#endif
#endif

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        printf("SDL_CreateWindow failed! in init\n");
        return false;
    }
#ifdef _LOG_
    printf("init::SDL_CreateWindow successful!\n");
#endif
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        printf("SDL_CreateRenderer failed in init\n");
        return false;
    }
#ifdef _LOG_
    printf("init::SDL_CreateRenderer successful!\n");
#endif
#ifdef SDL_TTF_H_
    gFont = TTF_OpenFont("./lazy.ttf", 28);
    if (!gFont) {
        printf("TTF_OpenFont failed! in init\n");
        return false;
    }
#ifdef _LOG_
    printf("init::TTF_OpenFont successful!\n");
#endif
#endif
    return true;
}

bool loadMedia()
{
//     if (!gDotTexture.loadFromFile("./dot.bmp")) {
//         printf("Failed to load dot texture!\n");
//         return false;
//     }
// #ifdef _LOG_
//     printf("loadMedia::loadFromFile dot.bmp successful!\n");
// #endif
//     if (!gTileTexture.loadFromFile("./tiles.png")) {
//         printf("Failed to load tile set texture!\n");
//         return false;
//     }
// #ifdef _LOG_
//     printf("loadMedia::loadFromFile tiles.png successful!\n");
// #endif
//     if (!setTiles(tiles)) {
//         printf("Failed to load tile set!\n");
//         return false;
//     }
// #ifdef _LOG_
//     printf("loadMedia::setTiles successful!\n");
// #endif
// 
    return true;
}

void close()
{
//    gPromptTexture.free();

//    Mix_FreeChunk(gScratch);
//    Mix_FreeChunk(gHigh);
//    Mix_FreeChunk(gMedium);
//    Mix_FreeChunk(gLow);
//
//    Mix_FreeMusic(gMusic);


#ifdef SDL_TTF_H_
    TTF_CloseFont(gFont);
#endif
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
#ifdef SDL_MIX_H_
    Mix_Quit();
#endif
#ifdef SDL_IMG_H_
    IMG_Quit();
#endif
    SDL_Quit();
}

bool checkCollision(SDL_Rect &a, SDL_Rect &b)
{
    if ( (a.x >= b.x + b.w) || (b.x >= a.x + a.w) ||
         (a.y >= b.y + b.h) || (b.y >= a.y + a.h) ) return false;
    return true;
}
