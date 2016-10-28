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
    std::string stringTiles();
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
    
    
};


#endif /* Player_hpp */
