/*
Joe Wonsil
CSC 1110
Project 7
*/

#include <iostream>
#include <string>

using namespace std;

char board[3][3] = { ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , ' ' , };

void PrintBoard()
{
	//Print A B C, 0 1 2 and each space of the board
	cout << "  A B C " << endl;
	cout << " +-+-+-+" << endl;
	cout << "0|" << board[0][0] << "|" << board[1][0] << "|" << board[2][0] << "|" << endl;
	cout << " +-+-+-+" << endl;
	cout << "1|" << board[0][1] << "|" << board[1][1] << "|" << board[2][1] << "|" << endl;
	cout << " +-+-+-+" << endl;
	cout << "2|" << board[0][2] << "|" << board[1][2] << "|" << board[2][2] << "|" << endl;
	cout << " +-+-+-+" << endl;
}

//This function checks to see if any player has won by looping through the rows to see if any three spaces are equal
int CheckColumns()
{
	int win = 0;

	for (int column_index = 0; column_index < 3; column_index++)
	{
		if (board[0][column_index] == board[1][column_index] && board[1][column_index] == board[2][column_index] && board[0][column_index] != ' ')
		{
			if (board[0][column_index] == 'x')
				win = -1;
			if (board[0][column_index] == 'o')
				win = 1;
		}
	}

	return win;
}

//This function checks to see if any player has won by looping through the rows to see if any three spaces are equal
int CheckRows()
{
	int win = 0;
	for (int row_index = 0; row_index < 3; row_index++)
	{
		if (board[row_index][0] == board[row_index][1] && board[row_index][1] == board[row_index][2] && board[row_index][0] != ' ')
		{
			if (board[row_index][0] == 'x')
				win = -1;
			if (board[row_index][0] == 'o')
				win = 1;
		}
	}
	return win;
}

//Function checks the two diagonals to see if there are any equal spots that aren't a space
int CheckDiagonals()
{
	int win = 0;
	if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[1][1] != ' ')
	{
		if (board[1][1] == 'x')
			win = -1;
		if (board[1][1] == 'o')
			win = 1;
	}
	if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[1][1] != ' ')
	{
		if (board[1][1] == 'x')
			win = -1;
		if (board[1][1] == 'o')
			win = 1;
	}
	return win;
}

//Function that runs through each win checker to see if either user won
int CheckForWin()
{
	int who_won = CheckRows();

	if (who_won == 0)
		who_won = CheckColumns();

	if (who_won == 0)
		who_won = CheckDiagonals();

	return who_won;
}

//This checks to see if there is a tie, if any spaces are found there is not tie.
//If the program makes it to this function and there are no spaces left, it means
//no one won, as CheckForWin runs first
bool ThereIsATie()
{
	for (int row_index = 0; row_index < 3; row_index++)
	{
		for (int column_index = 0; column_index < 3; column_index++)
		{
			if (board[row_index][column_index] == ' ')
				return false;
		}
	}
	
	return true;
}

//Step 1 of the AI algorithm, if it can win, do it
//Indexes through the board and if any of the (legal) moves it can make result in a win
//it will make that move. If not return -1, signalling to move to the next step.
int WinCheck()
{
	for (int row_index = 0; row_index < 3; row_index++)
	{
		for (int column_index = 0; column_index < 3; column_index++)
		{
			if (board[row_index][column_index] == ' ')
			{
				board[row_index][column_index] = 'x';
				if (CheckForWin() == -1)
				{
					board[row_index][column_index] = 'x';
					return 1;
				}
				else
				{
					board[row_index][column_index] = ' ';
				}
			}
				
		}
	}
	return -1;
}

//Step 2 of the alforithm, if it can stop the opponent from winning, do it.
//Indexes through the board and if any of the (legal) moves it can make result in stopping a win
//for the opponent it will make that move. If not return -1, signalling to move to the next step.
int LossCheck()
{
	for (int row_index = 0; row_index < 3; row_index++)
	{
		for (int column_index = 0; column_index < 3; column_index++)
		{
			if (board[row_index][column_index] == ' ')
			{
				board[row_index][column_index] = 'o';
				if (CheckForWin() == 1)
				{
					board[row_index][column_index] = 'x';
					return 1;
				}
				else
				{
					board[row_index][column_index] = ' ';
				}
			}

		}
	}
	return -1;
}

