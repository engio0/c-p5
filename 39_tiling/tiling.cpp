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
        SDL_Rect getBox() { return mBox; }
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
bool checkCollision(SDL_Rect a, SDL_Rect b);
bool touchesWall(SDL_Rect box, Tile *tiles[]);
bool setTiles(Tile *tiles[]);

LTexture gTileTexture, gDotTexture;
SDL_Rect gTileClips[TOTAL_TILES];
SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;

int main(int, char**)
{
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
