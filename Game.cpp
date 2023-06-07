#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include <random>
#include <cctype>
#include <conio.h>
#include <fstream>

#include "Game.h"

#define SIZE 15
#define LINE_LENGTH 5

using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::numeric_limits;
using std::streamsize;
using std::random_device;
using Intdist = std::uniform_int_distribution<int>;
using std::fstream;
using std::getline;
//Designed type to represent char 2D arrays
using BoardType = char[SIZE][SIZE];

int N_int_check(int range);

void goban::print_board() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			cout << board[i][j] << " ";
		}
		cout << endl;
	}
	}
//Method to check if and who won
bool goban::win_check(int x, int y, char color) {
	//Counts quantity of horizontal placed stones, set to 1 because middle stone is taken into account already
	int horizontal_count = 1;
	//Check if last placed stone made a horizontal 5 stones long line
	//From the right side
	for (int field_counter = 0, column = y + 1; field_counter < LINE_LENGTH - 1 && column < SIZE; ++field_counter, ++column)
	{
		if (board[x][column] == color) {
			++horizontal_count;
		}
	}
	//From the left side
	for (int field_counter = 0, column = y - 1; field_counter < LINE_LENGTH - 1 && column >= 0; ++field_counter, --column)
	{
		if (board[x][column] == color) {
			++horizontal_count;
		}
	}
	//Counts quantity of vertical placed stones, set to 1 because middle stone is taken into account already
	int vertical_cout = 1;
	//Check if last placed stone made a vertical 5 stones long line
	//From the top
	for (int field_counter = 0, row = x - 1; field_counter < LINE_LENGTH - 1 && row >= 0; ++field_counter, --row)
	{
		if (board[row][y] == color) {
			++vertical_cout;
		}
	}
	//From the bottom
	for (int field_counter = 0, row = x + 1; field_counter < LINE_LENGTH - 1 && row < SIZE; ++field_counter, ++row)
	{
		if (board[row][y] == color) {
			++vertical_cout;
		}
	}
	//Counts quantity of left diagonal(\) placed stones, set to 1 because middle stone is taken into account already
	int left_diagonal_count = 1;
	//Check if last placed stone made a diagonal(\) 5 stones long line
	//From the top
	for (int field_counter = 0, row = x - 1, column = y - 1; field_counter < LINE_LENGTH - 1 && row >= 0 && column >= 0; ++field_counter, --row, --column)
	{
		if (board[row][column] == color) {
			++left_diagonal_count;
		}
	}
	//From the bottom
	for (int field_counter = 0, row = x + 1, column = y + 1; field_counter < LINE_LENGTH - 1 && row < SIZE && column < SIZE; ++field_counter, ++row, ++column)
	{
		if (board[row][column] == color) {
			++left_diagonal_count;
		}
	}
	//Counts quantity of right diagonal(/) placed stones, set to 1 because middle stone is taken into account already
	int right_diagonal_count = 1;
	//Check if last placed stone made a diagonal(/) 5 stones long line
	//From the top
	for (int field_counter = 0, row = x - 1, column = y + 1; field_counter < LINE_LENGTH - 1 && row >= 0 && column < SIZE; ++field_counter, --row, ++column)
	{
		if (board[row][column] == color) {
			++right_diagonal_count;
		}
	}
	//From the bottom
	for (int field_counter = 0, row = x + 1, column = y - 1; field_counter < LINE_LENGTH - 1 && row < SIZE && column >= 0; ++field_counter, ++row, --column)
	{
		if (board[row][column] == color) {
			++right_diagonal_count;
		}
	}

	if (horizontal_count == LINE_LENGTH || vertical_cout == LINE_LENGTH || left_diagonal_count == LINE_LENGTH || right_diagonal_count == LINE_LENGTH) {
		return true;
	}
	else {
		return false;
	}
}
BoardType& goban::board_getter() { return board; }
void goban::board_setter(int x, int y, char c) { board[x][y] = c; };
//Sets board to default empty state
void goban::reset() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = '0';
		}
	}
}
goban::goban() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			board[i][j] = '0';
		}
	}
}

player::player(char c) { stone_color = c; }
//Check if placing a stone on set position is possible
bool player::position_possible(goban& g, int x, int y) {
	char position = g.board[x][y];
	if (position == '0') {
		return true;
	}
	else {
		return false;
	}
}

