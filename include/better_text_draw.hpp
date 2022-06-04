#ifndef BETTER_TEXT_DRAW_HPP
#define BETTER_TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <exception>
#include <tuple>

namespace g80 {
    
    using namespace std::placeholders;
    using expression_map = std::map<std::string, std::function<auto () -> void>>;

    class better_text_draw {

    public:

        better_text_draw(const int16_t width, const int16_t height, const std::string &command) : 
            width_(width), height_(height), size_(width_ * height_),
            buffer_ch_(width_ * height_, ch_),
            buffer_col_(width_ * height_, col_),
            command_(command) {

            expression_map_["x"] = std::bind(&better_text_draw::set_x, *this);
            expression_map_["y"] = std::bind(&better_text_draw::set_y, *this);
            expression_map_["ch"] = std::bind(&better_text_draw::set_ch, *this);
            expression_map_["col"] = std::bind(&better_text_draw::set_col, *this);
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
        int16_t ix_{0};
        int16_t width_, height_, size_;
        std::vector<uint8_t> buffer_ch_;
        std::vector<uint8_t> buffer_col_;
        const std::string command_;
        expression_map expression_map_;

    private:

        auto set_x() -> void {
            auto x = get_num();
        }

        auto set_y() -> void {
            auto y = get_num();
        }

        auto set_ch() -> void {
            ch_ = get_ch();
        }

        auto set_col() -> void {
            col_ = get_num();
        }

        auto draw_right() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x, y);
        }

    private: 

        auto throw_if_end_is_reached() -> void {
            if (end_is_reached()) throw(std::string("End is reached at i:") + std::to_string(ix_));
        }

        auto throw_if_is_not_number() -> void {
            if (is_not_number(command_[ix_])) throw(std::string("Expecting a number at i:") + std::to_string(ix_));
        }

    private:

        auto line(const int16_t x, const int16_t y) -> void {
            // int16_t dx = x2 - x_;
            // int16_t dy = y2 - y_;
            // int16_t sdx = dx < 0 ? -1 : 1;
            // int16_t sdy = dy < 0 ? -1 : 1;
            // int16_t adx = dx < 0 ? dx * -1 : dx;
            // int16_t ady = dy < 0 ? dy * -1 : dy;
            
            // if (adx >= ady) {    
            //     for (int16_t i = 0, t = ady; i <= adx; ++i, t += ady) {
            //         update_ch();
            //         update_col();

            //         if (t >= adx) {
            //             curr_point += sdy;
            //             t -= adx;
            //         }
            //         curr_point +=sdx;
            //     }
            // } else {
            //     for (int16_t i = 0, t = adx; i <= ady; ++i, t += adx) {
            //         update_ch();
            //         update_col();
                    
            //         if (t >= ady) {
            //             curr_point += sdx;
            //             t -= ady;
            //         }
            //         curr_point += sdy;
            //     }
            // }
        }    

    private:

        auto current_xy() -> std::tuple<int16_t, int16_t> {
            int16_t x = ix_ % size_;
            int16_t y = ix_ / size_;
            return {x, y};
        }

        inline auto ix(const int16_t x, const int16_t y) const -> const int16_t {
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

        auto get_num() -> int16_t {
            
            skip_spaces();
            throw_if_end_is_reached();
            throw_if_is_not_number();            
            
            int16_t num = 0;
            while (end_is_not_reached() && is_number(command_[ix_])) {
                num *= 10;
                num += command_[ix_++] - '0';
            }

            return num;
        }

        auto get_ch() -> uint8_t {
            
            skip_spaces();
            throw_if_end_is_reached();
            
            return command_[ix_++];
        }

        auto update_ch() -> void {
            if (ix_ >= size_) ix_ %= size_;
            buffer_ch_[ix_] = ch_;
        }
        
        auto update_col() -> void {
            if (ix_ >= size_) ix_ %= size_;
            buffer_col_[ix_] = col_;
        }

        auto catch_all() -> void {

        }
    };
}
#endif 