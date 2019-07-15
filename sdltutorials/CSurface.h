#ifndef _CSURFACE_H_
#define _CSURFACE_H_

#include <SDL.h>

class CSurface
{
    public:
        CSurface();
        static SDL_Surface *OnLoad(char *File);
        static bool OnDraw(SDL_Surface *Surf_Dest, SDL_Surface *Surf_Src, int x, int y);
    private:
        static Uint32 pixelFormat;
};

#endif