person::person(char c) : player(c) {};
//Setting desired field's coordinates and placing person stone there, if 'c' is clicked during row choice quitting game
bool person::place_stone(goban& g) 
{
	bool win = false;
	string input;
	int x = 0;
	int y = 0;
	//Checking if user presses 'c' to exit game, if not assigning proper value to x coordinate
	while (true)
	{
		cout << "Row number (press 'c' to exit the game): ";
		getline(cin, input);
		if ((input == "c" || input == "C")) {
			cin.putback(input[0]);
			return false;
		}
		else if ((isdigit(input[0]) != 0 && isdigit(input[1]) != 0 && input.length() == 2) || (input.length() == 1 && (isdigit(input[0]) != 0))) {
			x = stoi(input);
		}
		else {
			cout << "Please, choose a proper number\n";
		}
		cout << "Column number: ";
		y = N_int_check(SIZE);
		if (position_possible(g, x - 1, y - 1) == true) {
			g.board_setter(x - 1, y - 1, stone_color);
			break;
		}
		else {
			cout << "This field is occupied\nTry again\n";
		}
	}
	win = g.win_check(x - 1, y - 1, stone_color);
	if (win && stone_color == 'W') {
		cout << "!!!WHITE WON!!!\n";
		g.print_board();
	}
	else if (win && stone_color == 'B') {
		cout << "!!!BLACK WON!!!\n";
		g.print_board();
	}
	return win;
}

computer::computer(char c) : player(c) {}
//Setting random coordinates to x and y and placing computer stone on a board in drawn field
bool computer::place_stone(goban& g)
{
	bool win = false;
	int x = 0;
	int y = 0;
	std::random_device rd;
	std::mt19937 generator(rd());
	std::uniform_int_distribution<int> distribution(0, 14);
	do {
		x = distribution(generator);
		y = distribution(generator);

		if (position_possible(g, x, y)) {
			g.board_setter(x, y, stone_color);
			break;
		}
	} while (true);
	win = g.win_check(x - 1, y - 1, stone_color);
	if (win && stone_color == 'W') {
		cout << "!!!WHITE WON!!!\n";
		g.print_board();
	}
	else if (win && stone_color == 'B') {
		cout << "!!!BLACK WON!!!\n";
		g.print_board();
	}
	return win;
}

//Input validating for any natural integer range
int N_int_check(int range)
{
	int choice = 0;
	bool is_ok = true;
	do {
		if (cin.rdbuf()->in_avail() == 0) {
			cin >> choice;
		}
		if (choice >= 1 && choice <= range) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			is_ok = true;
		}
		else {
			is_ok = false;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Please, choose a proper number\n";
		}
	} while (is_ok == false);
	return choice;
}
//Interface to communicate with player
void menu(bool is_saved)
{
	cout << "HELLO, THIS IS GOMOKU\nPRESS DESIRED NUMBER TO CHOOSE OPTION\n";
	cout << "\nMENU\n";
	if (is_saved == true) {
		cout << "1. New Game\n";
		cout << "2. Rules\n";
		cout << "3. Exit\n";
		cout << "4. Continue\n";
	}
	else {
		cout << "1. New Game\n";
		cout << "2. Rules\n";
		cout << "3. Exit\n";
	}
}
//Checks if save file exists
bool is_saved(string& file_name)
{
	fstream file(file_name);
	return file.good();
}
//Turn process for human returns false if player wants to quit
bool human_turn(goban& g, person& p)
{
	bool win = false;
	g.print_board();
	win = p.place_stone(g);
	if (cin.rdbuf()->in_avail() > 0) {
		if (cin.get() == 'c' || cin.get() == 'C') {
			return false;
		}
	}
	if (win) {
		return false;
	}
	return true;
}
//Turn process for computer
bool pc_turn(goban& g, computer& c)
{
	bool win = false;
	bool wait = true;
	win = c.place_stone(g);
	g.print_board();
	cout << "Press ENTER to continue\n";
	while (wait)
	{
		if (_kbhit())
		{
			char key = _getch();
			if (key == '\r') { // Check for Enter key (carriage return)
				wait = false;
			}
		}
	}
	if (win) {
		return false;
	}
	return true;
}
//Saves game if desired
void save_game(goban& g, int round, int mode_choice)
{
	int choice = 0;
	cout << "DO YOU WANT TO SAVE THE GAME?\n";
	cout << "1.YES\t2.NO\n";
	int list = 2;
	choice = N_int_check(list);
	if (choice == 1)
	{
		fstream file("Save file.txt", std::ios::out);
		if (file.is_open())
		{
			//Variable that holds current situation on a board
			BoardType& current_board = g.board_getter();
			for (int i = 0; i < SIZE; ++i) {
				for (int j = 0; j < SIZE; ++j) {
					file << current_board[i][j];
				}
				file << endl;
			}
			file << round << endl;
			file << mode_choice;
		}
	}
	else {
		g.reset();
	}
}
//Loads last saved round 
void load_game(goban& g, int& round, int& mode_choice)
{
	fstream file("Save file.txt", std::ios::in);
	if (file.is_open())
	{
		string line;
		char field = '\0';
		for (int i = 0; i < SIZE; ++i) {
			for (int j = 0; j < SIZE; ++j) {
				file.get(field);
				if (field != '\n') {
					g.board_setter(i, j, field);
				}
				else {
					--j;
				}
			}
		}
		getline(file, line);
		file >> round;
		getline(file, line);
		file >> mode_choice;
	}
}
