/*
*   @file       Library Management System
*   @version    1.0.0
*   @brief      It is to save and manage the books
*   @details    The program allows users to add a book with author,title and ISBN. and can change the books states to:
*   "available," "checked out," "on hold," and "out of stock,". and can remove a book
*   @author     Yousef Khaled Omar Mahmoud
*/

/*========================================================================
*   Project             : Library Management System
========================================================================*/

/* ******************** Includes Section Start ************************ */
#include <iostream>
#include <string.h>
#include <fstream> //for text file
#include "book.h"
#include "function.h"
/* ******************** Includes Section End ************************** */

/* ******************** Defintion Section Start *********************** */
using namespace std;
/* ******************** Defintiion Section End ************************ */

/* ******************** Sub-program Decleration Section Start ********** */
void print_library(char filename[]);
void delete_library(char filename[]);
void get_isbn(char ISBN[],const int len);
int find_book(char filename[], char ISBN[],book &b,int &linenum);
void edit_book(char filename[], int linenum);
void delete_book(char filename[], int linenum);
char map_state(string message);
/* ******************** Sub-program Decleration Section End ************ */

int main(){
    cout << "------------------Library Management System------------------\n";
    cout << "Welcome!\n";
    char filename[] = "Library.txt";
    char ISBN[isbnsize + 1];
    char repeat = 0;

    //asking what to do
    while (1) {
        cout << "What Do You Want To Do?\n";
        cout << "0:Add a book     1:Remove a book     2:Print a book    3:Edit a book  \n4:Print the library    5:Delete the library\n";
        string input;
        getline(cin, input);
        //checking the input
    input_size:
        while (strlen(input.c_str()) != 1) {
            cout << "Invalid Input!\nTry Again!\n";
            getline(cin, input);
        }

        switch (input[0]) {
        case '0': {
            book newBook;
            char input_isbn[isbnsize+1];
            cout << "================Adding Books=================\n";
            newBook.set_book_info();
            newBook.get_isbn(input_isbn, isbnsize + 1);
            //repeted
            if (!strcmp(input_isbn, "978-")) {
                cout << "\n";
                cout << "Do you want to edit the book?\n";
                cout << "0:No   any other button:Yes\n";
                getline(cin, input);
                if (input[0] != '0') {
                    strcpy_s(ISBN, repeated_isbn);
                    repeat = 1;
                    goto edit;
                }

            }
            else {
                repeat = 0;
                newBook.print_book_info();
            }
            break; 
        }
        case '1': {
            cout << "================Removing Books=================\n";
            get_isbn(ISBN, isbnsize + 1);
            book removeBook;
            int linenum;
            if (find_book(filename, ISBN, removeBook, linenum)) {
                cout << "The book is found!\n";
                removeBook.print_book_info();
                delete_book(filename,  linenum);
                cout << "The book is removed!\n";
            }
            else {
                cout << "The book is not found!\n";
            }
            break;
        }
        case '2': {
            cout << "================Printing Books=================\n";
            get_isbn(ISBN, isbnsize + 1);
            book printBook;
            int linenum;
            if (find_book(filename, ISBN, printBook,linenum)) {
                cout << "The book is found!\n";
                printBook.print_book_info();
            }
            else {
                cout << "The book is not found!\n";
            }
            break; 
        }
        case '3': {
        edit:
            cout << "================Editing Books=================\n";
            book editBook;
            int linenum;
            if (!repeat) {
                get_isbn(ISBN, isbnsize + 1);
                if (find_book(filename, ISBN, editBook, linenum)) {
                    cout << "The book is found!\n";
                    editBook.print_book_info();
                    edit_book(filename, linenum);
                    cout << "The book is edited!\n";
                    if (find_book(filename, ISBN, editBook, linenum)) {
                        cout << "Here is the new Book!\n";
                        editBook.print_book_info();
                    }
                }
                else {
                    cout << "The book is not found!\n";
                }
            }
            else {
                if (find_book(filename, ISBN, editBook, linenum)) {
                    editBook.print_book_info();
                    edit_book(filename, linenum);
                    cout << "The book is edited!\n";
                    if (find_book(filename, ISBN, editBook, linenum)) {
                        cout << "Here is the new Book!\n";
                        editBook.print_book_info();
                    }
                }
            }
            break;
        }
        case '4': {
            cout << "================Printing Library=================\n";
            print_library(filename);
            break; 
        }
        case '5': {
            cout << "================Deleting Library=================\n";
            delete_library(filename);
            break;
        }
        default: {
            cout << "Invalid Input\nTry Again\n";
            getline(cin, input);
            goto input_size;
        }

        }
        repeat = 0;
        cout << "Do you want to do something else?\n";
        cout << "0:No   any other button:Yes\n";

        //exit
        getline(cin, input);
        if (input[0] == '0') {
            cout << "Good Bye!\n";
            break;
        }

    }
    return 0;

}


