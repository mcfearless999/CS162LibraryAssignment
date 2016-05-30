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


Users userList; 
LinkedList bookList;
LinkedList usersList;


const string defaultBook = "/users/chrism/bookList.txt";
const string defaultUsers = "/users/chrism/usersList.txt";
void ClearBookList();
void ClearUserList();
char printMenu();
bool cancelCheck(string);
string login();
char loginMenu();
void getUsersData(string fileLine,string usersData[]);
string getUserLogin();
Users* loadUsersPointer(string usersData[]);
void welcome(string userName);
Users* findUser(string userName);
void WriteBookToFile(); 
void printAllBooks();
string Register();
void ChangeUsers();  


void fileFunctions();
    void getBookFileName(string defaultBook);
    void getUsersFileName(string defaultUsers);
    void loadBookFile();
    void getBookData(string fileLine,string bookData[]);
    Book* loadBookPointer(string bookData[]);
    int lineCounter(char fileName[]);
    void loadUserFile();

void checkOutBook();
string getBookFromUser();
int getBookId(string bookTitle);
void checkOut(int bookId);
void removeFromLib();
bool inventoryCheck(int bookId);

void Decode(string checkOutString, int tempArr[]);
string Encode(int tempArr[]);
int checkOutList(int tempArr[]);

Book* getBookByID(int bookID);
void checkOut(int bookId);

void checkInBook();
int checkInPrompt(int bookIDs[]);



