#ifndef CP_CH7_PERSON
#define CP_CH7_PERSON

#include <string>
#include <vector>
#include <iostream>

class Screen;

class Window_mgr {
    public:
        using ScreenIndex = std::vector<Screen>::size_type;
        void clear(ScreenIndex);
    private:
        std::vector<Screen> screens;
};

class Screen {
    friend void Window_mgr::clear(ScreenIndex);

    public:
        using pos = std::string::size_type;

        Screen() = default;
        Screen(pos ht, pos wd) : height(ht), width(wd), contents(ht*wd, ' ') {}
        Screen(pos ht, pos wd, char c) : height(ht), width(wd), contents(ht*wd, c) {}

        char get() const { return contents[cursor]; }
        char get(pos ht, pos wd) const { return contents[ht*width+wd]; };
        Screen& move(pos r, pos c);
        Screen& set(char);
        Screen& set(pos, pos, char);

        Screen& display(std::ostream &os) { do_display(os); return *this; }
        const Screen& display(std::ostream &os) const { do_display(os); return *this; }

    private:
        pos cursor = 0;
        pos height = 0, width = 0;
        std::string contents;
        void do_display(std::ostream &os) const { os << contents; }
};

inline void Window_mgr::clear(ScreenIndex i)
{
    if (i >= screens.size()) return;
    Screen& s = screens[i];
    s.contents = std::string(s.height * s.width, ' ');
}

inline Screen& Screen::move(pos r, pos c)
{
    cursor = r * width + c;
    return *this;
}

inline Screen& Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen& Screen::set(pos r, pos c, char ch)
{
    contents[r*width + c] = ch;
    return *this;
}

int main()
{
    Screen myScreen(5, 5, 'X');
    myScreen.move(4, 0).set('#').display(std::cout);
    std::cout << '\n';
    myScreen.move(2, 0).set('%');
    myScreen.display(std::cout);
    std::cout << '\n';
}


#endif
