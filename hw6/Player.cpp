//
//  Player.cpp
//  hw4
//
//  Created by WangBingtang on 10/3/16.
//  Copyright © 2016 USC. All rights reserved.
//

#include "Player.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

Player::Player(string name, Bag& bag, unsigned int numTiles){
    _name = name;
    _score = 0;
    this->numTiles = numTiles;
    set<Tile*> temp = bag.drawTiles(numTiles); // draw 7 tiles from bag
    _tiles.insert(temp.begin(), temp.end());
    pass = false;
    for (set<Tile*>::iterator it = _tiles.begin(); it != _tiles.end(); ++it){
        _tiles_vector.push_back(string(1, (*it)->getLetter()));
    }
    
}



// print all tiles the player has
void Player::printTiles(){
    for (set<Tile*>::iterator it = _tiles.begin();
         it != _tiles.end(); ++it) {
        cout << (*it)->getLetter() << "(" << (*it)->getPoints() << ")" << " ";
    }
    cout << endl;
}

// find a tile by the given letter
bool Player::findTile(char letter){
    for (set<Tile*>::iterator it = _tiles.begin();
         it != _tiles.end(); ++it) {
        // ignore upper or lower case
        if ((*it)->getLetter() == letter ||
            (*it)->getLetter() == (letter - 32)) {
            return true;
        }
    }
    return false;
}

// take a tile off from the player's tiles
Tile* Player::takeTile(char letter){
    for (set<Tile*>::iterator it = _tiles.begin();
         it != _tiles.end(); ++it) {
        // ignore upper or lower case
        if ((*it)->getLetter() == letter ||
            (*it)->getLetter() == (letter - 32)) {
            Tile* reval = *it;
            _tiles.erase(it);
            return reval;
        }
        
    }
    throw invalid_argument("Could not find the tile");
}

// get a tile without removing from player's tiles
Tile* Player::getTile(char letter){
    for (set<Tile*>::iterator it = _tiles.begin();
         it != _tiles.end(); ++it) {
        // ignore upper or lower case
        if ((*it)->getLetter() == letter ||
            (*it)->getLetter() == (letter - 32)) {
            Tile* reval = *it;
            return reval;
        }
        
    }
    throw invalid_argument("Could not find the tile");
}

// Insert a set of tiles to player's tiles
void Player::insertTiles(std::set<Tile*> tiles){
    _tiles.insert(tiles.begin(), tiles.end());
}

// Exchange player's tile(s) with bag
bool Player::exchange(string word, Bag &bag){
    if (bag.tilesRemaining() < word.length()) {
        cout << "The bag donesn't have enough tiles to exchange\n";
        cout << "Remaining tiles in the bag: " << bag.tilesRemaining();
        return false;
    }
    
    string noQ_word = word; // copy word doesn't have question mark
    string noAfterQ_word = word;
    eraseQ(noQ_word);
    eraseAfterQ(noAfterQ_word);
    
    set<Tile*> temp;
    for (int i = 0; i < noAfterQ_word.length(); i++) {
        if (findTile(noQ_word[i])) {
            
            Tile* exTile = takeTile(noQ_word[i]);
            temp.insert(exTile);
            
        }
        else{
            cout << "You don't have the letter: " << word[i] << endl;
            _tiles.insert(temp.begin(), temp.end());
            return false;
        }
        
    }
    
    vector<Tile*> takeoff;
    for (set<Tile*>::iterator it = temp.begin(); it!=temp.end(); ++it) {
        takeoff.push_back(*it);
    }
    temp.clear();
    bag.addTiles(takeoff);
    temp = bag.drawTiles(takeoff.size());
    _tiles.insert(temp.begin(), temp.end());
    return true;
}
// pass: do nothing
void Player::passTurn(){
    /*  do nothing */
    pass = true;
}



