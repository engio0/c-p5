#include <SDL.h>

class LWindow
{
    public:
        bool init();
        SDL_Renderer* createRenderer();
        void handleEvent(SDL_Event& e);
        void free();
        int getWidth();
        int getHeight();
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();
    private:
        SDL_Window* mWindow = NULL;
        int mWidth = 0;
        int mHeight = 0;
        bool mMouseFocus = false;
        bool mKeyboardFocus = false;
        bool mFullScreen = false;
        bool mMinimized = false;
};

int main(int, char**)
{
    return 0;
}
