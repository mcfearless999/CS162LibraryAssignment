 //Chris McPherson G03852060
//working with Marcel Delisser

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
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
void WriteUsersToFile();



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
            //check in book from the user
            checkInBook();
            selection = ' ';
        }
        if (selection == 'd')
        {
            //Change Users
	    ChangeUsers(); 
            selection = ' ';
        }
        
        if (selection == 'e')
	{
        //quit program
        WriteBookToFile();
        WriteUsersToFile();
	    ClearBookList(); 
	    ClearUserList();	
	    return 0; 	
                
        }   
        else
	{

	   selection = printMenu(); 

        }
    
    }
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
    cout << "d) Change Users " << endl;
    cout << "e) Quit" << endl;
    cout << " -> ";
    
    cin >> choice;
    return choice;
}

//takes different options from the user in order to login, or register new user
string login()
{
    Users * curUser = 0;
    string userLogin;
    while(curUser == 0){
        
        char choice =loginMenu();
        if (choice == 'a')
        {
            //logs in with an email stored in the text file
            userLogin = getUserLogin();
            curUser = findUser(userLogin);
            if (curUser ==0)
            {
                cout << "ERROR: Username not found. Please retry logging in or register" << endl;
            }
            choice = ' ';
        }
        if (choice == 'b')
        {
            //adds a new user to the link list and appends to file
            userLogin = Register();
            curUser = findUser(userLogin);
            if (userLogin=="XXX")
            {
                cout << "ERROR: That email is already registered to another user" << endl;
            }
        choice= ' ';
        }
        if (choice == 'c')
        {
        return "XXX";

        }
        
    }
   
        
        
        return userLogin;
}


//displays options and takes input from the user
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
//allows user to cancel in the login menu, not fully implemented for the entire program
bool cancelCheck(string input)
{
    bool cancel = false;
    if (input == "XXX") cancel = true;
    return cancel;
}
//higher level function for all the file loading functions
void fileFunctions()
{

    getBookFileName(defaultBook);
    getUsersFileName(defaultUsers);
    loadBookFile();
    loadUserFile();
}
//checks the default path for the book file, if invalid, prompts user for new file path
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


//checks the default path for the users file, if invalid, prompts user for new file path
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


//opens file, counts number of lines, then closes file
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

//reads in lines from the book file, parses lines, dynamically creates book objects and loads into linked list
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
//parses the lines from the book list file
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
//loads parsed data into dynamically created book object
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



//gets users email through a prompt

string getUserLogin()
{
    string email; 
    cout << "Enter email: " << endl; 
    cin >> email;
    
    return email; 
     
    
}


//loads user, prints welcome message, prints books currently checked out

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

//searches through the linked list and returns the first book with a matching title to the parameter
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
//takes the checked out book string, parses it, and stores each element in an array
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
//takes array and encodes elements into a check out string
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

