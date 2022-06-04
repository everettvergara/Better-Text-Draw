#ifndef BETTER_TEXT_DRAW_HPP
#define BETTER_TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <exception>
#include <tuple>
#include <sstream>

namespace g80 {
    
    using namespace std::placeholders;
    using expression_map = std::map<std::string, std::function<auto () -> void>>;

    class better_text_draw {

    public:

        // THROW if size = 0
        better_text_draw(const int16_t width, const int16_t height, const std::string &command) : 
            width_(width), height_(height), size_(width_ * height_),
            buffer_ch_(width_ * height_, ch_),
            buffer_col_(width_ * height_, col_),
            command_(command) {

            // TODO: Could be a template? WHY? so expressionmap can be made static per widht_ height
            expression_map_["x"] = std::bind(&better_text_draw::set_x, *this);
            expression_map_["y"] = std::bind(&better_text_draw::set_y, *this);
            expression_map_["ch"] = std::bind(&better_text_draw::set_ch, *this);
            expression_map_["col"] = std::bind(&better_text_draw::set_col, *this);
            expression_map_["l"] = std::bind(&better_text_draw::draw_left, *this);
            expression_map_["r"] = std::bind(&better_text_draw::draw_right, *this);
            expression_map_["u"] = std::bind(&better_text_draw::draw_up, *this);
            expression_map_["d"] = std::bind(&better_text_draw::draw_down, *this);
            expression_map_["ul"] = std::bind(&better_text_draw::draw_upper_left, *this);
            expression_map_["ur"] = std::bind(&better_text_draw::draw_upper_right, *this);
            expression_map_["ll"] = std::bind(&better_text_draw::draw_lower_left, *this);
            expression_map_["lr"] = std::bind(&better_text_draw::draw_lower_right, *this);
            expression_map_["arc"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["fil"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["t"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["tcx"] = std::bind(&better_text_draw::catch_all, *this);
            expression_map_["tcy"] = std::bind(&better_text_draw::catch_all, *this);
        }

        // TODO: check if command / ix need not be instance of the class
        auto eval() -> bool {
            try {
                do {
                    std::string command = get_command();
                    auto f = expression_map_.find(command);
                    if (f == expression_map_.end()) {
                        std::cout << "command not found -> " << command << std::endl;
                        return false;
                    }
                } while (++ix_ != size_);

            } catch (std::exception e) {
                std::cout << e.what() << std::endl;
                return false;
            }

            return true;
        }

        auto show(bool clear_screen = false) const -> void {
            // todo: all size vars should be changed to size_t
            std::stringstream output;
            if (clear_screen) output << "\033[2J";
            
            int16_t next_line = width_, i = 0, current_color = -1;
            do {
                if (current_color != buffer_col_[i]) {
                    current_color = buffer_col_[i];
                    output << color_[current_color];
                }

                output << buffer_ch_[i++];
                if (i == next_line) {output << "\n"; next_line += width_;}
            } while (i != size_);

            output << "\033[0m\n";
            std::cout << output.str();
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

        static const std::string color_[];
        static const size_t sizeof_color_;
            
    private:

        auto set_x() -> void {
            ix_ = ix(get_num(), current_y());
        }

        auto set_y() -> void {
            ix_ = ix(current_x(), get_num());
        }

        auto set_ch() -> void {
            ch_ = get_ch();
        }

        auto set_col() -> void {
            auto t = get_num();
            col_ = t >= sizeof_color_ ? t % sizeof_color_ : t;
        }

        auto draw_right() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x + move, y);
        }

        auto draw_left() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x - move, y);
        }

        auto draw_up() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x, y - move);
        }

        auto draw_down() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x, y + move);
        }

        auto draw_upper_left() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x - move, y - move);
        }

        auto draw_upper_right() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x + move, y - move);
        }

        auto draw_lower_right() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x + move, y + move);
        }

        auto draw_lower_left() -> void {
            auto move = get_num();
            auto [x, y] = current_xy();
            line(x - move, y + move);
        }

    private: 

        auto throw_if_end_is_reached() const -> void {
            if (end_is_reached()) throw(std::string("End is reached at i:") + std::to_string(ix_));
        }

        auto throw_if_is_not_number() const -> void {
            if (is_not_number(command_[ix_])) throw(std::string("Expecting a number at i:") + std::to_string(ix_));
        }

        auto throw_if_is_not_ch() const -> void {
            if (is_not_ch(command_[ix_])) throw(std::string("Expecting a char command at i:") + std::to_string(ix_));
        }

    private:

        auto line(const int16_t x, const int16_t y) -> void {

            auto [cx, cy] = current_xy();
            int16_t dx = x - cx;
            int16_t dy = y - cy;
            int16_t sdx = dx < 0 ? -1 : 1;
            int16_t sdy = dy < 0 ? -width_ : width_;
            int16_t adx = dx < 0 ? dx * -1 : dx;
            int16_t ady = dy < 0 ? dy * -1 : dy;
            
            if (adx >= ady) {    
                for (int16_t i = 0, t = ady; i <= adx; ++i, t += ady) {
                    update_ch();
                    update_col();

                    if (t >= adx) {
                        ix_ += sdy;
                        t -= adx;
                    }
                    ix_ +=sdx;
                }
            } else {
                for (int16_t i = 0, t = adx; i <= ady; ++i, t += adx) {
                    update_ch();
                    update_col();
                    
                    if (t >= ady) {
                        ix_ += sdx;
                        t -= ady;
                    }
                    ix_ += sdy;
                }
            }
        }    

    private:


        inline auto current_x() const -> int16_t {
            return ix_ % size_;
        }
        
        inline auto current_y() const -> int16_t {
            return ix_ / size_;
        }

        inline auto current_xy() const -> std::tuple<int16_t, int16_t> {
            return {current_x(), current_y()};
        }

        inline auto ix(const int16_t x, const int16_t y) const -> const int16_t {
            auto t = y * width_ + x;
            return t >= size_ ? t % size_ : t;
        }

        inline auto end_is_reached() const -> bool {
            return ix_ == command_.size();
        }

        inline auto end_is_not_reached() const -> bool {
            return ix_ < command_.size();
        }

        inline auto skip_spaces() -> void {
            while(end_is_not_reached() && command_[ix_] == ' ') ++ix_;
        }

        inline auto is_number(const uint8_t ch) const -> bool {
            return ch >= '0' && ch <= '9';
        }

        inline auto is_not_number(const uint8_t ch) const -> bool {
            return ch < '0' || ch > '9';
        }

        inline auto is_ch(const uint8_t ch) const -> bool {
            return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
        }

        inline auto is_not_ch(const uint8_t ch) const -> bool {
            return !is_ch(ch);
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

        auto get_command() -> std::string {
            
            skip_spaces();
            // TODO: improve confidence and remove throws
            throw_if_end_is_reached();
            throw_if_is_not_ch();            
            
            std::string command;
            while (end_is_not_reached() && is_ch(command_[ix_])) command += command_[ix_++];

            return command;
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

    const std::string better_text_draw::color_[] { "\033[30m", "\033[31m", "\033[32m", "\033[33m", "\033[34m", "\033[35m", "\033[36m", "\033[37m" };
    const size_t better_text_draw::sizeof_color_{sizeof(better_text_draw::color_) / sizeof(std::string)};
}
#endif 