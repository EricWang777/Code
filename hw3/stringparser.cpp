//
//  main.cpp
//  hw2q7
//
//  Created by WangBingtang on 9/8/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include "stackstring.h"
#include <fstream>
using namespace std;

// remove end <
bool removeEnd (string& s){
    if (!s.empty()) {
        s.erase(s.end()-1);
        return true;
    }
    return false;
    
}

// remove head >
bool removeHead (string& s){
    if (!s.empty()) {
        s.erase(s.begin());
        return true;
    }
    return false;
}

void changeTab (string& s){
    for (unsigned int i = 0; i < s.size(); i++) {
        if (s[i] == '\t') {
            s[i] = ' ';
        }
    }
}


// check validity of the input
// false if not valid, true if yes.
bool validity (string input){
    int openPara = 0; // "("
    int closePara = 0; // ")"

    // if no + - < > in
//    if (input.find("+") == string::npos && input.find("-") == string::npos
//        && input.find("<") == string::npos && input.find(">") == string::npos) {
//        if (input.find("(") != string::npos && input.find(")") != string::npos) {
//            return false;
//        }
//        
//    }
    
 
    
    
    for (string::iterator it = input.begin(); it != input.end(); ++it){
        if (*it == '<' || *it == '>' || *it == ')' || *it == '(') {
            if (*(it-1) >= 'a' && *(it-1) <= 'z' &&
                *(it+1) >= 'a' && *(it+1) <= 'z') {
                return false;
            }
        }
    
    }
    
    for (unsigned long i = 0; i < input.size(); i++) {
        if (input[i] == ')') {
            unsigned long temp = i-1;
            
            while (temp == ' ') {
                temp -= 1;
            }
            if (temp == '<' || temp == '>') {
                return false;
            }
        }
        
        if (i == input.size()-1) {
            if (input[i] == '<' || input[i] == '>') {
                return false;
            }
        }
        
        // check continuous + "+ +"
        if (input[i] == '+') {
            unsigned long index = i+1;
            while (input[index] == ' ') {
                index+=1;
            }
            if (input[index] == '+') {
                return false;
            }
        }
    }
    
    
    
    for (unsigned long i = 0; i < input.size(); ++i) {
        if (input[i] == '(') {
            openPara ++;
        }
        else if (input[i] == ')'){
            closePara ++;
        }
        
    }
    
    if (closePara != openPara) {
        return false;
    }
    
    
    
    

    return true;
}




// Overloading - for s1-s2. If s2 doesn't match characters in s1,
// do nothing, return s1.
string operator - (const string& s1, const string& s2){
    string s = s1;
    unsigned long found = s.find(s2);
    
    
    if (found != string::npos) {
        for (unsigned int i = 0;i < s2.size() ; i++) {
            s.erase(s.begin()+found);
        }
    }
    //else cout << s1 << " fail to - " << s2 << endl;
    
    return s;
}

// Check the spaces between strings
bool checkSpace(string s){
    bool check = false;
    
    for (unsigned long i = 1; i < s.size()-1; i++){
        if (s[i-1] >= 'a' && s[i-1] <= 'z' && s[i] == ' ') {
            check = true;
        }
        unsigned long j = i+1;
        while (check == true && j < s.size()) {
            if (s[j] > 'a' && s[j] < 'z') {
                return false;
            }
            if (s[j] == ' ') {
                check = true;
                break;
            }
            else{
                if (s[j] != '<' && s[j] != '>') {
                    check = false;
                }
                
            }
            j++;
        }
        
        
    }
    return true;
}


