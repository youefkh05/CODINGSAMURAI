#ifndef _STUDENT_H_
#define _STUDENT_H_

#include "iostream"
#include "function.h"
#include <cctype>   //for string operations
#include <string>
#include <fstream> //for text file
using namespace std;

//the sizes
#define Maxname     30
#define idsize      7
#define Maxage      100
#define Maxscore    100

class student{
    private:
        //default values
        char name[Maxname]=" ";
        char id[idsize+1]=" ";
        char grade[3]="  ";
        short int age=0;
        float score=0;
    public:
        //setters:
        void set_name(const char arr[]);
        void set_id(const char arr[]);
        void set_grade(char c[]);
        void set_age(int n);
        void set_score(float n);
        void set_student_info();

        //getters
        void get_name(char arr[], const int len);
        void get_id(char arr[], const int len);
        void get_grade(char arr[], const int len);
        void get_age(int &n);
        void get_score(float &n);
        void print_student_info();

        //functions
        void map_grade(float n);
        void grade_message();
        void write_student_data(const char filename[]);
        void write_student_cell(ofstream &file,const char input[],const int maxinput);
};

void student::set_name(const char arr[]){
    string in=arr;
    //check if the name is valid
    if(!isalphainput(in)){
        cerr<<"Invalid Name!\n";
        return;
    }

    //check the input
    if(strlen(arr)>Maxname){
        cerr<<"The name is too long\n";
        return;
    }

    unsigned int i=0;
    //assign the name
    for ( ;(i<(Maxname-1))&&!(arr[i]=='\0');i++ )
        name[i]=arr[i];
    name[i]='\0';   //end the array
}

void student::set_id(const char arr[]){
    //check the input
    if(strlen(arr)>idsize){
        cerr<<"The ID is long\nTry again!\n";
        return;
    }
    else if(strlen(arr)<idsize){
        cerr<<"The ID is short\nTry again!\n";
        return;
    }

    unsigned int i=0;
    //assign the id
    for ( ;i<idsize;i++ )
        id[i]=arr[i];
    id[i]='\0';   //end the array
}

void student::set_grade(char c[]){
    //make it capital
    c[0]=toupper(c[0]);
    //the grades available
    const char grades[]     ="ABCDF";
    const char modifiers[]  =" + -";

    //check if the input is valid
    char gtest=0;
    char mtest=0;
    for (register unsigned int i=0;grades[i]!='\0';i++){
            if(c[0]==grades[i]){//It is valid
                    gtest=1;
            }
            if(c[1]==modifiers[i]){//It is valid
                    mtest=1;
            }
    }

    if(0==gtest||0==mtest){
        cerr<<"Invalid grade\n";
        return;
    }

    //assign the grade
    for (register unsigned int i=0;i<2;i++)
        grade[i] = c[i];
}

void student:: set_age(int n){
    //check the input
    if(n>Maxage){
        cerr<<"The age is long\n";
        return;
    }
    if(n<0){
        cerr<<"Invalid age\n";
        return;
    }
    //assign if correct
    age=n;
}

void student:: set_score(float n){
    //check the input
    if(n>Maxscore){
        cerr<<"The score is big\n";
        return;
    }
    else if (n<0-Maxscore){
        cerr<<"Invalid Score!\n";
        return;
    }
    //assign if correct
    score=n;
    //get the grade
    map_grade(score);
}

void student::set_student_info(){
    cout<<"Enter the name (Max "<<Maxname<<")\n";
    string input;    //string to take any input
    getline(cin,input);
    make_alpha("Name",input);   //make the name valid
    check_char_input("Name",input,Maxname);

    //send it as a character array
    set_name(input.c_str());

    //age
    cout<<"Enter the age ( Max "<<Maxage<<" )\n";
    getline(cin,input);
    check_int_input("Age",input,Maxage);

    //assign the age
    set_age(stoi(input));

    //ID
    cout<<"Enter the ID ( "<<idsize<<" characters)\n";
    getline(cin,input);
    check_char_input("ID",input,idsize,idsize);

    //send the array
    set_id(input.c_str());

    /*// if you want to enter the score
    //score
    cout<<"Enter the score ( Max "<<Maxscore<<" )\n";
    getline(cin,input);
    check_float_input("Score",input,Maxscore);

    //assign score
    set_score(stof(input));*/

    /*// if you want to set the grade
    //grade
    cout<<"Enter The grade\n";
    getline(cin,input);
    char input_grade[3]=" ",arrsize;

    //set the size
    if(strlen(input.c_str())<=2)
        arrsize=strlen(input.c_str());
    else
        arrsize=2;

    //assign the input
    for(register unsigned int i=0;i<arrsize;i++)
    input_grade[i]=input[i];
    if(strlen(input.c_str())==1)
        input_grade[1]=' ';
    set_grade(input_grade);*/
}

void student:: get_name(char arr[], const int len){
    //check the size
    if (len<strlen(name)){
        cout<<"The array is small\n";
        return;
    }

    register unsigned int i=0;
    for (;name[i]!='\0';i++)
        arr[i]=name[i];
    arr[i]='\0';
}

