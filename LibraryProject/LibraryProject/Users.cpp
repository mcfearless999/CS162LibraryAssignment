//
//  Users.cpp
//  LibraryProject
//
//  Created by Chris M on 5/17/16.
//  Copyright © 2016 Chris McPherson. All rights reserved.
//

#include "Users.h"


char Users::usersFileList_[512] = "";
string Users::currentUser_ = "";

Users::Users()
{
	firstName_ = ""; 
	lastName_ = ""; 
 	email_ = ""; 
        ID_ = "";  
	
	for (int idx = 0; idx <4; idx++)
	{
	checkOut[idx]=0;
	} 
}

Users::Users(string firstName_, string lastName_, string ID_, string checkOut_)
{
}
string Users::GetUserName()
{
    return userName_;
}
//Users::Users(string firstName_, string lastName_, string ID_, string checkOut_)
//{
//}
string Users::GetFirstName()
{
	return firstName_; 
}
string Users::GetLastName()
{
	return lastName_; 
}
string Users::GetID()
{
	return ID_; 
} 
string Users::GetEmail()
{
	return email_; 
}
string Users::GetCheckOut()
{
	return checkOut_; 
}
void Users::setFirstName(string fName)
{
	firstName_ = fName; 
}
void Users::setLastName(string lName)
{
	lastName_ = lName; 
}
void Users::setID(string id)
{
	ID_ = id; 
}
void Users::setEmail(string email)
{
	email_ = email; 
}



void Users::CheckOutBooks(string checkOutString)
{
    checkOut_ = checkOutString;
}


























 
			
