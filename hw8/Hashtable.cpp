//
//  main.cpp
//  Hashtable
//
//  Created by WangBingtang on 11/30/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include "Hashtable.h"
#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <cstdlib>
using namespace std;



// transfer the letter into int value, a = 0, z = 25
int letterToValue(char letter){
    if (letter == '0') {
        return 0;
    }
    int reval = letter - 'a';
    return reval;
}

long long sixLetterValue(string six_letter){
    long long reVal = 0;
    for (unsigned int i = 0; i < six_letter.length(); i++) {
        reVal += pow(26.0, double(5-i))*letterToValue(six_letter[i]);
    }
    return reVal;
}

// cut the string into string array of 6 letters, if shorter, add '0' in the front
vector<string> cutString(string entire_string){
    string temp = "";
    vector<string> reVal;
    
    for (int i = 0; i < 6; i++) {
        entire_string.insert(entire_string.begin(), '0');
    }
    
    int counter = 0;
    for (unsigned int i = 0; i < entire_string.length(); i++) {
        if (counter == 6) {
            counter = 0;
            reVal.insert(reVal.begin(), temp);
            temp = "";
        }
        temp = entire_string[entire_string.length()-1-i] + temp;
        counter ++;
        
    }
    return reVal;
}

// return a vector containing w1-5
vector<long long> w1w2w3w4w5(string s){
    vector<long long> reVal;
    vector<string> six_letter_string = cutString(s);
    for (unsigned int i = 0; i < six_letter_string.size(); i++) {
        reVal.push_back(sixLetterValue(six_letter_string[i]));
    }
    unsigned int size = reVal.size();
    if (size < 5) {
        for (unsigned int i = 0; i < 5-size; i++) {
            reVal.insert(reVal.begin(), 0);
        }
    }
    return reVal;
}

/*
 ------------------------Implementation of Hashtable-----------------------
 */

// Constructor
Hashtable::Hashtable(bool debug, unsigned int probing){
    for (int i = 0; i < 11; i++) {
        hash_array.push_back(make_pair("", 0));
    }
    this->debug = debug;
    this->probing = probing;
    this->num_items = 0;
    
    if (debug == true) {
        // create random r1-5
        r1 = rand()%1685759166;
        r2 = rand()%1685759166;
        r3 = rand()%1685759166;
        r4 = rand()%1685759166;
        r5 = rand()%1685759166;
    }
    
}

Hashtable::~Hashtable(){
    
}

// hash function
int Hashtable::hash(const std::string &k) const{
    vector<long long> w = w1w2w3w4w5(k);
    return (w[0]*r1 + w[1]*r2 + w[2]*r3 + w[3]*r4 + w[4]*r5)%hash_array.size();
}

// second hash function
long long Hashtable::secondHash(const std::string &k) const{
    long long p = 0;
    for (int i = 0; i < 27; i++) {
        if (second_hash_size[i+1] > hash_array.size() && second_hash_size[i] < hash_array.size() ) {
            p = second_hash_size[i];
        }
    }
    vector<long long> w = w1w2w3w4w5(k);
    return p - (w[0]+w[1]+w[2]+w[3]+w[4])%p;
}

// Returns the int associated with k, or 0 if k is not in the Hashtable.
int Hashtable::count(const std::string &k) const{
    int index = hash(k);
    // using linear probing
    if (probing == 0) {
        while (hash_array[index].first != k && hash_array[index].first != "") {
            index ++;
            index %= hash_array.size();
        }
        if (hash_array[index].first == "") {
            // k is not in the hash table
            return 0;
        }
        return hash_array[index].second;
    }
    // using quadradic probing
    else if (probing == 1){
        int i = 1;
        while (hash_array[index].first != k && hash_array[index].first != "") {
            index += pow(double(i), 2.0);
            index %= hash_array.size();
            i++;
        }
        if (hash_array[index].first == "") {
            // k is not in the hash table
            return 0;
        }
        return hash_array[index].second;
    }
    else if (probing == 2){
        int fail = 1;
        long long second_hash = secondHash(k);
        while (hash_array[index].first != k && hash_array[index].first != "") {
            index += fail*second_hash;
            index %= hash_array.size();
            fail++;
        }
        if (hash_array[index].first == "") {
            // k is not in the hash table
            return 0;
        }
        return hash_array[index].second;
    }
    return 0;
}

