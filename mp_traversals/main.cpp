
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

#include "cs225/HSLAPixel.h"
using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  /*
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");
  */

  PNG sus;
  sus.readFromFile("sus.png");
  FloodFilledImage image(sus);
  
  DFS dfs(sus, Point(20,20), 0.05);
  BFS bfs(sus, Point(100,5), 0.05);
  MyColorPicker based("sus.png");
  RainbowColorPicker rainbow(0.05);
  image.addFloodFill(dfs,based);
  image.addFloodFill(bfs,rainbow);
  Animation animation = image.animate(8000);
  PNG lastFrame = animation.getFrame(animation.frameCount() - 1);
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
