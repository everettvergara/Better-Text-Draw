#include <iostream>
#include <map>
#include "better_text_draw.hpp"

using namespace g80;
auto main(const int argc, const char *argv[]) -> int {
    better_text_draw btd(130, 30, ' ', 7);
    btd.eval(
        "x0y15"
        "ch h col1 r1ur5u3ul1l1ll1d13r2ul3u2ur3r3lr2d4"
        "ch e col2 lr1ur2r5ur2u1ul2l2ll2d4lr1r3"
        "ch l col3 r3ur5u6ul1l1ll1d10lr1"
        "ch ! col4 r3ur5u6ul1l1ll1d10lr1r3"
        "ch o col5 r5ur1r1ur2u1u2ul2l3ll2d4lr2r2"
        "ch . col0 r5ur2"
        "ch w col6 u4d4lr2r1ur2u4d4lr2r1ur2u4d4lr2"
        "ch o col7 r5ur1r1ur2u1u2ul2l3ll2d4lr2r2"
        "ch r col3 r3ur5u3ul1l1ll1d1lr1r10ur1u1ul1l1ll1d7lr1"
        "ch l col2 r3ur5u6ul1l1ll1d10lr1"     
        "ch o col4 r7ur1r1ur2u1u2ul2l3ll2d4lr2r5u13"   
        
        

        
        );
    btd.show();
}



