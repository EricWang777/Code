
/*
 * Board.h
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#ifndef BOARD_H_
#define BOARD_H_

#include <string>
#include "Tile.h"
#include "Dictionary.h"

class Board {
public:
    Board (std::string board_file_name);
    
    // What else will this need?
    
    // get _x
    int get_x() const {return _x;}
    int get_y() const {return _y;}
    int get_startx() const {return _startx;}
    int get_starty() const {return _starty;}
    
    // check if the location (x, y) has already had tile
    bool emptySlot(int row, int col);
    // print the board
    void printBoard();
    // get the letter on a square
    char getLetter(int row, int col){return _board[row][col];}
    
    // modify the board, both _board and _propery
    void modify(int row, int col, char letter);
    
    // check validity of the word
    // check the longest word bounded by empty suqare or boundary of the board
    // not finished
    bool checkWord(int row, int col);
    
    // check the if there is adjancent tile
    bool checkAdjacent(int row, int col);
    
    // setScore to the square
    void setScore(int row, int col, int score){_property[row][col].score = score;}
    // get total score on a squre
    int getScore(int row, int col){return _property[row][col].score
                                        * _property[row][col].letterMul;}
    // give out the maximal word in a row, the starting place depends on user's place location
    // if the word doesn't exist, return empty string ""
    std::string word_row(int row, int col, int &score, Dictionary &dict);
    // give out... in a col
    std::string word_col(int row, int col, int &score, Dictionary &dict);
    
    // reset a single square on the board
    void reset(int row, int col);
    
    // get the multipler
    int get_word_Mul(int row, int col);
    
    ~Board();
    
    
private:
    // x rows, y columns
    int _x, _y;
    int _startx, _starty;
    
    
    // What else will this need?
    
    // two-dimension array with notation
    char** _board;
    // two-dimension array of suqare checking for valid slot
    // record property of each square, including mutliplier and wether empty
    
    struct square{
        // empty return true, full return false
        bool empty;
        // '2' '3' muliplier for the single letter on this square
        int letterMul;
        // 't' 'd' multiplier for the entire word passing through this squre
        int wordMul;
        
        // score on this board
        int score;
    };
    
    // private function of checking empty, for the purpose of checkAdjacent
    // if out of bound, return true
    bool empty_for_adjacent(int row, int col);
    
    // format same as board, index same as board
    square** _property;
    
    
    
};


#endif /* BOARD_H_ */