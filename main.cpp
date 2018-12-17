#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
#include "conio.h"
using namespace std;

const char player = 'o';
const char border = '#';
const int x = 10;
const int y = 10;


void printWorld(char world[y][x]){
	// Print in a grid like effect looping through the array's elements
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < x; j++) {
			cout << "   " << world[i][j] << "   ";
		}
		cout << endl << endl; // for Grid Like effect
	}
	};
void addBorders(char world[y][x]){
	// Horinzontal axis
	for (int i = 0; i < x; i++) {
		world[0][i] = border;
		world[y-1][i] = border; // the number of elements is 10 , but keep in mind its always n-1
	}
	// Vertical Axis
	for (int k = 0; k < (x-1); k++) {
		world[k][0] = border;
		world[k][y-1] = border;
	};
	// Fill the rest with spaces
	for (int i = 1; i < (x-1); i++) {
		for (int j = 1; j < (x-1); j++) {
			world[i][j] = ' ';
		}
	}
};
void moveCharacter (char world[x][y], int &move ,int movePrevious, bool &collision ,string position) {

	int moveNext;// Used to see the next possible move and detect wether it's possible

	movePrevious = move;// save the orginal 

	if (position == "Up") {
		moveNext = move - 1;
		move--; // Subtracts so it can move up
	}
	else if (position == "Down") {
		moveNext = move + 1;
		move++; // adds so it can move down
	}

	if ((world[moveNext][1]) != (border)) { // check before moving it make sure it doesn't hit any borders
		world[move][1] = player; // move player
		world[movePrevious][1] = ' '; // Replace previous move with a space

		collision = false;
	}
	else {
		collision = true;
	}

};

void generateBorders(char world[y][x], int &movePosition) {

	// bug: when called keeps generating new values, rather then keeping
	// solution: create a seperate table, pass it by value(&) create borders based on that

	srand(time(0));
	int movePrevious;
	int random = rand() % 2 + 1; // Decides wether it should be on top or botton, bottom =2, top = 1
	int amplitude = rand() % (x-3) + 1; // generate numbers from the top to the bottom, given the bottom and top are filled
	// x-3 is used considering bottom is filled with borders and it will be too much for the player

	movePrevious = movePosition;// save the orginal 
	movePosition--;

	cout << "Amplitude " << amplitude << endl;
	cout << "movePosition: " << movePosition << endl;
	cout << "movePrevious: " << movePrevious << endl;

	if (random == 1) {
		cout << "Top" << endl;
		for (int i = 1; i <= amplitude; i++) {
			world[i][movePosition] = '-';
			world[i][movePrevious] = ' ';
			// x-2 is used because the bottom is filled
		}
	}
	else if (random == 2) {
		cout << "Bottom" << endl;
		for (int i = (x-3) ; i >= amplitude; i--) {
			world[i][movePosition] = '-';
			world[i][movePrevious] = ' ';
		}
	}

}
void controlCharacter (char world[y][x], char player) {
	int key;
	int moveStart = y / 2; // Always start in the middle
	int moveNext = 0; // Subtracts or adds one to find the upper elment
	int movePrevious = 0; // considering move is always changing this keeps a previous copy of it
	int movePosition = (x - 2);
	bool borderTouched = false;

	while (borderTouched != true) { //loop to keep checking key

		if ( _kbhit() ) { // Listens if a key is pressed and returns true

			key = _getch(); //saves the key

			if ((key) == char(32)) { // 32 is space
				moveCharacter(world, moveStart, movePrevious, borderTouched, "Up");
			}
		}
			else  {
				moveCharacter(world, moveStart, movePrevious, borderTouched, "Down");
			}

		generateBorders(world, movePosition);

		printWorld(world);
		Sleep(500);
		// system("cls"); //cleans the system
	}
cout << "End" << endl;
}
int main() {
	char world[y][x];

	addBorders(world);
	printWorld(world);
	controlCharacter(world, player);

	system("Pause");
	return 0;
}
