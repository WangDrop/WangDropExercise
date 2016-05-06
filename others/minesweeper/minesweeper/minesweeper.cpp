#include "minesweeper.h"

using namespace std;


/* default constructor, initializes the mineField to a 9x9 size with 10 mines
*/
minesweeper::minesweeper() :rowNum(9), colNum(9), minesNum(10), end(0), revealCount(0), mineField(9, vector<cell>(9, {0, 0, false})){
	// TODO - default two dimension array is 9 X 9 with 10 mines
	srand(time(NULL));
	int xpos, ypos;
	for (int i = 0; i < 10; ++i){
		xpos = rand() % 9;
		ypos = rand() % 9;
		while (mineField[xpos][ypos].isMine){
			xpos = rand() % 9;
			ypos = rand() % 9;
		}
		mineField[xpos][ypos].isMine = true;
		mineField[xpos][ypos].value = -1;
		mineField[xpos][ypos].state = 0;
	}
	setupGameBoard();
}



minesweeper::minesweeper(int row, int col, int numOfMines, vector<vector<int> >&mineField) 
	:rowNum(row), colNum(col), minesNum(numOfMines), end(0), revealCount(0), mineField(row, vector<cell>(col, { 0, 0, false })){
	// TODO Auto-generated constructor stub
	// TODO - two dimension gameboard size col x num with numOfMines mines
	srand(time(NULL));
	for (int i = 0; i < mineField.size(); ++i){
		for (int j = 0; j < mineField[i].size(); ++j){
			if (mineField[i][j] == 1){
				this->mineField[i][j].isMine = true;
				this->mineField[i][j].value = -1;
				this->mineField[i][j].state = 0;
			}
		}
	}
	setupGameBoard();
}



minesweeper::~minesweeper() { //default is ok
	// TODO Auto-generated destructor stub
}




/**
 * Returns int representing number of rows of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getRowNum()
{
	return rowNum;
}




/**
 * Returns int representing number of columns of current playing field.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getColNum()
{
	return colNum;
}


/**
 * Returns int representing number of mines on current playing field.
 * Includes both hidden and revealed mines.
 *
 * @return      Number of rows on playing field
 * */
int minesweeper::getMinesNum()
{
	return minesNum;
}



/*
 * Generates numbers for surrounding tiles of mines. The only
 * tiles with numbers are those surrounding mines; these tiles are
 * updated as mines are generated.

 *
 * @param   row Row number of generated mine
 * @param   col Column number of generated mine
 * */
void minesweeper::calculateSurrounding(int row, int col) {
	//TODO - should update surrounding tiles to reflect
	//presence of adjacent mine
	for (int i = row - 1; i <= row + 1; ++i){
		for (int j = col - 1; j <= col + 1; ++j){
			if (i < 0 || i >= rowNum || j < 0 || j >= colNum)
				continue;
			incrementCellValue(i, j);
		}
	}
}





/* increments the cell value(number of mines surrounding it) if the input location is valid
*  called from calculateSurrounding() for each adjacent mine.
*/
void minesweeper::incrementCellValue(int row, int col){
	if (mineField[row][col].isMine)
		return;
	this->mineField[row][col].value++;
}


/*This method sets up the game Board by calculating the number of neighbouring mines for each cell.
* calls calculateSurrounding() on each cell 
*/

void minesweeper::setupGameBoard(){
	for (int i = 0; i < rowNum; ++i){
		for (int j = 0; j < colNum; ++j){
			if (this->mineField[i][j].isMine)
				calculateSurrounding(i, j);
		}
	}
}



/**
 * Updates mineField with user selection of revealed location.
 * Reveals current location and immediately checks mineField
 * for mine. 
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         unmask();
 * */
void minesweeper::revealLocation(int x, int y) {
	//TODO - update the bitField to reflect the user's
	//tile selection. Should rely on unmask to do actual
	//reveal operation.
	if (mineField[x][y].state == 1 || mineField[x][y].state == 2	)
		return; //already revealed or marked
	if (mineField[x][y].isMine){
		end = -1;
		mineField[x][y].state = 1;
		revealCount++;
		displayMines();
		return;
	}
	if (mineField[x][y].value != 0){
		revealCount++;
		mineField[x][y].state = 1;
	}
	else if (mineField[x][y].value == 0){
		revealCount++;
		mineField[x][y].state = 1;
		unmask(x, y);
	}
	if (revealCount + minesNum == rowNum * colNum){
		cout << "You Win!" << endl;
		end = 1;
	}

}




/**
 * Allow the user to mark a cell as a potential mine. Marking an already
 * marked cell will result in no operation.
 * @param x column number of the cell selected
 * @param y row number of the cell selected
 */
void minesweeper::markLocation(int x, int y) {
    // TODO - update the display for the selected cell, change it
    // to marked if it's not marked, or to unmarked if it's already marked
	if (mineField[x][y].state == 0){//hidden
		revealCount++; // incre the rcount
		if (revealCount == rowNum * colNum)
			end = 1;
		mineField[x][y].state = 2;
	}
	else if (mineField[x][y].state == 1){//revealed
		return; //do nothing
	}
	else if (mineField[x][y].state == 2){//marked
		return; //do nothing
	}
	else{ //error
		cout << "Field Error!" << endl;
	}
    	   
}






