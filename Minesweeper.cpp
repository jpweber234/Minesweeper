#include <iostream>
#include <random>
#include <ctime>
#include <bitset>
#include "boardinitialize.cpp"
#include "playgame.cpp"


#define BOARDSIZE 25 //Maximum dimension (i.e board dimensions cannot exceed BOARDSIZE x BOARDSIZE

using namespace boardinitialize;
using namespace playgame;

const char gameType = getGameType(); //Game difficulty
const int xdim = getHorizontalDimension(gameType); //X dimension
const int ydim = getVerticalDimension(gameType); //Y dimension
const int mines = getMines(gameType); //Number of mines
std::mt19937 mersenne{ static_cast<std::mt19937::result_type>(std::time(nullptr)) }; //for random numbers


/////////////////////////////////////////////////////////////////////////////////////////////////

void initializeBoard(char board[][BOARDSIZE]) //initializes board with Xs
{
	for (int ii = 0; ii < xdim; ii++)
		for (int jj = 0; jj < ydim; jj++)
			board[ii][jj] = 'X';
}

void printBoard(char board[][BOARDSIZE]) //prints board
{
	cout << "\n\n";

	for (int ii = 0; ii < xdim; ii++)
	{
		for (int jj = 0; jj < ydim; jj++)
			cout << board[ii][jj] << ' ';

		cout << '\n';
	}

	cout << '\n';
}

int getRandom(int dim) //generates random number between 0 and dimension of board - 1
{
	std::uniform_int_distribution<> die{ 0, dim - 1 }; // we can create a distribution in any function that needs it
	return die(mersenne); // and then generate a random number from our global generator
}

int getCas(int ii, int jj) //determines location of square (and indirectly number of spaces adjacent to it)
{
	int cas{};	
	if ((ii == 0) && (jj == 0)) //top left corner
		cas = 1;
	else if ((ii == 0) && ((jj != 0) && (jj != ydim))) //top row, excluding corners
		cas = 2;
	else if ((ii == 0) && (jj == ydim)) //top right corner
		cas = 3;
	else if (((ii != 0) && (ii != xdim)) && (jj == 0)) //left column, excluding corners
		cas = 4;
	else if (((ii != 0) && (ii != xdim)) && ((jj != 0) && (jj != ydim))) //middle of board
		cas = 5;
	else if (((ii != 0) && (ii != xdim)) && (jj == ydim)) //right column, excluding corners
		cas = 6;
	else if ((ii == xdim) && (jj == 0)) //bottom left corner
		cas = 7;
	else if ((ii == xdim) && ((jj != 0) && (jj != ydim))) //bottom row, excluding corners
		cas = 8;
	else if ((ii == xdim) && (jj == ydim)) //bottom right corner
		cas = 9;

	return cas;
}

char mineNumber(char board[][BOARDSIZE], int ii, int jj) //determines number of mines near each square by checking each adjacent square and incrementing mine counter if a mine is present
{
	int mineCounter{};
	int cas = getCas(ii, jj);

	if (cas == 5 || cas == 6 || cas == 8 || cas == 9) //checks if mine is present top left of current square
	{
		if (board[ii - 1][jj - 1] == 'M')
			mineCounter++;
	}

	if (cas == 2 || cas == 3 || cas == 5 || cas == 6 || cas == 8 || cas == 9) //checks if mine is present left of curent square
	{
		if (board[ii][jj - 1] == 'M')
			mineCounter++;
	}

	if (cas == 2 || cas == 3 || cas == 5 || cas == 6) //checks if mine is present bottom left of current square
	{
		if (board[ii + 1][jj - 1] == 'M')
			mineCounter++;
	}

	if (cas == 1 || cas == 2 || cas == 3 || cas == 4 || cas == 5 || cas == 6) //checks if mine is present below current square
	{
		if (board[ii + 1][jj] == 'M')
			mineCounter++;
	}

	if (cas == 1 || cas == 2 || cas == 4 || cas == 5) //checks if mine is present bottom right of current square 
	{
		if (board[ii + 1][jj + 1] == 'M')
			mineCounter++;
	}

	if (cas == 1 || cas == 2 || cas == 4 || cas == 5 || cas == 7 || cas == 8) //checks if mine is present right of current square
	{
		if (board[ii][jj + 1] == 'M')
			mineCounter++;
	}

	if (cas == 4 || cas == 5 || cas == 7 || cas == 8) //checks if mine is present top right of current square
	{
		if (board[ii - 1][jj + 1] == 'M')
			mineCounter++;
	}

	if (cas == 4 || cas == 5 || cas == 6 || cas == 7 || cas == 8 || cas == 9) //checks if mine is present above current square
	{
		if (board[ii - 1][jj] == 'M')
			mineCounter++;
	}

	return static_cast<char>(mineCounter + '0');
}

