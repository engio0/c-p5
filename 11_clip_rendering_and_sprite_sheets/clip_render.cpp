#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Surface *gSurface = NULL;
SDL_Rect gSpriteClips[4];
int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

class LTexture
{
    public:
        ~LTexture();
        bool loadFromFile(std::string path);
        void free();
        void render(int x, int y, SDL_Rect* clip = NULL);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

LTexture gSpriteSheetTexture;


LTexture::~LTexture()
{
    free();
}

bool LTexture::loadFromFile(std::string path)
{
    if (!mTexture)
        free();

    SDL_Surface *tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        char szBuffer[81];
        wsprintf(szBuffer, "IMG_Load [%s] failed! SDL_image Error: %s", path.c_str(), IMG_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }

    SDL_SetColorKey(tmpSurface, SDL_TRUE, SDL_MapRGB(tmpSurface->format, 0x00, 0xff, 0xff));
    SDL_Texture *newTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!newTexture) {
        char szBuffer[81];
        wsprintf(szBuffer, "CreateTextureFromSurface failed! SDL Error: %s", SDL_GetError());
        MessageBox(NULL, szBuffer, "Error", MB_OK);
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    mTexture = newTexture;

    return true;
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

void LTexture::render(int x, int y, SDL_Rect *clip)
{
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };
    if (clip) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, clip, &renderQuad);
}

bool loadMedia()
{
    if (!gSpriteSheetTexture.loadFromFile("dots.png")) {
        MessageBox(NULL, "Failed to load sprite sheet texture", "Error", MB_OK);
        return false;
    }
    gSpriteClips[0].x = 0;
    gSpriteClips[0].y = 0;
    gSpriteClips[0].w = 100;
    gSpriteClips[0].h = 100;

    gSpriteClips[1].x = 100;
    gSpriteClips[1].y = 0;
    gSpriteClips[1].w = 100;
    gSpriteClips[1].h = 100;

    gSpriteClips[2].x = 0;
    gSpriteClips[2].y = 100;
    gSpriteClips[2].w = 100;
    gSpriteClips[2].h = 100;

    gSpriteClips[3].x = 100;
    gSpriteClips[3].y = 100;
    gSpriteClips[3].w = 100;
    gSpriteClips[3].h = 100;

    return true;
}

int main(int, char *[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        MessageBox(NULL, "Error SDL_Init", "Error", MB_OK);
        return 1;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        MessageBox(NULL, "Error IMG_Init", "Error", MB_OK);
        return 2;
    }

    gWindow = SDL_CreateWindow("SDL2 Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        MessageBox(NULL, "Error CreateWindow", "Error", MB_OK);
        return 3;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        MessageBox(NULL, "Error CreateRenderer", "Error", MB_OK);
        return 4;
    }
    loadMedia();

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            if (e.type == SDL_KEYDOWN) {
                if (e.key.keysym.sym == SDLK_q)
                    quit = true;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        gSpriteSheetTexture.render(0, 0, &gSpriteClips[0]);
        gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[1].w, 0, &gSpriteClips[1]);
        gSpriteSheetTexture.render(0, SCREEN_HEIGHT - gSpriteClips[2].h, &gSpriteClips[2]);
        gSpriteSheetTexture.render(SCREEN_WIDTH - gSpriteClips[3].w,
                                   SCREEN_HEIGHT - gSpriteClips[3].h,
                                   &gSpriteClips[3]);
        SDL_RenderPresent(gRenderer);
    }

    SDL_DestroyRenderer(gRenderer);
    SDL_FreeSurface(gSurface);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
    return 0;
}
