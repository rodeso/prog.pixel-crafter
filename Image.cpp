#include "Image.hpp"
#include <vector>
namespace prog
{
  Image::Image(int w, int h, const Color &fill) //construtor
  {
    width_ = w;
    height_ = h;
    
    for (int i = 0; i < width_; i++)
    {
      std::vector<Color> v;
      for(int j =0 ; j < height_ ;j++){
        v.push_back(fill);
      }
      pixel_.push_back(v);
      
    }
  }
  Image::Image(const Image& i){ //copia construtor
    width_ = i.width_;
    height_ = i.height_;
    pixel_ = i.pixel_;

  }
  Image::Image(int w, int h,const std::vector<std::vector<Color>>& pixel){ //construtor
    width_ = w;
    height_ = h;
    pixel_ = pixel;
  }
  Image::~Image() //destrutor
  {
    
  }
  int Image::width() const //retorna a largura do image
  {
    return width_;
  }
  int Image::height() const //retorna a altura do image
  {
    return height_;
  }

  
  

  Color& Image::at(int x, int y) //muda o pixel
  {
    return pixel_[x][y];
  }

  const Color& Image::at(int x, int y) const //mostra o pixel
  {
    return pixel_[x][y];
  }
}
