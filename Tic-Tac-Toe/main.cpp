/* the official documintation*/
/*
*   @file    Tic-Tac-Toe
*   @version 1.0.0
*   @brief   play the Tic-Tac-Toe game on the screen
*   @details You can chose if you want to play with the CPU or other player
*   @author  Yousef Khaled Omar Mahmoud
*/

/*========================================================================
*   Project             :   Tic-Tac-Toe
========================================================================*/

/* ******************** Includes Section Start ************************ */
#include <iostream>
#include <string>
#include "function.h"
#include <windows.h>  //for delay
#include <cmath>    
#include <fstream> //for text file
/* ******************** Includes Section End ************************** */

/* ******************** Defintion Section Start *********************** */
#define maxname 30
using namespace std;
/* ******************** Defintiion Section End ************************ */

/* ******************** Sub-program Decleration Section Start ********** */
void initialize_game(char name1[], char name2[], int n1, int n2, char& mode);
void start_game(char p1[], char p2[], char game[][3], char& symbol);
void play_game(char p1[], char p2[], char game[][3], char mode, char& symbol, int& code);
void print_board(char game[3][3], int code);
void print_board_file(const char filename[], char game[3][3], char p1[], char p2[]);
void fill_cell(char game[3][3], int n, char symbol, char mode);
int  check_board(char game[3][3], char symbol, int& code);
/* ******************** Sub-program Decleration Section End ************ */

int main()
{   
    while (1) {
        //making the default mode
        char game_mode = 0, p1symbol = 'X';
        char game_board[3][3] = { {'1','2','3'},{'4','5','6'} ,{'7','8','9'} };
        char p1name[maxname + 1] = " ", p2name[maxname + 1] = " ";
        int code = -3;

        //play
        initialize_game(p1name, p2name, maxname + 1, maxname + 1, game_mode);
        start_game(p1name, p2name, game_board, p1symbol);
        play_game(p1name, p2name, game_board, game_mode, p1symbol, code);
         
        //asking for another game
        string input;
        cout << "Do you want to play again?\n0:No any button:Yes\n";
        getline(cin, input);
        if (input[0] == '0' && strlen(input.c_str()) == 1) {
            cout << "Good Bye!\n";
            break;
        }
        cout << "Let's go!\n";
    }
    return 0;
}

/* ******************** Sub-program Section Start ********************* */
void initialize_game(char name1[], char name2[], int n1,int n2,char &mode) {
    //check the input array
    if ((n1 < maxname) || (n2 < maxname)) {
        cerr << "The input array is small!\n";
        return;
    }
    //welcome
    cout << "\t-----------------Tic-Tac-Toe-----------------\n";

    //getting the name
    string input;
    cout << "Enter the Player name (Max " << maxname << ")\n";
    getline(cin, input);
    check_char_input("Player name", input, 30);
    
    //assign the name
    for (unsigned int i = 0; i <= strlen(input.c_str()); i++)
        name1[i] = input[i];   

    cout << "Enter the mode\n 0:CPU   1:2 Players\n";
    getline(cin, input);
    input_size:
    while (strlen(input.c_str()) != 1) {
        cout << "Invalid Input\nTry Again\n";
        getline(cin, input);
    }

    switch (input[0]) {
    case '0':
        cout << "================CPU Mode=====================\n";
        strcpy_s(name2,sizeof(name2), "CPU");
        mode = 0;
        break;
    case '1':
        cout << "================2 Players Mode=================\n";
        cout << "Enter the Player2 name (Max " << maxname << ")\n";
        getline(cin, input);
        check_char_input("Player2 name", input, 30);
        strcpy_s(name2, sizeof(name2), input.c_str());
        mode = 1;
        break;
    default:
        cout << "Invalid Input\nTry Again\n";
        getline(cin, input);
        goto input_size;
    }
}

