#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //
  
  Image doge;
  doge.readFromFile("doge.png");
  
  Image gamer;
  gamer.readFromFile("gamer.png");
  
  Image hot;
  hot.readFromFile("hot.png");
  
  Image graphicdesigner;
  graphicdesigner.readFromFile("graphicdesigner.png");
  
  Image alma;
  alma.readFromFile("alma.png");
  Image output;
  StickerSheet meme(alma, 5);
  meme.addSticker(doge, 50, 400);
  meme.addSticker(gamer, 650, 200);
  meme.addSticker(hot, 260, 180);
  meme.addSticker(graphicdesigner, 0, 0);
  output = meme.render();
  output.writeToFile("myImage.png");

  return 0;
}
