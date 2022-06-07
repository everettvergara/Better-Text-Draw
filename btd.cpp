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
#include <string>
#include "better_text_draw.hpp"

using namespace g80;

auto validate(const int argc, const char *argv[]) -> void {

    static std::string format = 
    "\n\n"
    "Syntax:\n"
    "btd {width} {height} < command_input_file\n";

    auto is_number = [&](const std::string &to_check) -> bool {
        for (auto &ch : to_check) if (!std::isdigit(ch)) return false;
        return true;
    };

    if (argc < 3) throw std::runtime_error(std::string("Must have width and height of the canvass.") + format);    
    if (!is_number(argv[1])) throw std::runtime_error(std::string("Please input a valid width for the canvass") + format);
    if (!is_number(argv[2])) throw std::runtime_error(std::string("Please input a valid height for the canvass") + format);
    if (std::stoi(argv[1]) <= 0) throw std::runtime_error(std::string("Valid width for canvass shoud be > 0") + format);
    if (std::stoi(argv[2]) <= 0) throw std::runtime_error(std::string("Valid height for canvass should be > 0") + format);

}

auto main(const int argc, const char *argv[]) -> int {

    try {
        validate(argc, argv);

        std::string command;
        better_text_draw btd(std::stoi(argv[1]), std::stoi(argv[2]), '`', 7);
        do {
            getline(std::cin, command);
        } while(btd.eval(command));

        btd.show();
    
    } catch (std::runtime_error re) {
        std::cout << re.what() << std::endl;
    }
}
