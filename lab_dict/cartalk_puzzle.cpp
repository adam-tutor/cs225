/**
 * @file cartalk_puzzle.cpp
 * Holds the function which solves a CarTalk puzzler.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include <fstream>

#include "cartalk_puzzle.h"

using namespace std;

/**
 * Solves the CarTalk puzzler described here:
 * http://www.cartalk.com/content/wordplay-anyone.
 * @return A vector of (string, string, string) tuples
 * Returns an empty vector if no solutions are found.
 * @param d The PronounceDict to be used to solve the puzzle.
 * @param word_list_fname The filename of the word list to be used.
 */
vector<std::tuple<std::string, std::string, std::string>> cartalk_puzzle(PronounceDict d,
                                    const string& word_list_fname)
{
    vector<std::tuple<std::string, std::string, std::string>> ret;

    vector<std::string> words;
    string line;
    string word1, backup, word2;
    ifstream thefile(word_list_fname);
    if(thefile.is_open()){
        while(getline(thefile, line)){
            word1 = line.substr(1);
            backup = line.substr(0,1);
            if(line.length() > 2){
                word2 = line[0] + line.substr(2);
            }
            else{
                word2 = backup;
            }
            if(d.homophones(line, word1) && d.homophones(line, word2)){
                ret.push_back(make_tuple(line, word1, word2));
            }
        }     
    }
    thefile.close();
    return ret;
}
