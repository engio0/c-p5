#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <sstream>
#include <string>

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


SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
LTexture gStartPromptTexture, gPausePromptTexture, gTimeTextTexture;

bool init();
void close();

int main(int, char*[])
{
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }

    SDL_Color textColor = {0, 0, 0, 255};
    if (!gStartPromptTexture.loadFromRenderedText("Press S to Start or Stop the Timer", textColor)) {
        printf("loadFromRenderedText StartPromptTexture failed!\n");
        return 1;
    }
    if (!gPausePromptTexture.loadFromRenderedText("Press P to Pause or Unpause the Timer", textColor)) {
        printf("loadFromRenderedText gPausePromptTexture failed!\n");
        return 1;
    }

    LTimer timer;
    std::stringstream timeText;

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
                        case SDLK_s:
                            if (timer.isStarted()) {
                                timer.stop();
                            } else {
                                timer.start();
                            }
                            break;
                        case SDLK_p:
                            if (timer.isPaused()) {
                                timer.unpause();
                            } else {
                                timer.pause();
                            }
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
            // more event processing
            //
        }
        timeText.str("");
        timeText << "Seconds since start time " << (timer.getTicks() / 1000.f);

        if (!gTimeTextTexture.loadFromRenderedText(timeText.str().c_str(), textColor)) {
            printf("loadFromRenderedText %s failed!\n", timeText.str().c_str());
            return 1;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gStartPromptTexture.render((SCREEN_WIDTH - gStartPromptTexture.getWidth())/2, 0);
        gPausePromptTexture.render((SCREEN_WIDTH - gPausePromptTexture.getWidth())/2, 
                                                   gStartPromptTexture.getHeight());
        gTimeTextTexture.render((SCREEN_WIDTH - gTimeTextTexture.getWidth())/2,
                                (SCREEN_HEIGHT - gTimeTextTexture.getHeight())/2);
        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
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
    gFont = TTF_OpenFont("./lazy.ttf", 28);
    if (!gFont) {
        printf("TTF_OpenFont failed! in init\n");
        return false;
    }
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

    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    Mix_Quit();
    IMG_Quit();
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

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &destRect);
}
