//
//  Game.hpp
//  hw4
//
//  Created by WangBingtang on 10/4/16.
//  Copyright © 2016 USC. All rights reserved.
//

#ifndef Game_h
#define Game_h
#include "Player.h"
#include "Tile.h"
#include "Bag.h"
#include "Dictionary.h"
#include "Board.h"


class Game{
public:
    Game();
    
    // print players' scores
    void printScores();
    
    // add a player
    void addPlayer(std::string name, Bag& bag, unsigned num);
    
    // get a player
    Player* getPlayer(int i) {return players[i];}
    
    // check if all pass
    bool allPass();
    // clear all pass;
    void clearPass();
    
    // next moves
    void nextMoves(){_moves ++;}
    // calculate how many turns
    int turns(){return _moves/players.size()+1;}
    
    bool gameEnd(Bag &bag);
    
    // calculating score after game end
    void cal_score(); // i is the index of winner
    
    ~Game();
    
    
private:
    std::vector<Player*> players;
    int _moves; // record how many moves the players have done
    
};

#endif /* Game_h */