void start_game(char p1[], char p2[], char game[][3], char &symbol) {
    //check the name input
    if (strlen(p1) > maxname || strlen(p1) > maxname) {
        cerr << "Invalid Name!\n";
        return;
    }

    //getting player 1 symbol
    cout << p1 <<" Enter your symbol!\n X or O\n";
    string input;
    getline(cin, input);
    input_size:
    while (strlen(input.c_str()) != 1) {
        cout << "Invalid Input\nTry Again\n";
        getline(cin, input);
    }

    input[0]=toupper(input[0]);
    switch (input[0]) {
    case 'X':
        symbol = 'X';
        break;
    case 'O':
        symbol = 'O';
        break;
    default:
        cout << "Invalid Input\nTry Again\n";
        getline(cin, input);
        goto input_size;
    }

    //initialize the board
    unsigned int counter = 0;
    for (register unsigned int i = 0; i < 3; i++)
        for (register unsigned int j = 0; j < 3; j++) {
            game[i][j] = '1' + counter;
            counter++;
        }
    cout << "Player can chose where to play on the board by enterning the cell number!\n";
    print_board(game,-3);

}

void play_game(char p1[], char p2[], char game[][3], char mode, char& symbol,int &code) {
    //check the name input
    if (strlen(p1) > maxname || strlen(p1) > maxname) {
        cerr << "Invalid Name!\n";
        return;
    }

    //check the mode
    if (mode != 0 && mode != 1) {
        cerr << "Invalid Mode!\n";
        return;
    }

    //check the symbol
    if (symbol != 'X' && symbol != 'O') {
        cerr << "Invalid Symbol!\n";
        return;
    }

    //second player symbol
    char symbol2 = 'O';
    if(symbol == 'O')
        symbol2 = 'X';
    
    //start to play
    string input;
    int n;
    //check the mode
    if (mode == 1) {
        for (register unsigned int i = 0; i < 9; i++) {
            if (i % 2 == 0) {
                cout << "It is " << p1 << " Turn ( " << symbol << " )\n" << "Chose your cell!";
                //check the input
                getline(cin, input);
                check_int_input("Cell", input, 9, 1);
                n = stoi(input);
                fill_cell(game, n, symbol,1);
                print_board(game,code);
                if (check_board(game, symbol,code)) {
                    print_board(game, code);
                    cout << "Congratulations " << p1 << " You win!\n";
                    print_board_file("Game History.txt", game,p1,p2);
                    return;
                }

            }
            else {
                cout << "It is " << p2 << " Turn ( " << symbol2 << " )\n" << "Chose your cell!";
                //check the input
                getline(cin, input);
                check_int_input("Cell", input, 9, 1);
                n = stoi(input);
                fill_cell(game, n, symbol2,1);
                print_board(game,code);
                if (check_board(game, symbol2,code)) {
                    print_board(game, code);
                    cout << "Congratulations " << p2 << " You win!\n";
                    print_board_file("Game History.txt", game,p1,p2);
                    return;
                }
            }
        }
    }
    else {//CPU
        for (register unsigned int i = 0; i < 9; i++) {
            if (i % 2 == 0) {
                cout << "It is " << p1 << " Turn ( " << symbol << " )\n" << "Chose your cell!";
                //check the input
                getline(cin, input);
                check_int_input("Cell", input, 9, 1);
                n = stoi(input);
                fill_cell(game, n, symbol,1);
                print_board(game,code);
                if (check_board(game, symbol,code)) {
                    print_board(game, code);
                    cout << "Congratulations " << p1 << " You win!\n";
                    print_board_file("Game History.txt", game,p1,p2);
                    return;
                }

            }
            else {
                cout << "It is CPU Turn ( " << symbol2 << " )\n";

                //waiting
                for (register unsigned int j = 0; j < 3; j++) {
                    cout << "..";
                    Sleep(1000);
                }
                cout << endl;

                //CPU chooses
                n = (rand() % 9) + 1;
                fill_cell(game, n, symbol2,0);
                print_board(game,code);
                if (check_board(game, symbol2,code)) {
                    print_board(game, code);
                    cout << "CPU wins!\n";
                    print_board_file("Game History.txt", game,p1,p2);
                    return;
                }
            }
        }
    }


    
    //draw
    cout << "It is a Draw!\n";
    print_board_file("Game History.txt", game,p1,p2);
    return;

}

