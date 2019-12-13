#ifndef SIGNUP_H
#define SIGNUP_H

#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;
bool isSpecial( char ch )
//This function will test if a character is a $, %, # or *.
//It takes as its argument: a single character that represents the character to be tested.
//It returns true if the passed in character is a special character,
//or false if the character is not a special character.
{
    if(ch == '$' || ch == '%' || ch == '#' || ch == '*')
    return true;
    return false;
}
int SignUp()
{
int numOfCharsInPassword;
bool hasUpperCase, hasLowerCase, hasDigit, hasSpclChar, has6Chars;
char ch;
    string password;
    cout<<"Enter the password: ";
    cin>>password;
    hasUpperCase = false;
    hasLowerCase = false;
    hasDigit = false;
    hasSpclChar = false;
    has6Chars = false;
    for(int i = 0; i < password.length(); i++){
    cout<<ch; //Display the character.
//Code a cascading decision statement to test for the various required characters
    if(isalpha(ch) && isupper(ch))
        hasUpperCase = true;
    if(isalpha(ch) && islower(ch))
        hasLowerCase = true;
    if(isdigit(ch))
        hasDigit = true;
    if(isSpecial(ch))
        hasSpclChar = true;   
        numOfCharsInPassword++; //Increment a count of the number of characters in the password
    if(numOfCharsInPassword == 6)
        has6Chars = true;
        ch = password.at(i);
}
//Determine if the password was valid or not. If the password was invalid,
//display the things that were wrong. If the password was valid, display that it
//was valid.
    cout<<endl;
    if(!has6Chars)
        cout<<"Not enough characters"<<endl;
    if(!hasUpperCase)
        cout<<"Missing Uppercase letter"<<endl;
    if(!hasLowerCase)
        cout<<"Missing lowercase letter"<<endl;
    if(!hasDigit)
        cout<<"Missing digit"<<endl;
    if(!hasSpclChar)
        cout<<"Missing special character"<<endl;   
    if(has6Chars && hasUpperCase && hasLowerCase && hasDigit && hasSpclChar)
        cout<<"Valid password"<<endl;
}

#endif