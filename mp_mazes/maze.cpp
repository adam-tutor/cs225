/* Your code here! */
#include "maze.h"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;
using namespace cs225;

SquareMaze::SquareMaze(){
    w = 0; //clears the maze
    h = 0;
}

void SquareMaze::makeMaze(int width, int height){
    w = width;
    h = height;
    int dimensions = width * height;

    sets.addelements(dimensions);  

    for(int i = 0; i < dimensions; i++){
        rightwards.push_back(true);  
        downwards.push_back(true);
    }
    //I decided that using two vectors, rightwards and downwards, would be easier than using a two dimensional vector since we would have to keep splitting it to look for x and y values

    while(sets.size(0) != dimensions){
        int randx = rand() % w;
        int randy = rand() % h;
        int distance = w * randy + randx;
        if(rand() % 2 == 0){ //outputs 0 or 1, 0 being right and 1 being down
            if(randy != h - 1 && sets.find(distance) != sets.find(distance + w)){
                setWall(randx, randy, 1, false);
                sets.setunion(distance, distance + w);
            }
        }
        else{
            if(randx != w - 1 && sets.find(distance) != sets.find(distance + 1)){
                setWall(randx, randy, 0, false);
                sets.setunion(distance, distance + 1);
            }
        }
    }
}

void SquareMaze::setWall(int x, int y, int dir, bool exists){
    int distance = w * y + x;
    if(dir == 0){
        if(x != w - 1){
            rightwards[distance] = exists;
        }
    }
    else if(dir == 1){
        if(y != h - 1){
            downwards[distance] = exists;
        }
    }
    return;
}

bool SquareMaze::canTravel(int x, int y, int dir) const{
    //0 = right, 1 = down, 2 = left, 3 = up
    int distance = w * y + x;
    if(dir == 0){
        if(x != w - 1){
            return rightwards[distance] == false;
        }
    }
    else if(dir == 1){
        if(y != h - 1){
            return downwards[distance] == false;
        }
    }
    else if(dir == 2){
        if(x != 0){
            return (rightwards[distance - 1] == false); 
        }
    }
    else if(dir == 3){
        if(y != 0){
            return (downwards[distance - w] == false); 
        }
    }
    return false;
}

vector<int> SquareMaze::solveMaze(){
    queue<int> q;
    q.push(0); //pushes the initial position
    vector<int> length(w * h, -1); //the length of the path from the beginning
    vector<int> result; 
    vector<int> path_(w * h, -1); //takes into account every direction step we take
    vector<int> visited(w * h, -1); //the path we take to get to the end
    
    visited.push_back(0);
    length.push_back(0); //we mark the beginning as visited and then...

    for(int i = 1; i<w*h; i++){ //this is to mark the rest of the maze as not visited
        length.push_back(0);
        visited.push_back(-1);
    }

    int current;
    while(!q.empty()){
        current = q.front();
        //the if statements here determine if we are moving right, down, left, or up
        if(canTravel(current % w, current / w, 0) && visited[current + 1] == -1){
            visited[current + 1] = current; //updates that we've visited that position, and moves to our current position
            length[current + 1] = length[current] + 1; //adds 1 to the length of our path
            path_[current + 1] = 0;
            q.push(current + 1); //we push that position to the queue
        }
        if(canTravel(current % w, current / w, 1) && visited[current + w] == -1){
            visited[current + w] = current;
            length[current + w] = length[current] + 1;
            path_[current + w] = 1;
            q.push(current + w);
        }
        if(canTravel(current % w, current / w, 2) && visited[current - 1] == -1){
            visited[current - 1] = current;
            length[current - 1] = length[current] + 1;
            path_[current - 1] = 2;
            q.push(current - 1);
        }
        if(canTravel(current % w, current / w, 3) && visited[current - w] == -1){
            visited[current - w] = current;
            length[current - w] = length[current] + 1;
            path_[current - w] = 3;
            q.push(current - w);
        }
        q.pop();
    }
    path = w * (h - 1);
    for(int j = 0; j < w; j++){
        if(length[w * (h - 1) + j] > length[path]){
            path = w * (h - 1) + j;
        }
    }
    
    current = path; //using current instead of another variable in the above for loop puts our function way out of bounds, so i had to use a dummy variable
    while(current>0){
        result.insert(result.begin(), path_[current]); //here we add the directions we accumulated in the path_ vector and put them into our result vector
        current = visited[current];
    }
    return result;
}

PNG* SquareMaze::drawMaze() const{
    PNG* image = new PNG(w * 10 + 1, h * 10 + 1); //dimensions that we were told in the doxygen

    for(unsigned i = 10; i < image->width(); i++){
        HSLAPixel& pixel = image->getPixel(i, 0);
        pixel.l = 0; //sets the current pixel to black
        pixel.s = 0;
        pixel.h = 0;
    }

    for(unsigned i = 0; i < image->height(); i++){
        HSLAPixel& pixel = image->getPixel(0, i);
        pixel.l = 0;
        pixel.s = 0;
        pixel.h = 0;
    }
    
    for(int x = 0; x < w; x++){
        for(int y = 0; y < h; y++){
            int distance = y * w + x;
            if(rightwards[distance]){
                for(int k = 0; k<=10; k++){
                    HSLAPixel& pixel = image->getPixel((x+1) * 10, y * 10 + k);
                    pixel.l = 0; //now we go through the rest of the image and set everything to black
                    pixel.s = 0;
                    pixel.h = 0;
                }
            }
            if(downwards[distance]){
                for(int k = 0; k<=10; k++){
                    HSLAPixel& pixel = image->getPixel(x * 10 + k, (y+1) * 10);
                    pixel.l = 0;
                    pixel.s = 0;
                    pixel.h = 0;
                }
            }
        }
    }
    return image;
}

PNG* SquareMaze::drawMazeWithSolution(){
    PNG* image = drawMaze();
    vector<int> result = solveMaze();
    int x = 5;
    int y = 5;
    int idx;
    HSLAPixel red (0,1,0.5,1); //hsla of red saved for easy access
    int endX = path % w; //this marks where the position of the exit is
    int endY = path / h;

    for(unsigned i = 0; i < result.size(); i++){
        idx = 0;
        if(result[i] == 0){
            while(idx < 10){
                image->getPixel(x + idx, y) = red;
                idx++;
            }
            x = x+idx;
        }
        else if(result[i] == 1){
            while(idx < 10){
                image->getPixel(x, y + idx) = red;
                idx++;
            }
            y = y+idx;
        }
        else if(result[i] == 2){
            while(idx < 10){
                image->getPixel(x - idx, y) = red;
                idx++;
            }
            x = x-idx;
        }
        else if(result[i] == 3){
            while(idx < 10){
                image->getPixel(x, y - idx) = red;
                idx++;
            }
            y = y-idx;
        }
    }

    image->getPixel(x, y) = red;
    
    for(int k = 1; k <= 9; k++){
        HSLAPixel& pixel = image->getPixel(endX * 10 + k, (endY + 1)*10);
        pixel.l = 1;
    }
    return image;
}