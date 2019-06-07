#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <cstdio>

class Dot
{
    public:
        static const int DOT_WIDTH = 20, DOT_HEIGHT = 20;
        static const int DOT_VEL = 10;
        void handleEvent(SDL_Event& e);
        void move();
        void render();
    private:
        int mPosX = 0, mPosY = 0;
        int mVelX = 0, mVelY = 0;
};

class LTimer
{
    public:
        void start();
        void stop();
        void pause();
        void unpause();
        Uint32 getTicks();
        bool isStarted() { return mStarted; }
        bool isPaused() { return mPaused; }
    private:
        Uint32 mStartTicks = 0;
        Uint32 mPausedTicks = 0;
        bool mPaused = false;
        bool mStarted = false;
};

class LTexture
{
    public:
        ~LTexture() { free(); }
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

bool init();
void close();


const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gDotTexture;


int main(int, char*[])
{
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }
    if (!gDotTexture.loadFromFile("./dot.bmp")) {
        printf("loading texture failed!\n");
        return 1;
    }


    bool quit = false;
    SDL_Event e;

    Dot dot;

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
            dot.handleEvent(e);
        }

        dot.move();

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        dot.render();

        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
}

void Dot::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    if (e.type == SDL_KEYUP && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move()
{
    mPosX += mVelX;
    if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH)) {
        mPosX -= mVelX;
    }
    mPosY += mVelY;
    if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT)) {
        mPosY -= mVelY;
    }
}

void Dot::render()
{
    gDotTexture.render(mPosX, mPosY);
}

void LTimer::start()
{
    mStarted = true;
    mPaused = false;
    mStartTicks = SDL_GetTicks();
    mPausedTicks = 0;
}

void LTimer::stop()
{
    mStarted = false;
    mPaused = false;
    mStartTicks = 0;
    mPausedTicks = 0;
}

void LTimer::pause()
{
    if (mStartTicks && !mPaused) {
        mPaused = true;
        mPausedTicks = SDL_GetTicks() - mStartTicks;
        mStartTicks = 0;
    }
}

void LTimer::unpause()
{
    if (mStarted && mPaused) {
        mPaused = false;
        mStartTicks = SDL_GetTicks() - mPausedTicks;
        mPausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    Uint32 time = 0;
    if (mStarted) {
        if (mPaused) {
            time = mPausedTicks;
        } else {
            time = SDL_GetTicks() - mStartTicks;
        }
    }
    return time;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

#ifdef SDL_IMG_H_
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
#endif

#ifdef SDL_TTF_H_
    if (TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
#endif

#ifdef SDL_MIX_H_
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
        return false;
    }
#endif

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        printf("SDL_CreateWindow failed! in init\n");
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        printf("SDL_CreateRenderer failed in init\n");
        return false;
    }
#ifdef SDL_TTF_H_
    gFont = TTF_OpenFont("./lazy.ttf", 28);
    if (!gFont) {
        printf("TTF_OpenFont failed! in init\n");
        return false;
    }
#endif
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
    if (mTexture) free();

    SDL_Surface *tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        printf("IMG_Load file %s failed! IMG Error: %s", path.c_str(), IMG_GetError());
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        printf("SDL_CreateTextureFromSurface file %s failed! IMG Error: %s", path.c_str(), IMG_GetError());
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return true;
}

#ifdef SDL_TTF_H_
bool LTexture::loadFromRenderedText(std::string text, SDL_Color color)
{
    if (mTexture) free();

    SDL_Surface *tmpSurface = TTF_RenderText_Solid(gFont, text.c_str(), color);
    if (!tmpSurface) {
        printf("TTF_RenderText_Solif failed!\n");
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        printf("SDL_CreateTextureFromSurface failed!\n");
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;

    SDL_FreeSurface(tmpSurface);
    return true;
}
#endif

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &destRect);
}
