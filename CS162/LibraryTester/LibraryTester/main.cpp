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

void ClearBookList();
void ClearUserList();
char printMenu();
bool cancelCheck(string);
string login();
char loginMenu();
void getBookFileName(string defaultBook);
void getUsersFileName(string defaultUsers);
int lineCounter(char fileName[]);
void loadBookFile();
void getBookData(string fileLine,string bookData[]);
Book* loadBookPointer(string bookData[]);

string getUserLogin();
string Register();
void welcome(string userName);
Node* getCurUser(string userName);

void Decode(string checkOutString, int tempArr[]);
string Encode(int tempArr[]);

Book* getBookByID(int bookID);

void checkOutBook();
    string getBookFromUser();
    int getBookId(string bookTitle);
    void checkOut(int bookId);
    void removeFromLib();

void checkInBook();
    int checkInPrompt(int bookIDs[]);

int main() {
    
    string currentUser;
    
    char selection = ' ';
    

    currentUser = login();
    if (cancelCheck(currentUser) == true) return 0;
    welcome(currentUser);
    
    selection = printMenu();
    for (;;)
    {
        if (selection == 'a')
        {
            cout << "test decode" << endl;
            string temp = "3/5/11/0/23";
            int checkedOut[5];
            Decode(temp, checkedOut);
            
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
            //check in book
            //checkInBook();
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

void ClearBookList()
{
    //start at the first node
    Node * tempNode= (Node*)bookList.GetFirstNode();
    long idx = bookList.GetListLength();
    //for each node
    while (idx !=0)
    {
        //go to next node
        tempNode = (Node*)bookList.GetNextNode();
        Book* tempBook = (Book*)tempNode->data_;
        
        //delete data and set to NULL
        if (tempBook !=0)
        {
            delete tempBook;
            tempNode->data_ = NULL;
            
        }
        //delete node
        bookList.RemoveLinkFromFront();
        idx = bookList.GetListLength();
    }
}

void ClearUserList()
{
    //start at the first node
    Node * tempNode= (Node*)usersList.GetFirstNode();
    long idx = usersList.GetListLength();
    //for each node
    while (idx !=0)
    {
        //go to next node
        tempNode = (Node*)bookList.GetNextNode();
        Users* tempUser = (Users*)tempNode->data_;
        
        //delete data and set to NULL
        if (tempUser !=0)
        {
            delete tempUser;
            tempNode->data_ = NULL;
            
        }
        //delete node
        usersList.RemoveLinkFromFront();
        idx = usersList.GetListLength();
    }
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
    string defaultBook = "/users/chrism/bookList.txt";
    string defaultUsers = "/users/chrism/usersList.txt";
    
    getBookFileName(defaultBook);
    getUsersFileName(defaultUsers);
    loadBookFile();
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
    file.open(BookName.c_str(),ios_base::in) ;
    
    if (file.good() != true)
    {
        while(file.good() != true){
            cout << "Error: unable to open file, please enter a valid Input Book list file name" << endl;
            cin.clear();
            cin.ignore(1);
            cin.get(fileName,256, '\n'),
            file.open(fileName,ios_base::in) ;
        }
            strcpy(Book::bookFileList_,fileName);
    }else {
        strcpy(Book::bookFileList_,BookName.c_str());
    }
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

int lineCounter(char fileName[])
{
    int linecount = 0;
    fstream inFile;
    string fileLine;
    inFile.open(fileName,ios::in);
    do {
        getline(inFile,fileLine);
        linecount++;
    }while (inFile.peek() != EOF);
    inFile.close();
    inFile.clear();
    
    
    return linecount;
}

void loadBookFile()
{
    fstream inFile;
    string fileLine;
    Book* bookPtr;
    string bookData[5];
    int lineNum =0;
    string name;
    //clear list
    ClearBookList();
    //enter prompt for file path

    //get number of lines
    lineNum = lineCounter(Book::bookFileList_);
    //open and read file
    inFile.open(Book::bookFileList_,ios::in);
    for (int idx = 0; idx < lineNum; idx++)
    {
        //read data from each song file
        getline(inFile,fileLine);
        getBookData(fileLine, bookData);
        //dynamically create list of songs from mp3 collection
        bookPtr = loadBookPointer(bookData);
        bookList.AddLinkToBack(bookPtr);
    }
    cout << "File loaded, " <<  lineNum << " books loaded" << endl;
}


void getBookData(string fileLine,string bookData[])
{
    string tempWord;
    int lineIdx = 0;
    
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempWord = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    bookData[0] = tempWord;
    lineIdx=0;
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempWord = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    lineIdx=0;
    bookData[1] = tempWord;
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempWord = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    lineIdx=0;
    bookData[2] = tempWord;
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempWord = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    bookData[3] = tempWord;
    bookData[4] = fileLine;
    

}
Book* loadBookPointer(string bookData[])
{
    Book* tempBook = new Book;
    tempBook->SetTitle(bookData[0]);
    tempBook->SetAuth(bookData[1]);
    tempBook->SetPub(bookData[2]);
    tempBook->SetID(bookData[3]);
    tempBook->SetCheckout(bookData[4]);
    
    return tempBook;
}

string getUserLogin()
{
    string user;
    //prompt user for username
    //check login
    //if matched return Node*
    //set currentuser within the users object
    
    return user;
}

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

//loads user, prints welcome message, prints books currently checked out
//needs to be rechecked
void welcome(string userName)
{
    Users::currentUser_ =userName;
    string curBooksOut;
    int bookIds[5];
    Users* curUser;
    Node* tempNode=getCurUser(userName);
    usersList.SetCurNode(tempNode );
    //Display welcome message
    curUser = (Users*)tempNode->data_;
    userName = curUser->GetEmail();
    cout << "Welcome " <<  userName  << "CurUser lname" << endl;
    //curBookOut = CurUser->checkOut_;
    //checkOutDecode(curBookOut, bookIDs);
    
    cout << "You currently have the these books checked out" << endl;
   /* for (int idx = 0; idx <4; idx++)
    {
        Book* tempBook = getBookByID(bookIds[idx]);
        cout << tempBook->GetTitle() << endl;
    }*/
}

Node* getCurUser(string userName)
{
    Users* storedUser =0;
    Node * tempNode;
    tempNode= (Node*)usersList.GetFirstNode();
    storedUser = (Users*)tempNode->data_;
    tempNode = (Node*) usersList.GetFirstNode();
    long listLen = usersList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        if (userName == storedUser->GetUserName() )
        {
            return tempNode;
            
        }if(tempNode->next_)
        {
            tempNode =tempNode->next_;
        }
    }
    return 0;
}
//stores book titles in an array after searching through the list for each one
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


void checkOutBook()
{
    string bookTitle;
    bookTitle = getBookFromUser();
    int bookId = getBookId(bookTitle);
    //int bookId = 13; test value
    removeFromLib();
    checkOut(bookId);
}

string getBookFromUser()
{
    string title;
    cout << "Please enter the title of the book you wish to check out?" << endl << "-> ";
    cin.clear();
    cin.ignore(1);
    getline(cin,title);
    return title;
}

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




