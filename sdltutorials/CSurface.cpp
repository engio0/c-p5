#include "CSurface.h"

CSurface::CSurface()
{
}

SDL_Surface *CSurface::OnLoad(char *File)
{
    SDL_Surface *Surf_Temp = nullptr;
    SDL_Surface *Surf_Return = nullptr;

    if ((Surf_Temp = SDL_LoadBMP(File)) == nullptr) {
        return nullptr;
    }

    Surf_Return = SDL_ConvertSurfaceFormat(Surf_Temp, pixelFormat, 0);
    SDL_FreeSurface(Surf_Temp);

    return Surf_Return;
}
