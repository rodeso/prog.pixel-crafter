#include "Color.hpp"
#include <sstream>
#include <iomanip>

namespace prog {
    // construtor default
    Color::Color() {
        red_=0;
        green_=0;
        blue_=0;
    }
    // construtor copia
    Color::Color(const Color& other) {
        red_=other.red_;
        green_=other.green_;
        blue_=other.blue_;
    }
    // construtor com valores
    Color::Color(rgb_value red, rgb_value green, rgb_value blue) {
        red_=red;
        green_=green;
        blue_=blue;
    }
    // getters
    rgb_value Color::red() const {
        return red_;
    }
    rgb_value Color::green() const {
        return green_;
    }
    rgb_value Color::blue() const {
        return blue_;
    }
    //rgb para hex
    std::string Color::toHex() const {
        std::stringstream ss;
        ss << "#" << std::setfill('0') << std::setw(2) << std::hex << red_
           << std::setfill('0') << std::setw(2) << std::hex << green_
           << std::setfill('0') << std::setw(2) << std::hex << blue_;
        return ss.str();
    }

    // retorna referencias mutáveis
    

    rgb_value& Color::red()  {
        return red_;
    }
    rgb_value& Color::green()  {
      return green_;
    }
    rgb_value& Color::blue()  {
      return blue_;
    }
}
