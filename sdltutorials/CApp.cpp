#include "CApp.h"

CApp::CApp()
{
}

int CApp::OnExecute()
{
    return 0;
}

int main(int, char**)
{
    CApp theApp;

    return theApp.OnExecute();
}
