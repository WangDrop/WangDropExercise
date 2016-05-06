#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <stdlib.h>
#include <ctime>
#include <string>


using namespace std;

#ifndef MINESWEEPER_H_
#define MINESWEEPER_H_



// each cell is represented as a structure.
struct cell{
     int state;						//( 0 hidden, 1 revealed, 2 marked) 
     int value;						//(-1 mine, 0 no surrounding, # > 0 number of surrounding mines)
     bool isMine;
};


class minesweeper {
private:
	int colNum;                                     //number of columns on game board (X))
	int rowNum;                                     //number of rows on game board(Y)
	int minesNum;                                   //number of mines placed on game board
   	int end;                                      	//end game condition tracker (-1 loss, 0 ongoing, 1 win)
    	int revealCount;				//number of cells revealed
    	vector<vector<cell> > mineField;       		//actual representation of game board 
        
    	void calculateSurrounding(int row, int col);    //Updates board tiles by adding 1 to tiles surrounding mine except when adjacent tile is mine
    	void onlyMines();                               //Checks end game status (int end). Should check entire playing field, no internal counter
    	int randomPick(int num);                        //Randomly generates number between 0 and num
    	void unmask(int row, int col);                  //Actual function to reveal blank tile. Makes recursive calls for 0 value tiles
	

        
public:
	
	minesweeper();                                  //Default constructor
	virtual ~minesweeper();                         //Destructor
   	minesweeper(int col, int row, int numOfMines,vector<vector<int> >&mineField);  //Constructor given board dimensions and number of mines
        
	int getColNum();                                //Return # of columns for game board
	int getRowNum();                                //Return # of rows for game board
	int getMinesNum();                              //Return total # of mines on game board
    int endGame();                                  //Return current end game status
    bool isRevealed(int x, int y);                  //Checks if tile has been already revealed
	void revealLocation(int x, int y);              //Reveals selected tile. Selected tile should return true on subsequent isRevealed calls, the left click action
    void markLocation(int x, int y);                //mark a cell as potential mine, the right click action
	void unmarkLocation(int x,int y);				//unmark a cell if already marked
  	int valueOf(int x, int y);                      //Returns tile value (# of surrounding mines if not mine)


	void incrementCellValue(int x, int y);          //increments the cell value(# of surrounding mines if not mine)
	void setupGameBoard();

	void displayGameBoard();                        //displays the current status of the board after each move by the user
	void displayMines();				//displays the mines at game over
};


#endif /* MINESWEEPER_H_ */