int main() {

    
    string currentUser;
    
    char selection = ' ';
    
    ClearBookList();
    ClearUserList();
    fileFunctions();

    currentUser = login();
    if (cancelCheck(currentUser) == true){
        ClearUserList();
        ClearBookList();
    return 0;
    }
    welcome(currentUser);
    
    selection = printMenu();
    for (;;)
    {
        if (selection == 'a')
        {
            //print book list

            printAllBooks();             

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
            checkInBook(); 
            selection = ' ';
        }
        if (selection == 'd')
        {
            //PrintAllBooks();
            selection = ' ';
        }
        if (selection == 'e'){
            //change user
	    ChangeUsers(); 	
            selection = ' ';
            
        }
        if (selection == 'f'){
            WriteBookToFile();
            ClearBookList();
	    
            ClearUserList();
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
    cout << "a) Print All Books " << endl;
    cout << "b) Check out a book " << endl;
    cout << "c) Check in a book " << endl;
    cout << "d)  " << endl;
    cout << "e) Change Users " << endl;
    cout << "f) Quit" << endl;
    cout << " -> ";
    
    cin >> choice;
    return choice;
}


string login()
{
    Users * curUser = 0;
    for(;;){
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

        return "XXX";

        }
        curUser = findUser(userLogin);
        
        if (curUser ==0)
        {
            cout << "ERROR: Username not found. Please retry logging in or register" << endl;
        }else{
            return userLogin;
        }
        
    }
    
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
void fileFunctions()
{

    getBookFileName(defaultBook);
    getUsersFileName(defaultUsers);
    loadBookFile();
    loadUserFile();
}

void getBookFileName(string BookName){
    char* fileName;
    fileName = new char[256]; //new*
    fstream file;
    file.open(BookName.c_str(),ios_base::in) ;
    
    if (file.good() != true)
    {
        while(file.good() != true){
            cout << "Error: unable to open file, please enter a valid Book list file name" << endl;
            cin >> fileName;
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
    
    if (file.good() != true)
    {
        while(file.good() != true){
            cout << "Error: unable to open file, please enter a valid User list file name" << endl;

            cin >> fileName;
            file.open(fileName,ios_base::in) ;
        }
        strcpy(Users::usersFileList_,fileName);
    }else {
        strcpy(Users::usersFileList_,UsersName.c_str());
    }
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
        //dynamically create list of books from file
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



//unfinished

string getUserLogin()
{
    string email; 
    cout << "Enter email: " << endl; 
    cin >> email;
    
    return email; 
    
    
}


//loads user, prints welcome message, prints books currently checked out
//completely untested
//needs fixing
void welcome(string userName)
{

    string curBooksOut;
    int checkedOut[5];
    
    Node* tempNode = (Node*)usersList.GetCurNode();
    Users* curUser = (Users*)tempNode->data_;
    Book* tempBook;
    
    //Display welcome message
    cout << "Welcome " << curUser->GetFirstName() << " " << curUser->GetLastName() << endl;
    string curBookOut = curUser->GetCheckOut();
    Decode(curBookOut, checkedOut);
    int emptyListCheck =checkOutList(checkedOut);
    if (emptyListCheck == 0)
    {
        cout << "No Books currently checked out" << endl;
    }else{
    cout << "you curently have these books checked out" << endl;
    for (int idx = 0; idx <5; idx++)
    {
        //cout << checkedOut[idx] << endl;
            tempBook = getBookByID(checkedOut[idx]);
            if (tempBook !=0)
            {
                cout << tempBook->GetTitle()<< endl;
            }
        }
    }
}

//needs some work
Users* findUser(string userName)
{
    string title;
    
    Users * storedUser =0;
    Node * tempNode;
    tempNode= (Node*)usersList.GetFirstNode();
    storedUser = (Users*)tempNode->data_;
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        storedUser = (Users*)tempNode->data_;
        string tempUser =storedUser->GetEmail();
        if (userName == tempUser )
        {
            usersList.SetCurNode(tempNode);
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

int checkOutList(int tempArr[])
{
    int checkedOutCount = 0;
    for (int idx =0; idx < 5; idx++)
    {
        if (tempArr[idx] !=0) checkedOutCount++;
    }
    
    
    return checkedOutCount;
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
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        storedBook = (Book*)tempNode->data_;
        int tempID =storedBook->GetID();
        if (bookID == tempID )
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
        string email; 
	string id; 
	string firstName; 
	string lastName; 
 	string usersArray[4];
	cout << "Enter your First Name: " << endl;
	cin >> firstName; 
        cout << "Enter your Last Name: " << endl;
	cin >> lastName;  
	cout << "Enter your email: " << endl; 
	cin >> email;  
	cout << "Enter your ID Number: " << endl;
	cin >> id; 
	 
        
	usersArray[0] = firstName; 
	usersArray[1] = lastName; 
	usersArray[2] = email; 
	usersArray[3] = id; 
	 
	Users* tempPtr = loadUsersPointer(usersArray); 
	tempPtr->Users::AppendToUsersFile(); 
	return email; 

	
}
void ChangeUsers()
{
   cout << "Logging in as new user... " << '\n' << endl; 
   getUserLogin(); 
    

}
//higher level function, needs run through
//checks out books to the current user
void checkOutBook()
{
    string bookTitle;
    bookTitle = getBookFromUser();
    int bookId = getBookId(bookTitle);
    if (bookId == 0)
    {
        cout << "Error: book not found, check your spelling" << endl;;
        }else{
            if (inventoryCheck(bookId) == true)
            {
                cout << "I'm sorry, that book is already checked out" << endl << "Please choose another book" << endl;
            }else{
                removeFromLib();
                checkOut(bookId);
                cout << "checking out " << bookTitle << endl;
            }
    }
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
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        storedBook = (Book*)tempNode->data_;
        string tempTitle = storedBook->GetTitle();
        if (bookTitle == tempTitle )
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
//tested, works
void printAllBooks()
{
    Node* tempNode;
    Book* tempBook;
    tempNode = (Node*) bookList.GetFirstNode();
    tempBook = (Book*) tempNode->data_;
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        cout << tempBook->GetTitle()<< ", " << tempBook->GetAuth() << ", "<<
        tempBook->GetID() << "  ";
        if (tempBook->GetCheckOut() != "0")
        {
            cout << "Currently Checked out";
        }
        cout << endl;
        if (tempNode->next_){
            tempNode = tempNode->next_;
        }
        tempBook = (Book*)tempNode->data_;
        //print data to console
    }
    
    
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
    //extract numbers from encoded string
    Decode(checkedOutBooks,tempArr);
    if (checkOutList(tempArr) ==5)
    {
        cout << "I'm sorry you need to check in books before you can check out anymore" << endl;
    }else{
        for (int idx = 0; idx< 5; idx++)
        {
            if(tempArr[idx] == 0)
            {
                tempArr[idx] = bookId;
                bookId = 0;
            }
            
        }
        
        tempCheck = Encode(tempArr);
        //cout << tempCheck << endl;
        currentUser->CheckBooks(tempCheck);
    }

}

bool inventoryCheck(int bookID)
{
    bool check = true;
    getBookByID(bookID);
    Node* tempBookNode = (Node*)bookList.GetCurNode();
    Book* curBook = (Book*)tempBookNode->data_;
    if (curBook->GetCheckOut() == "0") check = false;
    return check;
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
    
    cout << "Please choose which book you wish to check in:" << endl;
    cout << "Enter 0 to cancel" << endl;
    tempBook = getBookByID(bookIDs[0]);
    if (bookIDs[0] !=0)
    {
        cout << "1) " << tempBook->GetTitle() << endl;
    }
    if (bookIDs[1] !=0)
    {
        tempBook = getBookByID(bookIDs[1]);
        cout << "2) " << tempBook->GetTitle() << endl;
    }
    if (bookIDs[2] !=0)
    {
        tempBook = getBookByID(bookIDs[2]);
        cout << "3) " << tempBook->GetTitle() << endl;
    }
    if (bookIDs[3] !=0)
    {
        tempBook = getBookByID(bookIDs[3]);
        cout << "4) " << tempBook->GetTitle() << endl;
    }
    if (bookIDs[4] !=0)
    {
        tempBook = getBookByID(bookIDs[4]);
        cout << "5) " << tempBook->GetTitle() << endl;
    }
    
    
    
    cin >> checkInBook;
    
    if(checkInBook !=0) checkInBook = bookIDs[(checkInBook-1)];
    
    return checkInBook;
}


void loadUserFile()
{
    fstream inFile;
    string fileLine;
    Users* UserPtr;
    string UserData[5];
    int lineNum =0;
    string name;
    //clear list
    //ClearBookList();
    //enter prompt for file path

    //get number of lines
    lineNum = lineCounter(Users::usersFileList_);
    //open and read file
    inFile.open(Users::usersFileList_,ios::in);
    for (int idx = 0; idx < lineNum; idx++)
    {
        //read data from each song file
        getline(inFile,fileLine);
        getUsersData(fileLine,UserData);
        //dynamically create list of songs from mp3 collection
        UserPtr = loadUsersPointer(UserData);
        usersList.AddLinkToBack(UserPtr);
    }
    cout << "File loaded, " <<  lineNum << " users loaded" << endl;
}
Users* loadUsersPointer(string usersData[])
{
    Users* tempUser = new Users;
    tempUser->setFirstName(usersData[0]);
    tempUser->setLastName(usersData[1]);
    tempUser->setID(usersData[2]);
    tempUser->setEmail(usersData[3]);
    tempUser->setCheckOut(usersData[4]);

    //tempUser->Users::AppendToUsersFile(); 
    return tempUser;  

}
void getUsersData(string fileLine,string usersData[])
{
    string tempUsers;
    int lineIdx = 0;

    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempUsers = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    usersData[0] = tempUsers;
    //cout << tempUsers << endl;
    lineIdx=0;
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempUsers = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    lineIdx=0;
    usersData[1] = tempUsers;
    //cout << tempUsers << endl;
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempUsers = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    lineIdx=0;
    usersData[2] = tempUsers;
    //cout << tempUsers << endl;
    while (fileLine[lineIdx] != ',')
    {
        lineIdx++;
    }
    tempUsers = fileLine.substr(0, lineIdx);
    fileLine.erase(0, lineIdx + 2);
    usersData[3] = tempUsers;
    //cout << tempUsers << endl;
    usersData[4] = fileLine;
    //cout << fileLine << endl;


}
void WriteBookToFile()
{
    ofstream outStream; 
    outStream.open("/users/chrism/bookListTest.txt",ios_base::out);
    Node* tempNode;
    Book* tempBook;
    tempNode = (Node*) bookList.GetFirstNode();
    tempBook = (Book*) tempNode->data_;
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        outStream << tempBook->GetTitle()<< ", " << tempBook->GetAuth() << ", "<<
        tempBook->GetID() << ", " << tempBook->GetCheckOut() << endl;
        if (tempNode->next_){
            tempNode = tempNode->next_;
        }
        tempBook = (Book*)tempNode->data_;
       
    }


}