/* ******************** Sub-program Section Start ********************* */
void print_library(char filename[]) {
    ifstream inputfile(filename);
    //check the file
    if (!inputfile.is_open()) {
        cerr << "Can't Open The file\n";
        return;
    }

    /* The text file is in this format
    * ISBN
    * Title
    * Author
    * State
    */
    string line ;
    register unsigned int book_counter = 0, line_count = 0;
    while (getline(inputfile,line)) {
        //printing
        if (line_count % 4 == 0)        //ISBN
            cout << "The book ISBN:        " << line << endl;
        else if(line_count % 4 == 1)    //title
            cout << "The book Title:       " << line << endl;
        else if (line_count % 4 == 2)   //Author
            cout << "The book Author:      " << line << endl;
        else {                          //State  
            cout << "The book State:       " << line << endl;
            cout << "----------------------------------\n";
            book_counter++;
        }

        line_count++;
    }
    //check the input
    if (line_count == 0) {   //empty
        cout << "The Library is empty!\n";
    }
    cout << "The Number of Books are " << book_counter << endl;

    // Close the file
    inputfile.close();
}

void get_isbn(char ISBN[], const int len) {
    //check the array
    if (len < isbnsize+1) {
        cerr << "The array is small!\n";
        return;
    }
 
    char arr[isbnsize + 1] = "978-";
    string input;
    //getting the ISBN
    cout << "Enter the ISBN ( " << isbnsize << " characters)\n";
    cout << arr;
    getline(cin, input);

isbn_size:
    check_char_input("ISBN", input, isbnsize - 4, isbnsize - 4);
    make_intdigit("ISBN", input);
    //check the size and the input
    if ((strlen(input.c_str()) != isbnsize - 4) || input[0] == '+' || input[0] == '-') {
        cout << "Invalid ISBN!\n Try Again!\n";
        getline(cin, input);
        goto isbn_size;
    }

    //assign the ISBN
    unsigned int i = 0;
    for (; i < isbnsize - 4; i++)
        arr[i + 4] = input[i];

    //the output
    for (i = 0; i < isbnsize + 1; i++)
        ISBN[i] = arr[i];

}

int find_book(char filename[], char ISBN[],book &b, int& linenum) {
    //check the array
    if (strlen(ISBN) < isbnsize ) {
        cerr << "The array is small!\n";
        return 0;
    }

    ifstream inputfile(filename);
    //check the file
    if (!inputfile.is_open()) {
        cerr << "Can't Open The file\n";
        return 0;
    }

    /* The text file is in this format
    * ISBN
    * Title
    * Author
    * State
    */

    string line,title;
    linenum = 0;
    register unsigned int line_count = 0;
    char input_isbn[isbnsize +1], author[maxauthor],state,test=0;
    while (getline(inputfile, line)) {

        //assigning
        if (line_count % 4 == 0) {   //ISBN
            for (register unsigned int i = 0; i <= strlen(line.c_str()); i++)
                input_isbn[i] = line[i];
            //check  the isbn
            if (!strcmp(ISBN, input_isbn)) {
                test = 1;
                linenum = line_count+1;
            }
            else
                test = 0;
        }
        else if (line_count % 4 == 1) {       //title
            title = line;
        }
        else if (line_count % 4 == 2) {    //Author
            register unsigned int i = 0;
            for (; line[i] != '\0'; i++)
                author[i] = line[i];
            author[i] = '\0';
        }
        else {                          //State  
            state = map_state(line);
            if (test)//the book is found
                break;
        }
        line_count++;
    }

    //check the input
    if (line_count == 0) {   //empty
        cout << "The Library is empty!\n";
    }

    // Close the file
    inputfile.close();

    if (test) {
        //assign  the book
        b.set_title(title);
        b.set_author(author);
        char arr[isbnsize - 3];
        register unsigned int i = 0;
        for (; i < isbnsize - 3; i++)
            arr[i] = input_isbn[i + 4];
        b.set_isbn(arr);
        b.set_state(state);
        return 1;
    }
    else {
        return 0;
    }

}

