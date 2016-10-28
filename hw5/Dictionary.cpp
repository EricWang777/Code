/*
 * Dictionary.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary (string dictionary_file_name)
{
    ifstream dictFile (dictionary_file_name.c_str());
    string word;
    
    if (dictFile.is_open())
    {
        while (getline (dictFile, word))
        {
            //word.erase(word.length()-1); // remove end-of-line character
            
            // What do you want to do with the word?
            _dictionary.insert(word);
            
        }
        dictFile.close();
        
    }
    else throw invalid_argument("Cannot open file: " + dictionary_file_name);
}

// using binary search
bool Dictionary::search(string target){
    transform(target.begin(), target.end(), target.begin(), ::tolower);
    //if (_dictionary.find(target)!=_dictionary.end()) return true;
    //else return false;
    return true;
}




