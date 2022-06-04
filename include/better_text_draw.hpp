#ifndef BETTER_TEXT_DRAW_HPP
#define BETTER_TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <exception>

namespace g80 {
    
    using namespace std::placeholders;
    using expression_map = std::map<std::string, std::function<auto () -> void>>;




    class better_text_draw {

    public:
        better_text_draw(const uint16_t width, const uint16_t height, const std::string &command) : 
        width_(width),
        height_(height),
        size_(width_ * height_),
        buffer_ch_(width_ * height_, ch_),
        buffer_col_(width_ * height_, col_),
        command_(command) {
            expression_map_["x"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["y"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["ch"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["col"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["l"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["r"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["u"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["d"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["ul"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["ur"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["ll"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["lr"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["arc"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["fil"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["t"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["tcx"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["tcy"] = std::bind(&better_text_draw::catch_all, *this);
        }



    private:
        uint8_t ch_{32};
        uint8_t col_{7};
        uint16_t ix_{0};
        uint16_t x_{0}, y_{0};
        uint16_t width_, height_, size_;
        std::vector<uint8_t> buffer_ch_;
        std::vector<uint8_t> buffer_col_;
        const std::string command_;
        expression_map expression_map_;

    private:
        
        inline auto ix(const uint16_t x, const uint16_t y) const -> const uint16_t {
            auto t = y * width_ + x;
            return t >= size_ ? t % size_ : t;
        }

        inline auto end_is_reached() -> bool {
            return ix_ == command_.size();
        }

        inline auto end_is_not_reached() -> bool {
            return ix_ < command_.size();
        }

        inline auto skip_spaces() -> void {
            while(end_is_not_reached() && command_[ix_++] == ' ');
        }

        inline auto is_number(const uint8_t ch) -> bool {
            return ch >= '0' && ch <= '9';
        }

        inline auto is_not_number(const uint8_t ch) -> bool {
            return ch < '0' || ch > '9';
        }

        auto get_num() -> uint16_t {
            
            uint16_t num = 0;
            
            skip_spaces();
            
            if (end_is_reached()) throw(std::string("End is reached at i:") + std::to_string(ix_));
            if (is_not_number(command_[ix_])) throw(std::string("Expecting a number at i:") + std::to_string(ix_));
            
            while (end_is_not_reached() && is_number(command_[ix_])) {
                num *= 10;
                num += command_[ix_++] - '0';
            }

            return num;
        }

        auto catch_all() -> void {

        }
    };
}
#endif 