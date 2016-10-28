#include "game.h"
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

Game::~Game(){
	delete welcome_window;
	delete _board;
	delete name_window;
	delete main_window;
	delete _bag;
	delete _dictionary;
	for (unsigned int i = 0; i < players.size(); ++i)
	{
		delete players[i];
	}
	// to be continue...
}

Game::Game(QApplication *app){
	this->app = app;
// initalize the board
	_board = new Board("board.txt");
// initalize the bag
	_bag = new Bag("bag.txt", 10);
	max_hand_tiles = 7;
// initalize the dictionary
	_dictionary = new Dictionary("dictionary.txt");

// welcome window
	// initialize variable
	welcome_window = new QWidget;
	choose_player_num = new QComboBox;
	welcome_title = new QLabel("Welcome to Scrabble Game!");
	QFont karmaFont; // set the font of welcome_title
	karmaFont.setBold(true);
	karmaFont.setPointSize(20);
	welcome_title->setFont(karmaFont);
	ask_choose = new QLabel("How many players: ");
	start_button = new QPushButton("Start");
	quit_button = new QPushButton("Quit");
	v_welcome = new QVBoxLayout;
	h_welcome = new QHBoxLayout;
	// set up
	welcome_window->setLayout(v_welcome);
	v_welcome->addWidget(welcome_title);
	h_welcome->addWidget(ask_choose);
	int i = 1;
	while(i <= 8){
		choose_player_num->addItem(QString::number(i));
		i++;
	}
	h_welcome->addWidget(choose_player_num);
	h_welcome->addWidget(start_button);
	// when press the start_button, close the welcome_window
	// and then jump to name_window
	QObject::connect(start_button, SIGNAL(clicked()), SLOT(NameWindow()));
	v_welcome->addLayout(h_welcome);
	v_welcome->addWidget(quit_button);
	//show the window
	welcome_window->setWindowTitle("Welcome Window");
	welcome_window->show();

// Input Name Window
	// initialzie variable
	name_window = new QWidget;
	ask_input_name = new QLabel("Please enter players' names!");
	karmaFont.setBold(true);
	karmaFont.setPointSize(15);
	ask_input_name->setFont(karmaFont);
	h_name = new QHBoxLayout;
	v_name = new QVBoxLayout;
	confirm_button = new QPushButton("Confirm and Start");
	// when press the confirm_button, close the name_window
	// and jump to the main_board
	QObject::connect(confirm_button, SIGNAL(clicked()), SLOT(MainWindow()));

// Main Board
	// initialize variable
	main_window = new QWidget;
	v_main = new QVBoxLayout;
	g_board = new QGridLayout;
	h_main = new QHBoxLayout;

	int size = _board->get_x();
	board_button = new QPushButton**[size];
	pass_button = new QPushButton("Pass");
	pass_button->setStyleSheet("QPushButton{background: orange}");
	exchange_confirm_button = new QPushButton("Confirm Exchange");
	exchange_confirm_button->setStyleSheet("QPushButton{background: lightYellow}");
	to_score_board = new QPushButton("Score Board");
	// connect the pass_button with Pass function
	QObject::connect(pass_button, SIGNAL(clicked()), SLOT(PASS()));
	// connect the exchange_confirm_button with Exchange();
	QObject::connect(exchange_confirm_button, SIGNAL(clicked()), SLOT(Exchange()));
	// connect the to_score_board button with ScoreBoard();
	QObject::connect(to_score_board, SIGNAL(clicked()), SLOT(ScoreBoard()));
	for(int i = 0; i < size; i++){
		board_button[i] = new QPushButton*[size];
		for(int j = 0; j < size; j++){
			if(_board->getLetter(i,j) == '*'){
				board_button[i][j] = new QPushButton("SP");
				board_button[i][j]->setStyleSheet("QPushButton {background: red; min-width: 25px; max-width: 25px;font-weight: bold}");
			}
			else if(_board->getLetter(i,j) == 't'){
				board_button[i][j] = new QPushButton("3W");
				board_button[i][j]->setStyleSheet("QPushButton {background: lightPink; min-width: 25px; max-width: 25px}");
			}
			else if(_board->getLetter(i,j) == 'd'){
				board_button[i][j] = new QPushButton("2W");
				board_button[i][j]->setStyleSheet("QPushButton {background: orange; min-width: 25px; max-width: 25px}");
			}
			else if(_board->getLetter(i,j) == '2'){
				board_button[i][j] = new QPushButton("2L");
				board_button[i][j]->setStyleSheet("QPushButton {background: lightGreen; min-width: 25px; max-width: 25px}");
			}
			else if(_board->getLetter(i,j) == '3'){
				board_button[i][j] = new QPushButton("3L");
				board_button[i][j]->setStyleSheet("QPushButton {background: lightBlue; min-width: 25px; max-width: 25px}");
			}
			else{
				board_button[i][j] = new QPushButton("");
				board_button[i][j]->setStyleSheet("QPushButton {background: white; min-width: 25px; max-width: 25px}");
			}
			g_board->addWidget(board_button[i][j],i+1,j+1);
			QObject::connect(board_button[i][j], SIGNAL(clicked()), this, SLOT(Place()));
		}
	}
	moves = new QComboBox;
	player_input = new QLineEdit;

	tiles_on_hand = new QLabel("");
	inform_whos_turn= new QLabel("");
	player_curr_score = new QLabel("");
	input_your_word = new QLabel("Please input your word: ");
	
	tiles_want_exchange = new QLabel("Tiles you want to exchange:");
	tiles_want_exchange->setStyleSheet("QLabel{font-weight: bold; font: 13pt}");
	tiles_want_exchange->setAlignment(Qt::AlignHCenter);
	tiles_want_exchange->setFixedHeight(30);
	
	h_place = new QRadioButton("Horizontal");
	v_place = new QRadioButton("Vertical");
	h_sub_v_main = new QHBoxLayout;

	// When switch content in combo box, display different left-hand side  content
	// hide vertical and horizontal radio box, display new label saying "Tiles you want to Exchange"
	// display new button saying "confirm"
	QObject::connect(moves, SIGNAL(currentIndexChanged(const QString&)), SLOT(SwitchExchangePlace(const QString&)));

// Score Board
	// initalize variable
	score_board_window = new QWidget;
	title = new QLabel("Score Board\n---------------------------------");
	ok = new QPushButton("GotCha!");
	QObject::connect(ok, SIGNAL(clicked()), this, SLOT(ExitScoreBoard()));
	v_score_board = new QVBoxLayout;
}

