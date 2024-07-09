#ifndef _BOOK_H_
#define _BOOK_H_

#include "iostream"
#include "function.h"
#include <string>
#include <fstream> //for text file
using namespace std;

//the sizes
#define maxauthor   50
#define isbnsize    14
char repeated_isbn[isbnsize+1] = "978-";

char map_state(string message);
string print_state(char s) {
    if (s == 0)
        return "Available";
    else if (1 == s)
        return "Checked Out";
    else if (2 == s)
        return "On hold";
    else if (3 == s)
        return "Out of Stock";
    else
        return "Invalid State";
}

class book{
    private:
        //default values
        string title=" ";
        char author[maxauthor] = " ";
        char ISBN [isbnsize+1] = "978-";
        char state = 0;
    public:
        //setters:
        void set_title(string input);
        void set_author(const char arr[]);
        void set_isbn(const char c[]);
        void set_state(int n);
        void set_book_info();

        //getters
        void get_title(string &input);
        void get_author(char arr[], const int len);
        void get_isbn(char arr[], const int len);
        void get_state(int &n);
        void print_book_info();

        //functions
        int check_book(char filename[], char ISBN[], string& title, char author[maxauthor], char& state);
        void write_book_data(const char filename[]);
};

void book::set_title(string input) {
    //check the input
    if (strlen(input.c_str()) == 0)    //empty
        return;

    //assign the title
    title = input;
}

void book::set_isbn(const char arr[]) {
    //check the input size
    if (strlen(arr) > isbnsize-4) {
        cerr << "The ISBN is long\n";
        return;
    }
    else if (strlen(arr) < isbnsize-4) {
        cerr << "The ISBN is short\n";
        return;
    }

    //check if the input is valid
    string in = arr;
    if (!isintdigit(in)) {
        cerr << "Invalid ISBN!\n";
        return;
    }

    //assign the ISBN
    in = "978-" + in;

    strcpy_s(ISBN, in.c_str());
}

void book::set_author(const char arr[]) {
    //check if the name is valid
    string in = arr;
    if (!isalphainput(in)) {
        cerr << "Invalid Author Name!\n";
        return;
    }

    //check the input
    if (strlen(arr) > maxauthor) {
        cerr << "The author name is too long\n";
        return;
    }

    unsigned int i = 0;
    //assign the name
    for (; (i < (maxauthor - 1)) && !(arr[i] == '\0'); i++)
        author[i] = arr[i];
    author[i] = '\0';   //end the array
}

void book::set_state(int n) {
    /*There are 4 states
    * 0="available" 
      1="checked out" 
      2="on hold"
      3="out of stock"
    */

    //check the input
    if (n < 0 || n>3) {
        cout << "Invalid State!\n";
            return;
    }
    
    state = n;
}

