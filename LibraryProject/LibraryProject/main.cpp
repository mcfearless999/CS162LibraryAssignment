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



int main(int argc, const char * argv[]) {
    string currentUser;
    char selection = ' ';
    //loadFile(Book)
    //loadFile(Users)
    //currentUser = LoginMenu();
    //if (currentUser == "XXX") return 0;
    //
    
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