void Game::NameWindow(){
	// close the welcome_window
	welcome_window->close();
	// set up the name_window
	name_window->setLayout(v_name);
	v_name->addWidget(ask_input_name);
	num_player = choose_player_num->currentText().toInt();
	for (int i = 0; i < num_player; ++i)
	{	
		// initialize the input_name[]
		QLineEdit* temp_line_edit = new QLineEdit();
		input_name.push_back(temp_line_edit);
		// initialize the player_index label
		QString s = QString::number(i+1);
		QString qstr = QString::fromStdString("Player ");
		qstr += s;
		QLabel *temp_label = new QLabel(qstr);
		player_index.push_back(temp_label);
	}
	for (int i = 0; i < num_player; ++i)
	{
		v_name->addWidget(player_index[i]);
		v_name->addWidget(input_name[i]);
	}
	v_name->addWidget(confirm_button);
	name_window->setWindowTitle("Name Window");
	name_window->show();
	
}

void Game::MainWindow(){
	// check if player enter all their names
	for (int i = 0; i < num_player; ++i)
	{
		if (input_name[i]->text().isEmpty())
		{
			QMessageBox msgBox;
			msgBox.setWindowTitle("Error");
			msgBox.setText("Empty Input");
			msgBox.setInformativeText("Please enter all players' names");
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.exec();
			return;
		}
	}
	// now everything is fine, store all players name in to vector players
	for (int i = 0; i < num_player; ++i)
	{
		addPlayer(input_name[i]->text().toStdString());
	}

	// this part is for score board
	score_board_window->setLayout(v_score_board);
	v_score_board->addWidget(title);
	for (int i = 0; i < num_player; ++i)
	{	
		QLabel *temp = new QLabel("");
		stringstream ss;
		ss << players[i]->getScore();
		temp->setText(QString::fromStdString(players[i]->getName() + ": " + ss.str()));
		print_player_score.push_back(temp);
	}
	for (int i = 0; i < num_player; ++i)
	{
		v_score_board->addWidget(print_player_score[i]);
	}
	v_score_board->addWidget(ok);

	// set the content of the inform_whos_turn
	inform_whos_turn->setText(QString::fromStdString("It's Player " + players[total_turns%num_player]->getName() + "'s Turn!"));
	QFont karmaFont; // set the font of inform_whos_turn;
	karmaFont.setBold(true);
	karmaFont.setPointSize(17);
	inform_whos_turn->setFont(karmaFont);
	inform_whos_turn->setFixedHeight(30);
	inform_whos_turn->setAlignment(Qt::AlignHCenter);
	inform_whos_turn->setStyleSheet("QLabel { color : blue; }");
	// set the content of the player_curr_score
	stringstream ss;
	ss << players[total_turns%num_player]->getScore();
	player_curr_score->setText(QString::fromStdString("Your Current Score: " + ss.str()));
	QFont scoreFont; // set the font of player_curr_score;
	scoreFont.setPointSize(14);
	player_curr_score->setFont(scoreFont);
	player_curr_score->setAlignment(Qt::AlignHCenter);
	player_curr_score->setStyleSheet("QLabel { color : green; }");
	// set the content of the tiles_on_hand label
	tiles_on_hand->setText(QString::fromStdString("Tiles on your hand: \n" + players[total_turns%num_player]->stringTiles()));
	QFont tilesFont;
	tilesFont.setPointSize(14);
	tilesFont.setBold(true);
	tiles_on_hand->setFont(tilesFont);
	tiles_on_hand->setAlignment(Qt::AlignCenter);
	tiles_on_hand->setStyleSheet("QLabel { color : purple; }");
	// set the font of input_your_label
	input_your_word->setStyleSheet("QLabel{font-weight: bold; font: 13pt}");


	// close the Name Window
	name_window->close();
	// set up the main window
	main_window->setLayout(h_main);
	h_main->addLayout(g_board);
	h_main->addLayout(v_main);

	v_main->addWidget(inform_whos_turn);
	v_main->addWidget(player_curr_score);
	v_main->addWidget(to_score_board);
	to_score_board->setStyleSheet("QPushButton{background: lightBlue}");
	
	v_main->addWidget(tiles_on_hand);
	
	moves->addItem("Place");
	moves->addItem("Exchange");

	v_main->addWidget(moves);
	v_main->addWidget(h_place);
	v_main->addWidget(v_place);
	
	h_sub_v_main->addWidget(input_your_word);
	v_main->addWidget(tiles_want_exchange);
	tiles_want_exchange->hide(); // first hide this label
	v_main->addLayout(h_sub_v_main);
	h_sub_v_main->addWidget(player_input);
	v_main->addWidget(exchange_confirm_button);
	exchange_confirm_button->hide(); // hide this button first
	v_main->addWidget(pass_button);
	main_window->setWindowTitle("Main Board");
	main_window->show();

}

