#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>

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

bool init();
bool loadMedia();
void close();

SDL_Window *gWindow = NULL;
SDL_Renderer *gRenderer = NULL;
TTF_Font *gFont = NULL;
const int SCREEN_WIDTH = 640, SCREEN_HEIGHT = 480;
const size_t TOTAL_DATA = 10;

int main(int, char**)
{
    if (!init()) {
        printf("Error in main::init!\n");
        return 1;
    }

    SDL_RWops *file = SDL_RWFromFile("./nums.bin", "r+b");
    Sint32 iData[TOTAL_DATA];

    if (!file) {
        printf("Warning: Unable to open file! SDL Error %s\n", SDL_GetError());
        file = SDL_RWFromFile("./nums.bin", "w+b");
        if (file) {
            printf("New file created!\n");
            for (size_t i = 0; i < TOTAL_DATA; ++i) {
                iData[i] = 0;
                SDL_RWwrite(file, &iData[i], sizeof(iData[i]), 1);
            }
        } else {
            printf("Error: Unable to create file! SDL Error: %s\n", SDL_GetError());
            return 1;
        }
    }

    printf("Reading file...\n");
    SDL_RWread(file, &iData, sizeof(iData[0]), TOTAL_DATA);
    SDL_RWclose(file);

    LTexture dataTexture[TOTAL_DATA];
    LTexture promptTexture;
    SDL_Color highlightColor = {255, 0, 0, 255};
    SDL_Color textColor = {0, 0, 0, 255};

    dataTexture[0].loadFromRenderedText(std::to_string(iData[0]), highlightColor);
    for (size_t i = 1; i < TOTAL_DATA; ++i) {
        dataTexture[i].loadFromRenderedText(std::to_string(iData[i]), textColor);
    }
    promptTexture.loadFromRenderedText("Enter Data:", textColor);



    bool quit = false;
    SDL_Event e;
    size_t currentData = 0;

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
                        case SDLK_UP:
                            if (currentData == 0) {
                                currentData = TOTAL_DATA - 1;
                            } else {
                                --currentData;
                            }
                            break;
                        case SDLK_DOWN:
                            if (currentData == TOTAL_DATA - 1) {
                                currentData = 0;
                            } else {
                                ++currentData;
                            }
                            break;
                        case SDLK_LEFT:
                            --iData[currentData];
                            break;
                        case SDLK_RIGHT:
                            ++iData[currentData];
                            break;
                        case SDLK_0:
                            iData[currentData] = 0;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
                    break;
            }
            for (size_t i = 0; i < TOTAL_DATA; ++i) {
                dataTexture[i].loadFromRenderedText(std::to_string(iData[i]),
                                                    ((i == currentData) ? highlightColor : textColor ));
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xff, 0xff, 0xff, 0xff);
        SDL_RenderClear(gRenderer);

        promptTexture.render((SCREEN_WIDTH - promptTexture.getWidth())/2, 0);

        for (size_t i = 0; i < TOTAL_DATA; ++i) {
            dataTexture[i].render((SCREEN_WIDTH - dataTexture[i].getWidth())/2,
                                  promptTexture.getHeight() + i * dataTexture[0].getHeight());
        }

        SDL_RenderPresent(gRenderer);
    }



    file = SDL_RWFromFile("./nums.bin", "w+b");
    if (file) {
        for (size_t i = 0; i < TOTAL_DATA; ++i) {
            SDL_RWwrite(file, &iData[i], sizeof(iData[i]), 1);
        }
        SDL_RWclose(file);
    } else {
        printf("Error: Unable to save file! %s\n", SDL_GetError());
    }

    TTF_CloseFont(gFont);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    TTF_Quit();
    SDL_Quit();

    return 0;
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


// bool loadMedia()
// {
//     if (!gDotTexture.loadFromFile("./dot.bmp")) {
//         printf("Error opening dot.bmp!\n");
//         return false;
//     }
//     if (!gBackground.loadFromFile("./bg.png")) {
//         printf("Error opening bg.bmp!\n");
//         return false;
//     }
//     return true;
// }
// 
bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

#ifdef SDL_IMG_H_
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
#endif

#ifdef SDL_TTF_H_
    if (TTF_Init()) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return false;
    }
#endif

#ifdef SDL_MIX_H_
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        printf("SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError());
        return false;
    }
#endif

    gWindow = SDL_CreateWindow("SDL2 Tutorial",
                               SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!gWindow) {
        printf("SDL_CreateWindow failed! in init\n");
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!gRenderer) {
        printf("SDL_CreateRenderer failed in init\n");
        return false;
    }
#ifdef SDL_TTF_H_
    gFont = TTF_OpenFont("./lazy.ttf", 28);
    if (!gFont) {
        printf("TTF_OpenFont failed! in init\n");
        return false;
    }
#endif
    return true;
}

void close()
{
//    gPromptTexture.free();

//    Mix_FreeChunk(gScratch);
//    Mix_FreeChunk(gHigh);
//    Mix_FreeChunk(gMedium);
//    Mix_FreeChunk(gLow);
//
//    Mix_FreeMusic(gMusic);

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
