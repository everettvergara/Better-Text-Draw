/*
 *  Main program for processing
 *  Copyright (C) 2022 Everett Gaius S. Vergara
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *	
 */

#include <iostream>
#include "better_text_draw.hpp"

using namespace g80;

auto validate(const int argc, const char *argv[]) -> std::string {

    static std::string format = 
    "\n\n"
    "Syntax:\n"
    "btd {width} {height} < command_input_file\n";

    auto is_number = [&](const std::string &to_check) -> bool {
        for (auto &ch : to_check) if (!std::isdigit(ch)) return false;
        return true;
    };

    if (argc < 3) return std::string("Must have width and height of the canvass.") + format;    
    if (!is_number(argv[1])) return std::string("Please input a valid width for the canvass") + format;
    if (!is_number(argv[2])) return std::string("Please input a valid height for the canvass") + format;
    if (std::stoi(argv[1]) <= 0) return std::string("Valid width for canvass > 0") + format;
    if (std::stoi(argv[2]) <= 0) return std::string("Valid height for canvass > 0") + format;

    return "";
}

auto main(const int argc, const char *argv[]) -> int {
    
    if (auto msg = validate(argc, argv); msg.size() > 0) {
        std::cout << msg << std::endl;
        return -1;
    }

    try {
        better_text_draw btd(130, 30, ' ', 7);
        btd.eval(
            "mlr10"
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
            "ch d col4 r7ur1r1ur2u1u2ul2l3ll2d4lr2r5u13"
            "ch + col 1 circ10circ15"        
            );
        btd.show();
    
    } catch (std::runtime_error re) {
        std::cout << re.what() << std::endl;
    }
}



