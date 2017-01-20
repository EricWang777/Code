#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QApplication>
#include <QLabel>
#include <QComboBox>
#include <iostream>
#include <QMessageBox>
#include <QString>
#include <QFont>
#include <QRadioButton>
#include <QPalette>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Bag.h"
#include "Dictionary.h"

class Game : public QWidget {
	Q_OBJECT
public slots:
	void NameWindow();
	void MainWindow();
	void PASS();
	void Pass();
	void SwitchExchangePlace(const QString& qstr);
	void Place();
	void Exchange();
	void ScoreBoard();
	void ExitScoreBoard();
	void Pass_for_place();
public:
	Game(QApplication *app, std::string dictionaryFileName, std::string boardFileName, std::string bagFileName, unsigned int numTiles);
	~Game();
	// public function of the game
	void addPlayer(std::string name);
	void printScores();
	void refreshBoardButton();
	// check if all pass
    bool allPass();
    // clear all pass;
    void clearPass();
    // if game end
    bool gameEnd();
    // calculate the final score
    void cal_score();
    // find the winner
    std::string findWinner();



private:
	QApplication* app;

	// Welcome Window
	QWidget *welcome_window;
	QComboBox *choose_player_num;
	QLabel *welcome_title, *ask_choose;
	QVBoxLayout *v_welcome;
	QHBoxLayout *h_welcome;
	QPushButton *start_button, *quit_button;
	

	// Input Name Window
	QWidget *name_window;
	std::vector<QLineEdit*> input_name;
	std::vector<QLabel*> player_index;
	QLabel *ask_input_name;
	QPushButton *confirm_button;
	QHBoxLayout *h_name;
	QVBoxLayout *v_name;

	// Main Board
	QWidget *main_window;
	QPushButton ***board_button, *pass_button, *exchange_confirm_button, *to_score_board;
	QGridLayout *g_board;
	QVBoxLayout *v_main;
	QComboBox *moves;
	QHBoxLayout *h_main, *h_sub_v_main;
	QLabel *tiles_on_hand, *inform_whos_turn, *player_curr_score, *input_your_word, *tiles_want_exchange;
	QLineEdit *player_input;
	QRadioButton *h_place, *v_place;

	// Score Board
	QWidget *score_board_window;
	QLabel *title;
	QPushButton *ok;
	std::vector<QLabel*> print_player_score;
	QVBoxLayout *v_score_board;

	// Variable other than Qt
	int num_player; // total number of players
	Board *_board;   // non-qt data of board
	std::vector<Player*> players;//std::vector<Player*> players;
	Bag *_bag; // the only bag in this game
	Dictionary *_dictionary;
	int max_hand_tiles; // the number of max tiles on hand
	int total_turns = 0; // the total number of turns that all players play


};

#endif /* GAME_H */