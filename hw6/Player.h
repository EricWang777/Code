//
//  Player.hpp
//  hw4
//
//  Created by WangBingtang on 10/3/16.
//  Copyright © 2016 USC. All rights reserved.
//

#ifndef Player_h
#define Player_h

#include <string>
#include <vector>
#include "Tile.h"
#include "Bag.h"
#include "Board.h"
#include "Dictionary.h"

class Player{
public:
    Player(std::string name, Bag& bag, unsigned int numTiles);
    std::string getName() const {return _name;}
    void setName(std::string name){_name = name;}
    int getScore() const {return _score;}
    void setScore(int score){_score = score;}
    ~Player();
    
    // print all tiles the player has
    void printTiles();
    /* find if a specfic letter is in the player's tiles
       if yes, return the tile, if no, notice the player */
    bool findTile(char letter);
    // take off a tile
    Tile* takeTile(char letter);
    // get a tile
    Tile* getTile(char letter);
    // insert a set of tiles
    void insertTiles(std::set<Tile*> tiles);
    
    
    // exchange, the player's tile, if succeed, return true
    bool exchange(std::string letter, Bag& bag);
    // Pass: do nothing
    void passTurn();
    bool if_pass(){return pass;} // true means pass
    void resetPass(){pass = false;}
    
    // Place:
    bool placeHorizontal(int row, int col, std::string word, Board &board, Dictionary &dict);
    bool placeVertical(int row, int col, std::string word, Board &board, Dictionary &dict);
    bool place(char command, int row, int col, std::string word,
               Board &board, Bag &bag, Dictionary &dict);
    // check if the vertical placing move is valid
    bool check_place_ver(int row, int col, std::string word, Board &board, Dictionary &dict);
    bool check_place_hor(int row, int col, std::string word, Board &board, Dictionary &dict);
    
    // erase question mark in a word
    void eraseQ(std::string &word);
    void eraseAfterQ(std::string &word);
    
    int num_tile_remain();
    
    int final_score(); // minus the score of left tiles
    
    ///////////////// hw6 AIMaxWord part
    // horizontal place
    // find all the possible horizontal place and store them into the variable
    // word_could_form is the world that formed, including the placed word, after placing a tile.
    // place_word is the world that try to place by AI. All letters in place_word should exist in AI's hand tiles.
    void possible_place_hor(int row, int col, std::string word_could_form, Dictionary &dict, Board &board, std::string place_word);
    void all_possible_hor(Board &board, Dictionary &dict);
    
    void tryToPlaceHor(Dictionary &dict, Board &board, Bag &bag);
    /////////
    void possible_place_ver(int row, int col, std::string word_could_form, Dictionary &dict, Board &board, std::string place_word);
    void all_possible_ver(Board &board, Dictionary &dict);
    
    bool tryToPlace(Dictionary &dict, Board &board, Bag &bag);
    
    
    
    // find max length of all possible word
    int findMaxScoreIndex(Dictionary &dict, Board &board);
    // refresh all the data of ai
    void refresh();
    void finalMove(Dictionary &dict, Board &board, Bag &bag);

    /////////////////
    // find max length of all possible word
    int findMaxScoreIndex_S(Dictionary &dict, Board &board);
    // for max score, first actually place on the board, find the score gained and then reset the board
    int placeAndReset(Dictionary &dict, Board &board, int index);
    bool tryToPlace_S(Dictionary &dict, Board &board, Bag &bag);
    void finalMove_S(Dictionary &dict, Board &board, Bag &bag);
    
    

    
private:
    std::string _name;
    int _score;
    std::set<Tile*> _tiles;
    bool pass;
    unsigned int numTiles;
    
    
    // work for reset
    std::vector<int> preRow;
    std::vector<int> preCol;
    std::set<Tile*> takenTiles;
    
    //////////////////////////////////////////////////////////////////////
    // convert the set of _tiles into vector
    std::vector<std::string> _tiles_vector;
    std::vector<std::string> Q_tiles_vector; // the ? is replaced by letters.
    
    // variable store possible valid place
    std::vector<std::string> word_could_placed; // possible word to place in the command
    std::vector<int> possible_row; // possible row in the command
    std::vector<int> possible_col; // possible col in the command
    std::vector<bool> isHorizontal; // place horizontally or not, true -> horizontal
    
    // find max length of all possible word
    int findMaxLength();
    // store the index of word with the max length
    void storeMaxWordInfo(int max);
    
    // index of info of most possible move
    std::vector<int> best_index;
    
    

    
    
};


#endif /* Player_hpp */
