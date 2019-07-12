#include "CApp.h"

CApp::CApp()
{
    Win_Display = nullptr;
    Ren_Display = nullptr;

    Running = true;
}

int CApp::OnExecute()
{
    if (!OnInit()) {
        return -1;
    }

    SDL_Event Event;

    while (Running) {
        while (SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}

int main(int, char**)
{
    CApp theApp;

    return theApp.OnExecute();
}
