//
//  Skyscraper.hpp
//  hw7
//
//  Created by WangBingtang on 11/19/16.
//  Copyright © 2016 USC. All rights reserved.
//

#ifndef Skyscraper_hpp
#define Skyscraper_hpp
#include "avlbst.h"
#include <iostream>



class Skyscraper{
public:
    Skyscraper();
    void print();
    void insert(const std::pair<long long, std::string> node);
    void insertSingleFloor(const std::pair<long long, std::string> node);
    
    std::string findColor(long long floor);
    // find the color of max small floor
    std::string maxSmallColor(long long floor);
    
    
    
    // clear the overlapping node
    void clearOverlap(long long lower_floor, long long upper_floor);
    
    
private:
    AVLTree<long long, std::string> skyscraper;
    AVLTree<long long, std::string> single_floor;
    
    
    
    
};


#endif /* Skyscraper_hpp */
