#ifndef TEXT_DRAW_HPP
#define TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>

namespace g80 {
    
    using int_type = int16_t;
    using expression_map = std::map<std::string, std::function<void*()>>;
    
    class text_draw {
    public:
        text_draw(int_type width, int_type height) : 
        width_(width + 1),
        height_(height),
        buffer_(width_ * height_, ' ') {
            for (int_type i = width_; i < width_ * height_; i += width_) buffer_[i] = '\n';
        }

    private:
        int_type width_, height_;
        std::string buffer_;
        expression_map expression_map_;
    };
}
#endif 