// check validity of placing veritcal
bool Player::check_place_ver(int row, int col, std::string word, Board &board, Dictionary &dict){
    string noQ_word = word; // copy word doesn't have question mark
    string noAfterQ_word = word;
    eraseQ(noQ_word);
    eraseAfterQ(noAfterQ_word);
    
    if (board.emptySlot(row, col) != true) {
        //cout << "You cannot place on a square that already used\n";
        return false;
    }
    // check if all characters in the word are possible to be placed in the board
    bool adjacent = false;
    // check if the word exists
    string check_word = "";
    int temp_row = row-1;
    while (temp_row >= 0 && board.emptySlot(temp_row, col) != true) {
        check_word = board.getLetter(temp_row, col) + check_word;
        temp_row --;
    }
    
    set<Tile*> temp;
    for (int i = 0; i < noAfterQ_word.length(); i++) {
        if (row+i >= board.get_y()) {
            _tiles.insert(temp.begin(), temp.end());
            //cout << "Out of Bound!" << endl;
            return false;
        }
        
        while (board.emptySlot(row+i, col) == false) {
            check_word = check_word+board.getLetter(row+i, col);
            row++;
            if (row > board.get_y()) {
                cout << "word will be out of right bound" << endl;
                _tiles.insert(temp.begin(), temp.end());
                return false;
            }
        }
        check_word += noQ_word[i];
        if (board.checkAdjacent(row+i, col) == true) {
            adjacent = true;
        }
        else{
            if (row+i == board.get_starty() && col == board.get_startx()) {
                adjacent = true;
            }
        }
        // check if the player has all characters in the word
        if (findTile(noAfterQ_word[i]) == false) {
            cout << "Letter " << noAfterQ_word[i] << " is not in your tiles" << endl;
            _tiles.insert(temp.begin(), temp.end());
            return false;
        }
        else {
            Tile* take = takeTile(noAfterQ_word[i]);
            temp.insert(take);
        }
    }
    _tiles.insert(temp.begin(), temp.end());
    row += noAfterQ_word.length();
    while (row >= 0 && row < board.get_y() && board.emptySlot(row, col) != true) {
        check_word += board.getLetter(row, col);
        row++;
    }
    
    
    if(!dict.search(check_word)){
        //cout << "The word: " << check_word << "is not valid\n";
        return false;
    }
    
    if (adjacent == false) {
        //cout << "The word is isolated or not start from the star place\n";
        return false;
    }
    return true;

}

// check validity of placing horizontal
bool Player::check_place_hor(int row, int col, std::string word, Board &board, Dictionary &dict){
    string noQ_word = word; // copy word doesn't have question mark
    string noAfterQ_word = word;
    eraseQ(noQ_word);
    eraseAfterQ(noAfterQ_word);
    
    if (board.emptySlot(row, col) != true) {
        //cout << "You cannot place on a square that already used\n";
        return false;
    }
    // check if all characters in the word are possible to be placed in the board
    bool adjacent = false;
    // check if the word exists
    string check_word = "";
    int temp_col = col-1;
    while (temp_col >= 0 && board.emptySlot(row, temp_col) != true) {
        check_word = board.getLetter(row, temp_col) + check_word;
        temp_col --;
    }
    
    set<Tile*> temp;
    
    for (int i = 0; i < noAfterQ_word.length(); i++) {
        if (col+i >= board.get_x()) {
            _tiles.insert(temp.begin(), temp.end());
            //cout << "Out of Bound!" << endl;
            return false;
        }
        
        while (board.emptySlot(row, col+i) == false) {
            check_word = check_word+board.getLetter(row, col+i);
            col++;
            if (col > board.get_x()) {
                cout << "word will be out of right bound" << endl;
                _tiles.insert(temp.begin(), temp.end());
                return false;
            }
        }
        check_word += noQ_word[i];
        if (board.checkAdjacent(row, col+i) == true) {
            adjacent = true;
        }
        else{
            if (col+i == board.get_startx() && row == board.get_starty()) {
                adjacent = true;
            }
        }
        // check if the player has all characters in the word

        if (findTile(noAfterQ_word[i]) == false) {
            cout << "Tile " << noAfterQ_word[i] << " is not in your tiles" << endl;
            _tiles.insert(temp.begin(), temp.end());
            return false;
        }
        else {
            Tile* take = takeTile(noAfterQ_word[i]);
            temp.insert(take);
        }
    }
    _tiles.insert(temp.begin(), temp.end());
    
    col += noAfterQ_word.length();
    while (col >= 0 && col < board.get_x() && board.emptySlot(row, col) != true) {
        check_word += board.getLetter(row, col);
        col++;
    }
    
    if(!dict.search(check_word)){
        //cout << "The word: " << check_word << " is not valid\n";
        return false;
    }
    
    if (adjacent == false) {
        //cout << "The word is isolated\n";
        return false;
    }
    return true;
}



