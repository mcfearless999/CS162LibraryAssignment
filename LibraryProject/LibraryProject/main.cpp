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
#include "LinkedList.h"

using namespace std;

LinkedList bookList;
LinkedList usersList;

char printMenu();
bool cancelCheck(string);
string login();
char loginMenu();
void getBookFileName(string defaultBook);
void getUsersFileName(string defaultUsers);
string getUserLogin();


int main() {
    
    string currentUser;
    char selection = ' ';


    currentUser = login();
    //if (cancelCheck(currentUser) == true) return 0;
    
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


string login()
{
    string defaultBook = "bookList.txt";
    string defaultUsers = "usersList.txt";
    
    getBookFileName(defaultBook);
    getUsersFileName(defaultUsers);
    string userLogin;
    char choice =loginMenu();
    if (choice == 'a')
    {
        //userLogin = getUserLogin();
        choice = ' ';
    }
    if (choice == 'b')
    {
        //userLogin = registerUser();
        choice= ' ';
    }
    if (choice == 'c')
    {
        userLogin = "XXX";
        choice = ' ';
    }
    return userLogin;
}

char loginMenu()
{
    char choice = ' ';
    cout << "Please choose an option" << endl;
    cout << "a) Login with Username" << endl;
    cout << "b) Register new Username" << endl;
    cout << "c) Quit" << endl;

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
    file.open(BookName.c_str(),ios_base::in) ;
    while (file.good() != true)
    {
        cout << "Error: unable to open file, please enter a valid Input Book list file name" << endl;
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
    file.open(UsersName.c_str(),ios_base::in) ;
    while (file.good() != true)
    {
        cout << "Error: unable to open file, please enter Input User list file name" << endl;
        cin.clear();
        cin.ignore(1);
        cin.get(fileName,256, '\n'),
        file.open(fileName,ios_base::in) ;
    }
    strcpy(Users::usersFileList_,fileName);
    delete [] fileName;
}

string getUserLogin()
{
    string user;
    //prompt user for username
    //check login
    //if matched return username
    //set currentuser within the users object
    
    return user;
}
