/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#pragma once
#include "Image.h"

class StickerSheet {
  public:
    StickerSheet(const Image &picture, unsigned max);
    StickerSheet(const StickerSheet &other);
    const StickerSheet & operator=(const StickerSheet &other);
    
    ~StickerSheet();
    
    void changeMaxStickers(unsigned max);
    int addSticker(Image &sticker, unsigned x, unsigned y);
    bool translate(unsigned index, unsigned x, unsigned y);
    void removeSticker(unsigned index);
    Image render() const;
    Image *getSticker(unsigned index) const;
  
  private:
    void copy(StickerSheet const &other);
    void destroy();
    Image base;
    Image **Background;
    unsigned maximum;
    unsigned *xcoordinate;
    unsigned *ycoordinate;
    unsigned quantity;
};
 
