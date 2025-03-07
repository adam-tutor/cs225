/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;
/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    string words;
    ifstream wordsfromfile(filename);
    if(wordsfromfile.is_open()){
        while(getline(wordsfromfile, words)){
            string line = words;
            sort(line.begin(), line.end());
            dict[line].push_back(words);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for(unsigned i = 0; i < words.size(); i++){
        string line = words[i];
        sort(line.begin(), line.end());
        dict[line].push_back(words[i]);
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    string line = word;
    sort(line.begin(), line.end());
    if(dict.find(line) == dict.end()){
        return vector<string>();
    }
    if(dict.at(line).size() == 1){
        return vector<string>();
    }
    return dict.at(line);
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> answer;
    for(auto i = dict.begin(); i != dict.end(); i++){
        if(!((i->second).size() < 2)){
            answer.push_back(i->second);
        }
    }
    return answer;
}
