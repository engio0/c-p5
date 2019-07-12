#include "CApp.h"

bool CApp::OnInit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
    if (SDL_CreateWindowAndRenderer(640, 480, SDL_WINDOW_RESIZABLE, &Win_Display, &Ren_Display)) {
        return false;
    }

    SDL_SetWindowTitle(Win_Display, "SDL2 Tutorial");

    return true;
}
