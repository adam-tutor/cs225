#include <cmath>
#include <iterator>
#include <iostream>

#include "../cs225/HSLAPixel.h"
#include "../cs225/PNG.h"
#include "../Point.h"

#include "ImageTraversal.h"

/**
 * Calculates a metric for the difference between two pixels, used to
 * calculate if a pixel is within a tolerance.
 *
 * @param p1 First pixel
 * @param p2 Second pixel
 * @return the difference between two HSLAPixels
 */
double ImageTraversal::calculateDelta(const HSLAPixel & p1, const HSLAPixel & p2) {
  double h = fabs(p1.h - p2.h);
  double s = p1.s - p2.s;
  double l = p1.l - p2.l;

  // Handle the case where we found the bigger angle between two hues:
  if (h > 180) { h = 360 - h; }
  h /= 360;

  return sqrt( (h*h) + (s*s) + (l*l) );
}

/**
 * Default iterator constructor.
 */
ImageTraversal::Iterator::Iterator() {
  /** @todo [Part 1] */
  current = Point(-1, -1);
  traversal = NULL;
  }

ImageTraversal::Iterator::Iterator(PNG png, Point start, double tolerance, ImageTraversal* trav) {
  png_ = png;
  tolerance_ = tolerance;
  traversal = trav;
  start_ = start;
  startpoint = start_;
  
  unsigned int i = 0;
  unsigned int j = 0;
  unsigned int height = png_.height();
  visit.resize(png_.width(), std::vector<bool>(height));

  for(i=0; i<png_.width(); i++){ //We fill the vector in with true everywhere to begin with because nothing has been visited yet
    for(j=0; j<png_.height(); j++){ //I used the AMA slides which showed a 3x3 grid being traversed, so using a 2D Vector seemed like the right choice
      visit[i][j] = true; //I messed around with a 1D vector but couldn't fill in the dimensions right so I quickly gave up on it
    }
  }
}

/**
 * Iterator increment opreator.
 *
 * Advances the traversal of the image.
 */
ImageTraversal::Iterator & ImageTraversal::Iterator::operator++() {
  /** @todo [Part 1] */
  //if(!traversal->empty()){
    Point current_t = traversal->pop();
  unsigned curx = current_t.x;
    unsigned cury = current_t.y;
    //std::cout<< current_t << "Yeah" << std::endl;
    visit[curx][cury] = false;
    
    Point above, right, below, left;
    above = Point(curx, cury - 1); 
    right = Point(curx + 1, cury);
    below = Point(curx, cury + 1);
    left = Point(curx - 1, cury);
    
    
    if(visitFlag(right) == true){ traversal->add(right); }
    if(visitFlag(below) == true){ traversal->add(below); }
    if(visitFlag(left) == true){ traversal->add(left); }
    if(visitFlag(above) == true){ traversal->add(above); }
    
    while(!traversal->empty() && !(visit[traversal->peek().x][traversal->peek().y])){
      traversal->pop();
    }
  if(traversal->empty()){
    traversal = NULL;
    return *this;
  }
  startpoint = traversal->peek();
  return *this;
}

/**
 * Iterator accessor opreator.
 *
 * Accesses the current Point in the ImageTraversal.
 */
Point ImageTraversal::Iterator::operator*() {
  /** @todo [Part 1] */
  return startpoint;
}

/**
 * Iterator inequality operator.
 *
 * Determines if two iterators are not equal.
 */
bool ImageTraversal::Iterator::operator!=(const ImageTraversal::Iterator &other) {
  /** @todo [Part 1] */
  //Taken from lab_trees
  bool thisEmpty = false;
  bool otherEmpty = false;
  
  if(traversal == NULL){
    thisEmpty = true;
  }
  if(other.traversal == NULL){
    otherEmpty = true;
  }
  if(!thisEmpty){
    thisEmpty = traversal->empty();
  }
  if(!otherEmpty){
    otherEmpty = other.traversal->empty();
  }
  if(thisEmpty && otherEmpty){ //If both are empty,then both traversals are equal
    return false;
  }
  else if(!thisEmpty && !otherEmpty){ //If both are not empty, we compare the two traversals to see if they're equal
    return traversal != other.traversal;
  }
  else{
    return true; //Any other case means that the traversals are not equal
  }
}

//A helper to check if we've been to a square before
bool ImageTraversal::Iterator::visitFlag(Point point) {
  if(point.x >= png_.width() || point.y >= png_.height() || 0 > point.x || 0 > point.y){
    return false;
  }
  cs225::HSLAPixel& startWanted = png_.getPixel(start_.x, start_.y);
  cs225::HSLAPixel& wanted = png_.getPixel(point.x, point.y);
  if(calculateDelta(startWanted, wanted) >= tolerance_){
    return false;
  }
  return true;
}

