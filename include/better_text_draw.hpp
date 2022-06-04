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
        uint16_t ix_{0};
        uint16_t x_{0}, y_{0};
        uint16_t width_, height_, size_;
        std::vector<uint8_t> buffer_ch_;
        std::vector<uint8_t> buffer_col_;
        const std::string command_;
        expression_map expression_map_;

    private:

        auto set_x() -> void {
            x_ = get_num();
        }

        auto set_y() -> void {
            y_ = get_num();
        }

        auto set_ch() -> void {
            ch_ = get_ch();
        }

        auto set_col() -> void {
            col_ = get_num();
        }

        auto draw_right() -> void {

        }

    private: 

        auto throw_if_end_is_reached() -> void {
            if (end_is_reached()) throw(std::string("End is reached at i:") + std::to_string(ix_));
        }

        auto throw_if_is_not_number() -> void {
            if (is_not_number(command_[ix_])) throw(std::string("Expecting a number at i:") + std::to_string(ix_));
        }

    private:

        auto line(int16_t x1, int16_t y1, int16_t x2, int16_t y2) -> void {
            int16_t dx = x2 - x1;
            int16_t dy = y2 - y1;
            int16_t sdx = dx < 0 ? -1 : 1;
            int16_t sdy = dy < 0 ? -width_ : width_;
            int16_t adx = dx < 0 ? dx * -1 : dx;
            int16_t ady = dy < 0 ? dy * -1 : dy;
            int16_t curr_point = ix(x1, y1);
            
            if (adx >= ady) {    
                for (int16_t i = 0, t = ady; i <= adx; ++i, t += ady) {
                    buffer_ch_[curr_point] = ch_;
                    buffer_col_[curr_point] = col_;

                    if (t >= adx) {
                        curr_point += sdy;
                        t -= adx;
                    }
                    curr_point +=sdx;
                }
            } else {
                for (int16_t i = 0, t = adx; i <= ady; ++i, t += adx) {
                    buffer_ch_[curr_point] = ch_;
                    buffer_col_[curr_point] = col_;
                    
                    if (t >= ady) {
                        curr_point += sdx;
                        t -= ady;
                    }
                    curr_point += sdy;
                }
            }
        }    

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
            
            skip_spaces();
            throw_if_end_is_reached();
            throw_if_is_not_number();            
            
            uint16_t num = 0;
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

        auto set_ch(uint16_t i, uint8_t ch) -> void {
            if (i >= size_) i %= size_;
            buffer_ch_[i] = ch;
        }
        
        auto set_col(uint16_t i, uint16_t col) -> void {
            if (i >= size_) i %= size_;
            buffer_col_[i] = col;
        }

        auto catch_all() -> void {

        }
    };
}
#endif 