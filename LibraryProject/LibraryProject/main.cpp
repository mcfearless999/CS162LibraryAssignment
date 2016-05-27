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
void welcome(string username);
Users* getCurUser();
void checkOutDecode(string checkOutString, string checkarr[]);
string getBookTitle(int bookID);

void Register(string data[]);


void checkOutBook();
string getBookFromUser();
int getBookId(string bookTitle);
void checkOut(int bookId);
void removeFromLib();

int main() {
    
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
            checkOutBook();
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
    cout << "b) Check out a book " << endl;
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
//unfinished
string getUserLogin()
{
    string  user;
    //prompt user for username
    //check login
    //if matched return Node*
    //set currentuser within the users object
    
    return user;
}


//loads user, prints welcome message, prints books currently checked out
//completely untested
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
//may need to be redone
Users* getCurUser()
{
    Users* storedUser =0;
    Node * tempNode;
    tempNode= (Node*)usersList.GetFirstNode();
    storedUser = (Users*)tempNode->data_;
    tempNode = (Node*) usersList.GetFirstNode();
    long listLen = usersList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        if (Users::currentUser_ == storedUser->GetUserName() )
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
//tested
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
//untested
//searches through book list for title based on ID

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
//We are going to need to have this return the username as a string
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
//higher level function, needs run through
//checks out books to the current user
void checkOutBook()
{
    string bookTitle;
    bookTitle = getBookFromUser();
    int bookId = getBookId(bookTitle);
    //int bookId = 13;
    checkOut(bookId);
}
//tested
//gets title from the user
string getBookFromUser()
{
    string title;
    cout << "Please enter the title of the book you wish to check out?" << endl << "-> ";
    cin.clear();
    cin.ignore(1);
    getline(cin,title);
    return title;
}

//untested
//searches through linked list by title
int getBookId(string bookTitle)
{
    int ID;
    Book * storedBook =0;
    Node * tempNode;
    tempNode= (Node*)bookList.GetFirstNode();
    storedBook = (Book*)tempNode->data_;
    tempNode = (Node*) usersList.GetFirstNode();
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        if (bookTitle == storedBook->GetTitle() )
        {
            ID = storedBook->GetID();
            return ID;
        }if(tempNode->next_)
        {
            tempNode =tempNode->next_;
        }
        bookList.SetCurNode(tempNode);
    }
    return 0;
}

//mechanics tested
//removes checked out books from checkedout string
void checkOut(int bookId)
{
    Node * tempNode =(Node*)usersList.GetCurNode();
    Users * currentUser = (Users*)tempNode->data_;
    string checkedOutBooks = currentUser->GetCheckOut(); //"5/23/11/0/0";
    string tempCheck ="";
    int tempArr[5];
    for (int arrIdx = 0; arrIdx < 5; arrIdx++ )
    {
        int lineIdx =0;
        while(checkedOutBooks[lineIdx] != '/')
        {
            lineIdx++;
        }
        tempArr[arrIdx] = stoi(checkedOutBooks.substr(0,lineIdx));
        checkedOutBooks.erase(0,lineIdx+1);
    }
    for (int idx = 0; idx < 5; idx++)
    {
        if(tempArr[idx] == 0)
        {
            tempArr[idx] = bookId;
            bookId = 0;
        }
        tempCheck.append(to_string(tempArr[idx]));
        tempCheck.append("/");
    }
    tempCheck.pop_back();
    //cout << tempCheck << endl;
    currentUser->CheckOutBooks(tempCheck);
    
}
//Untested
void removeFromLib()
{
    Node* tempBookNode = (Node*)bookList.GetCurNode();
    Node* tempUserNode = (Node*)usersList.GetCurNode();
    Book* curBook = (Book*) tempBookNode->data_;
    Users* curUser = (Users*) tempUserNode->data_;
    
    string userName = curUser->GetUserName();
    curBook->SetCheckout(userName);
}

