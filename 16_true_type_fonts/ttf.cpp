#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <cstdio>
#include <string>
#include <cmath>

class LTexture
{
    public:
        ~LTexture();
        bool loadFromFile(std::string path);
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
        void free();
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    private:
        SDL_Texture* mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

LTexture::~LTexture()
{
    if (mTexture) free();
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

bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    free();
    SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if (!textSurface) {
        MessageBoxA(NULL, "TTF_RenderText_Solid failed!", "Error", MB_OK);
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

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &destRect, angle, center, flip);
}

int main(int, char*[])
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    gFont = TTF_OpenFont("./lazy.ttf", 28);

    SDL_Color textColor = {0, 0, 0};
    LTexture gTextTexture;
    gTextTexture.loadFromRenderedText("The quick brown fox jumps over the lazy dog...", textColor);

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
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gTextTexture.render((SCREEN_WIDTH - gTextTexture.getWidth())/2,
                            (SCREEN_HEIGHT - gTextTexture.getHeight())/2);

        SDL_RenderPresent(gRenderer);
    }

    gTextTexture.free();
    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    TTF_Quit();
    SDL_Quit();
    
    return 0;
}
