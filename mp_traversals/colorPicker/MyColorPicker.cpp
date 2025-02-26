#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"

using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(string filename_){
  png_.readFromFile(filename_);
}

HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  double hue;
  HSLAPixel pixel_lol = png_.getPixel(x, y);
  hue = x*x + y*y;
  if(pixel_lol.l > .1){
    pixel_lol = HSLAPixel(HSLAPixel(100,0.8,0.5));
  }
  return pixel_lol;
}
