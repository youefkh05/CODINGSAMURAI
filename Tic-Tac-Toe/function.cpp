
#include "function.h"
#include <cmath>

void check_int_input(const char inputname[],string &input,const int maxnum,const int minimum){
    string maxsize;     //the max
    maxstr(maxsize,maxnum,minimum);
    input_size://we added extra char for the sign
    //check the size
    while(strlen(input.c_str())>strlen(maxsize.c_str())+1||strlen(input.c_str())==0){
        if(strlen(input.c_str())>strlen(maxsize.c_str()))
            cout<<"The "<<inputname<<" is big\n";
        else
            cout<<"Invalid "<<inputname<<"!\n";
        cout<<"Try again!\n";
        getline(cin,input);
    }

    //make sure it is a number
    make_intdigit(inputname,input);

    //the size is not right
    if(strlen(input.c_str())>strlen(maxsize.c_str())+1||strlen(input.c_str())==0)
            goto input_size;

    //check the number if it is valid
    int num=stoi(input);
    if(num>maxnum){
        cout<<"The is "<<inputname<<" is long\nTry again!\n";
        getline(cin,input);
        goto input_size;
    }
    else if(num<minimum){
        cout<<"The "<<inputname<<" is small\nTry again!\n";
        getline(cin,input);
        goto input_size;
    }
}

int isintdigit (string &input){
    if(strlen(input.c_str())==0)    //empty
        return 0;

    //to check if there is a sign
    if(input[0]!='+'&&input[0]!='-'&&!isdigit(input[0]))
        return 0;

    //check if it is only a sign
    if (strlen(input.c_str()) == 1 && (input[0] == '+' || input[0] == '-'))
        return 0;

    for(register unsigned int i=1;i<strlen(input.c_str());i++){
        if(!isdigit(input[i]))   //invalid input
            return 0;
    }

    return 1;
}

void make_intdigit(const char inputname[],string &input){
    //check if the input is valid
    while(!isintdigit(input)){
        cout<<"Invalid "<<inputname<<"\nTry again!\n";
        getline(cin,input);
    }
}

void check_float_input(const char inputname[],string &input,const int maxnum,const int minimum){
    string maxsize;     //the max
    maxstr(maxsize,maxnum,minimum);

    input_size:
    //make sure it is a number
    make_floatdigit(inputname,input);
    //check the size
    int int_counter=integer_part_counter(input);
    while(int_counter>strlen(maxsize.c_str())+1||strlen(input.c_str())==0){
        if(strlen(input.c_str())>strlen(maxsize.c_str())+1)
            cout<<"The "<<inputname<<" is big\n";
        else
            cout<<"Invalid "<<inputname<<"!\n";
        cout<<"Try again!\n";
        getline(cin,input);
        //make sure it is a float number
        make_floatdigit(inputname,input);
        int_counter=integer_part_counter(input);
    }

    //check the number if it is valid
    float num=stof(input);
    if(num>maxnum){
        cout<<"The is "<<inputname<<" is long\nTry again!\n";
        getline(cin,input);
        goto input_size;
    }
    else if(num<minimum){
        cout<<"The "<<inputname<<" is small\nTry again!\n";
        getline(cin,input);
        goto input_size;
    }
}

int isfloatdigit (string &input){
    if(strlen(input.c_str())==0)    //empty
        return 0;

    //to check if there is a sign
    if(input[0]!='+'&&input[0]!='-'&&input[0]!='.'&&!isdigit(input[0]))
        return 0;

    //check if it is only a sign
    if (strlen(input.c_str()) == 1 && (input[0] == '+' || input[0] == '-' || input[0] == '.'))
        return 0;

    //the point in float
    int dot_counter=0;
    if(input[0]=='.')
        dot_counter++;

    for(register unsigned int i=1;i<strlen(input.c_str());i++){
        if(!isdigit(input[i])&&input[i]!='.')   //invalid input
            return 0;
        if(input[i]=='.')
            dot_counter++;
        if(dot_counter>1)
            return 0;
    }

    return 1;
}

void make_floatdigit(const char inputname[],string &input){
   //check if the input is valid
    while(!isfloatdigit(input)){
        cout<<"Invalid "<<inputname<<"\nTry again!\n";
        getline(cin,input);
    }

    //if the is no number before the dot
    if(input[0]=='.'||(input[1]=='.'&&!isdigit(input[0]))){//we need to put 0 first
        char begining=0;//to know if there is a sign
        if(input[1]=='.')
            begining=1;

        //shifting right
        input[strlen(input.c_str())+2+begining]='\0';
        for(register unsigned int i=strlen(input.c_str())+1+begining;i>0;i--)
        input[i]=input[i-1];

        input[begining]='0';
    }
}

int integer_part_counter(string &input){
    //we count the integer part (assuming that the input is a number)
    //counting the ingerpart
    int ipart=0; //int part
    int y=stoi(input);
    y=abs(y);
    while(y>0){
        ipart++;
        y/=10;
        }
    return ipart;
}

int isalphainput (string &input){
    if(strlen(input.c_str())==0)    //empty
        return 0;

    for(register unsigned int i=0;i<strlen(input.c_str());i++){
        if(!isalpha(input[i])&&input[i]!=' ')   //invalid input
            return 0;
    }

    return 1;
}

void make_alpha(const char inputname[],string &input){
    //check if the input is valid
    while(!isalphainput(input)){
        cout<<"Invalid "<<inputname<<"\nTry again!\n";
        getline(cin,input);
    }
}

void check_char_input(const char inputname[],string &input,const int maxsize,const int minimum){
    //to make sure the size is right
    while(strlen(input.c_str())>maxsize||strlen(input.c_str())<minimum){
        if(strlen(input.c_str())>maxsize)
        cout<<"The "<<inputname<<" is too long\n";
        else
        cout<<"The "<<inputname<<" is short\n";

        cout<<"Try again!\n";
        getline(cin,input);
    }
}

void maxstr(string &maxstr,const int maxnum,const int mininum){
    //check which of them has the biggest number of characters
    string maxsize1=to_string(maxnum);
    string maxsize2=to_string(mininum);

    //compare to know
    if(strlen(maxsize1.c_str())>strlen(maxsize2.c_str()))
        maxstr=maxsize1;
    else
        maxstr=maxsize2;
}

