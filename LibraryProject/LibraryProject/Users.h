
//#include "Book.h" //I am not sure we need to include
#ifndef Users_h
#define Users_h
#include <iostream>
#include <string>

using namespace std;

class Users
{
private:
    
	string firstName_; 
	string lastName_; 
    string email_;
	string ID_; 
	string checkOut_; 
    //we might want to have a login field as well
    string userName_;
public:
    //added static variables
    static char usersFileList_[512];
    static string currentUser_;
    int checkOut[5]; 
    Users();
	Users(string firstName_, string lastName_, string ID_, string checkOut_);
	void Register(); 
	void LogOn(); 
	void CheckOutBooks();
        void CheckInBooks(); 
	void AlreadyCheckedOut();
	
	string GetUserName();
    //I think we should have both first and last
	string GetFirstName();
    string GetLastName();
	string GetID(); 
	string GetCheckOut();
	string GetEmail();  
	
	void setFirstName(string firstName); 
	void setLastName(string lastName); 
	void setID(string ID); 
};
#endif /* Users_h */