//Step 3 of the algorithm, if it can make a move that will result in the next move having
//two opportunites for a win do it. Indexes through the board and checks each blank space for
//wins, if the next move will result in two wins (or more), kept track of using the int tracker,
//make the move. If not, return -1 for the next step.
int ForkCheck()
{
	int tracker = 0;
	for (int row_index = 0; row_index < 3; row_index++)
	{
		for (int column_index = 0; column_index < 3; column_index++)
		{
			if (board[row_index][column_index] == ' ')
			{
				board[row_index][column_index] = 'x';
				for (int row_index2 = 0; row_index2 < 3; row_index2++)
				{
					for (int column_index2 = 0; column_index2 < 3; column_index2++)
					{
						if (board[row_index2][column_index2] == ' ')
						{
							board[row_index][column_index] = 'x';
							if (CheckForWin() == -1)
								tracker++;
							board[row_index][column_index] = ' ';

						}

					}
				}

				if (tracker >= 2)
				{
					board[row_index][column_index] = 'x';
					return 1;
				}
				else
				{
					board[row_index][column_index] = ' ';
					return -1;
				}
			}

		}
	}
	return -1;
}

//Step 4, Uses ForkChecker to see if the opponent can make a fork, if possible, take
//their spot instead. If not return -1 for the next step
int ForkBlock()
{
	int tracker = 0;
	for (int row_index = 0; row_index < 3; row_index++)
	{
		for (int column_index = 0; column_index < 3; column_index++)
		{
			if (board[row_index][column_index] == ' ')
			{
				board[row_index][column_index] = 'o';
				for (int row_index2 = 0; row_index2 < 3; row_index2++)
				{
					for (int column_index2 = 0; column_index2 < 3; column_index2++)
					{
						if (board[row_index2][column_index2] == ' ')
						{
							board[row_index][column_index] = 'o';
							if (CheckForWin() == 1)
								tracker++;
							board[row_index][column_index] = ' ';

						}
					}
				}

				if (tracker >= 2)
				{
					board[row_index][column_index] = 'x';
					return 1;
				}
				else
				{
					board[row_index][column_index] = ' ';
					return -1;
				}
			}

		}
	}
	return -1;
}

//Step 5, If the opponent has taken a corner, take the opposite one.
//Return -1 for the next step otherwise
int OppCorner()
{
	if (board[0][0] == 'o' && board[2][2] == ' ')
	{
		board[2][2] = 'x';
		return 1;
	}

	if (board[2][2] == 'o' && board[0][0] == ' ')
	{
		board[0][0] = 'x';
		return 1;
	}

	if (board[0][2] == 'o' && board[2][0] == ' ')
	{
		board[2][0] = 'x';
		return 1;
	}

	if (board[2][0] == 'o' && board[0][2] == ' ')
	{
		board[0][2] = 'x';
		return 1;
	}

	return -1;

}

//Step 6, If the center has not been taken, take it
//If not, return -1 for the next step
int Center()
{
	if (board[1][1] == ' ')
	{
		board[1][1] = 'x';
		return 1;
	}
	else
		return -1;
}

//Step 7, If there is an empty corner, take it 
//if not, move to the next step
int EmptyCorner()
{
	if (board[2][2] == ' ')
	{
		board[2][2] = 'x';
		return 1;
	}

	if (board[0][0] == ' ')
	{
		board[0][0] = 'x';
		return 1;
	}

	if (board[2][0] == ' ')
	{
		board[2][0] = 'x';
		return 1;
	}

	if (board[0][2] == ' ')
	{
		board[0][2] = 'x';
		return 1;
	}

	return -1;

}

//Step 8. This is a special case where if this step did not exist, it would be possible to beat the AI.
//It comes about when the user goes first and places a o at [0][2], then [2][0]. If this is not the case, 
//return -1 for the next step
int BadMove()
{
	if (board[0][0] == 'o' && board[2][2] == 'o')
	{
		board[1][2] = 'x';
		return 1;
	}
	if (board[2][0] == 'o' && board[0][2] == 'o')
	{
		board[1][2] = 'x';
		return 1;
	}

	return -1;
}

