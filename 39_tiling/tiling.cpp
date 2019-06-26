#define _LOG_
#include <SDL.h>
#include <SDL_image.h>
#include <cstdio>
#include <string>
#include <fstream>

const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
const int LEVEL_WIDTH = 1280, LEVEL_HEIGHT = 960;
const int TILE_WIDTH = 80, TILE_HEIGHT = 80;
const int TOTAL_TILES = 192, TOTAL_TILE_SPRITES = 12;

enum { TILE_RED, TILE_GREEN, TILE_BLUE,
       TILE_CENTER, TILE_TOP, TILE_TOPRIGHT,
       TILE_RIGHT, TILE_BOTTOMRIGHT, TILE_BOTTOM,
       TILE_BOTTOMLEFT, TILE_LEFT, TILE_TOPLEFT };

class LTexture
{
    public:
        ~LTexture() { free(); }
        void free();
        int getWidth() { return mWidth; }
        int getHeight() { return mHeight; }
        bool loadFromFile(std::string path);
#ifdef SDL_TTF_H_
        bool loadFromRenderedText(std::string text, SDL_Color color);
#endif
        void setColor(Uint8 r, Uint8 g, Uint8 b) { SDL_SetTextureColorMod(mTexture, r, g, b); }
        void setBlendMode(SDL_BlendMode blending) { SDL_SetTextureBlendMode(mTexture, blending); }
        void setAlpha(Uint8 alpha) { SDL_SetTextureAlphaMod(mTexture, alpha); }
        void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0,
                    SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
    private:
        SDL_Texture *mTexture = NULL;
        int mWidth = 0, mHeight = 0;
};

class Tile
{
    public:
        Tile(int x, int y, int tileType);
        void render(SDL_Rect &camera);
        int getType() { return mType; }
        SDL_Rect &getBox() { return mBox; }
    private:
        SDL_Rect mBox;
        int mType;
};

class Dot
{
    public:
        static const int DOT_WIDTH = 20, DOT_HEIGHT = 20;
        static const int DOT_VEL = 10;
        Dot();
        void handleEvent(SDL_Event &e);
        void move(Tile *tiles[]);
        void setCamera(SDL_Rect &camera);
        void render(SDL_Rect &camera);
    private:
        SDL_Rect mBox;
        int mVelX, mVelY;
};

bool init();
bool loadMedia(Tile *tiles[]);
void close(Tile *tiles[]);
bool checkCollision(SDL_Rect &a, SDL_Rect &b);
bool touchesWall(SDL_Rect &box, Tile *tiles[]);
bool setTiles(Tile *tiles[]);

LTexture gTileTexture, gDotTexture;
SDL_Rect gTileClips[TOTAL_TILE_SPRITES];
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

int main(int, char**)
{
    setbuf(stdout, NULL);

    printf("entering main...\n");
    if (!init()) {
        printf("main::init failed!\n");
        return 1;
    }
#ifdef _LOG_
    printf("main::init successful!\n");
#endif

    Tile *tileSet[TOTAL_TILES];
    if (!loadMedia(tileSet)) {
        printf("main::loadMedia failed!\n");
        return 2;
    }
#ifdef _LOG_
    printf("main::loadMedia successful!\n");
#endif

    Dot dot;
    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

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
                    break;
                default:
                    break;
            }
            dot.handleEvent(e);
        }
        dot.move(tileSet);
        dot.setCamera(camera);

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        for (int i = 0; i < TOTAL_TILES; ++i) {
            tileSet[i]->render(camera);
        }
        dot.render(camera);

        SDL_RenderPresent(gRenderer);
    }

    close(tileSet);

    return 0;
}

Tile::Tile(int x, int y, int tileType)
{
    mBox.x = x;
    mBox.y = y;
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    mType = tileType;
}

void Tile::render(SDL_Rect &camera)
{
    if (checkCollision(mBox, camera)) {
        gTileTexture.render(mBox.x - camera.x, mBox.y - camera.y, &gTileClips[mType]);
    }
}

Dot::Dot()
{
    mBox = {0, 0, DOT_WIDTH, DOT_HEIGHT};
    mVelX = 0; mVelY = 0;
}

void Dot::handleEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
        switch (e.key.keysym.sym) {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
        }
    }
    if (e.type == SDL_KEYUP) {
        switch (e.key.keysym.sym) {
            case SDLK_LEFT:
            case SDLK_RIGHT:
                mVelX = 0;
                break;
            case SDLK_UP:
            case SDLK_DOWN:
                mVelY = 0;
                break;
        }
    }
}
void Dot::move(Tile *tiles[])
{
    mBox.x += mVelX;
    if ((mBox.x < 0) || (mBox.x + DOT_WIDTH > LEVEL_WIDTH) || touchesWall(mBox, tiles)) {
        mBox.x -= mVelX;
    }
    mBox.y += mVelY;
    if ((mBox.y < 0) || (mBox.y + DOT_HEIGHT > LEVEL_HEIGHT) || touchesWall(mBox, tiles)) {
        mBox.y -= mVelY;
    }
}

