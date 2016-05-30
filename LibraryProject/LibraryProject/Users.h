
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
	 
	void LogOn(); 
    void CheckBooks(string booksList);
	void AlreadyCheckedOut();
        void AppendToUsersFile(); 	
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
	void setEmail(string email);
    void setCheckOut(string checkout);
};
#endif /* Users_h */