void fill_cell(char game[3][3], int n, char symbol, char mode) {
    
    //check the input
    if (n < 0 || n>9) {
        cerr << "Invalid Cell!\n";
        return;
    }

    //check the mode
    if (mode != 0 && mode != 1) {
        cerr << "Invalid Mode!\n";
        return;
    }

    //check the symbol
    if (symbol != 'X' && symbol != 'O') {
        cerr << "Invalid Symbol!\n";
        return;
    }

    if (mode == 1) {//player
        string input;
        n--;
        //check if the cell is empty
        while (game[n / 3][n % 3] == 'X' || game[n / 3][n % 3] == 'O') {
            cout << "The Cell is filled!\nTry Again!";
            //check the input
            getline(cin, input);
            check_int_input("Cell", input, 9, 1);
            n = stoi(input);
            n--;
        }
    }
    else {//CPU
        n--;
        //check if the cell is empty
        while (game[n / 3][n % 3] == 'X' || game[n / 3][n % 3] == 'O') {
            n = rand()%9;
        }
    }

    game[n / 3][n % 3] = symbol;

}

int  check_board(char game[3][3], char symbol, int &code) {
    //check the symbol
    if (symbol != 'X' && symbol != 'O') {
        cerr << "Invalid Symbol!\n";
        return -1;
    }

    //if player one win 1 
    int test = 0;
    /* checking by using this shape
            X
        X   X   X
            X   
    */
    //will start by chwcking the middle
    if (game[1][1] == symbol) {
        //row
        for (register unsigned int i = 0; i < 3; i = i + 2) {
            test = 1;
            if (game[1][i] != symbol) {
                test = 0;
                break;
            }
        }

        //win
        if (test) {
            code = 11;
            return test;
        }

        //column
        for (register unsigned int i = 0; i < 3; i = i + 2) {
            test = 1;
            if (game[i][1] != symbol) {
                test = 0;
                break;
            }
        }

        //win
        if (test) {
            code = 1;
            return test;
        }

        //right diagonal
        for (register unsigned int i = 0; i < 3; i = i + 2) {
            test = 1;
            if (game[i][i] != symbol) {
                test = 0;
                break;
            }
        }

        //win
        if (test) {
            code = -1;
            return test;
        }

        //left diagonal
        int j = 2;
        for (register unsigned int i = 0; i < 3; i = i + 2) {
            test = 1;
            if (game[i][j] != symbol) {
                test = 0;
                break;
            }
            j -= 2;
        }

        //win
        if (test) {
            code = -2;
            return test;
        }

    }

    //checking the horizontal edges
    for (register unsigned int i = 0; i < 3; i = i + 2) {
        if (game[i][1] == symbol)
            for (register unsigned int j = 0; j < 3; j = j + 2) {
                test = 1;
                if (game[i][j] != symbol) {
                    test = 0;
                    break;
                }
            }

        //win
        if (test) {
            code = 10 + i;
            return test;
        }
    }

    //checking the vertical edges
    for (register unsigned int i = 0; i < 3; i = i + 2) {
        if (game[1][i] == symbol)
            for (register unsigned int j = 0; j < 3; j = j + 2) {
                test = 1;
                if (game[j][i] != symbol) {
                    test = 0;
                    break;
                }
            }

        //win
        if (test) {
            code = i;
            return test;
        }
    }

    return 0;
}

