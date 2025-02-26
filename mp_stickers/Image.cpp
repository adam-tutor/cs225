#include "Image.h"

void Image::lighten(){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.l += 0.1;
      if (pixel.l > 1.0){
        pixel.l = 1.0;
      }
      if (pixel.l < 0.0){
        pixel.l = 0.0;
      }
    }
  }
}

void Image::lighten(double number){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.l += number;
      if (pixel.l > 1.0){
        pixel.l = 1.0;
      }
      if (pixel.l < 0.0){
        pixel.l = 0.0;
      }
    }
  }
}

void Image::darken(){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.l -= 0.1;
      if (pixel.l < 0.0){
        pixel.l = 0.0;
      }
      if (pixel.l > 1.0){
        pixel.l = 1.0;
      }
    }
  }
}

void Image::darken(double number){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.l -= number;
      if (pixel.l < 0.0){
        pixel.l = 0.0;
      }
      if (pixel.l > 1.0){
        pixel.l = 1.0;
      }
    }
  }
}

void Image::saturate(){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.s += 0.1;
      if (pixel.s > 1.0){
        pixel.s = 1.0;
      }
      if (pixel.s < 0.0){
        pixel.s = 0.0;
      }
    }
  }
}

void Image::saturate(double number){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.s += number;
      if (pixel.s > 1.0){
        pixel.s = 1.0;
      }
      if (pixel.s < 0.0){
        pixel.s = 0.0;
      }
    }
  }
}

void Image::desaturate(){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.s -= 0.1;
      if (pixel.s < 0.0){
        pixel.s = 0.0;
      }
      if (pixel.s > 1.0){
        pixel.s = 1.0;
      }
    }
  }
}

void Image::desaturate(double number){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.s -= number;
      if (pixel.s < 0.0){
        pixel.s = 0.0;
      }
      if (pixel.s > 1.0){
        pixel.s = 1.0;
      }
    }
  }
}

void Image::grayscale(){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.s = 0.0;
    }
  }
}

void Image::rotateColor(double degrees){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      pixel.h += degrees;
      while(pixel.h > 360.0){
        pixel.h -= 360.0;
      }
      while(pixel.h < 0.0){
        pixel.h += 360.0;
      }
    }
  }
}

void Image::illinify(){
  for(unsigned int y = 0; y < height(); y++){
    for(unsigned int x = 0; x < width(); x++){
      cs225::HSLAPixel & pixel = getPixel(x, y);
      if(pixel.h >= 114 && pixel.h <= 243){
        pixel.h = 216;
      }
      else{
        pixel.h = 11;
      }
    }
  }
}

void Image::scale(double size){
  unsigned int w = width() * size;
  unsigned int h = height() * size;
  Image * scaleImage = new Image();
  *scaleImage = *this;
  resize(w, h);
  
  for(unsigned int y = 0; y < h; y++){
    for(unsigned int x = 0; x < w; x++){
      cs225::HSLAPixel &pixel = getPixel(x, y);
      cs225::HSLAPixel &scalePixel = scaleImage->getPixel(x/size, y/size);
      pixel = scalePixel;
    }
  }
  delete scaleImage;
}
  
void Image::scale(unsigned x, unsigned y){
  Image * scaleImage = new Image();
  *scaleImage = *this;
  resize(x, y);
  
  double xResize = x/width();
  double yResize = y/width();
  
  for(unsigned int j = 0; j < y; j++){
    for(unsigned int i = 0; i < x; i++){
      cs225::HSLAPixel &pixel = getPixel(i, j);
      cs225::HSLAPixel &scalePixel = scaleImage->getPixel(i/xResize, j/yResize);
      pixel = scalePixel;
      
    }
  }
  delete scaleImage;
}