//checks the number of books checked out by user
int checkOutList(int tempArr[])
{
    int checkedOutCount = 0;
    for (int idx =0; idx < 5; idx++)
    {
        if (tempArr[idx] !=0) checkedOutCount++;
    }
    
    
    return checkedOutCount;
}


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
 	string usersArray[5];
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
	usersArray[2] = id;
	usersArray[3] = email;
    usersArray[4] = "0/0/0/0/0";
	
	Users* tempUser = findUser(email); 
        if (tempUser != 0)
	{
        
	  return "XXX";
	}
	else
	{ 
	Users* tempPtr = loadUsersPointer(usersArray);
    usersList.AddLinkToBack(tempPtr);
	tempPtr->Users::AppendToUsersFile(); 
	return email; 
	}
	
}
//allows user to change usernames
void ChangeUsers()
{
   cout << "Logging in as new user... " << '\n' << endl; 
   string email = getUserLogin();   
   findUser(email);
   welcome(email);  
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


//searches through linked list by title and returns the book ID
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
//prints all books to the console, hides which user has checked out which book
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


//decodes checkout string, changes it to store a book that is checked out, re-encodes string, and stores it with the user
void checkOut(int bookId)
{
    Node * tempNode =(Node*)usersList.GetCurNode();
    Users * currentUser = (Users*)tempNode->data_;
    string checkedOutBooks = currentUser->GetCheckOut();
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
//checks if the book is checked out or not
bool inventoryCheck(int bookID)
{
    bool check = true;
    getBookByID(bookID);
    Node* tempBookNode = (Node*)bookList.GetCurNode();
    Book* curBook = (Book*)tempBookNode->data_;
    if (curBook->GetCheckOut() == "0") check = false;
    return check;
}

//sets the checked out string on the book to whoever is checking it out
void removeFromLib()
{
    Node* tempBookNode = (Node*)bookList.GetCurNode();
    Node* tempUserNode = (Node*)usersList.GetCurNode();
    Book* curBook = (Book*) tempBookNode->data_;
    Users* curUser = (Users*) tempUserNode->data_;
    
    string userName = curUser->GetEmail();
    curBook->SetCheckout(userName);
}
//displays books currently checked out, allows user to choose which book to check in through a menu
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

            curBook = getBookByID(checkInID);
            curBook->SetCheckout("0");
            string checkInString = Encode(bookIDs);
            curUser->CheckBooks(checkInString);
            cout << curBook->GetTitle() << " checked in" << endl;
        }
        
    }
}
//displays check in menu
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
        
    
    cout << "-> ";
    cin >> checkInBook;
    if (checkInBook < 0 || checkInBook > 5){
            cout << "ERROR: unrecognized option" << endl;
            checkInBook=0;
    }
    if(checkInBook !=0) checkInBook = bookIDs[(checkInBook-1)];
    
    return checkInBook;
}
    
//
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
        //read data from each user
        getline(inFile,fileLine);
        getUsersData(fileLine,UserData);
        //dynamically create list of users from users file
        UserPtr = loadUsersPointer(UserData);
        usersList.AddLinkToBack(UserPtr);
    }
    cout << "File loaded, " <<  lineNum << " users loaded" << endl;
}
//dynamically create User and load data values
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
//parses data from the string that is being loaded from the file
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
//writes the book linked list to the book list tile
void WriteBookToFile()
{
    ofstream outStream; 
    outStream.open(Book::bookFileList_,ios_base::out);
    Node* tempNode;
    Book* tempBook;
    tempNode = (Node*) bookList.GetFirstNode();
    tempBook = (Book*) tempNode->data_;
    long listLen = bookList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        string temp = tempBook->GetCheckOut();
        outStream << tempBook->GetTitle()<< ", " << tempBook->GetAuth() << ", "<<
        tempBook->GetPub() << ", " << tempBook->GetID() << ", " << tempBook->GetCheckOut() << endl;
        
        if (tempNode->next_){
            tempNode = tempNode->next_;
        }
        tempBook = (Book*)tempNode->data_;
       
    }


}
void WriteUsersToFile()
{
    ofstream outStream;
    outStream.open(Users::usersFileList_,ios_base::out);
    Node* tempNode;
    Users* tempUsers;
    tempNode = (Node*) usersList.GetFirstNode();
    tempUsers = (Users*)tempNode->data_;
    long listLen = usersList.GetListLength();
    for( int idx = 0; idx < (listLen); idx++  )
    {
        string temp = tempUsers->GetCheckOut();
        outStream << tempUsers->GetFirstName() << ", " << tempUsers->GetLastName() << ", "<<
        tempUsers->GetID() << ", " << tempUsers->GetEmail() << ", " << tempUsers->GetCheckOut() << endl;
        
        if (tempNode->next_){
            tempNode = tempNode->next_;
        }
        tempUsers = (Users*)tempNode->data_;
        
    }
    
    
}