//  output, to the given stream, every (key,value) pair, in the order they appear in the hashtable; on each line, output the key, followed by a space, followed by the value, and then a newline.
void Hashtable::reportAll (ostream & out) const{
    for (unsigned int i = 0; i < hash_array.size(); i++) {
        if (hash_array[i].second != 0) {
            out << hash_array[i].first << " " << hash_array[i].second << endl;
        }
    }
}

// add function
/**
 * If the parameter k already exists as an element in the Hashtable, increment the
 * total number of entries. Otherwise create a new entry with a count of 1.
 */
void Hashtable::add(const std::string &k){
    int index = hash(k);
    
    // linear probing
    if (probing == 0) {
        // while the slot has already been taken
        while (hash_array[index].second != 0) {
            // there is a case that this slot is k
            if (hash_array[index].first == k) {
                // number of k increase by 1
                hash_array[index].second ++;
                return;
            }
            // stuff different from k
            index ++;
            index %= hash_array.size();
        }
        // now find an empty slot
        hash_array[index] = make_pair(k, 1);
        num_items++;
    }
    // quadradic probing
    else if (probing == 1){
        int i = 1;
        while (hash_array[index].second != 0) {
            if (hash_array[index].first == k) {
                // same stuff
                hash_array[index].second ++;
                return;
            }
            // different stuff
            index += pow(double(i), 2.0);
            index %= hash_array.size();
            i++;
        }
        // now find an empty slot
        hash_array[index] = make_pair(k, 1);
        num_items++;
    }
    // double hashing
    else if (probing == 2){
        int fail = 1;
        int second_hash = secondHash(k);
        while (hash_array[index].second != 0) {
            if (hash_array[index].first == k) {
                // same stuff
                hash_array[index].second ++;
                return;
            }
            index += fail*second_hash;
            index %= hash_array.size();
            fail++;
        }
        // now find an empty slot
        hash_array[index] = make_pair(k, 1);
        num_items++;

    }
    resize();
}

/**
* A helper function to resize and rehash the entries in the table when the load
* factor is >= 0.5. See the assignment description for the specific increments
* when increasing the size of the Hashtable as well as other implementation details.
*/
void Hashtable::resize(){
    // if load factor is less than 0.5, no need to resize
    if (loadFactor() < 0.5) {
        return;
    }
    
    // go through each value in the hash_array, store the item in a temp vector
    vector<pair<string, int> > temp;
    
    for (unsigned int i = 0; i < hash_array.size(); i++) {
        // if this slot is not an empty slot, push_back this item into temp
        if (hash_array[i].first != "") {
            temp.push_back(hash_array[i]);
        }
    }
    // now every item is in the temp array, and hash_array is now empty
    
    // try to find the next valid size from the resize_size array
    int curr_size_index = 0;
    for (int i = 0; i < 28; i++) {
        if (resize_size[i] == hash_array.size()) {
            curr_size_index = i;
        }
    }
    int next_size_index = curr_size_index+1;
    
    // reset the hash_array to size 0
    hash_array.clear();
    for (int i = 0; i < resize_size[next_size_index]; i++) {
        hash_array.push_back(make_pair("", 0));
    }
    
    // now the hash_array has size of resize_size[next_size_index] and every thing in it
    // is ("", 0)
    
    // then rehash everything in the temp and put it into the resized hash table
    for (unsigned int i = 0; i < temp.size(); i++) {
        for (int j = 0; j < temp[i].second; j++) {
            add(temp[i].first);
        }
    }
}

// find the loadFactor;
double Hashtable::loadFactor(){
    return double(num_items)/double(hash_array.size());
}