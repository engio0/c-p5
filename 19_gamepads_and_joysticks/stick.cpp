#include <SDL_log.h>
#include <SDL_image.h>
#include <windows.h>
#include <cstdio>
#include <string>
#include <cmath>

class LTexture
{
    public:
        ~LTexture() { free(); }
        void free();
        bool loadFromFile(std::string path);
        bool loadFromRenderedText(std::string text, SDL_Color color);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0,
                    SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

bool init();
void close();

const int JOYSTICK_DEAD_ZONE = 8000;
const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
SDL_Joystick *gGameController = NULL;
LTexture gArrowTexture;


int main(int, char*[])
{
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }
    gArrowTexture.loadFromFile("./arrow.png");

    int xDir = 0;
    int yDir = 0;

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
                case SDL_JOYAXISMOTION:
                    switch (e.jaxis.which) {
                        case 0:
                            switch (e.jaxis.axis) {
                                case 0:
                                    if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                                        xDir = -1;
                                        break;
                                    }
                                    if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                                        xDir = 1;
                                        break;
                                    }
                                    xDir = 0;
                                case 1:
                                    if (e.jaxis.value < -JOYSTICK_DEAD_ZONE) {
                                        yDir = -1;
                                        break;
                                    }
                                    if (e.jaxis.value > JOYSTICK_DEAD_ZONE) {
                                        yDir = 1;
                                        break;
                                    }
                                    yDir = 0;
                                default:
                                    break;
                            }
                        default:
                            break;
                    }
                default:
                    break;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        double joystickAngle = atan2( (double)yDir, (double)xDir * (180.0 / M_PI) );
        if (xDir == 0 && yDir == 0) {
            joystickAngle = 0;
        }
        gArrowTexture.render((SCREEN_WIDTH-gArrowTexture.getWidth())/2,
                             (SCREEN_HEIGHT-gArrowTexture.getHeight())/2,
                             NULL, joystickAngle);

        SDL_RenderPresent(gRenderer);
    }
    close();
    return 0;
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

#ifdef SDL_IMG_H_
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
#endif

#ifdef SDL_TTF_H_
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
#endif

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y,mWidth, mHeight};
    if (clip) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0) {
        printf("SDL_Init failed! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        printf("SDL_CreateWindow failed!\n");
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        printf("SDL_CreateRenderer failed!\n");
        return false;
    }
    if (SDL_NumJoysticks() < 1) {
        printf("Warning: No joystick found!\n");
        return false;
    }
    gGameController = SDL_JoystickOpen(0);
    if (!gGameController) {
        printf("Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void close()
{
    gArrowTexture.free();
    SDL_JoystickClose(gGameController);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}
