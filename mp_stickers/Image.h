/**
 * @file Image.h
 * Contains your declaration of the interface for the Image class.
 */

#pragma once
#include "cs225/PNG.h"

class Image:public cs225::PNG{
  public:
    void lighten();
    void lighten(double number);
    void darken();
    void darken(double number);
    void saturate();
    void saturate(double number);
    void desaturate();
    void desaturate(double number);
    void grayscale();
    void rotateColor(double degrees);
    void illinify();
    void scale(double size);
    void scale(unsigned x, unsigned y);
};