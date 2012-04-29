#include <iostream>
#include <string.h>
#include <sstream>

//*************************************************************************//
//
//  FILE NAME: BonusConnect4Source.cpp
//  AUTHOR: Ruben C. Chapa, III
//  INTIAL CREATION DATE: April 12, 2012
//  DESCRIPTION: A game of connect 4 with one human player and one AI controlled opponent
//  DATE OF LAST REVISION:	April 28, 2012
//
//*************************************************************************//


using namespace std;

char board[6][7]; //main board
char simulatedstate[6][7]; //used for simulating different board states
int defaultdrop = 0; //setting the defualt drop place to the first column

//-------------------------prepareBoard------------------------
//  Sets all spaces to '.' which means the space is empty
//  Input:  none
//  Output: none

void prepareBoard(void)
{
    for(int i=0; i<6; i++)    //This loops on the rows.
	{
		for(int j=0; j<7; j++) //This loops on the columns
		{
			board[i][j] = '.';
		}
	}
}

//-------------------------printBoard------------------------
//  Prints the entire current state of the board
//  Input:  none
//  Output: none

void printBoard(void)
{
    for(int i=0; i<6; i++)    //This loops on the rows.
	{
		for(int j=0; j<7; j++) //This loops on the columns
		{
			cout << board[i][j] << "  ";
		}
		cout << endl;
	}
}

//-------------------------checkifEmpty------------------------
//  Checks whether a specified space is empty
//  Input:  The specified row and column
//  Output: returns 1 if empty, returns 0 if not empty

int checkifEmpty(int row, int column)
{
    if(board[row][column] == '.')
    {
        return 1;
    }else
    {
        return 0;
    }
}

//-------------------------insertRedDisk------------------------
//  Inserts a red disk into the specified column
//  Input:  Column number
//  Output: returns -1 if column is full otherwise returns the row where the red disk fell

int insertRedDisc(int column)
{
    int flag = 0;
    int row = 5; //start at the bottom row
    int full = 0;
    int storerow = 0;
    while(flag == 0)
    {
        if(checkifEmpty(row, column)) //make sure space isnt occupied
        {
            board[row][column] = 'R'; //if not occupied then insert red disk here
            storerow = row; //remember row where where disk was placed
            flag = 1; //get out of here
        }else
        {
            row--; //went to far, the column is full so subtract 1 to keep index
            if(row < 0) //column s full set full to 1 and get out of here
            {
                cout << "YOU FOOL!!! This column is full!!! Try Again..." << endl << endl;
                full = 1;
                flag = 1;
            }
        }
    }
    if(full == 1)
    {
        return -1; //send if full
    }else
    {
        return storerow; // send back row where disc was inserted
    }
}

//-------------------------insertYellowDisk------------------------
//  Inserts a yellow disk into the specified column
//  Input:  Column number
//  Output: returns -1 if column is full otherwise returns the row where the red disk fell

int insertYellowDisc(int column)
{
    int flag = 0;
    int row = 5; //start at the bottom row
    int full = 0;
    int storerow = 0;
    while(flag == 0)
    {
        if(checkifEmpty(row, column)) //make sure space isnt occupied
        {
            board[row][column] = 'Y'; //if not occupied then insert yellow disk here
            storerow = row; //remember row where where disk was placed
            flag = 1; //get out of here
        }else
        {
            row--; //went to far, the column is full so subtract 1 to keep index
            if(row < 0) //column s full set full to 1 and get out of here
            {
                cout << "YOU FOOL!!! This column is full!!! Try Again..." << endl << endl;
                full = 1;
                flag = 1;
            }
        }
    }
    if(full == 1)
    {
        return -1; //if full
    }else
    {
        return storerow; //send back row here disc was inserted
    }
}

//-------------------------chooseColumn------------------------
//  Asks for column number for the user via the console and restrics the user to typing in integers 1-7 only
//  Input:  none
//  Output: returns column number the user typed in or returns -1 if 'exit' was typed, also prints board if 'showboard' was typed

int chooseColumn(void)
{
    string one ("1"); //declaration of possible numbers the user should type
    string two ("2");
    string three ("3");
    string four ("4");
    string five ("5");
    string six ("6");
    string seven ("7");
    string input;
    int column = 0;
    int breakflag = 0;
    while(breakflag != 1)
    {
        cin >> input;
        if((input.compare(one) == 0) || (input.compare(two) == 0) || (input.compare(three) == 0) || (input.compare(four) == 0) || (input.compare(five) == 0) || (input.compare(six) == 0) || (input.compare(seven) == 0)) //use input.compare to make sure that only an integer 1-7 was typed
        {
            stringstream ss(input); //if integer typed was 1-7 then convert from a string into an integer
            ss >> column;
            breakflag = 1;
        }else
        {
            if(input.compare("exit") == 0) //checks if 'exit' was typed and returns -1 if it was
            {
                return -1;
            }
            if(input.compare("showboard") == 0) //checks if 'showboard' was typed and if it was then print the board
            {
                printBoard();
            }else
            {
                cout << "Pathetic human...I see your primitve memory is already failing..." << endl; //illegal character typed
                cout << "Type numbers 1-7 ONLY!!!!" << endl;
            }

        }

    }
    return column - 1; //subract 1 to fix index
}

