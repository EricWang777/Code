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
#include <stdio.h>
#include <string>
#include "Dictionary.h"

using namespace std;

Dictionary::Dictionary (string dictionary_file_name)
{
    ifstream dictFile (dictionary_file_name.c_str());
    string word;
    _prefix.insert("");
    
    if (dictFile.is_open())
    {
        while (getline (dictFile, word))
        {
            // What do you want to do with the word?
            _dictionary.insert(word);
            string prefix = "";
            for (int i = 0; i < word.length(); i++) {
                prefix += string(1,word[i]);
                _prefix.insert(prefix);
            }
        }
        dictFile.close ();
        //cout << _prefix.size() << endl;
    }
    else throw invalid_argument("Cannot open file: " + dictionary_file_name);
}

// using binary search
bool Dictionary::search(string target){
    transform(target.begin(), target.end(), target.begin(), ::tolower);
    if (_dictionary.find(target)!=_dictionary.end()) return true;
    else return false;
}


// find the prefix in the _prefix
bool Dictionary::searchPrefix(string target){
    transform(target.begin(), target.end(), target.begin(), ::tolower);
    if (_prefix.find(target) != _prefix.end()) {
        return true;
    }
    else return false;
}


