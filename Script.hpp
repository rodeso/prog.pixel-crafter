#ifndef __prog_Script_hpp__
#define __prog_Script_hpp__

#include <string>
#include <fstream>
#include "Image.hpp"

namespace prog
{
  class Script
  {
  public: 
    Script(const std::string &filename);
    ~Script();
    void run();
  private:
    // Current image.
    Image *image;
    // Input stream for reading script commands.
    std::ifstream input;
  private:
    // Private functions
    void clear_image_if_any();
    void open();
    void blank();
    void save();
    void invert();
    void replace(Color c1 ,Color c2);
    void to_gray_scale();
    void fill(int x, int y, int w, int h, Color c);
    void v_mirror();
    void h_mirror();
    void add();
    void crop(int x, int y, int w, int h);
    void rotate_left();
    void rotate_right();
    void median_filter();
  };
}
#endif
