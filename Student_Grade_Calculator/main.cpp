
/*
*   @file       Student Grade Calculator
*   @version    1.0.0
*   @brief      It is to calculate overall Grade based on the assignments, quizzes, and exams points
*   @details    The program allows users to input student information   and their respective scores for assignments, quizzes, and exams.
                The program will calculate the overall grade based on user-defined weightage for each category and
                display the final grade along with any additional information like letter grades or comments.
*   @author     Yousef Khaled Omar Mahmoud
*/

/*========================================================================
*   Project             : Student Grade Calculator
========================================================================*/

/* ******************** Includes Section Start ************************ */
#include <iostream>
#include <string.h>
#include "student.h"
#include "function.h"
/* ******************** Includes Section End ************************** */

/* ******************** Defintion Section Start *********************** */
using namespace std;
#define maxstudent 100
/* ******************** Defintiion Section End ************************ */

/* ******************** Sub-program Decleration Section Start ********** */
void overall_grade(student &s);
float default_assement_calc(const char inputname[],int num,int maxinput);
float custome_assement_calc(const char inputname[],float &maxsum,int &num, int maxnum);
/* ******************** Sub-program Decleration Section End ************ */

int main(){
    int snum=0;     //students number
    string input;
    //getting the students number
    cout<<"Enter the Number of students (Max "<<maxstudent<<")\n";
    getline(cin,input);
    check_int_input("Student Number",input,maxstudent);
    //making the student array
    snum=stoi(input);
    student* s= new student[snum];

    //check if there is place in memory
    if (s==NULL){
        cout<<"Memory allocation failed.\n";
        return 1;
    }

    //getting the student's information
    for (register unsigned int i=0;i<snum;i++){
        s[i].set_student_info();
        overall_grade(s[i]);
    }
    //printing
    for (register unsigned int i=0;i<snum;i++){
        s[i].print_student_info();
    }

    //delete the array
    delete [] s;

    return 0;

}


/* ******************** Sub-program Section Start ********************* */
void overall_grade(student &s){
    string input;
    //choosing the mode
    cout<<"Enter the mode\n 0:Default   1:Customize\n";
    getline(cin,input);
    input_size:
    while(strlen(input.c_str())!=1){
        cout<<"Invalid Input\nTry Again\n";
        getline(cin,input);
    }

    char numbers[][10]={"first","second","third","fourth","fifth","sixth","seventh","eighth","ninth","tenth"};
    float sum=0;

    switch (input[0]){
        case '0':
            cout<<"================Default Mode=================\n";
            goto default_mode;
            break;
        case '1':
            cout<<"================Custom Mode=================\n";
            goto custome_mode;
             break;
        default:
            cout<<"Invalid Input\nTry Again\n";
            getline(cin,input);
            goto input_size;
    }

    custome_mode:{
    int qnum    =5;
    #define maxquiz 20
    int anum    =10;
    #define maxasii 20
    int mnum    =2;
    #define maxmid  40
    int fnum    =2;
    #define maxfin  100
    //prints the details
    cout<<"The Quiz         max point is "<<maxquiz<<" points\n";
    cout<<"The Assignment   max point is "<<maxasii<<" points\n";
    cout<<"The Midterm      max point is "<<maxmid<<" points\n";
    cout<<"The Final        max point is "<<maxfin<<" points\n";
    cout<<"=============================================\n";

    float maxsum=0;
    //quiz
    sum+=custome_assement_calc("Quiz",maxsum,qnum,maxquiz);
    //assignment
    sum+=custome_assement_calc("Assignment",maxsum,anum,maxasii);
    //midterm
    sum+=custome_assement_calc("Midterm",maxsum,mnum,maxmid);
    //final
    sum+=custome_assement_calc("Final",maxsum,fnum,maxfin);
    //map the score to be the max score point
    sum=(sum/maxsum)*Maxscore;
    s.set_score(sum);
    return;
    }

    default_mode:{
        //d for default
        #define dqnum    2
        #define dmaxquiz 5
        #define danum    2
        #define dmaxasii 5
        #define dmnum    1
        #define dmaxmid  20
        #define dfnum    1
        #define dmaxfin  60
        //prints the details
        cout<<dqnum<<" Quizzes with     5  max points\n";
        cout<<danum<<" Assignments with 5  max points\n";
        cout<<dmnum<<" Midterm with     20 max points\n";
        cout<<dfnum<<" Final with       60 max points\n";
        cout<<"=============================================\n";

        //quiz
        sum+=default_assement_calc("Quiz",dqnum,dmaxquiz);
        //assignment
        sum+=default_assement_calc("Assignment",danum,dmaxasii);
        //midterm
        sum+=default_assement_calc("Midterm",dmnum,dmaxmid);
        //final
        sum+=default_assement_calc("Final",dfnum,dmaxfin);
        //score
        s.set_score(sum);
        return;
    }
}

float default_assement_calc(const char inputname[],int num,int maxinput){
    #define maxarrnum 10
    if(num>maxarrnum)
        return 0;

    float sum=0;
    char numbers[][maxarrnum]={"first","second","third","fourth","fifth","sixth","seventh","eighth","ninth","tenth"};
    string input;
    for(register unsigned int i=0;i<num;i++){
        cout<<"Enter the "<<numbers[i]<<" "<<inputname<<endl;
        getline(cin,input);
        check_float_input(inputname,input,maxinput,0-maxinput);
        sum+=stof(input);
    }
    return sum;
}

float custome_assement_calc(const char inputname[],float &maxsum,int &num, int maxnum){
    #define maxarrnum 10
    if(num>maxarrnum)
        return 0;

    float sum=0;
    char numbers[][maxarrnum]={"first","second","third","fourth","fifth","sixth","seventh","eighth","ninth","tenth"};
    string input;

    //the number of assements
    cout<<"Enter The Number of "<<inputname<<"s ( Max "<<num<<" )\n";
    getline(cin,input);
    check_int_input(inputname,input,num);
    num=stoi(input);

    //entering the points
    for(register unsigned int i=0;i<num;i++){
        cout<<"Enter the "<<numbers[i]<<" "<<inputname<<" max point\n";
        getline(cin,input);
        check_float_input(inputname,input,maxnum);
        float maxinput=stof(input);
        maxsum+=maxinput;
        cout<<"Enter your "<<numbers[i]<<" "<<inputname<<" point\n";
        getline(cin,input);
        check_float_input(inputname,input,maxinput,0-maxinput);
        sum+=stof(input);
    }
    return sum;
}
/* ******************** Sub-program  Section End ********************** */

/*
**************************************************************************
User            Date            Task    Details
**************************************************************************
Yousef          3sep2023         1      Making the student class
Yousef          4sep2023         2      Making the inputs  valid
Yousef          5sep2023         3      Maping the grade
Yousef          7sep2023         4      Making the function.h
Yousef          9sep2023         5      Making the input's check functions
Yousef          11sep2023        6      Making the input's make functions
Yousef          12sep2023        7      Making the overallgrade function
*/
