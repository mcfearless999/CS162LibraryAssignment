
#include "Book.h"
#ifndef Users_h
#define Users_h

class Users
{
private:
	string firstName_; 
	string lastName_; 
        string email_; //did we want to include email?
	int ID_; 
	string checkOut; 
public:
        User();
	User(string firstName, string lastName, int ID, string checkout); 
	void Register(); 
	void LogOn(); 
	void CheckOutBooks();
        void CheckInBooks(); 
	void AlreadyCheckedOut();
	
	string GetUser(); 
	string GetFirstName(); //not sure if you prefer this or getuser
	string GetLastName(); //just let me know what you think. 
	int GetID(); 
	string GetCheckOut(); 
	
	void setFirstName(string firstName); 
	void setLastName(string lastName); 
	void setID(int ID); 
}
#endif /* Users_h */