void delete_book(char filename[],  int linenum) {
    //check the line
    if (linenum == 0) {
        cerr << "The Book is not found!\n";
        return;
    }

    ifstream inputfile(filename);
    ofstream tempfile("temp.txt");

    if (!inputfile.is_open() || !tempfile.is_open()) {
        cerr << "Can't Open The file\n";
        return ;
    }

    /* The text file is in this format
    * ISBN
    * Title
    * Author
    * State
    */

    string line;
    int line_count = 0;
    while (getline(inputfile, line)) {

        line_count++;

        //the book to delete
        if (line_count == linenum) {
            for (register unsigned int i = 0; i < 4; i++)
                getline(inputfile, line);
        }

        //copying the file
        tempfile << line << endl;
    }

    inputfile.close();
    tempfile.close();

    //check the input
    if (line_count == 0) {   //empty
        cout << "The Library is empty!\n";
    }

    // replace the files
    remove(filename);
    rename("temp.txt", filename);
}

void edit_book(char filename[], int linenum) {
    //check the line
    if (linenum == 0) {
        cerr << "The Book is not found!\n";
        return;
    }

    ifstream inputfile(filename);
    ofstream tempfile("temp.txt");

    if (!inputfile.is_open() || !tempfile.is_open()) {
        cerr << "Can't Open The file\n";
        return;
    }

    //asking what to edit
    //title
    string newtitle="\0", input;
    cout << "Do you want to change the title?\n";
    cout << "0:No   any other button:Yes\n";
    getline(cin, input);
    if (input[0] != '0') {
        cout << "What is the new title?\n";
        getline(cin, newtitle);
    }

    //author
    cout << "Do you want to change the author?\n";
    cout << "0:No   any other button:Yes\n";
    char newauthor[maxauthor] = "\0";
    getline(cin, input);
    if (input[0] != '0') {
        cout << "What is the new author?\n";
        cout << "Enter the Author ( Max " << maxauthor << " )\n";
        getline(cin, input);
        make_alpha("Author", input);   //make the name valid
        check_char_input("Author", input, maxauthor);
        strcpy_s(newauthor, input.c_str());
    }

    //state
    cout << "Do you want to change the state?\n";
    cout << "0:No   any other button:Yes\n";
    char newstate = '5';
    getline(cin, input);
    if (input[0] != '0') {
        cout << "What is the new state?\n";
        cout << "0:available  1:checked out   2:on hold   3:out of stock\n";
        getline(cin, input);
    state_size:
        while (strlen(input.c_str()) != 1) {
            cout << "Invalid State!\nTry Again\n";
            getline(cin, input);
        }

        if (input[0] == '0' || input[0] == '1' || input[0] == '2' || input[0] == '3')
            newstate = stoi(input);
        else {
            cout << "Invalid State!\nTry Again\n";
            getline(cin, input);
            goto state_size;
        }
    }

    /* The text file is in this format
    * ISBN
    * Title
    * Author
    * State
    */

    string line;
    int line_count = 0;
    while (getline(inputfile, line)) {

        line_count++;

        //the book to edit
        if (line_count == linenum+1) {
            if (newtitle != "\0") {//new title
                tempfile << newtitle << endl;
            }
            else 
                tempfile << line << endl;
            
            getline(inputfile, line);
            line_count++;
            if (newauthor[0] != '\0') {//new author
                tempfile << newauthor << endl;
            }
            else
                tempfile << line << endl;

            getline(inputfile, line);
            line_count++;
            if (newstate != '5') {//newstate
                tempfile << print_state(newstate) << endl;
            }
            else
                tempfile << line << endl;
        }

        else {
            //copying the file
            tempfile << line << endl;
        }
    }

    inputfile.close();
    tempfile.close();

    //check the input
    if (line_count == 0) {   //empty
        cout << "The Library is empty!\n";
    }

    // replace the files
    remove(filename);
    rename("temp.txt", filename);
}

void delete_library(char filename[]) {
    ifstream inputfile(filename);
    ofstream tempfile("temp.txt");

    if (!inputfile.is_open() || !tempfile.is_open()) {
        cerr << "Can't Open The file\n";
        return;
    }

    inputfile.close();
    tempfile.close();

    // replace the files
    remove(filename);
    if(!rename("temp.txt", filename))
        cout << "The library is deleted!\n";
    
}

/* ******************** Sub-program  Section End ********************** */

/*
**************************************************************************
User            Date            Task    Details
**************************************************************************
Yousef          23sep2023         1     Making the book class
Yousef          24sep2023         2     Making the find book function
Yousef          25sep2023         3     Finished the system
*/
