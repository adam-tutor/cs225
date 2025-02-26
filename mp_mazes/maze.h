#pragma once
#include <vector>
#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include "dsets.h"


using namespace std;
using namespace cs225;

class SquareMaze{
public:
    SquareMaze();
    void makeMaze(int width, int height);
    void setWall(int x, int y, int dir, bool exists);
    bool canTravel(int x, int y, int dir) const;
    vector<int> solveMaze();
    PNG* drawMaze() const;
    PNG* drawMazeWithSolution();
    
private:
    vector<bool> rightwards;
    vector<bool> downwards;
    DisjointSets sets;
    int w;
    int h;
    int path;
};