void student:: get_id(char arr[], const int len){
    //check the size
    if (len<idsize){
        cout<<"The array is small\n";
        return;
    }

    register unsigned int i=0;
    for (;i<idsize;i++)
        arr[i]=id[i];
    arr[i]='\0';
}

void student:: get_grade(char arr[],const int len){
    //check the size
    if (len<3){
        cout<<"Small size\n";
        return;
    }

    for(register unsigned int i=0;i<2;i++)
    arr[i]=grade[i];
    arr[2]='\0';
}

void student:: get_age(int &n){
    n=age;
}

void student:: get_score(float &n){
    n=score;
}

void student:: print_student_info(){
    cout<<"The student Name:  "<<name<<endl;
    cout<<"The student ID:    "<<id<<endl;
    cout<<"The student Age:   "<<age<<endl;
    cout<<"The student Score: "<<score<<endl;
    cout<<"The student Grade: "<<grade<<endl;
    grade_message();

    //text file
    char filename[] ="Students Data.txt";
    write_student_data(filename);

}

void student:: map_grade(float n){
    //check the input
    if (n>Maxscore){
       cerr<<"Score is big!\n";
       return;
    }
    else if (n<0-Maxscore){
        cerr<<"Invalid Score!\n";
        return;
    }
    //map the grade
    /*
    A+ (95-100)
    A (90-94)
    A- (85-89)
    B+ (80-84)
    B (75-79)
    B- (70-74)
    C+ (65-69)
    C (60-64)
    C- (55-59)
    D (50-54)
    F+ (45-49)
    F (35-44)
    F- (0-34)
    */

    if(n<35){
        strcpy_s(grade,"F-");
    }
    else if(n<45){
        strcpy_s(grade,"F ");
    }
    else if(n<50){
        strcpy_s(grade,"F+");
    }
    else if(n<55){
        strcpy_s(grade,"D ");
    }
    else if(n<60){
        strcpy_s(grade,"C-");
    }
    else if(n<65){
        strcpy_s(grade,"C ");
    }
    else if(n<70){
        strcpy_s(grade,"C+");
    }
    else if(n<75){
        strcpy_s(grade,"B-");
    }
    else if(n<80){
        strcpy_s(grade,"B ");
    }
    else if(n<85){
        strcpy_s(grade,"B+");
    }
    else if(n<90){
        strcpy_s(grade,"A-");
    }
    else if(n<95){
        strcpy_s(grade,"A ");
    }
    else if(n<=100){
        strcpy_s(grade,"A+");
    }
}

void student:: grade_message(){
    if(!strcmp(grade,"A+"))
        cout<<"Congratulations! Your performance has been outstanding."<<endl;
    else if(!strcmp(grade,"A "))
        cout<<"Excellent work! You've demonstrated a deep understanding of the material."<<endl;
    else if(!strcmp(grade,"A-"))
        cout<<"Great job! Your performance shows a strong grasp of the subject."<<endl;
    else if(!strcmp(grade,"B+"))
        cout<<"Well done! You've performed above average in the course."<<endl;
    else if(!strcmp(grade,"B "))
        cout<<"Good job! Your performance meets the expected standards."<<endl;
    else if(!strcmp(grade,"B-"))
        cout<<"You've passed the course, but there's room for improvement."<<endl;
    else if(!strcmp(grade,"C+"))
        cout<<"You've made it through, but consider seeking extra help if needed."<<endl;
    else if(!strcmp(grade,"C "))
        cout<<"You've passed, but there's room for improvement in your understanding."<<endl;
    else if(!strcmp(grade,"C-"))
        cout<<"You've passed, but you should review the material to improve."<<endl;
    else if(!strcmp(grade,"D"))
        cout<<"You've passed, but you may want to review the course material thoroughly."<<endl;
    else if(!strcmp(grade,"F+"))
        cout<<"You've fallen below the passing grade. Consider seeking help or reviewing your study habits."<<endl;
    else if(!strcmp(grade,"F "))
        cout<<"Unfortunately, you didn't pass. It's important to identify areas for improvement."<<endl;
    else if(!strcmp(grade,"F-"))
        cout<<"You didn't pass this time. Let's work together to improve your understanding."<<endl;

}

void student::write_student_data(const char filename[]){
    ofstream outfile(filename,ios::app);
    //check the file
    if(!outfile.is_open()){
        cerr<<"Can't Open The file\n";
        return;
    }

    //Name
    write_student_cell(outfile,name,Maxname);
    //ID
    write_student_cell(outfile,id,idsize);
    //Age Score grade
    outfile<<age<<'\t'<<score<<'\t'<<grade<<endl;
}

void student::write_student_cell(ofstream &file,const char input[],const int maxinput){
    //check the file
    if(!file.is_open()){
        cerr<<"Can't Open The file\n";
        return;
    }

    //calculating the space
    int spacesize=maxinput+(maxinput/10)-1-strlen(input);
    if(maxinput<10)
        spacesize+=2;

    file<<input;
    //put space
    for(register unsigned int i=0;i<spacesize;i++)
        file<<" ";
}
#endif
