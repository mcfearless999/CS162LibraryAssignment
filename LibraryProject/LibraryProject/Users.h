
//#include "Book.h" //I am not sure we need to include
#ifndef Users_h
#define Users_h
#include <iostream>

using namespace std;

class Users
{
private:
    
	string firstName_; 
	string lastName_; 
    string email_;
	int ID_; 
	string checkOut;
    //we might want to have a login field as well
    string login;
public:
    //added static variables
    static char usersFileList_[512];
    static char currentUser_[512];
    
    Users();
	Users(string firstName, string lastName, int ID, string checkout);
	void Register(); 
	void LogOn(); 
	void CheckOutBooks();
        void CheckInBooks(); 
	void AlreadyCheckedOut();
	
	string GetUser();
    //I think we should have both first and last
	string GetFirstName();
    string GetLastName();
	int GetID(); 
	string GetCheckOut(); 
	
	void setFirstName(string firstName); 
	void setLastName(string lastName); 
	void setID(int ID); 
};
#endif /* Users_h */
