//
//  Skyscraper.cpp
//  hw7
//
//  Created by WangBingtang on 11/19/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include "Skyscraper.h"
#include <climits>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;


/*
 ---------------Start the implementation of Skyscraper class--------------------
 */
Skyscraper::Skyscraper(){
    std::pair<long long, string> mostLeft(1, "white");
    skyscraper.insert(mostLeft);
    std::pair<long long, string> mostRight(LLONG_MAX, "white");
    skyscraper.insert(mostRight);
}

void Skyscraper::print(){
    skyscraper.print();
}

void Skyscraper::insert(const std::pair<long long, std::string> node){
    skyscraper.insert(node);
    // more to go
    
}

std::string Skyscraper::findColor(long long floor){
	AVLTree<long long, std::string>::iterator single_temp = single_floor.find(floor);
	if (single_temp != NULL)
	{
		return single_temp->second;
	}

	AVLTree<long long, std::string>::iterator temp = skyscraper.find(floor);
	if (temp != NULL)
	{
		return temp->second;
	
	}

    AVLTree<long long, std::string>::iterator it = skyscraper.begin();
    
    while (it != skyscraper.end()) {
        AVLTree<long long, std::string>::iterator temp = it;
        ++it;
        if (it->first >= floor) {
            return temp->second;
        }
    }
    return "";
}


// find the color of max small floor
string Skyscraper::maxSmallColor(long long floor){
    string reval =  findColor(floor);
    return reval;
}

// clear the overlapping node
void Skyscraper::clearOverlap(long long lower_floor, long long upper_floor){
    vector<long long> overlap_floor;
    vector<long long> single_overlap;

    AVLTree<long long, std::string>::iterator it = skyscraper.begin();
    while (it != skyscraper.end()) {
        if (it->first >= upper_floor) {
            break;
        }
        else if (it->first <= lower_floor) {
            ++it;
        }
        else{
            overlap_floor.push_back(it->first);
            ++it;
        }
    }
    
    for (int i = 0; i < overlap_floor.size(); i++) {
        skyscraper.remove(overlap_floor[i]);
    }

    it = single_floor.begin();
    while (it != single_floor.end()){
    	if (it->first >= upper_floor) {
            break;
        }
        else if (it->first <= lower_floor) {
            ++it;
        }
        else{
            single_overlap.push_back(it->first);
            ++it;
        }
    }

    for (int i = 0; i < single_overlap.size(); i++) {
        single_floor.remove(single_overlap[i]);
    }
}

void Skyscraper::insertSingleFloor(const std::pair<long long, std::string> node){
	single_floor.insert(node);
}