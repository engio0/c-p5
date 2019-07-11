#ifndef _CAPP_H
#define _CAPP_H

#include <SDL.h>

class CApp
{
    public:
        CApp();
        int OnExecute();
        bool OnInit();
        void OnEvent(SDL_Event* Event);
        void OnLoop();
        void OnRender();
        void OnCleanup();
    private:
        bool Running;
        SDL_Surface* Surf_Display;
};

#endif