//Step 9. The last step looks for an empty side and makes a move there.
void EmptySide()
{
	if (board[0][1] == ' ')
	{
		board[0][1] = 'x';
		return;
	}

	if (board[1][0] == ' ')
	{
		board[1][0] = 'x';
		return;
	}

	if (board[2][1] == ' ')
	{
		board[2][1] = 'x';
		return;
	}

	if (board[1][2] == ' ')
	{
		board[1][2] = 'x';
		return;
	}
}

//This function runs through all of the algorithms steps, if one returns -1, it goes to the next.
void ComputerTurn()
{
	int checker = -1;
	//Step 1
	checker = WinCheck();
	if (checker == -1)
	{
		//Step 2
		checker = LossCheck();
		if (checker == -1)
		{
			//Step 3
			checker = ForkCheck();
			if (checker == -1)
			{
				//Step 4
				checker = ForkBlock();
				if (checker == -1)
				{
					//Step 5
					checker = Center();
					if (checker == -1)
					{
						//Step 6
						checker = OppCorner();
						if (checker == -1)
						{
							//Step 7
							checker = BadMove();
							if (checker == -1)
							{
								//Step 8
								checker = EmptyCorner();
								if (checker == -1)
								{
									//Step 9
									EmptySide();
								}
							}
						}	
					}
				}
			}
		}
	}
}


int main()
{
	//-1 is Player 1, 1 is Player 2
	int who_won = 0;
	//-1 is Player 1, 1 is Player 2
	int whose_turn = -1;
	//Contains the users' raw selections
	string move;

	//Ask the user if he want to go first
	cout << "Do you want to go first? Y/N:";
	cin >> move;

	//Make user go first
	if (move == "Y")
	{
		whose_turn = 1;
	}
	//Let the computer go first
	if (move == "N")
	{
		whose_turn = -1;
	}
	//If the user inputs anything invalid, make the AI go first
	if (move != "Y" && move != "N")
	{
		cout << "Since you couldn't enter a valid input the computer is going first." << endl;
		//Pause to let them read the message, then continue
		system("pause");
	}

	while (true)
	{
		//The selections that relate to the board are initialized to a negative number
		//This way if they are still negative numbers after conversion we know it's invalid input
		int x = -1;
		int y = -1;

		PrintBoard();

		//If there are any wins on the board, declare the winner and exit
		if (CheckForWin() != 0)
		{
			if (CheckForWin() == -1)
			{
				cout << "The Computer Won" << endl;
				break;
			}
			if (CheckForWin() == 1)
			{
				cout << "It is impossible to beat this computer, if you're seeing this you cheated." << endl;
				break;
			}
		}

		//If there is a tie, declare so, and exit
		if (ThereIsATie() == true)
		{
			cout << "The game is a draw." << endl;
			break;
		}

		//If it is the computer's turn, run the algorithm
		if (whose_turn == -1)
		{
			cout << "The Computer's Move:" << endl;
			ComputerTurn();
		}
		
		//If it's the user's turn, let the user move
		if (whose_turn == 1)
		{
			cout << "Your Move:";

			//Receive their selection
			cin >> move;
			cout << endl;

			//If they input anything that's not two characters, it's invalid
			if (move.size() != 2)
			{
				cout << "Bad input" << endl;
				continue;
			}

			//Convert the letter to the corresponding number in the board index
			x = move[0] - 'A';

			//Convert the number from a char number to a int number
			y = move[1] - '0';

			//If either of the chars are still negative, this means it's invalid
			if (x < 0 || y < 0)
			{
				cout << "Bad input" << endl << endl;
				continue;
			}

			//If they selected a space that is already occupied it's also invalid
			if (board[x][y] != ' ')
			{
				cout << "Bad input" << endl << endl;
				continue;
			}

			//Place the correct mark into the correct space
			board[x][y] = 'o';

		}

		//This will switch users after their turn is over
		if (whose_turn == -1)
			whose_turn = 1;
		else
			whose_turn = -1;
	}
	system("pause");
}