// place command: ('-')(row)(col)(word), succeed return true
bool Player::placeHorizontal(int row, int col, string word, Board &board, Dictionary &dict){
    string noQ_word = word; // copy word doesn't have question mark
    string noAfterQ_word = word;
    eraseQ(noQ_word);
    eraseAfterQ(noAfterQ_word);
    
    if (check_place_hor(row, col, word, board, dict) == false){
        //cout << "Invalid move\n";
        return false;
    }
    
    preCol.clear();
    preRow.clear();
    takenTiles.clear();
    for (int i = 0; i < noAfterQ_word.size(); i++) {
        while (board.emptySlot(row, col) == false) {
            col++;
        }
        
        board.modify(row, col, noQ_word[i]);
        preCol.push_back(col);
        preRow.push_back(row);
        Tile* take = takeTile(noAfterQ_word[i]);
        takenTiles.insert(take);
        board.setScore(row, col, take->getPoints());
        
        int garbage = 0;
        
        string test = board.word_col(row, col, garbage, dict);
        if (test == "") { // find a non-exist word
            //cout << "Find non-existed word";
            //cout << " on (" << row+1 << ", " << col+1 << ")\n";
            // reset the board
            for (int i = 0; i < preRow.size(); i++) {
                board.reset(preRow[i], preCol[i]);
            }
            _tiles.insert(takenTiles.begin(), takenTiles.end());
            return false;
        }
        
        string temp_word = board.word_col(row, col, _score, dict);
//        if (temp_word.length() > 1) { // not a single letter
//            cout << "The word being checked is: " << temp_word << endl;
//        }
        
        
    }
    return true;
}

// place command: ('|')(row)(col)(word), succeed return true
bool Player::placeVertical(int row, int col, string word, Board &board, Dictionary &dict){
    string noQ_word = word; // copy word doesn't have question mark
    string noAfterQ_word = word;
    eraseQ(noQ_word);
    eraseAfterQ(noAfterQ_word);
    
    
    if (check_place_ver(row, col, word, board, dict) == false){
        //cout << "Invalid move\n";
        return false;
    }
    preCol.clear();
    preRow.clear();
    takenTiles.clear();
    
    for (int i = 0; i < noQ_word.size(); i++) {
        while (board.emptySlot(row, col) == false) {
            row++;
        }
        board.modify(row, col, noQ_word[i]);
        preCol.push_back(col);
        preRow.push_back(row);
        Tile* take = takeTile(noAfterQ_word[i]);
        takenTiles.insert(take);
        board.setScore(row, col, take->getPoints());
        
        int garbage = 0;
        string test = board.word_row(row, col, garbage, dict);
        if (test == "") { // find a non-exist word
            //cout << "Find non-existed word\n";
            //cout << " on (" << row+1 << ", " << col+1 << ")\n";
            // reset the board
            for (int i = 0; i < preRow.size(); i++) {
                board.reset(preRow[i], preCol[i]);
            }
            _tiles.insert(takenTiles.begin(), takenTiles.end());
            return false;
        }

        
        string temp_word = board.word_row(row, col, _score, dict);
//        if (temp_word.length() > 1) { // not a single letter
//            cout << "The word being checked is: " << temp_word << endl;
//        }
        
        
    }
    
    
    return true;
}


