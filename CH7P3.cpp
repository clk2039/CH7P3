/*
File name: CH7P3.cpp
Github URL: https://github.com/clk2039/CH7P3.git
Programmer: Kit Miller
Date: December 2025\
Requirements: Write a modular, procedural program that allows two players to play a game of Tic-Tac-Toe.
Use a two-dimensional char array with three rows and three columns as the game board.
Each element of the array should be initialized with an asterisk (*) to indicate an empty space on the board.
The program should run a loop that does the following:
-Displays the contents of the board array
-Ask player 1 to select a location on the board for an X. The program should ask the user to enter a row and column number
-Ask player 2 to select a location on the board for an O. The program should ask the user to enter a row and column number
-Determines whether a player has won, or a tie has occured.
*/

#include <iostream>
using namespace std;

//Constants
const int ROWS = 3;
const int COLS = 3;
const int PLAY = 0;
const int TIE = 1;
const int ONE_WIN = 2;
const int TWO_WIN = 3;
const int NOT_DONE = 0;
const int NO_SPACE = 1;
const int WINNER = 2;

//Function Prototypes
void initializeBoard(char board[ROWS][COLS]);
void displayBoard(const char board[ROWS][COLS]);
void placeToken(char board[ROWS][COLS], char token);
void getLocation(const char board[ROWS][COLS], int& row, int& col);
int getBoardStatus(const char board[ROWS][COLS], char token);
int checkWin(const char board[ROWS][COLS], char token);

int main()
{
	char board[ROWS][COLS];
	const char playerOneToken = 'X';
	const char playerTwoToken = 'O';
	int boardStatus = PLAY;

	//Initialize the board
	initializeBoard(board);

	//Keep playing until there's a win or tie
	while (boardStatus == PLAY)
	{
		//Player one's turn
		displayBoard(board);
		placeToken(board, playerOneToken);
		boardStatus = getBoardStatus(board, playerOneToken);
		if (boardStatus != PLAY)
			break;

		//Player two's turn
		displayBoard(board);
		placeToken(board, playerTwoToken);
		boardStatus = getBoardStatus(board, playerTwoToken);
	}

	//Display the finished board
	displayBoard(board);

	//Display the results
	if (boardStatus == ONE_WIN)
		cout << "Player One wins!" << endl;
	else if (boardStatus == TWO_WIN)
		cout << "Player Two wins!" << endl;
	else if (boardStatus == TIE)
		cout << "It's a tie!" << endl;

	return 0;

}

/*
Function: initializeBoard
Purpose: Initializes the game board with asterisks (*)
Parameters: board - a 3x3 array representing the game board
Returns: void
Preconditions: none
Postconditions: Every spot on the board is set to '*'
*/
void initializeBoard(char board[ROWS][COLS])
{
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			board[row][col] = '*';
		}
	}
}

/*
Function: displayBoard
Purpose: Display the board with row and column numbers
Parameters: board- a 3x3 board to display
Returns: void
Preconditions: none
Postconditions: The board is displayed on the screen
*/
void displayBoard(const char board[ROWS][COLS])
{
	cout << "  1 2 3" << endl;
	for (int row = 0; row < ROWS; row++)
	{
		cout << row + 1 << " ";
		for (int col = 0; col < COLS; col++)
		{
			cout << board[row][col] << " ";
		}
		cout << endl;
	}
}

/*
Function: placeToken
Purpose: Get a valid row and column from the player and place their token on the board
Parameters: board - a 3x3 array representing the game board
			token - the character to place on the board ('X' or 'O')
Returns: void
Preconditions: none
Postconditions: Board is set to token at a valid empty location
*/
void placeToken(char board[ROWS][COLS], char token)
{
	int row = 0;
	int col = 0;
	if (token == 'X')
		cout << "Player One's turn." << endl;
	else
		cout << "Player Two's turn." << endl;

	getLocation(board, row, col);

	board[row][col] = token;

	cout << endl;
}

/*
Function: getLocation
Purpose: Ask the user for a valid row and column number and ensure the spot is empty
Parameters: board - a 3x3 array representing the game board
			row - reference to an integer to store the row number
			col - reference to an integer to store the column number
Returns: void
Preconditions: Row and column are valid integers
Postconditions: Row and column are set to valid values for an empty spot on the board
*/
void getLocation(const char board[ROWS][COLS], int& row, int& col)
{
	int userRow = 0;
	int userCol = 0;

	bool validInput = false;
	while (!validInput)
	{
		cout << "Enter row (1-3): ";
		cin >> userRow;
		cout << "Enter column (1-3): ";
		cin >> userCol;
		//Adjust for 0-based indexing
		userRow--;
		userCol--;
		if (userRow < 0 || userRow >= ROWS || userCol < 0 || userCol >= COLS)
		{
			cout << "Error: Row and column must be between 1 and 3." << endl;
		}
		else if (board[userRow][userCol] != '*')
		{
			cout << "Error: That spot is already taken. Choose another." << endl;
		}
		else
		{
			validInput = true;
			row = userRow;
			col = userCol;
		}
	}
}

/*
Function: getBoardStatus
Purpose: Determine if the game continues, if there's a win, or if there's a tie
Parameters: board - a 3x3 array representing the game board
			token - the character of the current player ('X' or 'O')
Returns: int - status code indicating game state
Preconditions: board contains valid characters
Postconditions: Returns PLAY, TIE, ONE_WIN, or TWO_WIN based on the game state
*/
int getBoardStatus(const char board[ROWS][COLS], char token)
{
	int result = checkWin(board, token);
	//Check for win
	if (result == WINNER)
	{
		if (token == 'X')
			return ONE_WIN;
		else
			return TWO_WIN;
	}
	//Check for tie
	if (result == NO_SPACE)
		return TIE;

	return PLAY;
}

/*
Function: checkWin
Purpose: Check rows, columns, and diagonals for a win or if the board is full
Parameters: board - a 3x3 array representing the game board
			token - the character of the current player ('X' or 'O')
Returns: int - WINNER if the player has won,
			   NO_SPACE if the board is full,
			   NOT_DONE otherwise
Preconditions: none
Postconditions: Returns the game status
*/
int checkWin(const char board[ROWS][COLS], char token)
{
	//Check the rows
	for (int row = 0; row < ROWS; row++)
	{
		if (board[row][0] == token && board[row][1] == token && board[row][2] == token)
			return WINNER;
	}
	//Check the columns
	for (int col = 0; col < COLS; col++)
	{
		if (board[0][col] == token && board[1][col] == token && board[2][col] == token)
			return WINNER;
	}
	//Check the diagonals
	if (board[0][0] == token && board[1][1] == token && board[2][2] == token)
		return WINNER;
	if (board[0][2] == token && board[1][1] == token && board[2][0] == token)
		return WINNER;
	//Check for empty spaces
	for (int row = 0; row < ROWS; row++)
	{
		for (int col = 0; col < COLS; col++)
		{
			if (board[row][col] == '*')
				return NOT_DONE;
		}
	}
	return NO_SPACE;
}
