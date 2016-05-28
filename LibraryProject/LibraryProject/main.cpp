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

void PrintBooksList(); 
string Register();
void ChangeUsers();  
void LoadTextFiles();  
int lineCounter(); 



void checkOutBook();
string getBookFromUser();
int getBookId(string bookTitle);
void checkOut(int bookId);
void removeFromLib();

void Decode(string checkOutString, int tempArr[]);
string Encode(int tempArr[]);

Book* getBookByID(int bookID);
void checkOut(int bookId);

void checkInBook();
int checkInPrompt(int bookIDs[]);



int main() {

    
    string currentUser;
    
    char selection = ' ';
    

    currentUser = login();
    if (cancelCheck(currentUser) == true) return 0;
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
    cout << "c) Check in a book " << endl;
    cout << "d) " << endl;
    cout << "e) Change Users " << endl;
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
       userLogin = Register();
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




//unfinished

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
//completely untested
//needs fixing
void welcome()
{

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
//tested
void Decode(string checkOutString, int tempArr[])
{
    
    for (int arrIdx = 0; arrIdx < 5; arrIdx++ )
    {
        int lineIdx =0;
        while(checkOutString[lineIdx] != '/')
        {
            lineIdx++;
        }
        tempArr[arrIdx] = stoi(checkOutString.substr(0,lineIdx));
        checkOutString.erase(0,lineIdx+1);
    }
}

string Encode(int tempArr[])
{
    string encodedString;
    for (int idx = 0; idx < 5; idx++)
    {
        encodedString.append(to_string(tempArr[idx]));
        encodedString.append("/");
    }
    encodedString.pop_back();
    return encodedString;
}

//untested
//searches through book list for title based on ID
Book*  getBookByID(int bookID)
{
    string title;
    if (bookID == 0) return 0;
    
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
            bookList.SetCurNode(tempNode);
            return storedBook;
            
        }if(tempNode->next_)
        {
            tempNode =tempNode->next_;
        }
    }
    
    return 0;
}

//We are going to need to have this return the username as a string
string Register()
{
   
 	Users* User = new Users;
	string fname; 
	string lname; 
	string email; 
	string id;  
 	cout << "Enter your First Name: " << endl; 
	cin >> fname; 
 	User->setFirstName(fname); 
        cout << "Enter your Last Name: " << endl; 
	cin >> lname; 
	User->setLastName(lname); 
	cout << "Enter your email: " << endl; 
	cin >> email; 
	User->setEmail(email);
  
        usersList.AddLinkToBack(User); 
	
	
	return email; 	
        
	
}
void ChangeUsers()
{
   cout << "Logging in as new user... " << '\n' << endl;
   cout << "Enter email: " << endl; 
   getUserLogin(); 
    


    
 

}
//higher level function, needs run through
//checks out books to the current user
void checkOutBook()
{
    string bookTitle;
    bookTitle = getBookFromUser();
    int bookId = getBookId(bookTitle);
    //int bookId = 13; test value
    removeFromLib();
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
    //Node * tempNode =(Node*)usersList.GetCurNode();
    //Users * currentUser = (Users*)tempNode->data_;
    string checkedOutBooks = /*currentUser->GetCheckOut();*/ "5/23/11/0/0";
    string tempCheck ="";
    int tempArr[5];
    //extract numbers from encoded string
    Decode(checkedOutBooks,tempArr);
    for (int idx = 0; idx< 5; idx++)
    {
        if(tempArr[idx] == 0)
        {
            tempArr[idx] = bookId;
            bookId = 0;
        }
        
    }
    tempCheck = Encode(tempArr);
    cout << tempCheck << endl;
    //currentUser->CheckBooks(tempCheck);
    
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

void checkInBook()
{
    int bookIDs[5];
    Node* tempUserNode = (Node*)usersList.GetCurNode();
    Node* tempBookNode = (Node*)bookList.GetCurNode();
    Users* curUser = (Users*) tempUserNode->data_;
    Book* curBook = (Book*)tempBookNode->data_;
    string checkOutString = curUser->GetCheckOut();
    Decode(checkOutString, bookIDs);
    if (bookIDs[0] == 0)
    {
        cout << "No books currently checked out" << endl;
    }else
    {
        
        int checkInID = checkInPrompt(bookIDs);
        if (checkInID != 0)
        {
            for (int idx = 0; idx< 5; idx++)
            {
                //removing book from users list
                if (bookIDs[idx] == checkInID) bookIDs[idx]=0;
            }
            curBook->SetCheckout("0");
            string checkInString = Encode(bookIDs);
            curUser->CheckBooks(checkInString);
            cout << curBook->GetTitle() << " checked in" << endl;
        }
        
    }
}

int checkInPrompt(int bookIDs[])
{
    int checkInBook = 0;
    Book * tempBook;
    if (bookIDs[0] !=0)
    {
        cout << "Please choose which book you wish to check in:" << endl;
        cout << "Enter 0 to cancel" << endl;
        tempBook = getBookByID(bookIDs[0]);
        cout << "1) " << tempBook->GetTitle() << endl;
        if (bookIDs[1] !=0)
        {
            tempBook = getBookByID(bookIDs[1]);
            cout << "2) " << tempBook->GetTitle() << endl;
            if (bookIDs[2] !=0)
            {
                tempBook = getBookByID(bookIDs[2]);
                cout << "3) " << tempBook->GetTitle() << endl;
                if (bookIDs[3] !=0)
                {
                    tempBook = getBookByID(bookIDs[3]);
                    cout << "4) " << tempBook->GetTitle() << endl;
                    if (bookIDs[4] !=0)
                    {
                        tempBook = getBookByID(bookIDs[4]);
                        cout << "5) " << tempBook->GetTitle() << endl;
                    }
                }
            }
        }
        cin >> checkInBook;
    }
    if(checkInBook !=0) checkInBook = bookIDs[(checkInBook-1)];
    
    return checkInBook;
}


