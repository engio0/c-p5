#include "CApp.h"

void CApp::OnEvent(SDL_Event* Event)
{
    switch (Event->type) {
        case SDL_QUIT:
            Running = false;
            break;
        case SDL_KEYDOWN:
            switch (Event->key.keysym.sym) {
                case SDLK_q:
                    Running = false;
                    break;
                default:
                    break;
            }
        default:
            break;
    }
}
