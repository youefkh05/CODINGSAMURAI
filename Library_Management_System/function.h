#ifndef FUNCTION_H_
#define FUNCTION_H_

#include <string>
#include <iostream>
#include <string.h>
using namespace std;

//to make sure the input is valid
void check_int_input(const char inputname[],string &input,const int maxnum,const int mininum=0);
int isintdigit (string &input);
void make_intdigit(const char inputname[],string &input);

void check_float_input(const char inputname[],string &input,const int maxnum,const int mininum=0);
int isfloatdigit (string &input);
void make_floatdigit(const char inputname[],string &input);
int integer_part_counter(string &input);

void maxstr(string &maxstr,const int maxnum,const int mininum);
int isalphainput (string &input);
void make_alpha(const char inputname[],string &input);
void check_char_input(const char inputname[],string &input,const int maxsize,const int mininum=1);

#endif // FUNCTION_H_INCLUDED