std::bitset<8> isMine(char board[][BOARDSIZE], int ii, int jj) //creates 8 bit number that counts the number of mines and their locations (1 indicates a mine)
{

	std::bitset<8> bits{ 0b00000000 }; //format: <upper left, left, lower left, below, lower right, right, upper right, above>
	int cas = getCas(ii, jj);

	if (cas == 5 || cas == 6 || cas == 8 || cas == 9)
	{
		if (board[ii - 1][jj - 1] == 'M')
			bits.set(7);
	}

	if (cas == 2 || cas == 3 || cas == 5 || cas == 6 || cas == 8 || cas == 9)
	{
		if (board[ii][jj - 1] == 'M')
			bits.set(6);
	}

	if (cas == 2 || cas == 3 || cas == 5 || cas == 6)
	{
		if (board[ii + 1][jj - 1] == 'M')
			bits.set(5);
	}

	if (cas == 1 || cas == 2 || cas == 3 || cas == 4 || cas == 5 || cas == 6)
	{
		if (board[ii + 1][jj] == 'M')
			bits.set(4);
	}

	if (cas == 1 || cas == 2 || cas == 4 || cas == 5)
	{
		if (board[ii + 1][jj + 1] == 'M')
			bits.set(3);
	}

	if (cas == 1 || cas == 2 || cas == 4 || cas == 5 || cas == 7 || cas == 8)
	{
		if (board[ii][jj + 1] == 'M')
			bits.set(2);
	}

	if (cas == 4 || cas == 5 || cas == 7 || cas == 8)
	{
		if (board[ii - 1][jj + 1] == 'M')
			bits.set(1);
	}

	if (cas == 4 || cas == 5 || cas == 6 || cas == 7 || cas == 8 || cas == 9)
	{
		if (board[ii - 1][jj] == 'M')
			bits.set(0);
	}

	return bits;
}

void click(char board1[][BOARDSIZE], char board2[][BOARDSIZE], int x, int y) //If spaces adjacent to the clicked space are not mines, clear them (I actually don't know if that's what this does, I forget) 
{
	board1[x][y] = board2[x][y]; //board2 is "answer key", board1 is players board
	std::bitset<8> noMines = isMine(board2, x, y);
	for (int i = 0; i < 8; i++) //for each bit
		if (noMines.test(i) == 0) //if bit is 0 (mine is not present)
		{
			switch (i) //display corresponding square from board2 (by setting board1 square = board2 square
			{
			case 7: //upper left
				if (board2[x - 1][y - 1] != 'M')
					board1[x - 1][y - 1] = board2[x - 1][y - 1];
			case 6: //left
				if (board2[x][y - 1] != 'M')
					board1[x][y - 1] = board2[x][y - 1];
			case 5: //lower left
				if (board2[x + 1][y - 1] != 'M')
					board1[x + 1][y - 1] = board2[x + 1][y - 1];
			case 4: //below
				if (board2[x + 1][y] != 'M')
					board1[x + 1][y] = board2[x + 1][y];
			case 3: //lower right
				if (board2[x + 1][y + 1] != 'M')
					board1[x + 1][y + 1] = board2[x + 1][y + 1];
			case 2: //right
				if (board2[x][y + 1] != 'M')
					board1[x][y + 1] = board2[x][y + 1];
			case 1: //upper right
				if (board2[x - 1][y + 1] != 'M')
					board1[x - 1][y + 1] = board2[x - 1][y + 1];
			case 0: //above
				if (board2[x - 1][y] != 'M')
					board1[x - 1][y] = board2[x - 1][y];
			}
		}
		
		//otherwise, do not display square
}

void initializeMineBoard(char board[][BOARDSIZE]) //initializes Mine Board, which displays where mines are located
{
	for (int mm = 0; mm < mines;)
	{
		int randX = getRandom(xdim);
		int randY = getRandom(ydim);

		board[randX][randY] = 'M'; //places mines at random locations
		mm++;		
	}

	for (int ii = 0; ii < xdim; ii++)
	{
		for (int jj = 0; jj < ydim; jj++)
		{
			if (board[ii][jj] != 'M') //for every square on the board that does not have a mine
			{
				char mineCounter = mineNumber(board, ii, jj); //determines how many adjacent mines
				board[ii][jj] = mineCounter; //labels square with number of adjacent mines
			}
		}
	}
}

void playGame()
{
	char gameBoard[BOARDSIZE][BOARDSIZE]; //player's board
	char mineBoard[BOARDSIZE][BOARDSIZE]; //"answer key" board
	initializeBoard(gameBoard); //initializes Game Board, which is displayed to user
	initializeMineBoard(mineBoard); //initializes Mine Board, which displays locations of mines, and is not displayed to user
	printBoard(gameBoard); //prints Game Board
	
	while (true)
	{
		int x = getXCoord(); //gets X Coordinate from user 
		int y = getYCoord(); //gets Y Coordinate from user 
		char a = getAction(); //Click or Flag
		
		if (a == 'F') //if action is Flag
		{
			gameBoard[x][y] = 'M'; //set Game Board space to 'M'
			printBoard(gameBoard); //print Game Board
		}
		if (a == 'C') //if action is click
		{
			click(gameBoard, mineBoard, x, y);

			if (mineBoard[x][y] == 'M') //if you clicked on a mine
			{
				cout << "YOU LOSE!\n"; //YOU LOSE
				printBoard(mineBoard);
				break;
			}

			printBoard(gameBoard);
		}
		
		int match{ 0 };

		//determines how many squares of game board matches mine board
		for (int ii = 0; ii < xdim; ii++)
			for (int jj = 0; jj < ydim; jj++)
				if (gameBoard[ii][jj] == mineBoard[ii][jj])
					match++;
		
		if (match == (xdim * ydim)) //if match # = total number of squares
		{
			cout << "YOU WIN!\n"; //YOU WIN
			break;
		}

	}
}


int main()
{
	playGame();
	return 0;
}