/*
Pass Slots:
	re-set the inform_whos_turn label to next player's name
	re-set the player's score
	re-set the player's tiles on hand;
	make players' pass as true;
	only used after exchange and pass function
*/
void Game::Pass(){
	players[total_turns%num_player]->passTurn();
	total_turns++;
	if (gameEnd()){
		// game end
		QMessageBox msgBox;
		msgBox.setText("Game End!");
		msgBox.setInformativeText(QString::fromStdString(findWinner()));
		msgBox.setStandardButtons(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret > 0)
		{
			ScoreBoard();
			
		}
	}
	// reset the labels
	inform_whos_turn->setText(QString::fromStdString("It's Player " + players[total_turns%num_player]->getName() + "'s Turn!"));
	stringstream ss;
	ss << players[total_turns%num_player]->getScore();
	player_curr_score->setText(QString::fromStdString("Your Current Score: " + ss.str()));
	tiles_on_hand->setText(QString::fromStdString("Tiles on your hand: \n" + players[total_turns%num_player]->stringTiles()));
}

// dont change players' pass property
void Game::Pass_for_place(){
	total_turns++;
	clearPass();
	if (gameEnd()){
		// game end
		QMessageBox msgBox;
		msgBox.setText("Game End!");
		msgBox.setInformativeText(QString::fromStdString(findWinner()));
		msgBox.setStandardButtons(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret > 0)
		{
			ScoreBoard();
		}
	}
	// reset the labels
	inform_whos_turn->setText(QString::fromStdString("It's Player " + players[total_turns%num_player]->getName() + "'s Turn!"));
	stringstream ss;
	ss << players[total_turns%num_player]->getScore();
	player_curr_score->setText(QString::fromStdString("Your Current Score: " + ss.str()));
	tiles_on_hand->setText(QString::fromStdString("Tiles on your hand: \n" + players[total_turns%num_player]->stringTiles()));
}

