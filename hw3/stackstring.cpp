//
//  stackstring.cpp
//  hw2q7
//
//  Created by WangBingtang on 9/21/16.
//  Copyright © 2016 USC. All rights reserved.
//
#include "stackstring.h"

StackString::StackString(){
    
}

StackString::~StackString(){
    
}

bool StackString::empty() const{
    return (list.empty());
}

void StackString::push(const std::string &val){
    list.insert(list.size(), val);
}

std::string const & StackString::top() const{
    return list.get(list.size()-1);
}

void StackString::pop(){
    list.remove(list.size()-1);
}




