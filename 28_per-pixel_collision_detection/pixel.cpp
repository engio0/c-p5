#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <vector>

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
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0, mHeight = 0;
};

class Dot
{
    public:
        static const int DOT_WIDTH = 20, DOT_HEIGHT = 20;
//        static const int DOT_VEL = 1;
        static int DOT_VEL;
        Dot() {};
        Dot(int x, int y);
        void handleEvent(SDL_Event &e);
        void move(SDL_Rect &wall);
        void move(std::vector<SDL_Rect> &otherColliders);
        void render();
        void outline();
        std::vector<SDL_Rect> &getColliders();
    private:
        int mPosX = 0, mPosY = 0;
        int mVelX = 0, mVelY = 0;
        std::vector<SDL_Rect> mColliders;
        void shiftColliders();
        SDL_Rect mCollider = {mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT};
};

bool init();
bool loadMedia();
void close();
//bool checkCollision(SDL_Rect &a, SDL_Rect &b);
bool checkCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b);

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
#ifdef SDL_TTF_H_
TTF_Font *gFont = NULL;
#endif
LTexture gDotTexture;
const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int Dot::DOT_VEL = 10;

int main(int, char*[])
{
    char szBuffer[81];

    if (!init()) {
        printf("Error in main::init!\n");
        return 1;
    }
    if (!loadMedia()) {
        printf("Error in main::loadMedia!\n");
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    Dot dot(0, 0);
    Dot otherDot(SCREEN_WIDTH/4, SCREEN_HEIGHT/4);

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
                        case SDLK_EQUALS:
                        case SDLK_PLUS:
                            ++Dot::DOT_VEL;
                            break;
                        case SDLK_UNDERSCORE:
                        case SDLK_MINUS:
                            if (Dot::DOT_VEL > 1) --Dot::DOT_VEL;
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
        dot.move(otherDot.getColliders());

        sprintf(szBuffer, "SDL2Tutorial - VEL : %d", Dot::DOT_VEL);
        SDL_SetWindowTitle(gWindow, szBuffer);

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 0xff);

        dot.render();
        otherDot.render();

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
    SDL_Surface *tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        printf("IMG_Load failed opening file %s! IMG_Error: %s\n", path.c_str(), IMG_GetError());
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

Dot::Dot(int x, int y)
{
    mPosX = x;
    mPosY = y;
    mColliders.resize(11);
    mVelX = 0;
    mVelY = 0;

    mColliders[ 0 ].w = 6;
    mColliders[ 0 ].h = 1;

    mColliders[ 1 ].w = 10;
    mColliders[ 1 ].h = 1;

    mColliders[ 2 ].w = 14;
    mColliders[ 2 ].h = 1;

    mColliders[ 3 ].w = 16;
    mColliders[ 3 ].h = 2;

    mColliders[ 4 ].w = 18;
    mColliders[ 4 ].h = 2;

    mColliders[ 5 ].w = 20;
    mColliders[ 5 ].h = 6;

    mColliders[ 6 ].w = 18;
    mColliders[ 6 ].h = 2;

    mColliders[ 7 ].w = 16;
    mColliders[ 7 ].h = 2;

    mColliders[ 8 ].w = 14;
    mColliders[ 8 ].h = 1;

    mColliders[ 9 ].w = 10;
    mColliders[ 9 ].h = 1;

    mColliders[ 10 ].w = 6;
    mColliders[ 10 ].h = 1;

    shiftColliders();
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
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_RIGHT:
                mVelX = 0;
                break;
            case SDLK_UP:
            case SDLK_DOWN:
                mVelY = 0;
                break;
        }
    }
}

void Dot::move(std::vector<SDL_Rect> &otherColliders)
{
    mPosX += mVelX;
    mPosY += mVelY;
    shiftColliders();
    if ( (mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(mColliders, otherColliders) ) {
        mPosX -= mVelX;
        shiftColliders();
    }
    if ( (mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(mColliders, otherColliders) ) {
        mPosY -= mVelY;
        shiftColliders();
    }
}

void Dot::shiftColliders()
{
    int r = 0;
    for (unsigned set = 0; set < mColliders.size(); ++set) {
        mColliders[set].x = mPosX + (DOT_WIDTH - mColliders[set].w) / 2;
        mColliders[set].y = mPosY + r;
        r += mColliders[set].h;
    }
}

std::vector<SDL_Rect> &Dot::getColliders()
{
    return mColliders;
}

void Dot::render()
{
    gDotTexture.render(mPosX, mPosY);
}

void Dot::outline()
{
    SDL_Rect rectOutline = {mPosX, mPosY, DOT_WIDTH, DOT_HEIGHT};
    SDL_RenderDrawRect(gRenderer, &rectOutline);
}

bool loadMedia()
{
    if (!gDotTexture.loadFromFile("./dot.bmp")) {
        printf("Error opening dot.bmp!\n");
        return false;
    }
    return true;
}

bool checkCollision(std::vector<SDL_Rect> &a, std::vector<SDL_Rect> &b) {
    for (size_t Abox = 0; Abox < a.size(); ++Abox) {
        for (size_t Bbox = 0; Bbox < b.size(); ++Bbox) {
            if ( (a[Abox].x >= b[Bbox].x + b[Bbox].w) || (b[Bbox].x >= a[Abox].x + a[Abox].w) ||
                 (a[Abox].y >= b[Bbox].y + b[Bbox].h) || (b[Bbox].y >= a[Abox].y + a[Abox].h) ) return false;
        }
    }
    return true;
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

