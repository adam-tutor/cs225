/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>
#include "maptiles.h"
//#include "cs225/RGB_HSL.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    MosaicCanvas* canvas = new MosaicCanvas(theSource.getRows(), theSource.getColumns());
    vector<Point<3>> pixel_points;
    for(unsigned i = 0; i < theTiles.size(); i++){
      pixel_points.push_back(convertToXYZ(theTiles[i].getAverageColor()));
    }
    KDTree<3> mosaictree(pixel_points);
    TileImage* temp;
    for(int i = 0; i < theSource.getRows(); i++){
      for(int j = 0; j < theSource.getColumns(); j++){
        Point<3> color = mosaictree.findNearestNeighbor(convertToXYZ(theSource.getRegionColor(i,j)));
        int index = 0;
        for(int k = 0; pixel_points[k] != color; k++){
          index++;
        }
        temp = &theTiles[index];
        canvas->setTile(i,j,temp);
      }
    }
    

    return canvas;
}

