#include <SDL.h>
#include <SDL_image.h>
#include <windows.h>
#include <string>

int BUTTON_WIDTH = 300;
int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_MOUSE_TOTAL = 4
};

class LTexture
{
    public:
        ~LTexture();
        bool loadFromFile(std::string path);
#ifdef _SDL_TTF_H
        bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif
        void free();
        void setColor(Uint8 red, Uint8 green, Uint8 blue);
        void setBlendMode(SDL_BlendMode blending);
        void setAlpha(Uint8 alpha);
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

class LButton
{
    public:
        LButton();
        void setPosition(int x, int y);
        void handleEvent(SDL_Event *e);
        void render();
    private:
        SDL_Point mPosition;
        LButtonSprite mCurrentSprite;
};

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
int SCREEN_WIDTH = 640;
int SCREEN_HEIGHT = 480;
LButton gButtons[TOTAL_BUTTONS];
LTexture gButtonSpriteSheetTexture;
SDL_Rect gSpriteClips[BUTTON_SPRITE_MOUSE_TOTAL];

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        MessageBoxA(NULL, "SDL_Init failed!", "Error", MB_OK);
        return false;
    }
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        MessageBoxA(NULL, "IMG_Init failed", "Error", MB_OK);
        return false;
    }
    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        MessageBoxA(NULL, "SDL_CreateWindow failed", "Error", MB_OK);
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (!gRenderer) {
        MessageBoxA(NULL, "SDL_CreateRenderer failed", "Error", MB_OK);
        return false;
    }

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            gButtons[i + j*2].setPosition(i * BUTTON_WIDTH, j * BUTTON_HEIGHT);
        }
    }
    return true;
}

void close()
{
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

LTexture::~LTexture()
{
    if (mTexture) free();
}

bool LTexture::loadFromFile(std::string path)
{
    SDL_Surface *tmpSurface = NULL;
    tmpSurface = IMG_Load(path.c_str());
    if (!tmpSurface) {
        MessageBoxA(NULL, "IMG_Load failed", "Error", MB_OK);
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        MessageBoxA(NULL, "SDL_CreateTextureFromSurface failed", "Error", MB_OK);
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return true;
}

#ifdef _SDL_TTF_H
bool loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
    if( textSurface == NULL )
    {
        printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
        if( mTexture == NULL )
        {
            printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface( textSurface );
    }
    
    //Return success
    return mTexture != NULL;
}
#endif

void LTexture::free()
{
    if (mTexture) {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
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

void LTexture::render(int x, int y, SDL_Rect *clip, double angle,
            SDL_Point *center, SDL_RendererFlip flip)
{
    SDL_Rect destRect = {x, y, mWidth, mHeight};
    if (clip) {
        destRect.w = clip->w;
        destRect.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &destRect, angle, center, flip);
}

LButton::LButton()
{
    mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    mPosition.x = 0;
    mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
    mPosition.x = x;
    mPosition.y = y;
}

void LButton::handleEvent(SDL_Event *e)
{
    int x, y;
    bool inside = true;
    if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP) {
        SDL_GetMouseState(&x, &y);
        if (x < mPosition.x || x > mPosition.x + BUTTON_WIDTH ||
            y < mPosition.y || y > mPosition.y + BUTTON_HEIGHT) {
            inside = false;
        }
    }
    if (!inside) {
        mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
    } else {
        switch (e->type) {
            case SDL_MOUSEMOTION:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                break;
            case SDL_MOUSEBUTTONDOWN:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                break;
            case SDL_MOUSEBUTTONUP:
                mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                break;
        }
    }
}

void LButton::render()
{
    gButtonSpriteSheetTexture.render(mPosition.x, mPosition.y, &gSpriteClips[mCurrentSprite]);
}

bool loadMedia()
{
    if (!gButtonSpriteSheetTexture.loadFromFile("./button.png")) {
        MessageBoxA(NULL, "loadMedia loadFromFile failed!", "Error", MB_OK);
        return false;
    }
    for (int i = 0; i < BUTTON_SPRITE_MOUSE_TOTAL; ++i) {
        gSpriteClips[i].x = 0;
        gSpriteClips[i].y = BUTTON_HEIGHT * i;
        gSpriteClips[i].w = BUTTON_WIDTH;
        gSpriteClips[i].h = BUTTON_HEIGHT;
    }
    return true;
}


int main(int, char*[])
{
    if (!init()) {
        MessageBoxA(NULL, "Initialization failed", "Error", MB_OK);
        return 1;
    }

    if (!loadMedia()) {
        MessageBoxA(NULL, "loadMedia failed!", "Error", MB_OK);
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
                    for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                        gButtons[i].handleEvent(&e);
                    }
                    break;
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
            gButtons[i].render();
        }
        SDL_RenderPresent(gRenderer);
    }

    return 0;
}
