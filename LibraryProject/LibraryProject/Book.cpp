

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include "Book.h"

using namespace std;

static string bookFileList_;
static string currentBook_;

Book::Book()
{
    title_ = "";
    author_ = "";
    publisher_ ="";
    idNum_ = 0;
    checkedOut_ = "";
}
Book::Book(string title, string auth, string pub, string id, string checkOut)
{
    title_ = title;
    author_ = auth;
    publisher_ =pub;
    idNum_ = stoi(id);
    checkedOut_ = checkOut;
}
void Book::SetTitle(string title)
{
    title_ = title;
}
void Book::SetAuth(string auth)
{
    author_ = auth;
}
void Book::SetPub(string pub)
{
    publisher_ = pub;
}
void Book::SetID(int idNum)
{
    idNum_ = idNum;
}
void Book::SetID(string idNum)
{
    idNum_ = stoi(idNum);
}
void Book::SetCheckout(string userCheck)
{
    checkedOut_ = userCheck;
}

string Book::GetTitle()
{
    return title_;
}
string Book::GetAuth()
{
    return author_;
}
string Book::GetPub()
{
    return publisher_;
}
int Book::GetID()
{
    return idNum_;
}
string Book::GetCheckOut()
{
    return checkedOut_;
}

void Book::PrintBook()
{
    cout << publisher_ << ", " << author_ << ", " <<
    publisher_ << ", " << idNum_ << ", " << checkedOut_ << endl;
}
void Book::AppendToBookFile()
{
    ofstream outStream;
    outStream.open(Book::bookFileList_,ios_base::app);
    outStream << bookFileList_ << endl;
}
