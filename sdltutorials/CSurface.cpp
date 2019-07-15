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

bool CSurface::OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int x, int y)
{
    if (Surf_Dest == nullptr || Surf_Src == nullptr) {
        return false;
    }

    SDL_Rect DestR;
    
    DestR.x = x;
    DestR.y = y;

    SDL_BlitSurface(Surf_Src, NULL, Surf_Dest, &DestR);

    return true;
}