void Game::PASS(){
	QMessageBox msgBox;
	msgBox.setText("Are you sure to PASS?");
	msgBox.setStandardButtons(QMessageBox::Yes|QMessageBox::No);
	int ret = msgBox.exec();
	if (ret == QMessageBox::Yes){
		player_input->clear();
		Pass();
	}
	else return;
}

void Game::Exchange(){
	QString qstr = player_input->text();
	if(qstr.isEmpty()){
		QMessageBox msgBox;
		msgBox.setText("Empty input, try again!");
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.setDefaultButton(QMessageBox::Yes);
		msgBox.exec();
	}
	else if (players[total_turns%num_player]->exchange(qstr.toStdString(), *_bag))
	{
		QMessageBox msgBox;
		msgBox.setText("Successfully Exchange!");
		msgBox.setInformativeText("Move to Next Player");
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		if (ret > 0){
			qstr.clear();
			player_input->clear();
			Pass();
		}
	}
	else{
		QMessageBox msgBox;
		msgBox.setText("Fail to exchange, tiles not matched");
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.setDefaultButton(QMessageBox::Yes);
		msgBox.exec();
	}
}

void Game::SwitchExchangePlace(const QString& qstr){
	if (qstr.toStdString() == "Place"){
		tiles_want_exchange->hide();
		exchange_confirm_button->hide();
		input_your_word->show();
		h_place->show();
 		v_place->show();
	}
	else if(qstr.toStdString() == "Exchange"){
		tiles_want_exchange->show();
		exchange_confirm_button->show();
		input_your_word->hide();
		h_place->hide();
 		v_place->hide();
	}
}

void Game::Place(){
	QString qstr = player_input->text();
	int size = _board->get_x();
	
	QPushButton *called = (QPushButton*) QObject::sender();
	int i = 0, j = 0;
	for(int x = 0; x < size; x++){
		for (int y = 0; y < size; y++){
			if (board_button[x][y] == called){
				i = x;
				j = y;
			}
		}
	}


	if (h_place->isChecked())
	{
		if (players[total_turns%num_player]->place('-', i, j, qstr.toStdString(), *_board, *_bag, *_dictionary)) // current player
		{
			QMessageBox msgBox;
			msgBox.setText("Successfully Place!");
			msgBox.setInformativeText("Move to Next Player");
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setDefaultButton(QMessageBox::Yes);
			int ret = msgBox.exec();
			if (ret > 0){
				qstr.clear();
				player_input->clear();
				Pass_for_place();
			}
			refreshBoardButton();
		}
		else{
			QMessageBox msgBox;
			msgBox.setText("Your place movement is not valid, please try again");
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setDefaultButton(QMessageBox::Yes);
			int ret = msgBox.exec();
			if (ret > 0){
				qstr.clear();
				player_input->clear();
				return;
			}
		}
	}
	else if (v_place->isChecked()){
		if (players[total_turns%num_player]->place('|', i, j, qstr.toStdString(), *_board, *_bag, *_dictionary)) // current player
		{
			QMessageBox msgBox;
			msgBox.setText("Successfully Place!");
			msgBox.setInformativeText("Move to Next Player");
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setDefaultButton(QMessageBox::Yes);
			int ret = msgBox.exec();
			if (ret > 0){
				qstr.clear();
				player_input->clear();
				Pass_for_place();
			}
			refreshBoardButton();
		}
		else{
			QMessageBox msgBox;
			msgBox.setText("Your place movement is not valid, please try again");
			msgBox.setStandardButtons(QMessageBox::Yes);
			msgBox.setDefaultButton(QMessageBox::Yes);
			int ret = msgBox.exec();
			if (ret > 0){
				qstr.clear();
				player_input->clear();
				return;
			}
		}

	}
	
}

