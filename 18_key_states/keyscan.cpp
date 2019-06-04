#include <SDL.h>
#include <SDL_image.h>
#include <windows.h.>
#include <string>

class LTexture
{
    public:
        ~LTexture() { if (mTexture) free(); }
        void free();
        bool loadFromFile(SDL_Renderer *lRenderer, std::string path);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        void render(SDL_Renderer *lRenderer, int x, int y, SDL_Rect *clip = NULL);
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

void LTexture::free()
{
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

bool LTexture::loadFromFile(SDL_Renderer *lRenderer, std::string path)
{
    free();
    SDL_Surface *tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        MessageBoxA(NULL, "IMG_Load failed!", "Error", MB_OK);
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(lRenderer, tmpSurface);
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return (mTexture ? true : false);
}

void LTexture::render(SDL_Renderer *lRenderer, int x, int y, SDL_Rect *clip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopy(lRenderer, mTexture, clip, &destRect);
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        MessageBoxA(NULL, "SDL_Init failed!", "Error", MB_OK);
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        MessageBoxA(NULL, "IMG_Init failed!", "Error", MB_OK);
        return false;
    }
    return true;
}

void close()
{
    IMG_Quit();
    SDL_Quit();
}

int main(int, char*[])
{
    if (!init()) {
        MessageBoxA(NULL, "main::init failed", "Error", MB_OK);
        return 1;
    }

    int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

    SDL_Window *hWindow = SDL_CreateWindow("SDL2 Tutorial",
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SDL_WINDOWPOS_UNDEFINED,
                                           SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!hWindow) {
        MessageBoxA(NULL, "SDL_CreateWindow failed!", "Error", MB_OK);
        return 1;
    }

    SDL_Renderer *hRenderer = SDL_CreateRenderer(hWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!hRenderer) {
        MessageBoxA(NULL, "SDL_CreateRenderer failed!", "Error", MB_OK);
        return 1;
    }

    LTexture textureUP, textureDown, textureLeft, textureRight, texturePress;
    LTexture *currentTexture = NULL;
    textureUP.loadFromFile(hRenderer, "./up.png");
    textureDown.loadFromFile(hRenderer, "./down.png");
    textureRight.loadFromFile(hRenderer, "./right.png");
    textureLeft.loadFromFile(hRenderer, "./left.png");
    texturePress.loadFromFile(hRenderer, "./press.png");

    bool quit = false;
    SDL_Event e;

    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

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
                default:
                    break;
            }
        }

//        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            currentTexture = &textureUP;
        }
        else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            currentTexture = &textureDown;
        }
        else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            currentTexture = &textureRight;
        }
        else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            currentTexture = &textureLeft;
        }
        else {
            currentTexture = &texturePress;
        }

        SDL_SetRenderDrawColor(hRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(hRenderer);
        currentTexture->render(hRenderer, 0, 0);
        SDL_RenderPresent(hRenderer);
    }

    SDL_DestroyRenderer(hRenderer);
    SDL_DestroyWindow(hWindow);
    close();

    return 0;
}
