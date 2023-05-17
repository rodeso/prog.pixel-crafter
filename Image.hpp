#ifndef __prog_Image_hpp__
#define __prog_Image_hpp__
#include "Color.hpp"
#include <vector>
namespace prog
{
  class Image
  {
  private:
    int width_, height_;
    std::vector<std::vector<Color>> pixel_;
  public:
    Image(int w, int h, const Color &fill = {255, 255, 255});
    Image(const Image& i);
    Image(int w,int h, const std::vector<std::vector<Color>>& pixel);
    ~Image();
    int width() const;
    int height() const;
    Color &at(int x, int y);
    const Color &at(int x, int y) const;
    const int num_color();
  };
}
#endif
