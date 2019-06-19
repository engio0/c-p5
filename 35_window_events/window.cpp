#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <sstream>
#include <cstdio>

class LTexture
{
    public:
        ~LTexture() { free(); }
        void free();
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        bool loadFromFile(std::string path);
        void setColor(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(mTexture, r, g, b); }
        void setBlendMode(SDL_BlendMode blending) { SDL_SetTextureBlendMode(mTexture, blending); }
        void setAlpha(Uint8 alpha) { SDL_SetTextureAlphaMod(mTexture, alpha); }
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0, mHeight = 0;
};

class LWindow
{
    public:
        bool init();
        SDL_Renderer* createRenderer();
        void handleEvent(SDL_Event& e);
        void free();
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        bool hasMouseFocus() { return mMouseFocus; }
        bool hasKeyboardFocus() { return mKeyboardFocus; }
        bool isMinimized() { return mMinimized; }
    private:
        SDL_Window* mWindow = NULL;
        int mWidth = 0;
        int mHeight = 0;
        bool mMouseFocus = false;
        bool mKeyboardFocus = false;
        bool mFullScreen = false;
        bool mMinimized = false;
};

bool init();
void close();

LWindow gWindow;
LTexture gSceneTexture;
SDL_Renderer *gRenderer = NULL;
const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

int main(int, char**)
{
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }

    if (!gSceneTexture.loadFromFile("./window.png")) {
        printf("loading image window.png failed!\n");
        return 2;
    }

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
                default:
                    break;
            }
            gWindow.handleEvent(e);
        }
        if (!gWindow.isMinimized()) {
            SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
            SDL_RenderClear(gRenderer);
            gSceneTexture.render((gWindow.getWidth() - gSceneTexture.getWidth())/2,
                                 (gWindow.getHeight() - gSceneTexture.getHeight())/2);
            SDL_RenderPresent(gRenderer);
        }
    }

    return 0;
}

bool LWindow::init()
{
    mWindow = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (mWindow) {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
        return true;
    }
    return false;
}
            
SDL_Renderer* LWindow::createRenderer()
{
    return SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void LWindow::handleEvent(SDL_Event& e)
{
    bool updateCaption = false;
    std::stringstream caption;
    switch (e.type) {
        case SDL_WINDOWEVENT:
            switch (e.window.event) {
                case SDL_WINDOWEVENT_SIZE_CHANGED:
                    mWidth = e.window.data1;
                    mHeight = e.window.data2;
                    SDL_RenderPresent(gRenderer);
                    break;
                case SDL_WINDOWEVENT_EXPOSED:
                    SDL_RenderPresent(gRenderer);
                    break;
                case SDL_WINDOWEVENT_ENTER:
                    mMouseFocus = true;
                    updateCaption = true;
                    break;
                case SDL_WINDOWEVENT_LEAVE:
                    mMouseFocus = false;
                    updateCaption = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_GAINED:
                    mKeyboardFocus = true;
                    updateCaption = true;
                    break;
                case SDL_WINDOWEVENT_FOCUS_LOST:
                    mKeyboardFocus = false;
                    updateCaption = true;
                    break;
                case SDL_WINDOWEVENT_MINIMIZED:
                    mMinimized = true;
                    break;
                case SDL_WINDOWEVENT_MAXIMIZED:
                case SDL_WINDOWEVENT_RESTORED:
                    mMinimized = false;
                    break;
            }
            if (updateCaption) {
                caption << "SDL2 Test - MouseFocus:" << ((mMouseFocus) ? "On" : "Off")
                        << " KeyboardFocus:" << (mKeyboardFocus ? "On" : "Off");
                SDL_SetWindowTitle(mWindow, caption.str().c_str());
            }
            break;
        case SDL_KEYDOWN:
            if (e.key.keysym.sym == SDLK_RETURN) {
                if (mFullScreen) {
                    SDL_SetWindowFullscreen(mWindow, SDL_FALSE);
                    mFullScreen = false;
                } else {
                    SDL_SetWindowFullscreen(mWindow, SDL_TRUE);
                    mFullScreen = true;
                    mMinimized = false;
                }
            }
            break;
        default:
            break;
    }
}

void LWindow::free()
{
    SDL_DestroyWindow(mWindow);
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
    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0, 255, 255));
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
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    if (!gWindow.init()) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    gRenderer = gWindow.createRenderer();
    if (!gRenderer) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void close()
{
    gSceneTexture.free();
    SDL_DestroyRenderer(gRenderer);
//    SDL_DestroyWindow(gWindow);
    gWindow.free();
    IMG_Quit();
    SDL_Quit();
}
