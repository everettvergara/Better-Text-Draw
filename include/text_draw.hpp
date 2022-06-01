#ifndef TEXT_DRAW_HPP
#define TEXT_DRAW_HPP

#include <iostream>
#include <string>
#include <map>
#include <functional>

namespace g80 {
    
    using int_type = int16_t;
    using expression_map = std::map<std::string, std::function<void*()>>;
    
    class text_draw {
    public:
        text_draw() {}

    private:
        int_type width_, height_;
        expression_map expression_map_;
    };
}
#endif 