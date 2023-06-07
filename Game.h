#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <string>
#include <limits>
#include <ios>
#include <random>
#include <cctype>
#include <conio.h>
#include <fstream>

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

//Class representing gomoku game board
class goban {
	//Array to illustrate positions of all stones which players place on a board in this game
	BoardType board;
public:
	void print_board();
	//Method to check if and who won
	bool win_check(int x, int y, char color);
	BoardType& board_getter();
	void board_setter(int x, int y, char c);
	//Sets board to default empty state
	void reset();
	goban();
	friend class player;
};
//Base class representing any player of gomoku game
class player {
protected:
	//Color of stones each player will use
	char stone_color;
	//Way of placing stone on a board (Goban) for person or computer
	virtual bool place_stone(goban& g) = 0;
	//Check if placing a stone on set position is possible
	bool position_possible(goban& g, int x, int y);
public:
	player(char c);
};
//Derived class representing human player
class person : public player {
public:
	person(char c);
	//Setting desired field's coordinates and placing person stone there, if 'c' is clicked during row choice quitting game
	bool place_stone(goban& g) override;
};
//Derived class representing artificial computer player
class computer : public player {
public:
	computer(char c);
	//Setting random coordinates to x and y and placing computer stone on a board in drawn field
	bool place_stone(goban& g) override;
};
//Input validating for any natural integer range
int N_int_check(int range);
//Interface to communicate with player
void menu(bool is_saved);
//Checks if save file exists
bool is_saved(string& file_name);
//Turn process for human returns false if player wants to quit
bool human_turn(goban& g, person& p);
//Turn process for computer
bool pc_turn(goban& g, computer& c);
//Saves game if desired
void save_game(goban& g, int round, int mode_choice);
//Loads last saved round 
void load_game(goban& g, int& round, int& mode_choice);
#endif