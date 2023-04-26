#include "Image.hpp"

namespace prog
{
  Image::Image(int w, int h, const Color &fill) //2D Array or Vector to implement object pixel as color
  {
  }
  Image::~Image()
  {
  }
  int Image::width() const
  {
    return width_;
  }
  int Image::height() const
  {
    return height_;
  }


  Color& Image::at(int x, int y)
  {
    return pixel_[x][y];
  }

  const Color& Image::at(int x, int y) const
  {
    return pixel_[x][y];
  }
}