// total place function
bool Player::place(char command, int row, int col, std::string word,
                   Board &board, Bag &bag, Dictionary &dict){
    
    
    if (command == '|') {
        // place vertical
        
        if (placeVertical(row, col, word, board, dict)) {
            int wordMul = 1;
            int tempRow = row;
            int tempScore = 0;
            while (tempRow > 0 && !board.emptySlot(tempRow-1, col)) {
                wordMul *= board.get_word_Mul(tempRow-1, col);
                tempScore += board.getScore(tempRow-1, col);
                tempRow --;
            }
            while (tempRow >= 0 && tempRow < board.get_y()-1 && !board.emptySlot(tempRow, col)){
                wordMul *= board.get_word_Mul(tempRow, col);
                tempScore += board.getScore(tempRow, col);
                tempRow ++;
            }
            _score += tempScore * wordMul;
        }
        else return false;
    }
    else if (command == '-') {
        // place horizontal
        if (placeHorizontal(row, col, word, board, dict)) {
            int tempCol = col;
            int wordMul = 1;
            int tempScore = 0;
            while (tempCol > 0 && !board.emptySlot(row, tempCol-1)) {
                wordMul *= board.get_word_Mul(row, tempCol-1);

                tempScore += board.getScore(row, tempCol-1);
                tempCol --;
            }
            tempCol = col;
            while (tempCol >= 0 && tempCol < board.get_y()-1 && !board.emptySlot(row, tempCol)){
                wordMul *= board.get_word_Mul(row, tempCol);
                tempScore += board.getScore(row, tempCol);
                tempCol ++;
            }
            _score += tempScore * wordMul;
        }
        else return false;
    }
    
    
    if (_tiles.size() == 0) {
        cout << "Cong! You have received 50 points bonus!\n";
        _score += 50;
    }
    
    
    if ((numTiles-_tiles.size()) > bag.tilesRemaining()) { // not enough tiles in bag
        cout << "No more tiles in the bag\n";
        set<Tile*> draw = bag.drawTiles(bag.tilesRemaining());
        _tiles.insert(draw.begin(), draw.end());
    }
    else{
        set<Tile*> draw = bag.drawTiles(numTiles-_tiles.size());
        _tiles.insert(draw.begin(), draw.end());
    }
    return true;
}

// erase Q
void Player::eraseQ(std::string &word){
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == '?') {
            word.erase(word.begin() + i);
        }
    }
}

// erase letter after Q
void Player::eraseAfterQ(std::string &word){
    for (int i = 0; i < word.length(); i++) {
        if (word[i] == '?') {
            word.erase(word.begin() + i+1);
        }
    }
}

int Player::num_tile_remain(){
    return _tiles.size();
}

int Player::final_score(){
    int score_minus = 0;
    for (set<Tile*>::iterator it = _tiles.begin(); it != _tiles.end(); ++it) {
        _score -= (*it)->getPoints();
        score_minus += (*it)->getPoints();
    }
    return score_minus;
}

Player::~Player(){
   for (set<Tile*>::iterator it = _tiles.begin();
        it != _tiles.end(); ++it) {
       delete *it;
   }
   // for (set<Tile*>::iterator it = takenTiles.begin();
   //      it != takenTiles.end(); ++it) {
   //     delete *it;
   // }
}

