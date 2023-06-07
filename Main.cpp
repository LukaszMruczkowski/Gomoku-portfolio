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

int main()
{
	string file_name = "Save file.txt";
	int menu_choice = 0;
	int mode_choice = 0;
	int round = 0;
	bool continue_case = false;
	goban table;
	while (menu_choice != 3)
	{
		if (continue_case == false)
		{
			menu(is_saved(file_name));
			if (is_saved(file_name))
			{
				int list = 4; //Number of choices
				menu_choice = N_int_check(list);
			}
			else
			{
				int list = 3;
				menu_choice = N_int_check(list);
			}
			if (menu_choice == 1)
			{
				round = 0;
				//Setting all board fields to empty in order to start new game
				table.reset();
				cout << "GAME MODE\n";
				cout << "1. Player vs Player\n";
				cout << "2. Player vs Computer\n";
				int list = 2;
				mode_choice = N_int_check(list);
			}
		}
		switch (menu_choice)
		{
		case 1:
		{
			if (mode_choice == 1)
			{
				bool running = true;
				person white('W'), black('B');
				while (running)
				{
					string name;
					if (round % 2 == 0) {
						name = "White's";
					}
					else {
						name = "Black's";
					}
					cout << name << " turn\n";
					if (round % 2 == 0) {
						running = human_turn(table, white);
					}
					else {
						running = human_turn(table, black);
					}
					if (running)
					{
						++round;
					}
				}
				save_game(table, round, mode_choice);
			}
			else if (mode_choice == 2)
			{
				bool running = true;
				//Random selection which stones color player and computer will have
				std::random_device rd;
				std::mt19937 generator(rd());
				std::uniform_int_distribution<int> distribution(0, 1);
				int random_number = distribution(generator);
				//Game when PERSON has white stones and starts
				if (random_number == 0) {
					person human('W');
					computer pc('B');
					while (running)
					{
						string name;
						if (round % 2 == 0) {
							name = "(White) Your";
						}
						else {
							name = "(Black) Computer";
						}
						cout << name << " turn\n";
						if (round % 2 == 0) {
							running = human_turn(table, human);
						}
						else {
							running = pc_turn(table, pc);
						}
						if (running)
						{
							++round;
						}
					}
					save_game(table, round, mode_choice);
				}
				//Game when COMPUTER has white stones and starts
				else {
					person human('B');
					computer pc('W');
					while (running)
					{
						string name;
						if (round % 2 != 0) {
							name = "(Black) Your";
						}
						else {
							name = "(White) Computer";
						}
						cout << name << " turn\n";
						if (round % 2 != 0) {
							running = human_turn(table, human);
						}
						else {
							running = pc_turn(table, pc);
						}
						if (running)
						{
							++round;
						}
					}
					save_game(table, round, mode_choice);
				}
			}
			//After quitting game continue_case flag is down to print game menu for another game
			continue_case = false;
			break;
		}
		case 2:
		{
			cout << "On the Goban board, which consists of 225 fields arranged in a 15x15\ngrid, players aim to place 5 stones of their chosen color (black or white)\nin a continuous line, whether vertically, horizontally, or diagonally.\n\n\n";
			break;
		}
		case 3:
		{
			cout << "Game has been closed\n";
			return 0;
		}
		case 4:
		{
			//If player wants to continue saved game board is loads, continue_case flag is up and menu_choice is assigned to switch case 1
			load_game(table, round, mode_choice);
			continue_case = true;
			menu_choice = 1;
			break;
		}
		}
	}
}