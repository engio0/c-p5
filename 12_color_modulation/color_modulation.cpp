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
        void render(int x, int y, SDL_Rect* clip = NULL);
        int getWidth() { return mWidth; };
        int getHeight() {return mHeight; };
    private:
        SDL_Texture* mTexture = NULL;
        int mWidth = 0;
        int mHeight = 0;
};

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

int main(int, char*[])
{
    return 0;
}
