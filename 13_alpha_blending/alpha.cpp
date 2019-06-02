#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

class LTexture
{
    public:
        LTexture();
        ~LTexture();
        void free();
        bool loadFromFile(std::string path);
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        void render(int x, int y, SDL_Rect* clip = NULL);
        int getWidth() { return mWidth; }
        int getHeight() {return mHeight; }
    private:
        SDL_Texture* mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

LTexture::LTexture() {}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if (mTexture != NULL) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::loadFromFile(std::string path)
{
    SDL_Surface* tmpSurface = NULL;
    SDL_Texture* newTexture = NULL;

    if (mTexture) free();

    tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        MessageBox(NULL, "IMG_Load failed!", "Error", MB_OK);
        return false;
    }

    newTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!newTexture) {
        MessageBox(NULL, "SDL_CreateTextureFromSurface failed!", "Error", MB_OK);
        return false;
    }

    mTexture = newTexture;
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;

    SDL_FreeSurface(tmpSurface);

    return true;
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

void LTexture::render(int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

int main(int, char*[])
{
    SDL_Init(SDL_INIT_VIDEO);
    gWindow = SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

    /*
    SDL_Rect rectFill = {0, 0, SCREEN_WIDTH/2, SCREEN_HEIGHT/2};
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
    SDL_RenderFillRect(gRenderer, &rectFill);
    rectFill = {SCREEN_WIDTH/2, 0, SCREEN_WIDTH, SCREEN_HEIGHT/2};
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0xff);
    SDL_RenderFillRect(gRenderer, &rectFill);
    rectFill = {0, SCREEN_HEIGHT/2, SCREEN_WIDTH/2, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0xff);
    SDL_RenderFillRect(gRenderer, &rectFill);
    rectFill = {SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xff, 0xff);
    SDL_RenderFillRect(gRenderer, &rectFill);
    */

    LTexture modulatedTexture, backgroundTexture;
    modulatedTexture.loadFromFile("./fadeout.png");
    backgroundTexture.loadFromFile("./fadein.png");
    modulatedTexture.setBlendMode(SDL_BLENDMODE_BLEND);

    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;
    Uint8 a = 255;

    bool quit = false;
    SDL_Event evt;

    while (!quit) {
        while (SDL_PollEvent(&evt)) {
            if (evt.type == SDL_QUIT) {
                quit = true;
            }
            if (evt.type == SDL_KEYDOWN) {
                switch (evt.key.keysym.sym) {
                    case SDLK_q:
                        quit = true;
                        break;
                    case SDLK_w:
                        r += 32;
                        break;
                    case SDLK_e:
                        g += 32;
                        break;
                    case SDLK_r:
                        b += 32;
                        break;
                    case SDLK_s:
                        r -= 32;
                        break;
                    case SDLK_d:
                        g -= 32;
                        break;
                    case SDLK_f:
                        b -= 32;
                        break;
                    case SDLK_a:
                        r = g = b = 255;
                        break;
                    case SDLK_t:
                        (a + 32 > 255) ? a = 255 : a += 32;
                        break;
                    case SDLK_g:
                        (a - 32 < 0) ? a = 0 : a -= 32;
                        break;
                    default:
                        break;
                }
            }
        }
//        txtColors.setColor(r, g, b);
//        txtColors.render(0, 0);
        backgroundTexture.render(0, 0);
        modulatedTexture.setAlpha(a);
        modulatedTexture.render(0, 0);
        SDL_RenderPresent(gRenderer);
    }
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    SDL_Quit();
    return 0;
}
