#include "Color.hpp"

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

    // returna referencias mutáveis
    

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
