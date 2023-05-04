#include "Image.hpp"
#include <vector>
namespace prog
{
  Image::Image(int w, int h, const Color &fill)
  {
    w_=w;
    h_=h;
    
    for (int i = 0; i < w_; i++)
    {
      std::vector<Color> v;
      for(int j =0 ; j<h_ ;j++){
        v.push_back(fill);
      }
      pixeis_.push_back(v);
      
    }
    
    
  }
  Image::Image(const Image& i){
    w_=i.w_;
    h_=i.h_;
    pixeis_=i.pixeis_;

  }
  Image::Image(int w, int h,const std::vector<std::vector<Color>>& pixeis){
    w_=w;
    h_=h;
    pixeis_=pixeis;
  }
  Image::~Image()
  {
    
  }
  int Image::width() const
  {
    return w_;
  }
  int Image::height() const
  {
    return h_;
  }

  
  

  Color& Image::at(int x, int y)
  {
    return pixeis_[x][y];
  }

  const Color& Image::at(int x, int y) const
  {
    return pixeis_[x][y];
  }
}
