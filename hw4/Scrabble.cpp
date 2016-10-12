/*
 * Scrabble.cpp
 *
 *  Created on: Sep 18, 2016
 *      Author: kempe
 */

// The following is a suggestion for how to proceed.
// Feel free to make any changes you like.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <stdexcept>
#include <ctime>

#include "Board.h"
#include "Game.h"
#include "Player.h"

using namespace std;

void readConfigFile (string config_file_name,
                     string & dictionary_file_name,
                     string & board_file_name,
                     string & bag_file_name,
                     unsigned int & hand_size)
{
    ifstream configFile (config_file_name.c_str());
    string line;
    bool number = false, board = false, tiles = false, dictionary = false;
    
    if (!configFile.is_open())
        throw invalid_argument("Cannot open file: " + config_file_name);
        while (getline (configFile, line))
        {
            stringstream ss (line);
            string parameter;
            ss >> parameter;
            if (parameter == "NUMBER:")
            { ss >> hand_size; number = true; }
            else if (parameter == "BOARD:")
            { ss >> board_file_name; board = true; }
            else if (parameter == "TILES:")
            { ss >> bag_file_name; tiles = true; }
            else if (parameter == "DICTIONARY:")
            { ss >> dictionary_file_name; dictionary = true; }
        }
    if (!number)
        throw invalid_argument("Hand size not specified in config file");
    if (!board)
        throw invalid_argument("Board file name not specified in config file");
    if (!tiles)
        throw invalid_argument("Bag file name not specified in config file");
    if (!dictionary)
        throw invalid_argument("Dictionary file name not specified in config file");
}

int main (int nargs, char **args)
{
    if (nargs < 2 || nargs > 2)
        cout << "Usage: Scrabble <config-filename>\n";
    try {
        string dictionaryFileName, boardFileName, bagFileName;
        unsigned int numTiles;
        
        readConfigFile (args[1],
                        dictionaryFileName, boardFileName, bagFileName,
                        numTiles);
        
        Dictionary dict (dictionaryFileName);
        Board board (boardFileName);
        Bag bag (bagFileName, time(0)); // second argument is random seed
        
        // Good luck! 
        // Variable
    Game game;
    int num_player;
    
    cout << "---------Scrabble Game---------" << endl;
    cout << "How many players (1-8): ";
    cin >> num_player;
    while (num_player > 8 || num_player < 1){
        cout << "Please enter number between 1 and 8\n";
        cin >> num_player;
    }
    cin.ignore();
    for (int i = 0; i < num_player; i++) {
        string name;
        cout << "Please enter Player" << i+1 << "'s name: ";
       
        getline(cin, name);
        
        game.addPlayer(name, bag, numTiles);
    }
    
    board.printBoard();
    game.printScores();
    int i = 0;
    while (1) {
        if (i == 0) { // new turn starts
            game.clearPass();
        }
        
        cout << "It's player" << i+1 << "'s turn!\n";

        board.printBoard();
        cout << "Drawing tiles...\n";
        
        Player* currPlayer = game.getPlayer(i);
        cout << "Now you have these tiles: \n";
        currPlayer->printTiles();
        cout << endl;
        cout << "What do you want to do? \n";
        cout << "1. PLACE (direction) (row) (col) (word)\n";
        cout << "2. EXCHANGE (word)\n";
        cout << "3. PASS\n";
        cout << "Your choice: ";
        
        string userInput;
        getline(cin, userInput);
        stringstream ss(userInput);
        
        string command;
        char direction;
        int row, col;
        string word;
        ss >> command;
        if (command == "PLACE") {
            ss >> direction; ss >> row; ss >> col; ss >> word;
            if (ss.fail()){
                cout << "Invalid input, try again\n";
                i = i - 1;
            }
            else{
                row-=1;col-=1;
                if (currPlayer->place(direction, row, col, word, board, bag, dict)){
                    board.printBoard();
                    game.printScores();

                    
                    if (game.gameEnd(bag)){
                        cout << "Game Ends!" << endl;
                        game.printScores();
                        break;
                    }
                }
                else{
                    cout << "Invalid input, try again\n";
                    i = i - 1;
                    
                }
            }
        }
        else if (command == "EXCHANGE"){
            ss >> word;
            if (currPlayer->exchange(word, bag)){
                cout << "Exchanging..." << endl;
                
                cout << "Now you have:" << endl;
                currPlayer->printTiles();
                currPlayer->passTurn();
                if (game.gameEnd(bag)){
                    cout << "Game Ends!All player PASS\n" << endl;
                    game.printScores();
                    break;
                }
                
                cout << endl;
            }
            else{
                cout << "Invalid input, try again" << endl;
                i = i - 1;
            }
        }
        else if (command == "PASS"){
            cout << "Pass to next player...\n" << endl;
            currPlayer->passTurn();
           
            if (game.gameEnd(bag)){
                cout << "Game Ends! All player PASS\n" << endl;
                game.printScores();
                break;
            }
        }
        else{
            cout << "Invalid command, try again\n";
            i = i - 1;
        }
        
        i++;
        i = i % num_player;
    }
        return 0;
    }
    catch (invalid_argument & e)
    { cout << "Fatal Error! " << e.what(); }
    
    return 1;
       
}

