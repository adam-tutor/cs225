#include "StickerSheet.h"
#include "Image.h"
using namespace std;

StickerSheet::StickerSheet(const Image &picture, unsigned max){
  maximum = max;
  quantity = 0;
  base = picture;
  Background = new Image *[maximum];
  xcoordinate = new unsigned[maximum];
  ycoordinate = new unsigned[maximum];
  for (unsigned i = 0; i<maximum; i++){ //without initializing every pointer, nothing gets cleared for multiple runs
    Background[i] = NULL; //doing some tests with cout, this is ran a lot, so initialization is needed
    xcoordinate[i]=0;
    ycoordinate[i]=0;
  }
}

StickerSheet::StickerSheet(const StickerSheet &other){
  copy(other);
}

void StickerSheet::copy(StickerSheet const &other){
  base = other.base; //Since we are copying, we need to create temporary other variables
  maximum = other.maximum;
  quantity = other.quantity;
  
  xcoordinate = new unsigned[maximum]; //We need to create a whole new structure for obtaining maximums since this is a copy
  ycoordinate = new unsigned[maximum];
  
  Background = new Image *[maximum]; //A new image also needs to be created since this is a copy
  
  for(unsigned i=0; i<maximum; i++){
    Background[i]=NULL;
  }
  for(unsigned i = 0; i<quantity; i++){
    Background[i] = new Image();
    *(Background[i]) = *(other.Background[i]);
    xcoordinate[i] = other.xcoordinate[i];
    ycoordinate[i] = other.ycoordinate[i];
  }
}

StickerSheet::~StickerSheet(){
  destroy();
}

void StickerSheet::destroy(){
  for (unsigned i = 0; i<quantity; i++){
    delete Background[i];
    Background[i]=NULL; //We start by initializing the background and setting everything in the array to NULL and deleting it
  }
  delete[] Background;
  delete[] xcoordinate;
  delete[] ycoordinate;
  
  Background = NULL; //I don't know if this is required or not, but I feel like it's good practice to set them all to NULL
  xcoordinate = NULL;
  ycoordinate = NULL;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet &other){
  if(this == &other){
    return *this;
  }
  else{
    destroy();
    copy(other);
    return *this;
  }
}

void StickerSheet::changeMaxStickers(unsigned newmax){
  if (newmax == quantity){
    return;
  }
  
  Image* *newpicture = new Image*[newmax];
  unsigned* newxval = new unsigned[newmax];
  unsigned* newyval = new unsigned[newmax];
  for(unsigned i=0; i<newmax; i++){
    newpicture[i] = NULL;
  }

  if(quantity < newmax){
    for(unsigned i=0; i<quantity; i++){
      newpicture[i] = new Image(); //This is one of the parts that gave me the most trouble with figuring out how pointers work
      *newpicture[i] = *Background[i];
      newxval[i] = xcoordinate[i];
      newyval[i] = ycoordinate[i];
    }
  }
  else{
    for(unsigned i=0; i<newmax; i++){
      newpicture[i] = new Image();
      *newpicture[i] = *Background[i];
      newxval[i] = xcoordinate[i];
      newyval[i] = ycoordinate[i];
    }
    quantity = newmax;
  }
  destroy();
  Background = newpicture; //sets the new values we obtained through changing the maximums and sets them as the current values
  newpicture = NULL; //Then, we get rid of all of the temporary variables for when we need to run the function again
  xcoordinate = newxval;
  ycoordinate = newyval;
  newxval = NULL;
  newyval = NULL;
  maximum = newmax;
}

int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
  if(quantity < maximum){
    if(Background[quantity] == NULL){
      Background[quantity] = new Image();
    }
    *Background[quantity] = sticker;
    xcoordinate[quantity] = x;
    ycoordinate[quantity] = y;
    quantity++;
    return(quantity - 1);
  }
  return -1;
}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
  if (index < quantity){
    xcoordinate[index] = x;
    ycoordinate[index] = y;
    return true;
  }
  else{
    return false;
  }
}

void StickerSheet::removeSticker(unsigned index){
    delete Background[index];
    for(unsigned i = index; i<(quantity-1); i++){
      xcoordinate[i] = xcoordinate[i+1];
      ycoordinate[i] = ycoordinate[i+1];
      Background[i] = Background[i+1];
    }
    Background[quantity - 1] = NULL;
    quantity--;
}

Image StickerSheet::render() const{
  Image finalImage; //Rendering was also very hard, since there are so many equations that need to be inserted... more on that below
  unsigned totalwidth = base.width(); //Without creating a variable for base.width and height, you cannot do operations with base.width()
  unsigned totalheight = base.height();
  for(unsigned i = 0; i < quantity; i++){
    if(Background[i] != NULL){
      unsigned x = xcoordinate[i] + Background[i]->width();
      unsigned y = ycoordinate[i] + Background[i]->height();
      if(x > totalwidth){
        totalwidth = x;
      }
      if(y > totalheight){
        totalheight = y;
      }
    }
  }
  finalImage = base;
  finalImage.resize(totalwidth, totalheight);
  
  for(unsigned i=0; i<quantity; i++){
    if(Background[i] != NULL){
      unsigned x = xcoordinate[i] + Background[i]->width();
      unsigned y = ycoordinate[i] + Background[i]->height();
      unsigned cweight = x; //I thought it would be easier to create variables to store these equations instead of writing this out
      unsigned cheight = y;
      for(unsigned w = xcoordinate[i]; w<cweight; w++){
        for(unsigned h = ycoordinate[i]; h<cheight; h++){
          cs225::HSLAPixel &current_pixels = Background[i]->getPixel((w-xcoordinate[i]), (h-ycoordinate[i])); //Same here, this line is very long and even though we use it twice, it's to keep organized
          if(current_pixels.a !=0){
            finalImage.getPixel(w,h) = current_pixels;
          }
        }
      }
    }
  }
  return finalImage;
}

Image * StickerSheet::getSticker(unsigned index) const{ //required in order to test
  if(index < quantity){
    return Background[index];
  }
  return NULL;
}