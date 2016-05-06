#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include "minesweeper.h"
using namespace std;


/* structure to receive the user input and pass it to processInput() for game play 
*
*/
struct input_t{
	char operation;			// 'm'= mark,'u' = unmark, 'r' = reveal 
	int  row;
	int  column;
};


void playTime(minesweeper& play);
void viewStatistics();
void loadGameFromFile();
input_t loadGameFromProgram();
input_t getUserInput( );
void processInput(minesweeper& play, input_t input);


/* Global variables that read the minefield and number of rows and columns
* the minesweeper object is constructed using these values
*/
vector<vector<int> > mineField;
int rows=0;
int columns=0;
int mines=0;
minesweeper mField;


/*
 * 
 */
int main() {
     char option;
     /* This will be your main GUI loop. You should query the user for  
     *  starting a game, or quitting the program. You should
     * 	handle user input either succinctly or by making a call to a helper method
     *	to perform the desired operations.
     */
     while (1) {
		// TODO - Ask the user with options to perform either Starting a game, Viewing
		// statistics, Quitting the program,  and any 
		// other functionality you feel is necessary.
		// Each iteration here is one round of the game.
	
		// somewhere you need to create a minesweeper game object first if the 
		// user decides to start a new round of game, e.g., 
		// minesweeper play();
		 cout << "Please enter your option, (p) for play and (q) for quit: ";
		 cin >> option;
		 if (option == 'p'){
			 cout << "Please enter how to play the game, (h) for human input and (f) for file input: ";
			 cin >> option;
			 if (option == 'h'){
				 input_t firstInput = loadGameFromProgram();
				 int xpos, ypos;
				 for (int i = 0; i < mines; ++i){
					 xpos = rand() % rows;
					 ypos = rand() % columns;
					 while (mineField[xpos][ypos] == 1 || (firstInput.row == xpos && firstInput.column == ypos)){
						 xpos = rand() % rows;
						 ypos = rand() % columns;
					 }
					 mineField[xpos][ypos] = 1;
				 }
				 mField = minesweeper(columns, rows, mines, mineField);
			 }
			 else if(option == 'f'){
				 loadGameFromFile();
			 }
			 else{
				 cout << "Wrong Input, restart the game...";
				 continue;
			 }
		 }
		 else if (option == 'q'){
			 cout << "Now Exit The Game..." << endl;
			 break;
		 }
		 else{
			 cout << "Wrong Option!" << endl;
			 break;
		 }
		 playTime(mField);
	}  
    return 0;
}


/* This method is used to populate the minefield by reading the input file.
 *  Ensure that the input file is according to the specified format.
*/
void loadGameFromFile(){
	cout << "Please Enter the filename: ";
	string fileName;
	cin >> fileName;
	ifstream infile(fileName, ios::in);
	infile >> rows >> columns >> mines;
	mineField = vector<vector<int>>(rows, vector<int>(columns, 0));
	int posX, posY;
	while (infile >> posX >> posY){
		mineField[posX][posY] = 1;
	}
	mField = minesweeper(columns, rows, mines, mineField);
}



/*
* This method is used to populate the minefield by randomly generated location values.
* This method will query the user for the first input and based on that input,
* it will populate the minefield such that the  first input is not a mine and the user does not lose the game on first turn.
* Returns the first input to be updated on the actual minesweeper object.
*/

input_t loadGameFromProgram(){
	cout << "Please enter the size row and column for the field, and the total mine Number (split them with space): ";
	cin >> rows >> columns >> mines;
	mineField = vector<vector<int>>(rows, vector<int>(columns, 0)); //use -1 to check if need to randomly generate the mine
	cout << "Please Enter your first operation: (such as 'u 4 5')";
	input_t firstInput;
	cin >> firstInput.operation >> firstInput.row >> firstInput.column;
	return firstInput;
}


/* This should be your game UI function. If a user decides to play a game of minesweeper,
* UI interaction with a minesweeper object should be done here. This method repeatedly 
* queries for user input and checks the game staus at each turn. If game is ongoing, user is queried for input
* and the function processInput is called.
* If the user hits a mine, the game is lost and the message along with all the mines is displayed on the console.
* If the user reveals all the locations without hitting a mine, the game is won and the message is displayed on the console.
*/
void playTime(minesweeper& play) {
//TODO - Begin the minesweeper game function; should interact with minesweeper class/object here
	cout<<" The game is Setup!! Let us Play "<<endl;
	input_t input;
	while (play.endGame() == 0){ // while is ongoing
		play.displayGameBoard();
		input = getUserInput();
		processInput(play, input);
	}
}



/* This method queries the user for location input. 
*  It validates the operation to be performed (mark, unmark, reveal) on a cell and the coordinates of the cell.
*  Returns a structure input_t that packs these values.
*/


input_t getUserInput(){
	input_t tmp;
	cin >> tmp.operation >> tmp.row >> tmp.column;
	return tmp;
}



/*
*This method performs the user actions on the minesweeper object.
* For example, the repeated printing of the board state
* and handling of user game action such as left/right click
* on a particular cell should be done here.
*/


void processInput(minesweeper& play, input_t input){
	if (input.operation == 'r'){
		play.revealLocation(input.row, input.column);
	}
	else if (input.operation == 'm'){
		play.markLocation(input.row, input.column);
	}
	else if (input.operation == 'u'){
		play.unmarkLocation(input.row, input.column);
	}
	else{
		cout << "Wrong operation!\n";
	}
}

