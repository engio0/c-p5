//void f();
struct X {
    friend void f() { }
    X() { f(); }
    void g();
    void h();
};

void X::g() { return f(); }
void f();
void X::h() { return f(); }

