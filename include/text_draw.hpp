#ifndef TEXT_DRAW_HPP
#define TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <exception>

namespace g80 {
    

    using namespace std::placeholders;
    
    using expression_map = std::map<std::string, std::function<auto (const std::string &, const uint16_t) -> uint16_t>>;
    

    auto right(const std::string &command, const uint16_t i) -> uint16_t {
        
        return i;
    }
    auto catch_all(const std::string &command, const uint16_t i) -> uint16_t {
        return i;
    }
    auto get_num(const std::string &command, uint16_t &i, std::string &num) -> void {
        while(command[i] == ' ') ++i;
        if (command[i] < '0' || command[i] > '9') throw("Expecting a number");
        num = "0";
        while (command[i] < '0' || command[i] > '9'))
    }

    class text_draw {
    public:
        text_draw(const uint16_t width, const uint16_t height) : 
        width_(width),
        height_(height),
        size_(width_ * height_),
        buffer_ch_(width_ * height_, ch_),
        buffer_col_(width_ * height_, col_) {
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
            expression_map_["arc"] = std::bind(catch_all, _1, _2);
            expression_map_["fil"] = std::bind(catch_all, _1, _2);
            expression_map_["t"] = std::bind(catch_all, _1, _2);
            expression_map_["tcx"] = std::bind(catch_all, _1, _2);
            expression_map_["tcy"] = std::bind(catch_all, _1, _2);

        }

        inline auto ix(const uint16_t x, const uint16_t y) const -> const uint16_t {
            return y * width_ + x;
        }

    private:
        bool wrap_around_ = true;
        uint8_t ch_{32};
        uint8_t col_{7};
        uint16_t x_{0}, y_{0};
        uint16_t width_, height_, size_;
        std::vector<uint8_t> buffer_ch_;
        std::vector<uint8_t> buffer_col_;
        expression_map expression_map_;
    };
}
#endif 