void Dot::setCamera(SDL_Rect &camera)
{
    camera.x = (mBox.x + DOT_WIDTH / 2) - SCREEN_WIDTH / 2;
    camera.y = (mBox.y + DOT_HEIGHT / 2) - SCREEN_HEIGHT / 2;

    if (camera.x < 0) camera.x = 0;
    if (camera.y < 0) camera.y = 0;
    if (camera.x > LEVEL_WIDTH - camera.w) camera.x = LEVEL_WIDTH - camera.w;
    if (camera.y > LEVEL_HEIGHT - camera.h) camera.y = LEVEL_HEIGHT - camera.h;
}

void Dot::render(SDL_Rect &camera)
{
    gDotTexture.render(mBox.x - camera.x, mBox.y - camera.y);
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

#ifdef SDL_TTF_H_
bool LTexture::loadFromRenderedText(std::string text, SDL_Color color)
{
    free();
    SDL_Surface *tmpSurface =  TTF_RenderText_Solid(gFont, text.c_str(), color);
    if (!tmpSurface) {
        printf("TTF_RenderText_Solid failed!\n");
        return false;
    }
    mTexture = SDL_CreateTextureFromSurface(gRenderer, tmpSurface);
    if (!mTexture) {
        printf("SDL_CreateTextureFromSurface failed rendering from text\n");
        return false;
    }
    mWidth = tmpSurface->w;
    mHeight = tmpSurface->h;
    SDL_FreeSurface(tmpSurface);
    return true;
}
#endif

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
#ifdef _LOG_
    printf("entering init...\n");
#endif
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::SDL_Init successful!\n");
#endif

#ifdef SDL_IMG_H_
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::IMG_Init successful!\n");
#endif
#endif

#ifdef SDL_TTF_H_
    if (TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::TTF_Init successful!\n");
#endif
#endif

#ifdef SDL_MIX_H_
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
        return false;
    }
#ifdef _LOG_
    printf("init::Mix_OpenAudio successful!\n");
#endif
#endif

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        printf("SDL_CreateWindow failed! in init\n");
        return false;
    }
#ifdef _LOG_
    printf("init::SDL_CreateWindow successful!\n");
#endif
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        printf("SDL_CreateRenderer failed in init\n");
        return false;
    }
#ifdef _LOG_
    printf("init::SDL_CreateRenderer successful!\n");
#endif
#ifdef SDL_TTF_H_
    gFont = TTF_OpenFont("./lazy.ttf", 28);
    if (!gFont) {
        printf("TTF_OpenFont failed! in init\n");
        return false;
    }
#ifdef _LOG_
    printf("init::TTF_OpenFont successful!\n");
#endif
#endif
    return true;
}

bool loadMedia(Tile *tiles[])
{
    if (!gDotTexture.loadFromFile("./dot.bmp")) {
        printf("Failed to load dot texture!\n");
        return false;
    }
#ifdef _LOG_
    printf("loadMedia::loadFromFile dot.bmp successful!\n");
#endif
    if (!gTileTexture.loadFromFile("./tiles.png")) {
        printf("Failed to load tile set texture!\n");
        return false;
    }
#ifdef _LOG_
    printf("loadMedia::loadFromFile tiles.png successful!\n");
#endif
    if (!setTiles(tiles)) {
        printf("Failed to load tile set!\n");
        return false;
    }
#ifdef _LOG_
    printf("loadMedia::setTiles successful!\n");
#endif

    return true;
}