/**
 * Allow the user to unmark a cell that is already marked. Unmarking an already
 * unmarked cell will result in no operation.
 * @param x column number of the cell selected
 * @param y row number of the cell selected
 */
void minesweeper::unmarkLocation(int x,int y){
	if (mineField[x][y].state == 0){//hidden
		return; //do nothing
	}
	else if (mineField[x][y].state == 1){//revealed
		return; //do nothing
	}
	else if (mineField[x][y].state == 2){//marked
		revealCount--; //do nothing
		mineField[x][y].state = 0; //unrev a field
	}
	else{ //error
		cout << "Field Error!" << endl;
	}
}





/**
 * Checks end game status (int end). End -1 is loss condition.
 * Also checks onlyMines() for a win condition. onlyMines will
 * update the end game status and endGame should return this value.
 *
 * @return      end game status (-1 loss, 0 ongoing, 1 win)
 * @see         onlyMines();
 * @see		revealLocation();
 * */
int minesweeper::endGame() {
	//TODO - return current end game status.
	//Calling this method should only update int end with
	//win or ongoing condition. revealLocation should
	//update if there is loss condition.
	return end;// return status
}






/**
 * Checks if the value of selected tile. isRevealed
 * should be called before this for correct gameplay. 
 * 
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         isRevealed();
 * */
int minesweeper::valueOf(int x, int y) {
	//TODO - returns the value of specific tile.
	//should only be called if tile isRevealed.
	if (isRevealed(x, y)){
		return mineField[x][y].value;
	}
	return 0;
}



bool minesweeper::isRevealed(int x, int y)                  //Checks if tile has been already revealed
{
	if (mineField[x][y].state == 1)
		return true;
	return false;
}

/**
 * Reveals surrounding tiles. Should only be called if
 * user selected tile was not mine or had no surrounding
 * mines. Will recursively call itself to reveal all
 * adjacent blank tiles.
 *
 * @param   row Row number of user selected tile
 * @param   col Column number of user selected tile
 * @see         revealLocation();
 * */
void minesweeper::unmask(int row,int col) {
	//TODO - reveal the tile here.
	//This method should reveal surrounding tiles
	//if the tile revealed had a value of 0
	for (int i = row - 1; i <= row + 1; ++i){
		for (int j = col - 1; j <= col + 1; ++j){
			if (i < 0 || i >= rowNum || j < 0 || j >= colNum)
				continue;
			if (mineField[i][j].state == 0){
				revealCount++;
				mineField[i][j].state = 1;
				if (mineField[i][j].value == 0)
					unmask(i, j);
			}
		}
	}

}







/* This method is called at each turn of the user input. This method dispalys the actual status of the game.
*  It queries the status of each cell if it has to marked, unmarked or revealed and displays the result accordingly
*  '#' indicates the cell is hidden, '!' indicates the cell is marked, and a number indicates the cell is 
* revealed and has so many mines in the neighbourhood.
*/

void minesweeper::displayGameBoard(){
	printf("\t");
	for (int i = 0; i < colNum; ++i)
		printf("%d\t", i);
	printf("\n");
	for (int i = 0; i < 10 * colNum; ++i)
		putchar('=');
	printf("\n");
	for (int i = 0; i < 2 * rowNum + 1; ++i){
		if (i % 2){
			printf("%d|\t", i/2);
			for (int j = 0; j < colNum; ++j){
				if (mineField[i / 2][j].state == 0){//hidden
					printf("#\t");
				}
				else if (mineField[i / 2][j].state == 1){//revealed
					printf("%d\t", mineField[i/2][j].value);
				}
				else if (mineField[i / 2][j].state == 2){//marked
					printf("!\t");
				}
				else{
					printf("Wrong state!\n");
				}
			}
		}
		else{
			printf(" |\n");
		}
	}
	printf(" |\n\n");
	for (int i = 0; i < 10 * colNum; ++i)
		putchar('=');
	printf("\n");
	printf("revealCount %d\n", revealCount);
	printf("Select the row and column numbers to be MARKED, UNMARKED or REVEALED within the range \n usage : 'm 5 4', 'u 5 4', 'r 5 4'\n");
}

/* This method is called at the end of the game play when the game is lost. This method displays all the mines to the user.
*
*/


void minesweeper::displayMines(){
	printf("\t");
	for (int i = 0; i < colNum; ++i)
		printf("%d\t", i);
	printf("\n");
	for (int i = 0; i < 10 * colNum; ++i)
		putchar('=');
	printf("\n");
	for (int i = 0; i < 2 * rowNum + 1; ++i){
		if (i % 2){
			printf("%d|\t", i / 2);
			for (int j = 0; j < colNum; ++j){
				if (mineField[i / 2][j].isMine){//hidden
					printf("*\t");
				}
				else{
					printf("#\t");
				}
			}
		}
		else{
			printf(" |\n");
		}
	}
	printf(" |\n\n");
	for (int i = 0; i < 10 * colNum; ++i)
		putchar('=');
	printf("\n");
	printf("revealCount %d\n", revealCount);
	printf("Game Over! You Loss.\n");
}
