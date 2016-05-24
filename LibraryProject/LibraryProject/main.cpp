//
//  main.cpp
//  LibraryProject
//
//  Created by Chris M on 5/17/16.
//  Copyright © 2016 Chris McPherson. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "Book.h"
#include "Users.h"

using namespace std;

char printMenu();
bool cancelCheck(string);
void getBookFileName(string defaultBook);
void getUsersFileName(string defaultUsers);

int main() {
    
    string currentUser;
    char selection = ' ';
    string defaultBook = "bookList.txt";
    string defaultUsers = "usersList.txt";
    
    getBookFileName(defaultBook);
    //loadFile(defaultUsers)
    //currentUser = LoginMenu();
    //if (cancelCheck(currentUser) == false) return 0;
    //
    printMenu();
    for (;;)
    {
        if (selection == 'a')
        {

            
            selection = ' ';
        }
        if (selection == 'b')
        {


            selection = ' ';
        }
        if (selection == 'c')
        {

            selection = ' ';
        }
        if (selection == 'd')
        {

            selection = ' ';
        }
        if (selection == 'e'){


            selection = ' ';
            
        }
        if (selection == 'f'){

            return 0;
            
        }else{
            selection = printMenu();
        }
    

    }
    
    
    return 0;
}
//this is a generalized menu that would display different options
char printMenu()
{
    char choice = ' ';
    cout << "Please choose an option" << endl;
    cout << "a) " << endl;
    cout << "b) " << endl;
    cout << "c) " << endl;
    cout << "d) " << endl;
    cout << "e) " << endl;
    cout << "f) Quit" << endl;
    cout << " -> ";
    
    cin >> choice;
    return choice;
}

bool cancelCheck(string input)
{
    bool cancel = false;
    if (input == "XXX") cancel = true;
    return cancel;
    
        
}

void getBookFileName(string BookName){
    char* fileName;
    fileName = new char[256]; //new*
    fstream file;
    
    cout << "Input Book list file name?";
    
    cin.clear();
    cin.ignore(1);
    cin.get(fileName, 256, '\n');
    file.open(BookName.c_str(),ios_base::in) ;
    while (file.good() != true)
    {
        cout << "?unable to open file, please enter a valid file name" << endl;
        cin.clear();
        cin.ignore(1);
        cin.get(fileName,256, '\n'),
        file.open(fileName,ios_base::in) ;
    }
    strcpy(Book::bookFileList_,fileName);
    delete [] fileName;
}

void getUsersFileName(string UsersName){
    char* fileName;
    fileName = new char[256]; //new*
    fstream file;
    
    cout << "Input Book list file name?";
    
    cin.clear();
    cin.ignore(1);
    cin.get(fileName, 256, '\n');
    file.open(UsersName.c_str(),ios_base::in) ;
    while (file.good() != true)
    {
        cout << "?unable to open file, please enter a valid file name" << endl;
        cin.clear();
        cin.ignore(1);
        cin.get(fileName,256, '\n'),
        file.open(fileName,ios_base::in) ;
    }
    strcpy(Users::usersFileList_,fileName);
    delete [] fileName;
}



