// assignment 5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>                                
using namespace std;                               //when multiple jump input problem 
int y = 0;
int x = 0;
class piece
{
	char Player;
	int LocationX;
	int LocationY;
	bool IsKing,justking;
	friend class Board;

public:
	piece(char p, int x, int y)
	{
		Player = p;
		LocationX = x;
		LocationY = y;
		IsKing = false;
	}
	char getplayer()
	{
		return Player;
	}
	void changeX(int a) {
		LocationX = a;
	}
	void changeY(int a) {
		LocationY = a;
	}
};
class Board
{
	char board[8][8];
	piece** dark;
	piece** light;
	static int noofdarkpieces, nooflightpieces;
public:
	Board()
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = ' ';
			}
		}
		dark = new piece * [12];
		int y = 0;
		int k = 0;
		for (int i = 0; i < 12; i++)
		{

			if (k != 0 && k % 4 == 0)
			{
				k = 0;
				y++;
			}
			if (y % 2 == 0)
				x = 2 * k + 1;
			else
				x = 2 * k;

			k++;

			dark[i] = new piece('d', x, y);
			SetPosition(x, y, 'd');
		}

		light = new piece * [12];
		y = 7;
		k = 0;
		for (int i = 0; i < 12; i++)
		{

			if (k != 0 && k % 4 == 0)
			{
				k = 0;
				y--;
			}
			if (y % 2 == 0)
				x = 2 * k + 1;
			else
				x = 2 * k;

			k++;

			light[i] = new piece('l', x, y);
			SetPosition(x, y, 'l');
		}

	}
	void display()
	{
		cout << "<<01234567>>" << endl;
		for (int i = 0; i < 8; i++)
		{
			cout << i<<"|";
			for (int j = 0; j < 8; j++)
			{
				cout << board[i][j];
			}

			cout << "|" <<i << endl;
		}
		cout << "<<01234567>>" << endl;
	}
	void SetPosition(int x, int y, char player)
	{
		board[y][x] = player;
	}
	bool gamecheck(char color) {
		if (color == 'd') {
			if (nooflightpieces)
				return true;
			else return false;
		}
		else {
			if (noofdarkpieces)
				return true;
			else return false;
		}
	}
	void canjump(int row, int col, piece* mypiece) {                       
		int todeleterow, todeletecol;
		todeleterow = (row + mypiece->LocationY) / 2;
		todeletecol = (col + mypiece->LocationX) / 2;
		if (board[row][col] == ' ') {
			if (mypiece->Player=='d'){
				for (int count = 0;count < nooflightpieces;count++) {
					if (light[count]->LocationY == todeleterow && light[count]->LocationX == todeletecol) {
						jump(todeleterow, todeletecol, mypiece, row, col);
						checkjumps(mypiece);
						return;
					}
				}
			}
			else {
				for (int count = 0;count < noofdarkpieces;count++) {
					if (dark[count]->LocationY == todeleterow && dark[count]->LocationX == todeletecol) {
						jump(todeleterow, todeletecol, mypiece, row, col);
						checkjumps(mypiece);
						return;
					}
				}
			}
			return;
		}
		else {
			cout << "Specified position already taken by a piece. Please enter row again of the piece you wish to move ";
			cin >> row;
			cout << "Please enter COLUMN again of the piece you want to move ";
			cin >> col;
			checkpiece(row, col, mypiece->Player);
		}
	}
	void jump(int todeleterow, int todeletecol, piece* mypiece, int tomoverow, int tomovecol) {
		int todeletepos ;
		if ( mypiece->Player == 'd') {
			for (int count = 0;count < nooflightpieces;count++) {
				if (light[count]->LocationY == todeleterow && light[count]->LocationX == todeletecol) {
					todeletepos = count;
					break;
				}
			}
			for (int count = todeletepos;count < nooflightpieces;count++) {
				light[count] = light[count + 1];
			}
			light[nooflightpieces - 1] = NULL;
			delete light[nooflightpieces - 1];
			nooflightpieces--;
			board[todeleterow][todeletecol] = ' ';
			setjustkingfalse('D');
			if (tomoverow == 7) {
				mypiece->IsKing = true; mypiece->justking = true;
				board[tomoverow][tomovecol] = 'D';
				mypiece->Player = 'D';
			}
		}
		else if (mypiece->Player == 'l'){
			for (int count = 0;count < noofdarkpieces;count++) {
				if (dark[count]->LocationY == todeleterow && dark[count]->LocationX == todeletecol) {
					todeletepos = count;
					break;
				}
			}
			for (int count = todeletepos;count < noofdarkpieces;count++) {
				dark[count] = dark[count + 1];
			}
			dark[noofdarkpieces - 1] = NULL;
			delete dark[(noofdarkpieces - 1)];
			noofdarkpieces--;
			board[todeleterow][todeletecol] = ' ';
		}
		board[tomoverow][tomovecol] = board[mypiece->LocationY][mypiece->LocationX];
		board[mypiece->LocationY][mypiece->LocationX] = ' ';
		mypiece->changeX(tomovecol);
		mypiece->changeY(tomoverow);
		setjustkingfalse('L');
		if (tomoverow == 0) {
			mypiece->IsKing = true; mypiece->justking = true;
			board[tomoverow][tomovecol] = 'L';
			mypiece->Player = 'L';
		}
	}
	void movepiece(int row, int col, piece* mypiece) {//g		
		if (mypiece->Player == 'd') {
			if ((mypiece->LocationY + 1) == row) {
				if ((mypiece->LocationX - 1) == col || (mypiece->LocationX + 1) == col) {
					if (board[row][col] != ' ') {
						cout << "Specified position already taken by a piece.Enter ROW of piece you want to move ";
						cin >> row;
						cout << "Enter COLUMN of piece you want to move ";
						cin >> col;
						checkpiece(row, col, mypiece->Player);
					}
					else {
						board[row][col] = mypiece->Player;
						board[mypiece->LocationY][mypiece->LocationX] = ' ';
						mypiece->changeY(row);
						mypiece->changeX(col);
						setjustkingfalse('D');
						if (row == 7) {
							mypiece->IsKing = true; mypiece->justking = true;
							board[row][col] = 'D';
							mypiece->Player = 'D';
						}
						return;
					}
				}
				else {
					cout << "Can not move to the specified column.Enter column again ";
					cin >> col;
					movepiece(row, col, mypiece);
				}
			}
			else {
				if ((mypiece->LocationY + 2) == row && (mypiece->LocationX + 2 == col || mypiece->LocationX - 2 == col)) {
					canjump(row, col, mypiece);
				}
				else {
					cout << "Can not move to the specified row, Enter valid row again ";
					cin >> row;
					movepiece(row, col, mypiece);
				}
			}
		}
		else if(mypiece->Player == 'l'){
			if ((mypiece->LocationY - 1) == row) {
				if (mypiece->LocationX - 1 == col || mypiece->LocationX + 1 == col) {
					if (board[row][col] != ' ') {
						cout << "Specified position already taken by a piece.Enter row of piece you want to move ";
						cin >> row;
						cout << "Enter col of piece you want to move ";
						cin >> col;
						checkpiece(row, col, mypiece->Player);

					}
					else {
						board[row][col] = mypiece->Player;
						board[mypiece->LocationY][mypiece->LocationX] = ' ';
						mypiece->changeY(row);
						mypiece->changeX(col);
						setjustkingfalse('L');
						if (row == 0) {
							mypiece->IsKing = true; mypiece->justking = true;
							board[row][col] = 'L';
							mypiece->Player = 'L';
						}
					}
				}
				else {
					cout << "Can not move to the specified column, Enter column again ";
					cin >> col;
					movepiece(row, col, mypiece);

				}
			}
			else {
				if ((mypiece->LocationY - 2) == row && (mypiece->LocationX + 2 == col || mypiece->LocationX - 2 == col)) {
					canjump(row, col, mypiece);
				}
				else {
					cout << "Can not move to the specified row, Enter row again ";
					cin >> row;
					movepiece(row, col, mypiece);
				}
			}
		}
	}
	void kingjump(int todeleterow, int todeletecol, piece* mypiece, int tomoverow, int tomovecol){
		int todeletepos;
		if (mypiece->justking == false && mypiece->IsKing == true) {
			if (mypiece->Player == 'D') {
				for (int count = 0;count < nooflightpieces;count++) {
					if (light[count]->LocationY == todeleterow && light[count]->LocationX == todeletecol) {
						todeletepos = count;
						break;
					}
				}
				for (int count = todeletepos;count < nooflightpieces;count++) {
					light[count] = light[count + 1];
				}
				light[nooflightpieces - 1] = NULL;
				delete light[nooflightpieces - 1];
				nooflightpieces--;
				board[todeleterow][todeletecol] = ' ';
				setjustkingfalse('D');
			}
			else {
				for (int count = 0;count < noofdarkpieces;count++) {
					if (dark[count]->LocationY == todeleterow && dark[count]->LocationX == todeletecol) {
						todeletepos = count;
						break;
					}
				}
				for (int count = todeletepos;count < noofdarkpieces;count++) {
					dark[count] = dark[count + 1];
				}
				dark[noofdarkpieces - 1] = NULL;
				delete dark[(noofdarkpieces - 1)];
				noofdarkpieces--;
				board[todeleterow][todeletecol] = ' ';
			}
			board[tomoverow][tomovecol] = board[mypiece->LocationY][mypiece->LocationX];
			board[mypiece->LocationY][mypiece->LocationX] = ' ';
			mypiece->changeX(tomovecol);
			mypiece->changeY(tomoverow);
			setjustkingfalse('L');
			checkjumps(mypiece);
		}
		else { 
			int row, col;
			cout << "The piece just become a king and can not jump any other pieces"<<endl;
			cout << "Enter row of piece you want to move ";
			cin >> row;
			cout << "Enter coloumn of piece you want to move ";
			cin >> col;
			checkpiece(row, col, mypiece->Player);
		}
	}
	void moveking(int row, int col, piece* mypiece) {             
		if ((mypiece->LocationY + 1) == row || mypiece->LocationY - 1 == row) {
			if ((mypiece->LocationX - 1) == col || (mypiece->LocationX + 1) == col) {
				if (board[row][col] != ' ') {
					cout << "Specified position already taken by a piece.Enter row of piece you want to move ";
					cin >> row;
					cout << "Enter col of piece you want to move";
					cin >> col;
					checkpiece(row, col, mypiece->Player);
				}
				else {
					board[row][col] = mypiece->Player;
					board[mypiece->LocationY][mypiece->LocationX] = ' ';
					mypiece->changeY(row);
					mypiece->changeX(col);
					if (mypiece->Player == 'D'|| mypiece->Player== 'd')
						setjustkingfalse('D');
					else setjustkingfalse('L');
					return;
				}
			}
			else {
				cout << "Can not move to the specified column.Enter column again ";
				cin >> col;
				moveking(row, col, mypiece);
			}
		}
		else {
			if (((mypiece->LocationY + 2) == row || mypiece->LocationY-2==row) && (mypiece->LocationX + 2 == col || mypiece->LocationX - 2 == col)){ //king jumping
				int todeleterow = (mypiece->LocationY + row) / 2;
				int todeletecol = (mypiece->LocationX + col) / 2;
				kingjump(todeleterow, todeletecol, mypiece, row, col);
			}
			else {
				cout << "Can not move to the specified row, Enter valid row again ";
				cin >> row;
				moveking(row, col, mypiece);
			}
		}
	}
	void checkpiece(int row, int col, char color) {
		char scolor, ccolor;
		if (color == 'd' || color == 'D') {
			scolor = 'd';ccolor = 'D';
		}
		else {
			scolor = 'l';ccolor = 'L';
		}
		if ((board[row][col] ==scolor || board[row][col] == ccolor)   && row >=0 && row < 8 && col >=0 && col<8) {
			if (color == 'D' || color == 'd') {
				for (int count = 0;count < noofdarkpieces;count++) {
					if (dark[count]->LocationY == row && dark[count]->LocationX == col)
					{
						int tomoverow, tomovecol;
						cout << "Enter row to which you want to move the piece ";
						cin >> tomoverow;
						cout << "Enter column to which you want to move the piece ";
						cin >> tomovecol;
						if (dark[count]->IsKing == false) {
							movepiece(tomoverow, tomovecol, dark[count]);             
						}
						else {
							moveking(tomoverow, tomovecol,  dark[count]);
						}
						return;
					}
				}

			}
			else if(color == 'L'|| color == 'l') {
				for (int count = 0;count < nooflightpieces;count++) {
					if (light[count]->LocationY == row && light[count]->LocationX == col)
					{
						int tomoverow, tomovecol;
						cout << "Enter row to which you want to move the piece ";
						cin >> tomoverow;
						cout << "Enter column to which you want to move the piece ";
						cin >> tomovecol;
						if (light[count]->IsKing == false) {
							movepiece(tomoverow, tomovecol, light[count]);                    
						}
						else {
							moveking(tomoverow, tomovecol, light[count]);
						}
						return;
					}
				}
			}

		}
		else {
			cout << "ERROR!!! Either input row is greater than 7 or less than 0 OR the piece on this position doesnot belong to you."<<endl<<"Enter ROW again : ";
			cin >> row;
			cout << "ERROR!!! Either input column is greater than 7 or less than 0 OR the piece on this position doesnot belong to you." << endl << "Enter COLUMN again : ";
			cin >> col;
			checkpiece(row, col, color);
		}}
	void setjustkingfalse(char color) {    
		if (color == 'D' || color == 'd') {
			for (int count = 0;count < noofdarkpieces;count++) {
				dark[count]->justking = false;
			}
		}
		else {
			for (int count = 0;count < nooflightpieces;count++) {
				light[count]->justking = false;
			}
		}
	} 
	void checkjumps(piece* mypiece){
		int currrow = mypiece->LocationY; int currcol = mypiece->LocationX;
		if (mypiece->Player == 'd' || mypiece->Player == 'D') {
			if (mypiece->IsKing == false) {
				if (board[currrow + 2][currcol + 2] == ' ') {
					if (board[currrow + 1][currcol + 1] == 'l' || board[currrow + 1][currcol + 1] == 'L') {
						movepiece( currrow+2,currcol+2 ,mypiece);
					}
					else return;
				}
				else if (board[currrow + 2][currcol - 2] == ' ') {
					if (board[currrow + 1][currcol - 1] == 'l' || board[currrow + 1][currcol - 1] == 'L') {
						movepiece(currrow + 2, currcol - 2, mypiece);;
					}
					else return;
				}
				else return;
				}
			if (mypiece->IsKing == true && mypiece->justking == false) {
				if (board[currrow + 2][currcol + 2] == ' ') {
					if (board[currrow + 1][currcol + 1] == 'l' || board[currrow + 1][currcol + 1] == 'L') {
						moveking(currrow + 2, currcol + 2, mypiece);
					}
					else return;
				}
				else if (board[currrow + 2][currcol - 2] == ' ') {
					if (board[currrow + 1][currcol - 1] == 'l' || board[currrow + 1][currcol - 1] == 'L') {
						moveking(currrow + 2, currcol - 2, mypiece);
					}
					else return;
				}
				if (board[currrow - 2][currcol + 2] == ' ') {
					if (board[currrow - 1][currcol + 1] == 'l' || board[currrow - 1][currcol + 1] == 'L') {
						moveking(currrow - 2, currcol + 2, mypiece);
					}
					else return;
				}
				else if (board[currrow - 2][currcol - 2] == ' ') {
					if (board[currrow - 1][currcol - 1] == 'l' || board[currrow - 1][currcol - 1] == 'L') {
						moveking(currrow - 2, currcol- 2, mypiece);
					}
					else return ;
				} return;
			}
		}
		else {
			if (mypiece->IsKing == false) {
				if (board[currrow - 2][currcol + 2] == ' ') {
					if (board[currrow - 1][currcol + 1] == 'd' || board[currrow - 1][currcol + 1] == 'D') {
						movepiece(currrow - 2, currcol + 2, mypiece);;
					}
					else return ;
				}
				else if (board[currrow - 2][currcol - 2] == ' ') {
					if (board[currrow - 1][currcol - 1] == 'd' || board[currrow - 1][currcol - 1] == 'D') {
						movepiece(currrow - 2, currcol - 2, mypiece);
					}
					else return ;
				}
			}
			if (mypiece->IsKing == true && mypiece->justking == false) {
				if (board[currrow + 2][currcol + 2] == ' ') {
					if (board[currrow + 1][currcol + 1] == 'd' || board[currrow + 1][currcol + 1] == 'D') {
						moveking(currrow + 2, currcol + 2, mypiece);
					}
					else return;
				}
				else if (board[currrow + 2][currcol - 2] == ' ') {
					if (board[currrow + 1][currcol - 1] == 'd' || board[currrow + 1][currcol - 1] == 'D') {
						moveking(currrow + 2, currcol - 2, mypiece);
					}
					else return;
				}
				if (board[currrow - 2][currcol + 2] == ' ') {
					if (board[currrow - 1][currcol + 1] == 'd' || board[currrow - 1][currcol + 1] == 'D') {
						moveking(currrow - 2, currcol + 2, mypiece);;
					}
					else return;
				}
				else if (board[currrow - 2][currcol - 2] == ' ') {
					if (board[currrow - 1][currcol - 1] == 'd' || board[currrow - 1][currcol - 1] == 'D') {
						moveking(currrow - 2, currcol - 2, mypiece);
					}
					else return;
				} return;
			}
		}
		return;
	}
};
int Board::noofdarkpieces = 12;
int Board::nooflightpieces = 12;


