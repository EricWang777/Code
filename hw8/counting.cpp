//
//  main.cpp
//  Hashtable
//
//  Created by WangBingtang on 11/30/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include "Hashtable.h"

#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <stdexcept>

using namespace std;

string wordGenerator(){
    string reval = "";
    int length = rand()%28+1;
    for (int i = 0; i < length; i++){
        char temp = 'a' + rand()%26;
        reval += temp;
    }
    return reval;
}

vector<string> readWord(char* fileName){
    vector<string> reVal;
    string line;
    
    ifstream in (fileName);
    if (in.fail()){
        cerr << "No such file\n";
        throw invalid_argument("Cannot open file");
    }
    
    while (getline(in, line)) {
        if (!line.empty())
        {
            stringstream ss(line);
            string temp_word;
            while (ss >> temp_word){
                // clear all non letters
                for (size_t i = 0; i < temp_word.size(); ++i)
                {
                    if (!isalpha(temp_word[i]))
                    {
                        temp_word.erase(temp_word.begin()+i);
                        i--;
                    }
                }
                // change the temp_word to lower case
                transform(temp_word.begin(), temp_word.end(), temp_word.begin(), ::tolower);
                reVal.push_back(temp_word);
            }
        }
        
    }
    return reVal;
}



int main(int argc, char* argv[]){
    if (argc != 6)
    {
        cout << "Usage: ./counting [input] [output] x d r\n";
        return 0;
    }

    ofstream output(argv[2]);
    int x = atoi(argv[3]); // 0, 1, 2 probing method
    int d = atoi(argv[4]); // 0, 1, debug
    int r = atoi(argv[5]); // repeat the program
    vector<string> my_string = readWord(argv[1]);
    cout << my_string.size() << endl;
    

    
    
    clock_t start;
    double duration;
    
    
    
    /* Your algorithm here */
    int repeat = r;
    Hashtable* hash_table;
    start = clock();


    while(1)
    {
        hash_table = new Hashtable(d, x);
    
        for (size_t i = 0; i < my_string.size(); ++i)
        {
            hash_table->add(my_string[i]);
        }
        r--;

        if (r == 0)
        {
            break;
        }
        delete hash_table;
    }
    

    
    
    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;
    
    cout << duration/repeat << endl;

    hash_table->reportAll(output);
    
    
    return 0;
}
