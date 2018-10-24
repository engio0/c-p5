#include "default-arg.h"
int Test::testing(int input = 1000) {return input;}
int f() { Test t; return t.testing(); }
