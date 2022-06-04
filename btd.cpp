#include <iostream>
#include <map>
#include "better_text_draw.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {
    better_text_draw btd(100, 30);
    btd.eval(
        "x0y15ch+col1r1ur5u3ul1l1ll1d13r2ul3u2ur3r3lr2d4"
        "ch~col2lr1ur2r5ur2u1ul2l2ll2d4lr1r3"
        "ch|col3r3ur5u6ul1l1ll1d10lr1"
        "ch!col4r3ur5u6ul1l1ll1d10lr1r3"
        "ch*col5r5ur1r1ur2u1u2ul2l3ll2d4lr2");
    btd.show();
}