void Game::ScoreBoard(){
	for (int i = 0; i < num_player; ++i)
	{	
		stringstream ss;
		ss << players[i]->getScore();
		print_player_score[i]->setText(QString::fromStdString(players[i]->getName() + ": " + ss.str()));
	}
	score_board_window->show();
}

void Game::ExitScoreBoard(){
	score_board_window->close();
}

// non-slot function
void Game::addPlayer(string name){
	Player* newPlayer = new Player(name, *_bag, max_hand_tiles);
    players.push_back(newPlayer);
}

void Game::printScores(){
    cout << "------ScoreBoard------" << endl;
    for (unsigned int i = 0; i < players.size(); i++) {
        cout << players[i]->getName() << ": " <<players[i]->getScore() << endl;
    }
    cout << endl;
}

void Game::refreshBoardButton(){
	for (int i = 0; i < _board->get_x(); ++i)
	{
		for (int j = 0; j < _board->get_y(); ++j)
		{
			if(_board->getLetter(i,j) == '*'){
				board_button[i][j]->setText(QString::fromStdString("SP"));
			}
			else if(_board->getLetter(i,j) == 't'){
				board_button[i][j]->setText(QString::fromStdString("3W"));
			}
			else if(_board->getLetter(i,j) == 'd'){
				board_button[i][j]->setText(QString::fromStdString("2W"));
			}
			else if(_board->getLetter(i,j) == '2'){
				board_button[i][j]->setText(QString::fromStdString("2L"));
			}
			else if(_board->getLetter(i,j) == '3'){
				board_button[i][j]->setText(QString::fromStdString("3L"));
			}
			else if(_board->getLetter(i,j) == '.'){
				board_button[i][j]->setText("");
			}
			else{
				board_button[i][j]->setText(QString::fromStdString(string(1, _board->getLetter(i,j))));
				board_button[i][j]->setStyleSheet("QPushButton {background: light yellow; min-width: 25px; max-width: 25px; font-weight: bold}");
			}
		}
	}
}

bool Game::allPass(){
	for (unsigned int i = 0; i < players.size(); ++i) {
        if (!players[i]->if_pass()) {
            return false;
        }
    }
    return true;
}

void Game::clearPass(){
    for (unsigned int i = 0; i < players.size(); ++i) {
        players[i]->resetPass();
    }
}

bool Game::gameEnd(){
	 if (allPass()) {
        cal_score();
        return true;
    }
    
    
    if (_bag->tilesRemaining() == 0) {
        for (unsigned int i= 0; i < players.size(); i++) {
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
    bool useAllTile = false;
    int winnerIndex = 0;
    for (int i = 0; i < num_player; i++) {
        if (players[i]->num_tile_remain() == 0) {
            useAllTile = true;
            winnerIndex = i;
        }
    }
    if (useAllTile == true) {
        int total_minus_score = 0;
        for (int i = 0; i < num_player; ++i) {
            if (i == winnerIndex) {
                players[i]->setScore(players[i]->getScore()+total_minus_score);
            }
            else{
                int socre_lose = players[i]->final_score();
                total_minus_score += socre_lose;
            }
        }
    }
}

string Game::findWinner(){
	vector<int> winner_indexs;
	int max_score = -1;
	string reval = "";
	for (int i = 0; i < num_player; ++i)
	{
		if (players[i]->getScore() >= max_score)
		{
			max_score = players[i]->getScore();
		}
	}
	for (int i = 0; i < num_player; ++i)
	{
		if (players[i]->getScore() == max_score)
		{
			winner_indexs.push_back(i);
		}
	}
	for (unsigned int i = 0; i < winner_indexs.size(); ++i)
	{	
		stringstream ss;
		ss << players[winner_indexs[i]]->getScore();
		reval = reval + players[winner_indexs[i]]->getName() + " Win! " + "Score: " + ss.str() + "\n";
	}
	return reval;
}





int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	Game game(&app);
	return app.exec();
}