void book::set_book_info() {
    //Title
    cout << "Enter the Title \n";
    string input;    //string to take any input
    getline(cin, input);

    //send it as a character array
    set_title(input);

    //Author
    cout << "Enter the Author ( Max " << maxauthor << " )\n";
    getline(cin, input);
    make_alpha("Author", input);   //make the name valid
    check_char_input("Author", input, maxauthor);

    //assign the author
    set_author(input.c_str());

    //ID
    cout << "Enter the ISBN ( " << isbnsize << " characters)\n";
    cout << ISBN;
    getline(cin, input);

    isbn_size:
    check_char_input("ISBN", input, isbnsize-4, isbnsize-4);
    make_intdigit("ISBN", input);
    //check the size and the input
    if ((strlen(input.c_str()) != isbnsize - 4) || input[0] == '+' || input[0] == '-') {
        cout << "Invalid ISBN!\n Try Again!\n";
        getline(cin, input);
        goto isbn_size;
    }

    //check if there is a book with same ISBN
    char file[] = "Library.txt";
    string ititle;
    char iauthor[maxauthor], istate, test = 0;
    char input_isbn[isbnsize + 1];
    input = "978-" + input;
    strcpy_s(input_isbn, input.c_str());
    if(check_book(file, input_isbn, ititle, iauthor, istate)) {
        cout << "There is a book with the same ISBN!\n";
        cout << "The book Title:     " << ititle << endl;
        cout << "The book Author:    " << iauthor << endl;
        cout << "The book ISBN:      " << input_isbn << endl;
        cout << "The book State:     " << print_state(state) << endl;
        //returning everything to default
        strcpy_s(repeated_isbn, input_isbn);
        title = " ";
        strcpy_s(author, " ");
        strcpy_s( ISBN, "978-");
        state = 0;
        return;
    }
    //not repeated
    strcpy_s(repeated_isbn, "978-");
    for (register unsigned int i = 0; i <= 10; i++)
        input[i] = input[i + 4];

    //send the array
    set_isbn(input.c_str());

    //the state
    cout << "Enter the state:\n";
    cout << "0:available  1:checked out   2:on hold   3:out of stock\n";
    getline(cin, input);
    
state_size:
    while (strlen(input.c_str()) != 1) {
        cout << "Invalid State!\nTry Again\n";
        getline(cin, input);
    }

    if (input[0] == '0' || input[0] == '1' || input[0] == '2' || input[0] == '3')
        set_state(stoi(input));
    else {
        cout << "Invalid State!\nTry Again\n";
        getline(cin, input);
        goto state_size;
    }

    //text file
    char filename[] = "Library.txt";
    write_book_data(filename);
}

void book::print_book_info() {
    cout << "The book Title:     " << title << endl;
    cout << "The book Author:    " << author << endl;
    cout << "The book ISBN:      " << ISBN << endl;
    cout << "The book State:     " << print_state(state) << endl;
}

void book::write_book_data(const char filename[]) {
    ofstream outfile(filename, ios::app);
    //check the file
    if (!outfile.is_open()) {
        cerr << "Can't Open The file\n";
        return;
    }

    //Printing to the file
    outfile << ISBN << '\n' << title << '\n' << author << '\n' << print_state(state) << endl;

    // Close the file
    outfile.close();
}

void book::get_author(char arr[], const int len) {
    //check the size
    if (len < strlen(author)) {
        cout << "The array is small\n";
        return;
    }

    register unsigned int i = 0;
    for (; author[i] != '\0'; i++)
        arr[i] = author[i];
    arr[i] = '\0';
}

void book::get_title(string& input) {
    input = title;
}

void book::get_isbn(char arr[], const int len) {
    //check the size
    if (len < strlen(ISBN)) {
        cout << "The array is small\n";
        return;
    }

    register unsigned int i = 0;
    for (; ISBN[i] != '\0'; i++)
        arr[i] = ISBN[i];
    arr[i] = '\0';
}

void book::get_state(int& n) {
    n = state;
}

int book::check_book(char filename[], char ISBN[], string &title,char author[maxauthor],char &state) {
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

    string line;
    register unsigned int line_count = 0;
    char test = 0,input_isbn[isbnsize+1];
    while (getline(inputfile, line)) {
        //check the input
        if (strlen(line.c_str()) == 0 && line_count == 0) {   //empty
            // Close the file
            inputfile.close();
            return 0;
        }

        //printing
        if (line_count % 4 == 0) {   //ISBN
            for (register unsigned int i = 0; i <= strlen(line.c_str()); i++)
                input_isbn[i] = line[i];
            //check  the isbn
            if (!strcmp(ISBN, input_isbn)) {
                test = 1;
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

    // Close the file
    inputfile.close();

    if (test) {
        return 1;
    }
    else {
        return 0;
    }

}

char map_state(string message) {
    if ("Available" == message)
        return 0;
    else if ("Checked Out" == message)
        return 1;
    else if ("On hold" == message)
        return 2;
    else if ("Out of Stock" == message)
        return 3;
    else
        return -1;
}

#endif