void print_board(char game[3][3], int code) {
    //check the input
    if (code < -4 || code > 100 || abs(code) / 10 > 1 || (abs(code) % 10 > 2) && code>0) {
        cerr << "Invalid Code!\n";
        return;
    }

    /* we will use this code
     we check with the sign if there is a diagonal or not
     if not the first digit tells if it is row or not
     the last digit represents which row\column number
     if there is a diagonal (it will be negative number)
     the digit represent if it is right or not
     ex:
     the negatives:
     -1:the right diagonal
     -2:the right diagonal
     -3:no win yet
     12
     means the third row (as the first is 0)
    */

    //it is right diagonal
    if (code == -1) {
        cout << "\t+--------------+--------------+--------------+\n";
        for (register unsigned int i = 0; i < 3; i++) {
            cout << "        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                if (i == j) {
                    // Change text color to red then return it to default
                    cout << "\033[1;31m" << "       " << game[i][j] << "\033[0m" << "      |";

                }
                else
                    cout << "       " << game[i][j] << "      |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n\t+--------------+--------------+--------------+\n";
        }
        
    }

    else if (code == -2) {//left diagonal
        cout << "\t+--------------+--------------+--------------+\n";
        unsigned int red_mark = 2;
        for (register unsigned int i = 0; i < 3; i++) {
            cout << "        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                if (j == red_mark) {
                    // Change text color to red then return it to default
                    cout << "\033[1;31m" << "       " << game[i][j] << "\033[0m" << "      |";
                }
                else
                    cout << "       " << game[i][j] << "      |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n\t+--------------+--------------+--------------+\n";
            red_mark--;
        }
    }
    else if(code==-3) {// no win
        cout << "\t+--------------+--------------+--------------+\n";
        for (register unsigned int i = 0; i < 3; i++) {
            cout << "        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "       " << game[i][j] << "      |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n\t+--------------+--------------+--------------+\n";
        }
    }
    //it is a row
    else if (code / 10 == 1) {
        cout << "\t+--------------+--------------+--------------+\n";
        for (register unsigned int i = 0; i < 3; i++) {
            cout << "        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                if (i == code%10) {
                    // Change text color to red then return it to default
                    cout << "\033[1;31m" << "       " << game[i][j] << "\033[0m" << "      |";

                }
                else
                    cout << "       " << game[i][j] << "      |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n\t+--------------+--------------+--------------+\n";
        }
    }
    else {//it is a column
        cout << "\t+--------------+--------------+--------------+\n";
        for (register unsigned int i = 0; i < 3; i++) {
            cout << "        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                if (j == code % 10) {
                    // Change text color to red then return it to default
                    cout << "\033[1;31m" << "       " << game[i][j] << "\033[0m" << "      |";

                }
                else
                    cout << "       " << game[i][j] << "      |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n        |";
            for (register unsigned int j = 0; j < 3; j++)
                cout << "              |";
            cout << "\n\t+--------------+--------------+--------------+\n";
        }
    }

}

void print_board_file(const char filename[], char game[3][3],char p1[], char p2[]) {
    ofstream outfile(filename, ios::app);
    //check the file
    if (!outfile.is_open()) {
        cerr << "Can't Open The file\n";
        return;
    }

    outfile << "\n\t\t" << p1 << "\tVs\t" << p2 << endl;
    outfile << "\t+--------------+--------------+--------------+\n";
    for (register unsigned int i = 0; i < 3; i++) {
        outfile << "        |";
        for (register unsigned int j = 0; j < 3; j++)
            outfile << "              |";
        outfile << "\n        |";
        for (register unsigned int j = 0; j < 3; j++)
            outfile << "              |";
        outfile << "\n        |";
        for (register unsigned int j = 0; j < 3; j++)
            outfile << "       " << game[i][j] << "      |";
        outfile << "\n        |";
        for (register unsigned int j = 0; j < 3; j++)
            outfile << "              |";
        outfile << "\n        |";
        for (register unsigned int j = 0; j < 3; j++)
            outfile << "              |";
        outfile << "\n\t+--------------+--------------+--------------+\n";
    }

}
/* ******************** Sub-program  Section End ********************** */

/*

**************************************************************************
User            Date            Task    Details
**************************************************************************
Yousef          19sep2023       1       Making the file
Yousef          20sep2023       2       Making the initial and start function
Yousef          21sep2023       3       Finish the program

*/