void Player::possible_place_hor(int row, int col, string word_could_form, Dictionary &dict, Board &board, string place_word){
    // if out of bound, return
    if (row >= board.get_x() || col >= board.get_y()) {
        return;
    }
    // if the word_could_form doesn't match a prefix, return
    if (!dict.searchPrefix(word_could_form)) {
        return;
    }
    string temp = place_word;
    eraseQ(temp);
    // if the word formed exists in dictionary, it could be a possible valid move
    if (dict.search(word_could_form)) {
        // if those two world are not equal, it means that AI must use a word already on the board, hence adjacent
        
            // now store the info of this place movement into the variable
            word_could_placed.push_back(place_word);
            possible_row.push_back(row);
            isHorizontal.push_back(true);
            
            // now we only have the ending col info of the place, we need to find the starting col
            int start_col = col;
            for (int i = 0; i < temp.length(); i++) {
                start_col --;
                while (start_col > 0 && !board.emptySlot(row, start_col)) {
                    start_col--;
                }
            }
            possible_col.push_back(start_col);
        
    }
    else{
        // get the letters from this row
        int tempCol = col-1;
        while (tempCol >= 0 && !board.emptySlot(row, tempCol)) {
            word_could_form = string(1, board.getLetter(row, tempCol)) + word_could_form;
            tempCol--;
        }
        while (col >= 0 && col < board.get_x() && !board.emptySlot(row, col) ) {
            word_could_form += string(1, board.getLetter(row, col));
            col ++;
        }
        for (int i = 0; i < _tiles_vector.size(); ++i) {
            if (_tiles_vector[i] == "?") {
                for (int x = 0; x < 27; x++) {
                    _tiles_vector[i] = string(1, 'A'+x);
                    word_could_form += _tiles_vector[i];
                    place_word = place_word + "?" + _tiles_vector[i];
                    
                    string taken_letter = "?";
                    _tiles_vector.erase(_tiles_vector.begin()+i);
                    // backtracking
                    possible_place_hor(row, col+1, word_could_form, dict, board, place_word);
                    word_could_form.erase(word_could_form.end()-1);
                    place_word.erase(place_word.end()-1);
                    place_word.erase(place_word.end()-1);
                    
                    if (i >= _tiles_vector.size())
                    {
                        _tiles_vector.push_back(taken_letter);
                    }
                    else{
                    string temp2 = _tiles_vector[i];
                    _tiles_vector[i] = taken_letter;
                    _tiles_vector.push_back(temp2);
                    }
                    
                }
            }
            else{
                word_could_form += _tiles_vector[i];
                place_word += _tiles_vector[i];
                
                string taken_letter = _tiles_vector[i];
                _tiles_vector.erase(_tiles_vector.begin()+i);
                // backtracking
                possible_place_hor(row, col+1, word_could_form, dict, board, place_word);
                // fail, then
                word_could_form.erase(word_could_form.end()-1);
                place_word.erase(place_word.end()-1);
                
                _tiles_vector.push_back(taken_letter);
            }
            
        }
        
    }
}

void Player::all_possible_hor(Board &board, Dictionary& dict){
    string a = "";
    string b = "";
    for (int i = 0; i < board.get_x(); i++) {
        for (int j = 0; j < board.get_y(); j++) {
            possible_place_hor(i, j, a, dict, board, b);
        }
    }
}

int Player::findMaxScoreIndex(Dictionary &dict, Board &board){
    all_possible_hor(board, dict);
    all_possible_ver(board, dict);
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < word_could_placed.size(); i++) {
        int temp = placeAndReset(dict, board, i);
        if (temp > max) {
            max = temp;
            maxIndex = i;
        }
    }
    //cout << max << endl;
    return maxIndex;
}

int Player::placeAndReset(Dictionary &dict, Board &board, int index){
    int row, col;
    int currScore = _score;
    row = possible_row[index];
    col = possible_col[index];
    string word = word_could_placed[index];
    
    if (isHorizontal[index]) {
        if (placeHorizontal(row, col, word, board, dict)) {
            _tiles.insert(takenTiles.begin(), takenTiles.end());
            int tempCol = col;
            int wordMul = 1;
            int tempScore = 0;
            while (tempCol > 0 && tempCol < board.get_y() && !board.emptySlot(row, tempCol-1)) {
                wordMul *= board.get_word_Mul(row, tempCol-1);
                
                tempScore += board.getScore(row, tempCol-1);
                tempCol --;
            }
            tempCol = col;
            while (tempCol >= 0 && tempCol < board.get_y()-1 && !board.emptySlot(row, tempCol)){
                wordMul *= board.get_word_Mul(row, tempCol);
                tempScore += board.getScore(row, tempCol);
                tempCol ++;
            }
            _score += tempScore * wordMul;
        }
        
    }
    else{
        if (placeVertical(row, col, word, board, dict)) {
            _tiles.insert(takenTiles.begin(), takenTiles.end());
            int wordMul = 1;
            int tempRow = row;
            int tempScore = 0;
            while (tempRow > 0 && tempRow < board.get_x() && !board.emptySlot(tempRow-1, col)) {
                wordMul *= board.get_word_Mul(tempRow-1, col);
                tempScore += board.getScore(tempRow-1, col);
                tempRow --;
            }
            tempRow = row;
            while (tempRow >= 0 && tempRow < board.get_y()-1 && !board.emptySlot(tempRow, col)){
                wordMul *= board.get_word_Mul(tempRow, col);
                tempScore += board.getScore(tempRow, col);
                tempRow ++;
            }
            _score += tempScore * wordMul;
        }
        
    }
    // reset the board
    for (int i = 0; i < preRow.size(); i++) {
        board.reset(preRow[i], preCol[i]);
    }
    //    cout << _score-currScore << endl;
    int reval = _score-currScore;
    _score = currScore;
    return reval;
    
}


