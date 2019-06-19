#include <SDL.h>
#include <string>
#include <cstdio>
#include <sstream>

class LWindow
{
    public:
        bool init();
        void handleEvent(SDL_Event &e);
        void focus();
        void render();
        void free();
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        bool hasMouseFocus() { return mMouseFocus; }
        bool hasKeyboardFocus() { return mKeyboardFocus; }
        bool isMinimized() { return mMinimized; }
        bool isShown() { return mShown; }
    private:
        SDL_Window *mWindow = NULL;
        SDL_Renderer *mRenderer = NULL;
        int mWindowID = 0;

        int mWidth = 0;
        int mHeight = 0;

        bool mMouseFocus = false;
        bool mKeyboardFocus = false;
        bool mFullScreen = false;
        bool mMinimized = false;
        bool mShown = false;
};

bool init();
void close();

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
const int TOTAL_WINDOWS = 3;
LWindow gWindows[TOTAL_WINDOWS];

int main(int, char**)
{
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }

    for (int i = 1; i < TOTAL_WINDOWS; ++i) {
        gWindows[i].init();
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
                        case SDLK_1:
                            gWindows[0].focus();
                            break;
                        case SDLK_2:
                            gWindows[1].focus();
                            break;
                        case SDLK_3:
                            gWindows[2].focus();
                            break;
                        default:
                            break;
                    }
                default:
                    break;
            }
            for (int i = 0; i < TOTAL_WINDOWS; ++i) {
                gWindows[i].handleEvent(e);
            }
            // before ending event processing...
        }
        for (int i = 0; i < TOTAL_WINDOWS; ++i) {
            gWindows[i].render();
        }

        bool allWindowsClosed = true;
        for (int i = 0; i < TOTAL_WINDOWS; ++i) {
            if (gWindows[i].isShown()) {
                allWindowsClosed = false;
                break;
            }
        }
        if (allWindowsClosed) {
            quit = true;
        }
        // before ending main loop...
    }

    close();

    return 0;
}


bool LWindow::init()
{
    mWindow = SDL_CreateWindow("SDL2 Test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    if (!mWindow) {
        printf("LWindow::init SDL_CreateWindow failed!\n");
        return false;
    }
    mMouseFocus = true;
    mKeyboardFocus = true;
    mWidth = SCREEN_WIDTH;
    mHeight = SCREEN_HEIGHT;
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!mRenderer) {
        printf("LWindow::init SDL_CreateRenderer failed!\n");
        SDL_DestroyWindow(mWindow);
        mWindow = NULL;
        return false;
    }
    SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
    mWindowID = SDL_GetWindowID(mWindow);
    mShown = true;
    return true;
}

void LWindow::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID) {
        bool updateCaption = false;
        switch (e.window.event) {
            case SDL_WINDOWEVENT_SHOWN:
                mShown = true;
                break;
            case SDL_WINDOWEVENT_HIDDEN:
                mShown = false;
                break;
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                SDL_RenderPresent(mRenderer);
                break;
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(mRenderer);
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
            case SDL_WINDOWEVENT_CLOSE:
                SDL_HideWindow(mWindow);
                break;
        }
        if (updateCaption) {
            std::stringstream caption;
            caption << "SDL2 Test - ID: " << mWindowID << " MouseFocus: " << (mMouseFocus ? "On" : "Off")
                    << " KeyboardFocus: " << (mKeyboardFocus ? "On" : "Off");
            SDL_SetWindowTitle(mWindow, caption.str().c_str());
        }
    }
}

void LWindow::focus()
{
    if (!mShown) {
        SDL_ShowWindow(mWindow);
    }
    SDL_RaiseWindow(mWindow);
}

void LWindow::render()
{
    if (!mMinimized) {
        SDL_SetRenderDrawColor(mRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(mRenderer);
        SDL_RenderPresent(mRenderer);
    }
}

void LWindow::free()
{
    SDL_DestroyRenderer(mRenderer);
    mRenderer = NULL;
    SDL_DestroyWindow(mWindow);
    mWindow = NULL;
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL_Init failed!\n");
        return false;
    }
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }
    if (!gWindows[0].init()) {
        printf("Window 0 could not be created!\n");
        return false;
    }
    return true;
}

void close()
{
    for (int i = 0; i < TOTAL_WINDOWS; ++i) {
        gWindows[i].free();
    }
    SDL_Quit();
}
