
#include <iostream>
#include <string>


using namespace std;

class Book
{
private:
    string title_;
    string author_;
    string publisher_;
    int idNum_;
    string checkedOut_;
    
public:
    static string bookFileList_;
    static string currentBook_;
    
    Book();
    Book(string title, string auth, string pub, string id, string checkout);
    void SetTitle(string title);
    void SetAuth(string auth);
    void SetPub(string pub);
    void SetID(int idNum);
    void SetID(string idNum);
    void SetCheckout(string userCheck);
    
    string GetTitle();
    string GetAuth();
    string GetPub();
    int GetID();
    string GetCheckOut();
    
    void PrintBook();
    void AppendToBookFile();
    
};