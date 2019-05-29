#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>


class LTexture
{
    public:
        LTexture();
        ~LTexture();
        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y);
        int getWidth();
        int getHeight();
    private:
        SDL_Texture *mTexture;
        int mWidth;
        int mHeight;
};


char szBuffer[81];
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
LTexture gFooTexture;
LTexture gBackgroundTexture;
int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    SDL_Texture *newTexture = NULL;

    free();
    SDL_Surface *loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        wsprintf(szBuffer, "IMG_Load %s failed! SDL_image Error: %s", path.c_str(), IMG_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
    } else {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0x00, 0xff, 0xff));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (!newTexture) {
            wsprintf(szBuffer, "Create texture %s failed! SDL Error: %s", path.c_str(), SDL_GetError());
            MessageBox(NULL, szBuffer, "Error", MB_OK);
        } else {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

void LTexture::free()
{
    if (!mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::render(int x, int y)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderQuad);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

bool loadMedia()
{
    if (!gFooTexture.loadFromFile("foo.png")) {
        MessageBox(NULL, "Failed to load Foo.png", "Error", MB_OK);
        return false;
    }
    if (!gBackgroundTexture.loadFromFile("background.png")) {
        MessageBox(NULL, "Failed to load background.png", "Error", MB_OK);
        return false;
    }
    return true;
}

bool init()
{
    char szBuffer[81]; 

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        wsprintf(szBuffer, "SDL Init failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        wsprintf(szBuffer, "CreateWindow failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        wsprintf(szBuffer, "CreateRendere failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        wsprintf(szBuffer, "SDL_image init failed! SDL Error: %s", IMG_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    return true;
}


void close()
{
    gFooTexture.free();
    gBackgroundTexture.free();

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}


int main(int argc, char *argv[])
{
    init();
    loadMedia();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q) {
                    quit = true;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gBackgroundTexture.render(0, 0);
        gFooTexture.render(240, 190);

        SDL_RenderPresent(gRenderer);
    }

    close();

    return 0;
}
