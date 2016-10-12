/*
 * Board.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Board.h"

using namespace std;

Board::Board (string board_file_name)
{
    ifstream boardFile (board_file_name.c_str());
    string row;
    
    _x = _y = _startx = _starty = 0; // to appease compiler
    if (!boardFile.is_open())
        throw invalid_argument("Cannot open file: " + board_file_name);
    getline (boardFile, row);
    stringstream s1 (row);
    s1 >> _x >> _y;
    getline (boardFile, row);
    stringstream s2 (row);
    s2 >> _startx >> _starty;
    _startx --; _starty --;  // coordinates from 0 in array
                             // start from (7,7)
    
    // Anything else you need to initialize?
    
    // two dimensional array of the board
    _board = new char*[_x]; // x rows
    for (int i = 0; i < _y; i++) {
        _board[i] = new char[_y]; // y columns
    }
    
    // same format as board but boolean check empty slot
    // true means empty, false means not
    _property = new square*[_x];
    for (int i = 0; i < _x; i++) {
        _property[i] = new square[_y];
    }
    
    
    
    
    
    for (int i = 0 ; i < _x; ++ i)
    {
        getline (boardFile, row);
        for (int j = 0; j < _y; ++ j)
        {
            // Fill in the following based on how you store the board.
            if (i == _starty && j == _startx) {
                _board[i][j] = '*';
                _property[i][j].empty = true;
                _property[i][j].wordMul = 2;
                _property[i][j].letterMul = 1;
            }
            else switch (row[j]) {
                case '.' :
                    _board[i][j] = '.';
                    _property[i][j].empty = true;
                    _property[i][j].wordMul = 1;
                    _property[i][j].letterMul = 1;
                    break;
                case '2' :
                    _board[i][j] = '2';
                    _property[i][j].empty = true;
                    _property[i][j].wordMul = 1;
                    _property[i][j].letterMul = 2;
                    break;
                case '3' :
                    _board[i][j] = '3';
                    _property[i][j].empty = true;
                    _property[i][j].wordMul = 1;
                    _property[i][j].letterMul = 3;
                    break;
                case 'd' :
                    _board[i][j] = 'd';
                    _property[i][j].empty = true;
                    _property[i][j].wordMul = 2;
                    _property[i][j].letterMul = 1;
                    break;
                case 't' :
                    _board[i][j] = 't';
                    _property[i][j].empty = true;
                    _property[i][j].wordMul = 3;
                    _property[i][j].letterMul = 1;
                    break;
                default:
                    string error = "Improper character in Board file: ";
                    throw invalid_argument(error + row[j]);
            }
            
        }
    }
    boardFile.close ();
}

// destructor
Board::~Board(){
    for (int i = 0;i < _y ; i++) {
        delete _board[i];
        delete _property[i];
    }
    delete _board;
    delete _property;
    _board = NULL;
    _property = NULL;
}

// check if the slot is empty
bool Board::emptySlot (int row, int col){
    if (row < 0 || col < 0) {
        cout << "out of bound" << endl;
        return false;
    }
    if (row > _x || col > _y) {
        cout << "out of bound" << endl;
        return false;
    }
    return _property[row][col].empty;
}




// print the Board
void Board::printBoard(){
    cout << "  ";
    for (int i = 0; i < _y; i++) {
        if (i < 10) {
            cout << " " << i+1 << "  ";
        }
        else{
            cout << i+1 << "  ";
        }
    }
    cout << endl;
    for (int row = 0; row < _x; row++) {
        if (row < 9) {
            cout << row+1 << "  ";
        }
        else{
            cout << row+1 << " ";
        }
        
        for (int col = 0; col < _y; col++) {
            if (_board[row][col] == '.') {
                cout << "... ";
            }
            else if (_board[row][col] == '2'){
                cout << "Lx2 ";
            }
            else if (_board[row][col] == '3'){
                cout << "Lx3 ";
            }
            else if (_board[row][col] == 't'){
                cout << "Wx3 ";
            }
            else if (_board[row][col] == 'd'){
                cout << "Wx2 ";
            }
            else if (_board[row][col] == '*'){
                cout << "*** ";
            }
            else{
                cout << " " << _board[row][col] << "  ";
            }
        }
        cout << endl;
    }
}

// modify the Board
void Board::modify(int row, int col, char letter){
    if (letter >= 'a') {
        letter -= 32;
    }
    _board[row][col] = letter;
    _property[row][col].empty = false;
}





// check Adjacent
bool Board::checkAdjacent(int row, int col){
    return !(empty_for_adjacent(row+1, col)&&
           empty_for_adjacent(row-1, col)&&
           empty_for_adjacent(row, col+1)&&
           empty_for_adjacent(row, col-1));
}

// check empty for adjancent
// regard the outofbound place as empty square
bool Board::empty_for_adjacent(int row, int col){
    if (row < 0 || col < 0 || row > _y || col > _x) {
        return true;
    }
    else return _property[row][col].empty;
}


// word_row const row
string Board::word_row(int row, int col, int &score, Dictionary &dict){
    string reval = "";
    while (col >= 0 && !emptySlot(row, col-1)) {
        col--;
    }
    // col now is the head of the word in this row
    int headCol = col;
    while (col < _x && !emptySlot(row, col)) {
        reval += _board[row][col];

        col++;
    }
    
    
    
    if (reval.length() > 1) {
        if (dict.search(reval) == false){
            return "";
        }
        col = headCol;
        while (row < _x && !emptySlot(row, col)) {
            score += _property[row][col].score;
            col++;
        }
    }
    
    return reval;
}

string Board::word_col(int row, int col, int &score, Dictionary &dict){
    string reval = "";
    while (row >= 0 && !emptySlot(row-1, col)) {
        row--;
    }
    // row now is the head of the word in this row
    int headRow = row;
    while (row < _x && !emptySlot(row, col)) {
        reval += _board[row][col];
        
        row++;
    }
    if (reval.length() > 1) {
        if (dict.search(reval) == false){
            return "";
        }
        row = headRow;
        while (row < _x && !emptySlot(row, col)) {
            score += _property[row][col].score;
            row++;
        }
    }
    return reval;
}

// reset a single square
void Board::reset(int row, int col){
    if (_property[row][col].letterMul == 2){
        _board[row][col] = '2';
    }
    else if (_property[row][col].letterMul == 3){
        _board[row][col] = '3';
    }
    else if (_property[row][col].wordMul == 2){
        _board[row][col] = 'd';
    }
    else if (_property[row][col].wordMul == 3){
        _board[row][col] = 't';
    }
    else{
        _board[row][col] = '.';
    }
    _property[row][col].score = 0;
    _property[row][col].empty = true;
}

int Board::get_word_Mul(int row, int col){
    return _property[row][col].wordMul;
}


