//
//  Game.cpp
//  hw4
//
//  Created by WangBingtang on 10/4/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(){
    _moves = 0;
}

// print players' scores
void Game::printScores(){
    cout << "------ScoreBoard------" << endl;
    for (unsigned int i = 0; i < players.size(); i++) {
        cout << players[i]->getName() << ": " <<players[i]->getScore() << endl;
    }
    cout << endl;
}

// add a player
void Game::addPlayer(std::string name, Bag& bag, unsigned num){
    Player* newPlayer = new Player(name, bag, num);
    players.push_back(newPlayer);
}

// check all pass, true == all pass, game end
bool Game::allPass(){
    for (unsigned int i = 0; i < players.size(); ++i) {
        if (!players[i]->if_pass()) {
            return false;
        }
    }
    return true;
}
// clear all pass
void Game::clearPass(){
    for (unsigned int i = 0; i < players.size(); ++i) {
        players[i]->resetPass();
    }
}

bool Game::gameEnd(Bag &bag){
    if (allPass()) {
        cal_score();
        return true;
    }
    
    
    if (bag.tilesRemaining() == 0) {
        for (int i= 0; i < players.size(); i++) {
            if (players[i]->num_tile_remain() == 0){
                cal_score();
                return true;
            }
        }
    }
    return false;
}

// cal score
void Game::cal_score(){
    cerr << "Calculating Score...";
    bool useAllTile = false;
    int winnerIndex = 0;
    for (unsigned int i = 0; i < players.size(); i++) {
        if (getPlayer(i)->num_tile_remain() == 0) {
            useAllTile = true;
            winnerIndex = i;
        }
    }
    if (useAllTile == true) {
        int total_minus_score = 0;
        for (unsigned int i = 0; i < players.size(); ++i) {
            if (i == winnerIndex) {
                getPlayer(i)->setScore(getPlayer(i)->getScore()+total_minus_score);
            }
            else{
                int socre_lose = getPlayer(i)->final_score();
                total_minus_score += socre_lose;
            }
        }
    }
    
}

Game::~Game(){
    for (unsigned int i = 0; i < players.size(); i++) {
        delete players[i];
    }
}



