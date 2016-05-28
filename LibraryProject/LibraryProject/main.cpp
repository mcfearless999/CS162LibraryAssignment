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
void welcome();
Users* getCurUser(string email);
void checkOutDecode(string checkOutString, string checkarr[]);
string getBookTitle(int bookID);
void PrintBooksList(); 
void Register(string data[]);
void ChangeUsers();  
void LoadTextFiles();  
int lineCounter(); 

int main()
{
    
    string currentUser;
    
    char selection = ' ';
    

    currentUser = login();
    //if (cancelCheck(currentUser) == true) return 0;
    //welcome(currentUser);
    
    printMenu();
    for (;;)
    {
        if (selection == 'a')
        {
            //print book list
            
            selection = ' ';
        }
        if (selection == 'b')
        {
            //check out book

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
            //change user

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
        userLogin = getUserLogin();
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
    cout << "Enter Book file name: " << endl; 
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
    cout << "Enter Users file name: " << endl; 
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
void LoadTextFiles()
{
  fstream inFile; 
  
  string data[4]; 
  string fileLine; 
  Users* userptr; 
 
  //getUsersFileName(); 

  //ClearList(); 
 
  inFile.open(Users::usersFileList_,ios::in); 
  int lineNum = lineCounter(); 
  for (int idx = 0; idx < lineNum; idx++)
  {
     getline(inFile,fileLine); 
     //GetData(data, fileLine); 
  }

  cout << "This worked " << endl; 
  inFile.close(); 
  inFile.clear();

 
}
     

int lineCounter()
{
    int linecount = 0;
    fstream inFile;
    string fileLine;
    inFile.open(Users::usersFileList_,ios::in);
    do {
        getline(inFile,fileLine);
        linecount++;
    }while (inFile.peek() != EOF);
    inFile.close();
    inFile.clear();
    
    
    return linecount;
}



string getUserLogin()
{
    Node* tempNode; 
    Users* storedUser = 0; 
    string email; 
    cout << "Enter email: " << endl; 
    cin >> email; 
    storedUser = (Users*)tempNode->data_;
    long listlen = usersList.GetListLength();  
    for (int idx = 0; idx < (listlen); idx++)
     {
       if (email == storedUser->GetEmail()) 
	{
	    return email; 
        }
        
     cout << "Email Not Found Please Register " << endl; 
    	
    getCurUser(email); 
     }
    return 0; 
    
    
}


//loads user, prints welcome message, prints books currently checked out
void welcome(string userName)
{
    Users::currentUser_ =userName;
    string curBooksOut;
    string checkedOut[5];
    //Users* curUser;
    //curUser= getCurUser();
    //Display welcome message
    //cout << "Welcome " << CurUser->GetUserName(); << " " << "CurUser lname" << endl;
    //curBookOut = CurUser->checkOut_;
    //checkOutDecode(curBookOut, checkedOut);
    for (int idx = 0; idx <4; idx++)
    {
        cout << checkedOut[idx] << endl;
    }
}

Users* getCurUser(string email)
{
    string user; 
    Users* storedUser =0;
    Node * tempNode;
    tempNode= (Node*)usersList.GetFirstNode();
    storedUser = (Users*)tempNode->data_;
    tempNode = (Node*) usersList.GetFirstNode();
    long listLen = usersList.GetListLength();
    cout << "Enter the user to login as: " << endl; 

    cin >> user; 
    

    for( int idx = 0; idx < (listLen); idx++  )
    {
        if (email  == storedUser->GetUserName() )
        {
            return storedUser;
        }if(tempNode->next_)
        {
            tempNode =tempNode->next_;
        }
    }
    return 0;
}
//stores book titles in an array after searching through the list for each one
void checkOutDecode(string checkOutString, string checkArr[])
{
    int tempArr[5];
    for (int arrIdx = 0; arrIdx < 5; arrIdx++ )
    {
        int lineIdx =0;
        while(checkOutString[lineIdx] != '/')
        {
            lineIdx++;
        }
        tempArr[arrIdx] = stoi(checkOutString.substr(0,lineIdx));
        string temp = getBookTitle(tempArr[arrIdx]);
        checkArr = &temp;
        checkOutString.erase(0,lineIdx+1);
    }
    
    
}

string getBookTitle(int bookID)
{
    string title;
    if (bookID == 0) return "";
    
    Book * storedBook =0;
    Node * tempNode;
    tempNode= (Node*)bookList.GetFirstNode();
    storedBook = (Book*)tempNode->data_;
    tempNode = (Node*) usersList.GetFirstNode();
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        if (bookID == storedBook->GetID() )
        {
            string temp = storedBook->GetTitle();
            return temp;
        }if(tempNode->next_)
        {
            tempNode =tempNode->next_;
        }
    }
    
    return title;
}
void Register(string data[])
{
   
 	Users User;
	string fname; 
	string lname; 
	string email; 
	string id;  
 	cout << "Enter your First Name: " << endl; 
	cin >> fname; 
 	User.setFirstName(fname); 
        cout << "Enter your Last Name: " << endl; 
	cin >> lname; 
	User.setLastName(lname); 
	cout << "Enter your email: " << endl; 
	cin >> email; 
	User.setEmail(email);
        
	
}
void ChangeUsers()
{
   cout << "Logging in as new user... " << '\n' << endl;
   cout << "Enter email: " << endl; 
   getUserLogin(); 
    
} 