void Player::storeMaxWordInfo(int max){
    for (int i = 0; i < word_could_placed.size(); i++) {
        if (word_could_placed[i].length() == max) {
            best_index.push_back(i);
        }
    }
}

bool Player::tryToPlace(Dictionary &dict, Board &board, Bag &bag){
    int maxIndex = findMaxScoreIndex(dict, board);
    if (isHorizontal[maxIndex]) {
        if (place('-', possible_row[maxIndex], possible_col[maxIndex], word_could_placed[maxIndex], board, bag, dict)) {
            cout << "PLACE - " << possible_row[maxIndex]+1 << " " << possible_col[maxIndex]+1
            << " " << word_could_placed[maxIndex] << endl;
            return true;
        }
        
    }
    else{
        if (place('|', possible_row[maxIndex], possible_col[maxIndex], word_could_placed[maxIndex], board, bag, dict)) {
            cout << "PLACE | " << possible_row[maxIndex]+1 << " " << possible_col[maxIndex]+1
            << " " << word_could_placed[maxIndex] << endl;
            return true;
        }
        
    }
    return false;
}

void Player::possible_place_ver(int row, int col, string word_could_form, Dictionary &dict, Board &board, string place_word){
    // if out of bound, return
    if (row >= board.get_x() || col >= board.get_y()) {
        return;
    }
    // if the word_could_form doesn't match a prefix, return
    if (!dict.searchPrefix(word_could_form)) {
        return;
    }
    string temp = place_word;
    eraseQ(temp);
    // if the word formed exists in dictionary, it could be a possible valid move
    if (dict.search(word_could_form)) {
        // if those two world are not equal, it means that AI must use a word already on the board, hence adjacent
        
            // now store the info of this place movement into the variable
            word_could_placed.push_back(place_word);
            possible_col.push_back(col);
            isHorizontal.push_back(false);
            // now we only have the ending col info of the place, we need to find the starting col
            int start_row = row;
            for (int i = 0; i < temp.length(); i++) {
                start_row --;
                while (start_row > 0 && start_row < board.get_x() && !board.emptySlot(start_row, col)) {
                    start_row--;
                }
            }
            possible_row.push_back(start_row);
        
    }
    else{
        // get the letters from this row
        int tempRow = row-1;
        while (tempRow >= 0 && !board.emptySlot(tempRow, col)) {
            word_could_form = string(1, board.getLetter(tempRow, col)) + word_could_form;
            tempRow--;
        }
        while (row >= 0 && row < board.get_y() && !board.emptySlot(row, col)) {
            word_could_form += string(1, board.getLetter(row, col));
            row ++;
        }
        for (int i = 0; i < _tiles_vector.size(); ++i) {
            if (_tiles_vector[i] == "?") {
                for (int x = 0; x < 27; x++) {
                    _tiles_vector[i] = string(1, 'A'+x);
                    word_could_form += _tiles_vector[i];
                    place_word = place_word + "?" + _tiles_vector[i];
                    
                    string taken_letter = "?";
                    _tiles_vector.erase(_tiles_vector.begin()+i);
                    // backtracking
                    possible_place_hor(row+1, col, word_could_form, dict, board, place_word);
                    word_could_form.erase(word_could_form.end()-1);
                    place_word.erase(place_word.end()-1);
                    place_word.erase(place_word.end()-1);
                    if (i >= _tiles_vector.size())
                    {
                        _tiles_vector.push_back(taken_letter);
                    }
                    else{
                    string temp2 = _tiles_vector[i];
                    _tiles_vector[i] = taken_letter;
                    _tiles_vector.push_back(temp2);
                    }
                    
                }
            }
            else{
                word_could_form += _tiles_vector[i];
                place_word += _tiles_vector[i];
                
                string taken_letter = _tiles_vector[i];
                _tiles_vector.erase(_tiles_vector.begin()+i);
                // backtracking
                possible_place_ver(row+1, col, word_could_form, dict, board, place_word);
                // fail, then
                word_could_form.erase(word_could_form.end()-1);
                place_word.erase(place_word.end()-1);
                _tiles_vector.push_back(taken_letter);
            }
            
        }
        
    }
}