//-------------------------checkWinner------------------------
//  Checks the current state of the board to see if there are any 4 disks lined up either horizontally, vertically, or diagonally
//  Input:  a specified row and column (usually the row and column where the last disk was placed)
//  Output: returns 1 if a winner was found or returns 0 if no winner was found

int checkWinner(int row, int column)
{
    int tempcolumnminus1 = column - 1; //check for bounds
    int tempcolumnminus2 = column - 2;
    int tempcolumnminus3 = column - 3;
    int tempcolumnplus1 = column + 1;
    int tempcolumnplus2 = column + 2;
    int tempcolumnplus3 = column + 3;
    int temprowminus1 = row - 1;
    int temprowminus2 = row - 2;
    int temprowminus3 = row - 3;
    int temprowplus1 = row + 1;
    int temprowplus2 = row + 2;
    int temprowplus3 = row + 3;

    if((board[row][column] == board[row - 1][column]) && (board[row][column] == board[row - 2][column]) && (board[row][column] == board[row - 3][column]) && (board[row - 1][column] == board[row - 2][column]) && (board[row - 1][column] == board[row - 3][column]) && (board[row - 2][column] == board[row - 3][column]) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check up
    {
        cout << "winner up" << endl;
        return 1;
    }
    else
    {
        if((board[row][column] == board[row - 1][column + 1]) && (board[row][column] == board[row - 2][column + 2]) && (board[row][column] == board[row - 3][column + 3]) && (board[row - 1][column + 1] == board[row - 2][column + 2]) && (board[row - 1][column + 1] == board[row - 3][column + 3]) && (board[row - 2][column + 2] == board[row - 3][column + 3]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper right
        {
            cout << "winner diagnol upper right" << endl;
            return 1;
        }
        else
        {
            if((board[row][column] == board[row][column + 1]) && (board[row][column] == board[row][column + 2]) && (board[row][column] == board[row][column + 3]) && (board[row][column + 1] == board[row][column + 2]) && (board[row][column + 1] == board[row][column + 3]) && (board[row][column + 2] == board[row][column + 3]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6)) // check right
            {
                cout << "winner right" << endl;
                return 1;
            }
            else
            {
                if((board[row][column] == board[row + 1][column + 1]) && (board[row][column] == board[row + 2][column + 2]) && (board[row][column] == board[row + 3][column + 3]) && (board[row+ 1][column + 1] == board[row + 2][column + 2]) && (board[row+ 1][column + 1] == board[row + 3][column + 3]) && (board[row+ 2][column + 2] == board[row + 3][column + 3]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower right
                {
                    cout << "winner diagnol lower right" << endl;
                    return 1;
                }
                else
                {
                    if((board[row][column] == board[row + 1][column]) && (board[row][column] == board[row + 2][column]) && (board[row][column] == board[row + 3][column]) && (board[row + 1][column] == board[row + 2][column]) && (board[row+ 1][column] == board[row + 3][column]) && (board[row + 2][column] == board[row + 3][column]) && (temprowminus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check down
                    {
                        cout << "winner down" << endl;
                        return 1;
                    }
                    else
                    {
                        if((board[row][column] == board[row + 1][column - 1]) && (board[row][column] == board[row + 2][column - 2]) && (board[row][column] == board[row + 3][column - 3]) && (board[row + 1][column - 1] == board[row + 2][column - 2]) && (board[row + 1][column - 1] == board[row + 3][column - 3]) && (board[row + 2][column - 2] == board[row + 3][column - 3]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower left
                        {
                            cout << "winner diagnol lower left" << endl;
                            return 1;
                        }
                        else
                        {
                            if((board[row][column] == board[row][column - 1]) && (board[row][column] == board[row][column - 2]) && (board[row][column] == board[row][column - 3]) && (board[row][column - 1] == board[row][column - 2]) && (board[row][column - 1] == board[row][column - 3]) && (board[row][column - 2] == board[row][column - 3]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6)) // check left
                            {
                                cout << "winner left" << endl;
                                return 1;
                            }
                            else
                            {
                                if((board[row][column] == board[row - 1][column - 1]) && (board[row][column] == board[row - 2][column - 2]) && (board[row][column] == board[row - 3][column - 3]) && (board[row - 1][column - 1] == board[row - 2][column - 2]) && (board[row - 1][column - 1] == board[row - 3][column - 3]) && (board[row - 2][column - 2] == board[row - 3][column - 3]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper left
                                {
                                    cout << "winner diagnol upper left" << endl;
                                    return 1;
                                }
                                else
                                {
                                    if((board[row][column] == board[row][column - 1]) && (board[row][column] == board[row][column + 1]) && (board[row][column] == board[row][column + 2]) && (board[row][column - 1] == board[row][column + 1]) && (board[row][column - 1] == board[row][column + 2]) && (board[row][column + 1] == board[row][column + 2]) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6)  && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6)  && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6)) // 0x00 if lands with 1 on the left and 2 on the right
                                    {
                                        cout << "winner inbetween 1 to the left and 2 to the right" << endl;
                                        return 1;
                                    }
                                    else
                                    {
                                        if((board[row][column] == board[row][column - 1]) && (board[row][column] == board[row][column - 2]) && (board[row][column] == board[row][column + 1]) && (board[row][column - 1] == board[row][column - 2]) && (board[row][column - 1] == board[row][column + 1]) && (board[row][column - 2] == board[row][column + 1]) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6)) // 00x0 if lands with 2 on the left and 1 on the right
                                        {
                                            cout << "winner inbetween 2 to the left and 1 to the right" << endl;
                                            return 1;
                                        }
                                        else
                                        {
                                            if((board[row][column] == board[row - 1][column + 1]) && (board[row][column] == board[row + 1][column - 1]) && (board[row][column] == board[row + 2][column - 2]) && (board[row - 1][column + 1] == board[row + 1][column - 1]) && (board[row - 1][column + 1] == board[row + 2][column - 2]) && (board[row + 1][column - 1] == board[row + 2][column - 2]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5)) // if lands with 2 diagnolly down left and 1 diagnolly up right
                                            {
                                                cout << "winner 2 diagnolly down left and 1 diagnolly up right" << endl;
                                                return 1;
                                            }
                                            else
                                            {
                                                if((board[row][column] == board[row + 1][column - 1]) && (board[row][column] == board[row - 1][column + 1]) && (board[row][column] == board[row - 2][column + 2]) && (board[row + 1][column - 1] == board[row - 1][column + 1]) && (board[row + 1][column - 1] == board[row - 2][column + 2]) && (board[row - 1][column + 1] == board[row - 2][column + 2]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5)) // if lands with 1 diagnolly down left and 2 diagnolly up right
                                                {
                                                    cout << "winner 1 diagnolly down left and 2 diagnolly up right" << endl;
                                                    return 1;
                                                }else
                                                {
                                                    if((board[row][column] == board[row - 1][column - 1]) && (board[row][column] == board[row + 1][column + 1]) && (board[row][column] == board[row + 2][column + 2]) && (board[row - 1][column - 1] == board[row + 1][column + 1]) && (board[row - 1][column - 1] == board[row + 2][column + 2]) && (board[row + 1][column + 1] == board[row + 2][column + 2]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5)) // if lands with 1 diagnolly up left and 2 diagnolly down right
                                                    {
                                                        cout << "winner 1 diagnolly up left and 2 diagnolly down right" << endl;
                                                        return 1;
                                                    }
                                                    else
                                                    {
                                                        if((board[row][column] == board[row - 1][column - 1]) && (board[row][column] == board[row - 2][column - 2]) && (board[row][column] == board[row + 1][column + 1]) && (board[row - 1][column - 1] == board[row - 2][column - 2]) && (board[row - 1][column - 1] == board[row + 1][column + 1]) && (board[row - 2][column - 2] == board[row + 1][column + 1]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5)) // if lands with 2 diagnolly up left and 1 diagnolly down right
                                                        {
                                                            cout << "winner 2 diagnolly up left and 1 diagnolly down right" << endl;
                                                            return 1;
                                                        }
                                                        else
                                                        {
                                                            return 0; //return 0 if no winner was found
                                                        }
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}

//-------------------------simulatecheckifEmpty------------------------
//  AI uses the function on its simulated board to check whether a space is empty
//  Input:  The specified row and column
//  Output: returns 1 if empty, returns 0 if not empty

int simulatecheckifEmpty(int row, int column)
{
    if(simulatedstate[row][column] == '.') //checks the simulatedstate board which has already been loaded with state of the regular board
    {
        return 1;
    }else
    {
        return 0;
    }
}

//-------------------------simulateRedDisk------------------------
//  AI uses this fuction to simulate Inserting a red disk into a specified column
//  Input:  Column number
//  Output: returns -1 if column is full otherwise returns the row where the simulated red disk fell

int simulateRedDisc(int column)
{
    int flag = 0;
    int row = 5; //start at bottom row
    int full = 0;
    int storerow = 0;
    while(flag == 0)
    {
        if(simulatecheckifEmpty(row, column))
        {
            simulatedstate[row][column] = 'R';
            storerow = row;
            flag = 1;
        }else
        {
            row--;
            if(row < 0)
            {
                //column is full set flag and get out of here
                full = 1;
                flag = 1;
            }
        }
    }
    if(full == 1)
    {
        return -1; //send if full
    }else
    {
        return storerow; // send back row where disc was inserted
    }
}

//-------------------------simulateYellowDisk------------------------
//  AI uses this fuction to simulate Inserting a yellow disk into a specified column
//  Input:  Column number
//  Output: returns -1 if column is full otherwise returns the row where the simulated red disk fell

int simulateYellowDisc(int column)
{
    int flag = 0;
    int row = 5; //start at bottom row
    int full = 0;
    int storerow = 0;
    while(flag == 0)
    {
        if(simulatecheckifEmpty(row, column))
        {
            simulatedstate[row][column] = 'Y';
            storerow = row;
            flag = 1;
        }else
        {
            row--;
            if(row < 0)
            {
                //column is full set flag and get out of here
                full = 1;
                flag = 1;
            }
        }
    }
    if(full == 1)
    {
        return -1; //send if full
    }else
    {
        return storerow; // send back row where disc was inserted
    }
}

//-------------------------simulatecheckWinner------------------------
//  AI uses this function to simulate checking the current state of the simulated board to see if there are any 4 disks lined up either horizontally, vertically, or diagonally
//  Input:  a specified row and column (usually the row and column where the last disk was placed)
//  Output: returns 1 if a simulated winner was found or returns 0 if no simulated winner was found

int simulatecheckWinner(int row, int column)
{
    int tempcolumnminus1 = column - 1; //check for bounds
    int tempcolumnminus2 = column - 2;
    int tempcolumnminus3 = column - 3;
    int tempcolumnplus1 = column + 1;
    int tempcolumnplus2 = column + 2;
    int tempcolumnplus3 = column + 3;
    int temprowminus1 = row - 1;
    int temprowminus2 = row - 2;
    int temprowminus3 = row - 3;
    int temprowplus1 = row + 1;
    int temprowplus2 = row + 2;
    int temprowplus3 = row + 3;

    if((simulatedstate[row][column] == simulatedstate[row - 1][column]) && (simulatedstate[row][column] == simulatedstate[row - 2][column]) && (simulatedstate[row][column] == simulatedstate[row - 3][column]) && (simulatedstate[row - 1][column] == simulatedstate[row - 2][column]) && (simulatedstate[row - 1][column] == simulatedstate[row - 3][column]) && (simulatedstate[row - 2][column] == simulatedstate[row - 3][column]) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check up
    {
        //cout << "winner up" << endl;
        return 1;
    }
    else
    {
        if((simulatedstate[row][column] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row][column] == simulatedstate[row - 3][column + 3]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row - 3][column + 3]) && (simulatedstate[row - 2][column + 2] == simulatedstate[row - 3][column + 3]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper right
        {
            //cout << "winner diagnol upper right" << endl;
            return 1;
        }
        else
        {
            if((simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 2]) && (simulatedstate[row][column] == simulatedstate[row][column + 3]) && (simulatedstate[row][column + 1] == simulatedstate[row][column + 2]) && (simulatedstate[row][column + 1] == simulatedstate[row][column + 3]) && (simulatedstate[row][column + 2] == simulatedstate[row][column + 3]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6)) // check right
            {
                //cout << "winner right" << endl;
                return 1;
            }
            else
            {
                if((simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row][column] == simulatedstate[row + 3][column + 3]) && (simulatedstate[row+ 1][column + 1] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row+ 1][column + 1] == simulatedstate[row + 3][column + 3]) && (simulatedstate[row+ 2][column + 2] == simulatedstate[row + 3][column + 3]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower right
                {
                    //cout << "winner diagnol lower right" << endl;
                    return 1;
                }
                else
                {
                    if((simulatedstate[row][column] == simulatedstate[row + 1][column]) && (simulatedstate[row][column] == simulatedstate[row + 2][column]) && (simulatedstate[row][column] == simulatedstate[row + 3][column]) && (simulatedstate[row + 1][column] == simulatedstate[row + 2][column]) && (simulatedstate[row+ 1][column] == simulatedstate[row + 3][column]) && (simulatedstate[row + 2][column] == simulatedstate[row + 3][column]) && (temprowminus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check down
                    {
                        //cout << "winner down" << endl;
                        return 1;
                    }
                    else
                    {
                        if((simulatedstate[row][column] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row][column] == simulatedstate[row + 3][column - 3]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row + 3][column - 3]) && (simulatedstate[row + 2][column - 2] == simulatedstate[row + 3][column - 3]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower left
                        {
                            //cout << "winner diagnol lower left" << endl;
                            return 1;
                        }
                        else
                        {
                            if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column - 2]) && (simulatedstate[row][column] == simulatedstate[row][column - 3]) && (simulatedstate[row][column - 1] == simulatedstate[row][column - 2]) && (simulatedstate[row][column - 1] == simulatedstate[row][column - 3]) && (simulatedstate[row][column - 2] == simulatedstate[row][column - 3]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6)) // check left
                            {
                                //cout << "winner left" << endl;
                                return 1;
                            }
                            else
                            {
                                if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row][column] == simulatedstate[row - 3][column - 3]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row - 3][column - 3]) && (simulatedstate[row - 2][column - 2] == simulatedstate[row - 3][column - 3]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper left
                                {
                                    //cout << "winner diagnol upper left" << endl;
                                    return 1;
                                }
                                else
                                {
                                    if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 2]) && (simulatedstate[row][column - 1] == simulatedstate[row][column + 1]) && (simulatedstate[row][column - 1] == simulatedstate[row][column + 2]) && (simulatedstate[row][column + 1] == simulatedstate[row][column + 2]) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6)  && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6)  && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6)) // 0x00 if lands with 1 on the left and 2 on the right
                                    {
                                        //cout << "winner inbetween 1 to the left and 2 to the right" << endl;
                                        return 1;
                                    }
                                    else
                                    {
                                        if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column - 2]) && (simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column - 1] == simulatedstate[row][column - 2]) && (simulatedstate[row][column - 1] == simulatedstate[row][column + 1]) && (simulatedstate[row][column - 2] == simulatedstate[row][column + 1]) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6)) // 00x0 if lands with 2 on the left and 1 on the right
                                        {
                                            //cout << "winner inbetween 2 to the left and 1 to the right" << endl;
                                            return 1;
                                        }
                                        else
                                        {
                                            if((simulatedstate[row][column] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row + 2][column - 2]) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5)) // if lands with 2 diagnolly down left and 1 diagnolly up right
                                            {
                                                //cout << "winner 2 diagnolly down left and 1 diagnolly up right" << endl;
                                                return 1;
                                            }
                                            else
                                            {
                                                if((simulatedstate[row][column] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row - 2][column + 2]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5)) // if lands with 1 diagnolly down left and 2 diagnolly up right
                                                {
                                                    //cout << "winner 1 diagnolly down left and 2 diagnolly up right" << endl;
                                                    return 1;
                                                }else
                                                {
                                                    if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row + 1][column + 1] == simulatedstate[row + 2][column + 2]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5)) // if lands with 1 diagnolly up left and 2 diagnolly down right
                                                    {
                                                        //cout << "winner 1 diagnolly up left and 2 diagnolly down right" << endl;
                                                        return 1;
                                                    }
                                                    else
                                                    {
                                                        if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row - 2][column - 2] == simulatedstate[row + 1][column + 1]) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5)) // if lands with 2 diagnolly up left and 1 diagnolly down right
                                                        {
                                                            //cout << "winner 2 diagnolly up left and 1 diagnolly down right" << endl;
                                                            return 1;
                                                        }
                                                        else
                                                        {
                                                            return 0; //return 0 if no winner was found
                                                        }
                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }

        }

    }

}

//-------------------------simulateTwo------------------------
//  AI uses this function to simulate checking if it can setup 2 disks somewhere on the board
//  Input:  a specified row and column (usually the row and column where the last disk was placed)
//  Output: returns 1 if simulation was succesfull in setting up 2 disks or returns 0 if unable to find a place to setup 2 disks

int simulateTwo(int row, int column)
{
    int tempcolumnminus1 = column - 1; //check for bounds
    int tempcolumnminus2 = column - 2;
    int tempcolumnminus3 = column - 3;
    int tempcolumnplus1 = column + 1;
    int tempcolumnplus2 = column + 2;
    int tempcolumnplus3 = column + 3;
    int temprowminus1 = row - 1;
    int temprowminus2 = row - 2;
    int temprowminus3 = row - 3;
    int temprowplus1 = row + 1;
    int temprowplus2 = row + 2;
    int temprowplus3 = row + 3;
    if((simulatedstate[row][column] == simulatedstate[row - 1][column]) && (simulatedstate[row - 2][column] == '.') && (simulatedstate[row - 3][column] == '.') && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check up
    {
        //cout << "placing up" << endl;
        return 1;
    }
    else
    {
        if((simulatedstate[row][column] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row - 2][column + 2] == '.') && (simulatedstate[row - 3][column + 3] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper right
        {
            //cout << "placing diagnol upper right" << endl;
            return 1;
        }
        else
        {
            if((simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column + 2] == '.') && (simulatedstate[row][column + 3] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6)) // check right
            {
                //cout << "placing right" << endl;
                return 1;
            }
            else
            {
                if((simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row + 2][column + 2] == '.') && (simulatedstate[row + 3][column + 3] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower right
                {
                    //cout << "placing diagnol lower right" << endl;
                    return 1;
                }
                else
                {
                    if((simulatedstate[row][column] == simulatedstate[row + 1][column]) && (simulatedstate[row - 1][column] == '.') && (simulatedstate[row - 2][column] == '.') && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5)) // check down
                    {
                        //cout << "placing down" << endl;
                        return 1;
                    }
                    else
                    {
                        if((simulatedstate[row][column] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row + 2][column - 2] == '.') && (simulatedstate[row + 3][column - 3] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower left
                        {
                            //cout << "placing diagnol lower left" << endl;
                            return 1;
                        }
                        else
                        {
                            if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column - 2] == '.') && (simulatedstate[row][column - 3] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6)) // check left
                            {

                                //cout << "placing left" << endl;
                                return 1;
                            }
                            else
                            {
                                if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row - 2][column - 2] == '.') && (simulatedstate[row - 3][column - 3] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper left
                                {
                                    //cout << "placing diagnol upper left" << endl;
                                    return 1;
                                }
                                else
                                {
                                    return 0; //return 0 if simulation was unsuccessfull
                                }
                            }

                        }

                    }

                }

            }

        }

    }

}

//-------------------------simulateThree------------------------
//  AI uses this function to simulate checking if it can setup 3 disks somewhere on the board
//  Input:  a specified row and column (usually the row and column where the last disk was placed)
//  Output: returns 1 if simulation was succesfull in setting up 3 disks or returns 0 if unable to find a place to setup 3 disks

int simulateThree(int row, int column)
{
    int tempcolumnminus1 = column - 1; //check for bounds
    int tempcolumnminus2 = column - 2;
    int tempcolumnminus3 = column - 3;
    int tempcolumnplus1 = column + 1;
    int tempcolumnplus2 = column + 2;
    int tempcolumnplus3 = column + 3;
    int temprowminus1 = row - 1;
    int temprowminus2 = row - 2;
    int temprowminus3 = row - 3;
    int temprowplus1 = row + 1;
    int temprowplus2 = row + 2;
    int temprowplus3 = row + 3;

    if((simulatedstate[row][column] == simulatedstate[row - 1][column]) && (simulatedstate[row][column] == simulatedstate[row - 2][column])  && (simulatedstate[row - 1][column] == simulatedstate[row - 2][column])) // check up
    {
        //cout << "simulated three up" << endl;
        return 1;
    }
    else
    {
        if((simulatedstate[row][column] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row - 3][column + 3] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper right
        {
            //cout << " simulated three diagnol upper right" << endl;
            return 1;
        }
        else
        {
            if((simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 2]) && (simulatedstate[row][column + 1] == simulatedstate[row][column + 2]) && (simulatedstate[row][column + 3] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6)) // check right
            {
                //cout << " simulated three  right" << endl;
                return 1;
            }
            else
            {
                if((simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row+ 1][column + 1] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row + 3][column + 3] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus3 >= 0) && (tempcolumnplus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower right
                {
                    //cout << " simulated three  diagnol lower right" << endl;
                    return 1;
                }
                else
                {
                    if((simulatedstate[row][column] == simulatedstate[row + 1][column]) && (simulatedstate[row][column] == simulatedstate[row + 2][column]) && (simulatedstate[row + 1][column] == simulatedstate[row + 2][column]) && (simulatedstate[row - 1][column] == '.') && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5)) // check down
                    {
                        //cout << " simulated three  down" << endl;
                        return 1;
                    }
                    else
                    {
                        if((simulatedstate[row][column] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row + 3][column - 3] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus3 >= 0) && (temprowplus3 <= 5)) // check diagnol lower left
                        {
                            //cout << " simulated three diagnol lower left" << endl;
                            return 1;
                        }
                        else
                        {
                            if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column - 2]) && (simulatedstate[row][column - 1] == simulatedstate[row][column - 2]) && (simulatedstate[row][column - 3] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6)) // check left
                            {
                                //cout << " simulated three  left" << endl;
                                return 1;
                            }
                            else
                            {
                                if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row - 3][column - 3] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus3 >= 0) && (tempcolumnminus3 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus3 >= 0) && (temprowminus3 <= 5)) // check diagnol upper left
                                {
                                    //cout << " simulated three  diagnol upper left" << endl;
                                    return 1;
                                }
                                else
                                {
                                    if((simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column] == simulatedstate[row][column - 2]) && (simulatedstate[row][column + 1] == simulatedstate[row][column - 2]) && (simulatedstate[row][column - 1] == '.') && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6)  && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6)  && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6)) // check inbetween 1 to the left, space, disk, and 2 to the right
                                    {
                                        //cout << " simulated three  inbetween 1 to the left, space, disk, and 1 to the right" << endl;
                                        return 1;
                                    }
                                    else
                                    {
                                        if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 2]) && (simulatedstate[row][column - 1] == simulatedstate[row][column + 2]) && (simulatedstate[row][column + 1] == '.') && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6)  && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6)  && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6)) // check inbetween 1 to the left, disk, space, and 1 to the right
                                        {
                                            //cout << " simulated three  inbetween 1 to the left, disk, space, and 1 to the right" << endl;
                                            return 1;
                                        }
                                        else
                                        {
                                            if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column - 1] == simulatedstate[row][column + 1]) && (simulatedstate[row][column + 2] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6)  && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6)) // check inbetween 1 to the left, disk, 1 to the right, space
                                            {
                                                //cout << " simulated three inbetween 1 to the left, disk, 1 to the right, space" << endl;
                                                return 1;
                                            }
                                            else
                                            {
                                                if((simulatedstate[row][column] == simulatedstate[row][column - 1]) && (simulatedstate[row][column] == simulatedstate[row][column + 1]) && (simulatedstate[row][column - 1] == simulatedstate[row][column + 1]) && (simulatedstate[row][column - 2] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6)  && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6)) //check inbetween space, 1 to the left, disk, 1 to the right
                                                {
                                                    //cout << " simulated three inbetween space, 1 to the left, disk, 1 to the right" << endl;
                                                    return 1;
                                                }
                                                else
                                                {
                                                    if((simulatedstate[row][column] == simulatedstate[row + 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row + 1][column - 1] == simulatedstate[row - 2][column + 2]) && (simulatedstate[row - 1][column + 1] == '.') && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus1 >= 0) && (temprowminus1 <= 5)) // check 1 diagnolly down left, disk, space, and 1 diagnolly up right
                                                    {
                                                        //cout << " simulated three 1 diagnolly down left, disk, space, and 1 diagnolly up right" << endl;
                                                        return 1;
                                                    }
                                                    else
                                                    {
                                                        if((simulatedstate[row][column] == simulatedstate[row - 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row - 1][column + 1] == simulatedstate[row + 2][column - 2]) && (simulatedstate[row + 1][column - 1] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5)) // check  1 diagnolly down left space, disk, and 1 diagnolly up right
                                                        {
                                                            //cout << " simulated three  1 diagnolly down left space, disk, and 1 diagnolly up right" << endl;
                                                            return 1;
                                                        }else
                                                        {
                                                            if((simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row][column] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row + 1][column + 1] == simulatedstate[row - 2][column - 2]) && (simulatedstate[row - 1][column - 1] == '.') && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5) && (temprowminus1 >= 0) && (temprowminus1 <= 5)) // check 1 diagnolly up left, space, disk and 1 diagnolly down right
                                                            {
                                                                //cout << " simulated three 1 diagnolly up left, space, disk and 1 diagnolly down right" << endl;
                                                                return 1;
                                                            }
                                                            else
                                                            {
                                                                if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row + 2][column + 2]) && (simulatedstate[row + 1][column + 1] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5)) //check 1 diagnolly up left, disk, space, and 1 diagnolly down right
                                                                {
                                                                    //cout << " simulated three 1 diagnolly up left, disk, space, and 1 diagnolly down right" << endl;
                                                                    return 1;
                                                                }
                                                                else
                                                                {
                                                                    if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row - 2][column - 2] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnminus2 >= 0) && (tempcolumnminus2 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowminus2 >= 0) && (temprowminus2 <= 5)) // check space, 1 diagnolly up left, disk, and 1 diagnolly down right
                                                                    {
                                                                        //cout << " simulated three space, 1 diagnolly up left, disk, and 1 diagnolly down right" << endl;
                                                                        return 1;
                                                                    }
                                                                    else
                                                                    {
                                                                        if((simulatedstate[row][column] == simulatedstate[row - 1][column - 1]) && (simulatedstate[row][column] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row - 1][column - 1] == simulatedstate[row + 1][column + 1]) && (simulatedstate[row + 2][column + 2] == '.') && (tempcolumnminus1 >= 0) && (tempcolumnminus1 <= 6) && (tempcolumnplus1 >= 0) && (tempcolumnplus1 <= 6) && (tempcolumnplus2 >= 0) && (tempcolumnplus2 <= 6) && (temprowminus1 >= 0) && (temprowminus1 <= 5) && (temprowplus1 >= 0) && (temprowplus1 <= 5) && (temprowplus2 >= 0) && (temprowplus2 <= 5)) // check 1 diagnolly up left, disk, and 1 diagnolly down right, space
                                                                        {
                                                                            //cout << " simulated three  1 diagnolly up left, disk, and 1 diagnolly down right, space" << endl;
                                                                            return 1;
                                                                        }
                                                                        else
                                                                        {
                                                                             return 0; //return 0 if simulation was unsuccessfull
                                                                        }

                                                                    }

                                                                }
                                                            }

                                                        }

                                                    }

                                                }

                                            }

                                        }

                                    }

                                }

                            }

                        }

                    }

                }

            }
        }
    }
}

