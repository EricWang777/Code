/*
 * Dictionary.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include <string>
#include <vector>
#include <set>

class Dictionary {
public:
    Dictionary (std::string dictionary_file_name);
    
    // what else will this need?
    
    // serach a word
    bool search (std::string target); // use interpoliation serach
    
    
    
    bool searchPrefix(std::string target);
    
    

private:
    std::set<std::string> _dictionary;
    std::set<std::string> _prefix;
    
    
};


#endif /* DICTIONARY_H_ */