void Player::all_possible_ver(Board &board, Dictionary& dict){
    string a = "";
    string b = "";
    for (int i = 0; i < board.get_x(); i++) {
        for (int j = 0; j < board.get_y(); j++) {
            possible_place_ver(i, j, a, dict, board, b);
        }
    }
}



void Player::refresh(){
    _tiles_vector.clear();
    for (set<Tile*>::iterator      it = _tiles.begin(); it != _tiles.end(); ++it){
        _tiles_vector.push_back(string(1, (*it)->getLetter()));
    }
    word_could_placed.clear();
    possible_row.clear();
    possible_col.clear();
    best_index.clear();
    isHorizontal.clear();
    preRow.clear();
    preCol.clear();
}

void Player::finalMove(Dictionary &dict, Board &board, Bag &bag){
    if (tryToPlace(dict, board, bag)) {
        return;
    }
    else{
        string temp = "";
        for (int i = 0; i < _tiles_vector.size(); i++) {
            temp += _tiles_vector[i];
        }
        exchange(temp, bag);
        passTurn();
        cout << "\nEXCHANGE " << temp << endl;
    }
}


int Player::findMaxScoreIndex_S(Dictionary &dict, Board &board){
    all_possible_hor(board, dict);
    all_possible_ver(board, dict);
    int max = 0;
    int maxIndex = 0;
    for (int i = 0; i < word_could_placed.size(); i++) {
        int temp = placeAndReset(dict, board, i);
        if (temp > max) {
            max = temp;
            maxIndex = i;
        }
    }
    //cout << max << endl;
    return maxIndex;
}

bool Player::tryToPlace_S(Dictionary &dict, Board &board, Bag &bag){
    int maxIndex = findMaxScoreIndex(dict, board);
    if (isHorizontal[maxIndex]) {
        if (place('-', possible_row[maxIndex], possible_col[maxIndex], word_could_placed[maxIndex], board, bag, dict)) {
            cout << "PLACE - " << possible_row[maxIndex]+1 << " " << possible_col[maxIndex]+1
            << " " << word_could_placed[maxIndex] << endl;
            return true;
        }
        
    }
    else{
        if (place('|', possible_row[maxIndex], possible_col[maxIndex], word_could_placed[maxIndex], board, bag, dict)) {
            cout << "PLACE | " << possible_row[maxIndex]+1 << " " << possible_col[maxIndex]+1
            << " " << word_could_placed[maxIndex] << endl;
            return true;
        }
        
    }
    return false;
}

void Player::finalMove_S(Dictionary &dict, Board &board, Bag &bag){
    if (tryToPlace_S(dict, board, bag)) {
        return;
    }
    else{
        string temp = "";
        for (int i = 0; i < _tiles_vector.size(); i++) {
            temp += _tiles_vector[i];
        }
        exchange(temp, bag);
        passTurn();
        cout << "\nEXCHANGE " << temp << endl;
    }
}