int main()
{
	Board checker;
	int row, col;
	char color;
	int input;
	bool turn = true;
	while (true) {
		cout << "Enter 1 to play. 2 to draw. 3 to resign ";
		cin >> input;
		if (input == 1) {
			if (turn == true) {
				color = 'd';
				system("CLS");
				checker.display();
				cout << "Dark turn.Enter row of piece you want to move ";
				cin >> row;
				cout << "Enter coloumn of piece you want to move ";
				cin >> col;
				checker.checkpiece(row, col, 'd');
				system("CLS");
				checker.display();
				if (checker.gamecheck('d')) {
					turn = false;
				}
				else {
					cout << color << " has won the game...... CONGRATULATIONS  !!!!!" << endl;
					break;
				}
			}
			else {
				color = 'l';
				system("CLS");
				checker.display();
				cout << "Light turn now.Enter row of piece you want to move ";
				cin >> row;
				cout << "Enter coloumn of piece you want to move ";
				cin >> col;
				checker.checkpiece(row, col, 'l');
				system("CLS");
				checker.display();
				if (checker.gamecheck('L')) {
					turn = true;
				}
				else {
					cout << color << " has won the game...... CONGRATULATIONS  !!!!!" << endl;
					break;
				}
			}
		}

		else if (input == 2) {
			cout << "You have selected to draw the game i.e. NO PLAYER WINS" <<endl;
			break;
		}
		else if (input == 3) {
			cout << "We are sorry one player has resigned ."<< endl;
			if (turn == true) {
				cout << "Dark resigned ....  Light wins"<<endl;
			}
			else cout << "Light resigns ...... Dark wins"<<endl;
			break;
		}
		else {
			continue;
		}

}
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
