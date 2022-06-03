#ifndef TEXT_DRAW_HPP
#define TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>

namespace g80 {
    

    using namespace std::placeholders;
    using int_type = int16_t;
    
    using expression_map = std::map<std::string, std::function<void(const std::string &, const int_type)>>;
    
    // Function Signatures:
    // [direction] [length-int]

    auto right(const std::string &command, const int_type i) -> void {
    }
    auto catch_all(const std::string &command, const int_type i) -> void {
    }

    class text_draw {
    public:
        text_draw(int_type width, int_type height) : 
        width_(width),
        height_(height),
        buffer_ch_(width_ * height_, ' '),
        buffer_col_(width_ * height_, 7) {
            expression_map_["x"] = std::bind(catch_all, _1, _2);
            expression_map_["y"] = std::bind(catch_all, _1, _2);
            expression_map_["ch"] = std::bind(catch_all, _1, _2);
            expression_map_["col"] = std::bind(catch_all, _1, _2);
            expression_map_["l"] = std::bind(catch_all, _1, _2);
            expression_map_["r"] = std::bind(catch_all, _1, _2);
            expression_map_["u"] = std::bind(catch_all, _1, _2);
            expression_map_["d"] = std::bind(catch_all, _1, _2);
            expression_map_["ul"] = std::bind(catch_all, _1, _2);
            expression_map_["ur"] = std::bind(catch_all, _1, _2);
            expression_map_["ll"] = std::bind(catch_all, _1, _2);
            expression_map_["lr"] = std::bind(catch_all, _1, _2);

        }

    private:
        int_type width_, height_;
        std::vector<char> buffer_ch_;
        std::vector<uint8_t> buffer_col_;
        expression_map expression_map_;
        int_type x_, y_;

    };
}
#endif 