// Operating lines of sentences
string opLine(StackString stack, string sentences){
    
    changeTab(sentences);
    // check the spaces between strings
    if (!checkSpace(sentences)){
        return "Malformed";
    }
    
    string optr = "";
    string s1, s2;
    string reval = "";
    bool switchString = false;
    
    
    if (!validity(sentences)) {
        return "Malformed";
    }
    
    for (string::iterator it = sentences.begin(); // go through each character in sentences
         it != sentences.end();
         ++it){
        if (*it != ')') { // when not seeing close para, pushing on stack
            // character by character
            if (*it < 'a' || *it > 'z'){
                if (*it != '+' && *it != '-' && *it != '<' && *it != '>' &&
                    *it != '(' && *it != ')' && *it != ' '){
                    // check input format
                    //throw invalid_argument("Invalid input");
                    return "Malformed";
                }
            }
            if (*it != ' ') {
                stack.push(string(1, *it));
            }
        }
        else if (*it == ')'){ // when seeing close para, start to pop the top
            if (stack.empty()) {
                return "malformed";
            }
            // and do operation
           
            while (stack.top() != "(") {
                // do operation until seeing the open para
                if (stack.top() == "+" || stack.top() == "-"){
                    
                    if (switchString == true){
                        // reach the second same operator in
                        // check wheter mixing operator
                        if (stack.top() != optr ){
                            //throw invalid_argument("Mixing operator");
                            return "Malformed";
                        }
                        if (stack.top() == optr && optr == "-") {
                            return "Malformed";
                        }
                        
                        string temp = "";
                        if (optr == "+"){
                            temp = s1+s2;
                            
                        }
                        else if (optr == "-"){
                            temp = s1-s2;
                            
                        }
                        stack.push(temp);
                        s1 = s2 = "";
                        
                        switchString = false;
                    }
                    else {
                        // the first time seeing operator
                        optr = stack.top();
                        switchString = true;
                        stack.pop();
                    }
                }
                else if (switchString == false){
                    // reading the right-hand side of the operator into s2
                    if (stack.top() == "<"){
                        // if see the remove end notation, remove the end of s2
                        stack.pop(); // pop the "<"
                        if (stack.empty()){ // nothing after <
                            //throw invalid_argument("Malformed");
                            return "Malformed";
                        }
                        if (*stack.top().c_str() > 'a' && *stack.top().c_str() < 'z'){
                            // < in the middle of the string
                            //throw invalid_argument("< is in the middle of the string");
                            return "Malformed";
                        }
                        // after everything is fine
                        removeEnd(s2);
                        
                    }
                    else if (stack.top() == ">"){
                        stack.pop();
                        if (stack.empty()){
                            //throw invalid_argument("Malformed");
                            return "Malformed";
                        }
                        if (*stack.top().c_str() >= 'a' && *stack.top().c_str() <= 'z'){
                            // < in the middle of the string
                            //throw invalid_argument("> is in the middle of the string");
                            return "Malformed";
                        }
                        // after everything is fine
                        removeHead(s2);
                        
                    }
                    else {
                        // normal case
                        s2 = stack.top() + s2;
                        stack.pop(); // immediately pop from stack
                        
                    }
                    
                }
                else if (switchString == true){
                    // reading the lefthand side of the operator into s1
                    if (stack.top() == "<"){
                        // if see the remove end notation, remove the end of s2
                        stack.pop(); // pop the "<"
                        if (stack.empty()){ // nothing after <
                            //throw invalid_argument("Malformed");
                            return "Malformed";
                        }
                        if (*stack.top().c_str() > 'a' && *stack.top().c_str() < 'z'){
                            // < in the middle of the string
                            //throw invalid_argument("< is in the middle of the string");
                            return "Malformed";
                        }
                        // after everything is fine
                        removeEnd(s1);
                        
                    }
                    else if (stack.top() == ">"){
                        stack.pop();
                        if (stack.empty()){
                            //throw invalid_argument("Malformed");
                            return "Malformed";
                        }
                        if (*stack.top().c_str() > 'a' && *stack.top().c_str() < 'z'){
                            // < in the middle of the string
                            //throw invalid_argument("> is in the middle of the string");
                            return "Malformed";
                        }
                        // after everything is fine
                        removeHead(s1);
                        
                    }
                    else {
                        // normal case
                        s1 = stack.top() + s1;
                        stack.pop(); // immediately pop from stack
                    }
                    
                }
                
            }
            // finish collecting data from one pair of para
            // check the case of nothing + string
            if (s1.empty() || s2.empty()){
                if (optr != ""){
                    //throw invalid_argument("Malformed");
                    return "Malformed";
                }
            }
            
            
            
            // doing operation of s1 and s2
            string s = "";
            if (optr == "+"){
                s = s1+s2;
            }
            else if (optr == "-"){
                s = s1-s2;
            }
            else if (optr == ""){
                s = s1+s2;
            }
            s1 = s2 = ""; // reset s1 and s2
            optr = ""; // reset operator
            switchString = false; // reset switchString
            stack.pop(); // pop the ( notation
            stack.push(s);
        }
    }
    
    // check validity of the stack
    while (!stack.empty()) {
        if (stack.top() == ">") {
            // if find remove start notation
            stack.pop(); // pop the notation
            removeHead(reval);
            stack.push(reval);
            reval = "";
        }
        else if (stack.top() == "<"){
            // if find remove end notation
            stack.pop(); // pop the notation
            removeEnd(reval);
            stack.push(reval);
            reval = "";
        }
        else {
            
            reval = stack.top() + reval;
            stack.pop();
        }
    }
    
    // final check of the output
    if (reval.find("+") != string::npos || reval.find("-") != string::npos
        || reval.find("<") != string::npos || reval.find(">") != string::npos
        || reval.find("(") != string::npos || reval.find(")") != string::npos) {
        //throw invalid_argument ("Malformed");
        return "Malformed";
    }
    
    return reval;
}


int main(int argc, const char * argv[]) {
    // Variable
    StackString stack;
    
    
    ifstream file(argv[1]);
    ofstream ofile(argv[2]);
    
    if (!file.fail()){
        string line;
        while (getline(file, line)) {
            if (line.empty()) {
                ofile << endl;
            }
            else{
                
                ofile << opLine(stack, line) << endl;
                while (!stack.empty()) {
                    stack.pop();
                }
            }
        }
    }
    else {
        cout << "Cannot find the file";
    }
    
    
    
    
    
    
    
    
    return 0;
}