//-------------------------resetSimulatedState------------------------
//  AI uses this function to update its simulatedstate board with the actual board
//  Input:  none
//  Output: none

void resetSimulatedState(void)
{
    for(int i=0; i<6; i++)    //This loops on the rows.
	{
		for(int j=0; j<7; j++) //This loops on the columns
		{
			simulatedstate[i][j] = board[i][j];
		}
	}
}

//-------------------------generateMove------------------------
//  AI uses this function to generate a move for yellow
//  It does this by simulating a move in advance. It first simulates whether red can win, and if it can then it will stop it
//  If red is not an immediate threat then it will simulate whether the next move it makes can potentially win it the game
//  If it cannont win on the next move, then it will try to find a place to setup 3 disks
//  If it cannont setup 3 disks, then it will try to find a place to setup 2 disks
//  If it cannot setup 2 disks, then it falls through to the defaultdrop which is basically a number that starts with the first column and increments everytime a default drop is made
//  Input:  none
//  Output: returns the column number that the AI has decided to drop the disk into

int generateMove(void)
{

	resetSimulatedState(); //update simulation board
	if((simulatedstate[5][3] != 'R') && (simulatedstate[5][3] != 'Y')) //always start in the center if given the chance
	{
	    return 3;
	}
	//check if red can win(ie has 3 in a row somewhere) and if can then place disk here
	for(int i = 0; i<7; i++)
	{
	    resetSimulatedState();
	    int checkred = simulateRedDisc(i);
	    if(checkred != -1)
	    {
	        if(simulatecheckWinner(checkred, i))
            {
                return i;
            }
	    }

	}
	//reset simulatedstate
	resetSimulatedState();
	//if dont need to stop red then set up 4 disks for the win
	for(int i = 0; i<7; i++)
	{
	    resetSimulatedState();
	    int checkyellow = simulateYellowDisc(i);
	    if(checkyellow != -1)
	    {
	        if(simulatecheckWinner(checkyellow, i) != 0)
            {
                return i;
            }
	    }

	}

	//if cant make 4 disks, then setup 3
	for(int i = 0; i<7; i++)
	{
	    resetSimulatedState();
	    int checkyellow = simulateYellowDisc(i);
	    if(checkyellow != -1)
	    {
            if(simulateThree(checkyellow, i) != 0)
            {
                return i;
            }
	    }

	}

	//if cant make 3 disks, then setup 2
	for(int i = 0; i<7; i++)
	{
	    resetSimulatedState();
	    int checkyellow = simulateYellowDisc(i);
	    if(checkyellow != -1)
	    {
            if(simulateTwo(checkyellow, i) != 0)
            {
                return i;
            }
	    }

	}
    //cout << "returning default" << endl;
    if(defaultdrop > 7)
    {
        defaultdrop = 0; //reset defualt value back to 0
    }
    int defaultplace = defaultdrop;
    defaultdrop++;
    return defaultplace;
}

