#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

#define NO_ROW 11 // the board is in size 10 x 10, and I need one extra column
#define NO_COLUMN 11 // and row to display the number.

int detect_num(int row, int column); // initiating the function
void prep_board(); 
void show_board();
void show_player_board();
void prep_player_board();
int board[NO_ROW][NO_COLUMN]; // initiating the board globally, this board is for developing and testing and comparing bombs locations
int player_board[NO_ROW][NO_COLUMN]; // initiating player board globally, this board is for the users.

int BOMB_NUM = 20; // initiating number of bombs globally


bool game_stat; // a global boolean 

void main() {
	prep_board();               // 1. prepare board: insert bombs into board, mark all the non-bomb bricks with numbers of bombs around them
	//show_board();				// (1.1) can display the board if needed
	prep_player_board();		
	game_stat = true;			
	int cor_x, cor_y;
	int operation;
	//cout << "How many bombs do yo want to insert? " << endl; 
	//cin >> BOMB_NUM;

	while (game_stat == true) { // 2. game on, it is a while loop, sentinal is the status of the boolean variable "game_stat",
								// while it's true, keep running. Otherwise, break.

		show_player_board();
		cout << "Which block do you want to reveal or mark(by entering the coordinates)? \n" << endl;
		cout << "Enter row number(1-10): " << endl;
		cin >> cor_x;
		cout << "Enter column number(1-10): " << endl;
		cin >> cor_y;
		cout << "Dou you want to reveal(1) or mark(2) it? " << endl;
		cin >> operation;                                  // Obtain coordinates and operation from users

		if (operation == 2) { // while marking
			player_board[cor_x][cor_y] = -2; // -2 means mark
			if (board[cor_x][cor_y] == -1) {
				BOMB_NUM--;
			}
		}
		else if (operation == 1) { // while revealing
			if (board[cor_x][cor_y] == -1) { // if it is a bomb, set stat to false
				game_stat = false;
				cout << "GG! Maybe try next time! " << endl;
			}
			else {
				player_board[cor_x][cor_y] = detect_num(cor_x, cor_y);
			}
		}

		if (BOMB_NUM == 0) {
			game_stat = false;
			cout << "You win!" << endl;
		}
	}
	system("pause");
}

void prep_board() {
	
	for (int i = 1; i < NO_ROW; i++) { // pre-set all the blocks with 0
		for (int j = 1; j < NO_COLUMN; j++) {
			board[i][j] = 0;
		}
	}

	//srand(time(NULL)); // change seed every time
	int bomb_x, bomb_y; // location of bombs 
	for (int i = 0; i < BOMB_NUM; i++) { // generate 20 bombs
		bomb_x = rand() % 10 + 1;
		bomb_y = rand() % 10 + 1;

		bool flag = false;
		while (flag == false) { // if the new bomb is the same as anyone has already existed, generate again
			if (board[bomb_x][bomb_y] == 0) { // Otherwise put into the board marked as "-1
				board[bomb_x][bomb_y] = -1;
				flag = true;
			}
			else if (board[bomb_x][bomb_y] == -1) {
				bomb_x = rand() % 10 + 1;
				bomb_y = rand() % 10 + 1;
			}
		}
	}
	for (int i = 1; i < NO_ROW; i++) {
		for (int j = 1; j < NO_COLUMN; j++) {
			if (board[i][j] != -1) {
				board[i][j] = detect_num(i, j); // allocating numbers of bombs into the board
			}
		}
	}


}

int detect_num(int row, int column) { // this function is for detecing how many blocks around a target block	
	int counter = 0;
	if (row - 1 >= 1 && column - 1 >= 1) {   // check the up-left block
		if (board[row - 1][column - 1] == -1) {
			counter++;
		}
	}
	if (column - 1 >= 1) { // check the left block
		if (board[row][column - 1] == -1) {
			counter++;
		}
	}
	if (row + 1 <= 10 && column - 1 >= 1) { // check the down-left block
		if (board[row + 1][column - 1] == -1) {
			counter++;
		}
	}
	if (row - 1 >= 1) { // check the up block
		if (board[row - 1][column] == -1) {
			counter++;
		}
	}
	if (row + 1 <= 10) { // check the down block
		if (board[row + 1][column] == -1) {
			counter++;
		}
	}
	if (row - 1 >= 1 && column + 1 <= 10) { //check the up-right block
		if (board[row - 1][column + 1] == -1) {
			counter++;
		}
	}
	if (column + 1 <= 10) { // check the right block
		if (board[row][column + 1] == -1) {
			counter++;
		}
	}
	if (row + 1 <= 10 && column + 1 <= 10) { // check the down-right block
		if (board[row + 1][column + 1] == -1) {
			counter++;
		}
	}
	return counter;

}

void show_board() {
	cout << "================================ Developer Version Starts ================================" << endl;
	board[0][0] = 0; // the origin should be 0
	for (int i = 1; i < NO_COLUMN; i++) { // displaying the row number
		board[0][i] = i;
	}
	for (int j = 1; j < NO_ROW; j++) { // displaying the column number
		board[j][0] = j;
	}
	for (int i = 0; i < NO_ROW; i++) { // displaying the board
		for (int j = 0; j < NO_COLUMN; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
	cout << "================================ Developer Version Ends ================================" << endl;
}

void show_player_board() {
	int bomb_remained;
	bomb_remained = BOMB_NUM;	
	cout << "================================ Player Version Starts ================================" << endl;
	cout << " Bomb remaining: " << bomb_remained << endl;

	
	for (int i = 0; i < NO_ROW; i++) { // displaying the board
		for (int j = 0; j < NO_COLUMN; j++) {
			cout << player_board[i][j] << "\t";
		}
		cout << endl;
	}

	

	cout << "================================ Player Version Ends ================================" << endl;
}

void prep_player_board() {
	player_board[0][0] = 0; // the origin should be 0
	for (int i = 1; i < NO_COLUMN; i++) { // displaying the row number
		player_board[0][i] = i;
	}
	for (int j = 1; j < NO_ROW; j++) { // displaying the column number
		player_board[j][0] = j;
	}

	for (int i = 1; i < NO_ROW; i++) {
		for (int j = 1; j < NO_COLUMN; j++) {
			player_board[i][j] = 9; // 9 means unrevealed block
		}
	}
}