bool setTiles(Tile *tiles[])
{
#ifdef _LOG_
    printf("entering setTiles...\n");
#endif
    std::ifstream map("./lazy.map");
    if (map.fail()) {
        printf("Unable to load map file!\n");
        return false;
    }
#ifdef _LOG_
    printf("after ifstream initialize...\n");
#endif
    int tileType = -1;
    for (int y = 0; y < LEVEL_HEIGHT / TILE_HEIGHT; ++y) {
        for (int x = 0; x < LEVEL_WIDTH / TILE_WIDTH; ++x) {
            map >> tileType;
#ifdef _LOG_
            printf("data x: %4d, y: %3d, value: %3d\n", x, y, tileType);
#endif
            if (map.fail()) {
                printf("Error loading map: Unexpected end of file!\n");
                return false;
            }
            if (tileType < 0 || tileType >= TOTAL_TILE_SPRITES) {
                printf("Error loading map: Invalid file type at x = %d, y = %d!\n", x, y);
                return false;
            }
            tiles[x + y * (LEVEL_WIDTH / TILE_WIDTH)] = new Tile(x * TILE_WIDTH, y * TILE_HEIGHT, tileType);
        }
    }
#ifdef _LOG_
    printf("after reading loop...\n");
#endif
    map.close();
    gTileClips[TILE_RED].x = 0;
    gTileClips[TILE_RED].y = 0;
    gTileClips[TILE_RED].w = TILE_WIDTH;
    gTileClips[TILE_RED].h = TILE_HEIGHT;

    gTileClips[TILE_GREEN].x = 0;
    gTileClips[TILE_GREEN].y = 80;
    gTileClips[TILE_GREEN].w = TILE_WIDTH;
    gTileClips[TILE_GREEN].h = TILE_HEIGHT;

    gTileClips[TILE_BLUE].x = 0;
    gTileClips[TILE_BLUE].y = 160;
    gTileClips[TILE_BLUE].w = TILE_WIDTH;
    gTileClips[TILE_BLUE].h = TILE_HEIGHT;

    gTileClips[TILE_TOPLEFT].x = 80;
    gTileClips[TILE_TOPLEFT].y = 0;
    gTileClips[TILE_TOPLEFT].w = TILE_WIDTH;
    gTileClips[TILE_TOPLEFT].h = TILE_HEIGHT;

    gTileClips[TILE_LEFT].x = 80;
    gTileClips[TILE_LEFT].y = 80;
    gTileClips[TILE_LEFT].w = TILE_WIDTH;
    gTileClips[TILE_LEFT].h = TILE_HEIGHT;

    gTileClips[TILE_BOTTOMLEFT].x = 80;
    gTileClips[TILE_BOTTOMLEFT].y = 160;
    gTileClips[TILE_BOTTOMLEFT].w = TILE_WIDTH;
    gTileClips[TILE_BOTTOMLEFT].h = TILE_HEIGHT;

    gTileClips[TILE_TOP].x = 160;
    gTileClips[TILE_TOP].y = 0;
    gTileClips[TILE_TOP].w = TILE_WIDTH;
    gTileClips[TILE_TOP].h = TILE_HEIGHT;

    gTileClips[TILE_CENTER].x = 160;
    gTileClips[TILE_CENTER].y = 80;
    gTileClips[TILE_CENTER].w = TILE_WIDTH;
    gTileClips[TILE_CENTER].h = TILE_HEIGHT;

    gTileClips[TILE_BOTTOM].x = 160;
    gTileClips[TILE_BOTTOM].y = 160;
    gTileClips[TILE_BOTTOM].w = TILE_WIDTH;
    gTileClips[TILE_BOTTOM].h = TILE_HEIGHT;

    gTileClips[TILE_TOPRIGHT].x = 240;
    gTileClips[TILE_TOPRIGHT].y = 0;
    gTileClips[TILE_TOPRIGHT].w = TILE_WIDTH;
    gTileClips[TILE_TOPRIGHT].h = TILE_HEIGHT;

    gTileClips[TILE_RIGHT].x = 240;
    gTileClips[TILE_RIGHT].y = 80;
    gTileClips[TILE_RIGHT].w = TILE_WIDTH;
    gTileClips[TILE_RIGHT].h = TILE_HEIGHT;

    gTileClips[TILE_BOTTOMRIGHT].x = 240;
    gTileClips[TILE_BOTTOMRIGHT].y = 160;
    gTileClips[TILE_BOTTOMRIGHT].w = TILE_WIDTH;
    gTileClips[TILE_BOTTOMRIGHT].h = TILE_HEIGHT;

    return true;
}

void close(Tile *tiles[])
{
//    gPromptTexture.free();

//    Mix_FreeChunk(gScratch);
//    Mix_FreeChunk(gHigh);
//    Mix_FreeChunk(gMedium);
//    Mix_FreeChunk(gLow);
//
//    Mix_FreeMusic(gMusic);

    for (int i = 0; i < TOTAL_TILES; ++i) {
        delete tiles[i];
        tiles[i] = NULL;
    }

    gTileTexture.free();
    gDotTexture.free();

#ifdef SDL_TTF_H_
    TTF_CloseFont(gFont);
#endif
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
#ifdef SDL_MIX_H_
    Mix_Quit();
#endif
#ifdef SDL_IMG_H_
    IMG_Quit();
#endif
    SDL_Quit();
}

bool checkCollision(SDL_Rect &a, SDL_Rect &b)
{
    if ( (a.x >= b.x + b.w) || (b.x >= a.x + a.w) ||
         (a.y >= b.y + b.h) || (b.y >= a.y + a.h) ) return false;
    return true;
}

bool touchesWall(SDL_Rect &box, Tile *tiles[])
{
    for (int i = 0; i < TOTAL_TILES; ++i) {
        if (tiles[i]->getType() > TILE_BLUE) {
            if (checkCollision(box, tiles[i]->getBox())) {
                return true;
            }
        }
    }
    return false;
}
