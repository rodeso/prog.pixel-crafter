#ifndef __prog_XPM2_hpp__
#define __prog_XPM2_hpp__

#include <string>
#include <unordered_map>
#include "Image.hpp"

namespace prog {
    Image* loadFromXPM2(const std::string &file);
    void saveToXPM2(const std::string& file, const Image* img);
    Color getColor(const std::string& str);
    bool hasColor(const std::unordered_map<char, Color>& colorMap, const Color& color);
    char colorToSymbol(const std::unordered_map<char, Color>& colorMap, const Color& currentColor);
}
#endif
