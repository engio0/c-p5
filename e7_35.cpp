#include <string>

typedef std::string Type;
Type initVal();

class Excercise {
    public:
        typedef double Type;
        Type setVal(Type);
        Type initVal();
    private:
        int val;
};

Excercise::Type Excercise::setVal(Type parm) {
    val = parm + initVal();
    return val;
}
