#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>

SDL_Renderer* gRenderer = NULL;
SDL_Window* gWindow = NULL;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;

class LTexture
{
    public:
        ~LTexture();
        bool loadFromFile(std::string path);
        void free();
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
        int getWidth() { return mWidth; };
        int getHeight() { return mHeight; };
    private:
        SDL_Texture* mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

LTexture::~LTexture()
{
    if (mTexture) free();
}

bool LTexture::loadFromFile(std::string path)
{
    SDL_Surface* tempSurface = NULL;
    tempSurface = IMG_Load(path.c_str());
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tempSurface);
    mWidth = tempSurface->w;
    mHeight = tempSurface->h;
    SDL_FreeSurface(tempSurface);
    return (mTexture ? true : false);
}

void LTexture::free()
{
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y,mWidth, mHeight};
    if (clip) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int main(int, char*[])
{
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    LTexture gArrowTexture;
    gArrowTexture.loadFromFile("./arrow.png");

    bool quit = false;
    SDL_Event e;
    double degrees = 0.0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

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
                        case SDLK_a:
                            degrees -= 30.0;
                            break;
                        case SDLK_d:
                            degrees += 30.0;
                            break;
                        case SDLK_s:
                            flipType = SDL_FLIP_NONE;
                            break;
                        case SDLK_w:
                            flipType = SDL_FLIP_VERTICAL;
                            break;
                        case SDLK_x:
                            flipType = SDL_FLIP_HORIZONTAL;
                            break;
                        default:
                            break;
                    }
            }
        }
        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);
        gArrowTexture.render( (SCREEN_WIDTH - gArrowTexture.getWidth())/2,
                              (SCREEN_HEIGHT - gArrowTexture.getHeight())/2,
                              NULL, degrees, NULL, flipType);
        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