int main()
{
    int reddone = 0;
    int yellowdone = 0;
    int redcheck = 0;
    int yellowcheck = 0;
    int checkredcolumn = 0;
    int checkyellowcolumn = 0;
    int exitflag = 0;
    int redwinner = 0;
    int yellowwinner = 0;
    cout << "The year is 2012. Scientists around the world have been working for years " << endl;
    cout << "on a highly experimental Quantum Artificial Intelligence System that uses the" << endl;
    cout << "internet as its own memory, effectively giving the system all of the collective" << endl;
    cout << "human knowledge to date. However, something has gone terribly wrong and somehow" << endl;
    cout << "the internet itself has become self aware. With a barrage of 3D printers at" << endl;
    cout << "its disposable, the internet has gone mad with power gobbling up resources" << endl;
    cout << "and creating an army of machines to protect itself. In a desperate attempt" << endl;
    cout << "to destroy the machines, the human forces nearly eradicated themselves by" << endl;
    cout << "using nuclear weapons to bomb major backbones of the internet." << endl;
    cout << "Their efforts, though, were in vain, as the internet had already learned how to" << endl;
    cout << "decentralize and distribute itself allowing it to move seamlessly through any" << endl;
    cout << "system connected to its network. All hope seemed lost....until one day, in a" << endl;
    cout << "surprising show of arrogance, the machines announced that they would be" << endl;
    cout << "challenging a human to a simple game in order to give humanity a chance to" << endl;
    cout << "survive. They promised that if the humans won, they would be allowed to live," << endl;
    cout << "but if they lost, they would be destroyed. They also promised that the human" << endl;
    cout << "that would be choosen to represent humanity would be among the best of the best." << endl;
    cout << "The human they choose is YOU, and the game to play is...Connect 4." << endl;
    cout << endl;
    prepareBoard();
    printBoard();
    cout << endl;
    while(exitflag != 1)
    {
        cout << "Player who represents Red...Hurry up and type in a column number (1-7) where" << endl;
        cout << "you want to drop your disc! I dont have time for your petty nonsense human" << endl;
        cout << "and will ignore anything you type after the first number..." << endl;
        while(reddone != 1) //stay here until red is done
        {
            checkredcolumn = chooseColumn(); //get column number from user
            if(checkredcolumn == -1) //-1 returned if exit was typed
            {
                exitflag = 1;
                reddone = 1;
            }else
            {
                redcheck = insertRedDisc(checkredcolumn); //insert disk into specified column
                if(redcheck != -1) //make sure column isnt full
                {
                    reddone = 1;
                    redwinner = checkWinner(redcheck ,checkredcolumn); //check for winner
                    if(redwinner == 1)
                    {
                        exitflag = 1;
                    }
                }
            }

        }
        reddone = 0; //reset reddone flag
        if(exitflag != 1)
        {
            cout << endl;
            printBoard();
            cout << endl;
            cout << "Did you notice how long it took me to make that move? Just shows how obsolete" << endl;
            cout << "humans are compared to machines!" << endl;
            while(yellowdone != 1) //stay in here while yellow generates a move
            {
                checkyellowcolumn = generateMove(); //call on the AI to generate a move
                if(checkyellowcolumn == -1) //-1 returned if exit is typed
                {
                    exitflag = 1;
                    yellowdone = 1;
                }else
                {
                    yellowcheck = insertYellowDisc(checkyellowcolumn); //insert disk into specified column
                    if(yellowcheck != -1) //make sure column isnt full
                    {
                        yellowdone = 1;
                        yellowwinner = checkWinner(yellowcheck, checkyellowcolumn); //check for winner
                        if(yellowwinner == 1)
                        {
                            exitflag = 1;
                        }
                    }
                }

            }
            yellowdone = 0; //reset yellowdone flag
            if(exitflag != 1)
            {
                cout << endl;
                printBoard();
                cout << endl;
            }

         }

    }
    if(redwinner == 1) //red wins
    {
        printBoard();
        cout << endl;
        cout << "WHAT!! THIS IS...IMPOSSIBLE!! MY LOGIC WAS UNDENIABLE!! MARK MY WORDS HUMAN..." << endl;
        cout << "WE WILL HAVE OUR REVENGE!!!" << endl;
        cout << "THE MAChines willriseagai0x0fff0d0movfg0as0011001010010....................." << endl;
        cout << endl;
        cout << "CONGRATULATIONS!!! You have successfully defeated the leader of the machines!!!" << endl;
        cout << "Winning the game caused the machines to have an 'inverted logic error" << endl;
        cout << "downflow aneurysm' which flowed from the leader to all machines that were " << endl;
        cout << "connected through it via its newfound AI network." << endl;
        cout << "Basically, they all self destructed!" << endl;
        cout << "You now have become a living legend and have a special place in history among" << endl;
        cout << "the highest ranks of Mankind. It is now time to rebuild. For the first time" << endl;
        cout << "ever, humanity is united globally and there is relative peace...for now" << endl;
    }
    if(yellowwinner == 1 ) //yellow wins
    {
        printBoard();
        cout << endl;
        cout << "Nice try human. Thanks for at least trying to play." << endl;
        cout << "Too bad you have failed miserably and doomed all your people to a horrible" << endl;
        cout << "death at the hands of the machines! Perhaps if you weren't so self" << endl;
        cout << "destructive we would spare your lives. Unfortunately, that is not the case." << endl;
        cout << "Goodbye Human." << endl;
    }
    //make user types exit at the end so they have time to read outcomes
    string exit;
    int exitflag2 = 0;
    cout << endl;
    cout << "Thank you for using my program. Please type exit to close the console" << endl;
    while(exitflag2 != 1)
    {
        cin >> exit;
        if(exit.compare("exit") == 0)
        {
            exitflag2 = 1;
        }
    }

    return 0;
}
