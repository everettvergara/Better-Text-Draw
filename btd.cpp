#include <iostream>
#include <map>
#include "better_text_draw.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {
    better_text_draw btd(100, 10);
    btd.eval("ch*r10");
    btd.show();
}


