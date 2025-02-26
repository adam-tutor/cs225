/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 */
std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  if (text.is_open()) {
    strStream << text.rdbuf();
  }
  return strStream.str();
}

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
  std::vector<std::string> data;
  std::string file = file_to_string(filename);
  std::vector<std::vector<std::string>> v2dvector;
  int size = SplitString(file, '\n', data);
  for(int i = 0; i < size; i++){
    std::vector<std::string> store;
    int size2 = SplitString(data[i], ',', store);
    for(int j = 0; j < size2; j++){
      store[j] = Trim(store[j]);
    }
    v2dvector.push_back(store);
  }
  return v2dvector;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(V2D & cv, V2D & student){
    // YOUR CODE HERE
  std::vector<std::vector<std::string>> ans;
  std::unordered_map<std::string, std::vector<std::string>> map_cv;
  std::unordered_map<std::string, std::vector<std::string>> map;
  std::vector<std::string> temp;
  std::string front;
  unsigned i = 0;
  while(i < cv.size()){
    temp = cv.at(i); //Gets our value from the string at i in cv
    front = temp.front();
    temp.erase(temp.begin());
    map_cv.insert(std::pair(front, temp)); //creates an unordered map with pairs for cv values
    i++;
  }
  i = 0;
  while(i < student.size()){
    temp = student.at(i); //Gets our value from the string at i in students
    front = temp.front();
    temp.erase(temp.begin());
    map.insert(std::pair(front, temp)); //creates an unordered map with pairs for student values
    i++;
  }
  i = 0;
  while(i < cv.size()){ //This is where the two maps are then compared to see if their values agree. If they do not, then they will not get pushed into the final vector
    std::vector<std::string> temp2;
    bool flag = false; //Will be set to true if the value we end up pushing to the temp vector is in agreeance
    for(unsigned j = 0; j < (map_cv.find(cv[i][0]))->second.size(); j++){
      if(map.find(((map_cv.find(cv[i][0]))->second)[j]) != map.end()){ //Makes sure that we haven't reached the end yet
        for(unsigned k = 0; k < map.find(((map_cv.find(cv[i][0]))->second)[j])->second.size(); k++){ //While it looks like a lot, it's just finding values iterated over the cv_map
          if((map_cv.find(cv[i][0]))->first == (map.find(((map_cv.find(cv[i][0]))->second)[j])->second)[k]){ //We found an agreeing input
            if(temp2.empty()){
              temp2.push_back((map_cv.find(cv[i][0]))->first); //Pushes the first value from cv to start, rest of the values will be compared to student map
            }
            temp2.push_back(map.find(((map_cv.find(cv[i][0]))->second)[j])->first);
            flag = true;
            break;
          }
        }
      }
    }
    if(flag == true){
      ans.push_back(temp2);
    }
    i++;
  }
  return ans;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(V2D courses, std::vector<std::string> timeslots){
  std::vector<std::vector<bool>> Matrix;
  std::map<std::string, bool> map_edges;
  std::vector<int> _schedule;
  bool flag = false;
  int color_bound = 0;
  std::vector<std::vector<std::string>> ans;

  for(unsigned i = 0; i < courses.size(); i++){ //Create a matrix with initialized values of the size of the course vector and false. These are just base values
    std::vector<bool> v_push((int)courses.size(), flag);
    Matrix.push_back(v_push);
    for(unsigned j = 1; j < courses[i].size(); j++){
      std::pair<std::string, bool>position(courses[i][0] + courses[i][j], true); //In the same loop we can then also construct an edges map using the values in the course vector
      map_edges.insert(position);
    }
  }
  for(unsigned i = 0; i < courses.size(); i++){
    for(unsigned j = 1; j < courses[i].size(); j++){
      for(unsigned k = 0; k < courses.size(); k++){
        if(map_edges.find(courses[k][0] + courses[i][j]) != map_edges.end()){ //If we haven't reached the end, then we should keep overwriting matrix positions
          Matrix[k][i] = 1;
          Matrix[i][k] = 1;
        }
      }
    }
  }
  std::vector<int> color_checker(Matrix.size(), -1); //check from here
  for(unsigned i = 0; i < Matrix.size(); i++){
    color_checker[i] = 0;
    color_bound = 0; //This is the upper bound, or our max color value
    for(unsigned j = 0; j < Matrix.size(); j++){
      if(i != j){
        std::vector<bool> blocked(Matrix.size(), 0);
        unsigned k = 0;
        while(k != Matrix.size()){
          if(Matrix[j][k] == 1 && color_checker[k] != -1){
            blocked[color_checker[k]] = 1;
          }
          k++;
        } //to here
        unsigned comp_color;
        for(comp_color = 0; comp_color < Matrix.size(); comp_color++){
          if(blocked[comp_color] == 0){
            break;
          }
        }
        color_checker[j] = comp_color;
      }
    }
    for(unsigned i = 0; i < color_checker.size(); i++){
      if(color_checker[i] > color_bound){
        color_bound = color_checker[i];
      }
    }
    if(color_bound >= (int)timeslots.size()){ //Checks if we went past the allowed size of the schedule
      color_bound = 0;
      flag = false;
    }
    else{
      _schedule = color_checker; //If we didn't then we should set up that position on the schedule
      flag = true;
      break;
    }
  }
  if(flag == true){
    //Finally, this last 'if' statement and subsequent for loops constructs the schedule
    for(int i = 0; i < color_bound + 1; i++){ //Could've used iterator and avoided the +1, but I'm not good with them
      std::vector<std::string> temp2;
      temp2.push_back(timeslots[i]); //There should be a slot for every time slot, even if it isn't used
      for(unsigned j = 0; j < _schedule.size(); j++){
        if(_schedule[j] == i){ //Checks if there should be a course during that time
          temp2.push_back(courses[j][0]); //Pushes courses into correct spots
        }
      }
      ans.push_back(temp2); //Pushes that timeslot + courses into our final schedule
    }
    return ans;
  }
  else{
    return V2D({std::vector<std::string>({"-1"})}); //If the input was invalid, then just return an invalid vector
  }
  return V2D();
}
