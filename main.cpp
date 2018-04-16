#include <iostream>
#include <fstream>
#include <cstring>
#include <strstream>
#include "Books.h"
#include "Authors.h"

using namespace std;

int main()
{
    Books Bobj;
    Authors Aobj;
    int choice;
    Bobj.LoadIndex();
    Aobj.LoadIndex();

    Bobj.savePIndex();
    Bobj.saveSIndex();
    Aobj.savePIndex();
    Aobj.saveSIndex();

    cout<<"Enter Your Choice\n(1) Add New Book\n(2) Add New Author\n(3) Delete Book(ID)\n(4) Delete Author(ID)\n"
        <<"(5) Print Book(ID)\n(6) Print Book(Author_ID)\n(7) Print Author (ID)\n(8) Print Author (Author_Name)\n"
        <<"(9) Write a Query\n(10) EXIT\n";
    cin>>choice;
    char ID[30];
    while (choice!=10)
    {
        switch (choice)
        {
            case 1: cin.ignore();Bobj.AddBook();Bobj.LoadIndex();Bobj.savePIndex();Bobj.saveSIndex();break;
            case 2: cin.ignore();Aobj.AddAuthor();Aobj.LoadIndex();Aobj.savePIndex();Aobj.saveSIndex();break;
            case 3: cin.ignore();cout<<"Please Enter the ID \n";cin>>ID;Bobj.DeleteBook(ID);break;
            case 4: cin.ignore();cout<<"Please Enter the ID \n";cin>>ID;Aobj.DeleteAuthor(ID);break;
            case 5: cin.ignore();Bobj.PrintBookBID();break;
            case 6: cin.ignore();Bobj.PrintBookAID();break;
            case 7: cin.ignore();Aobj.PrintAuthorAID();break;
            case 8: cin.ignore();Aobj.PrintAuthorAName();break;
            case 9: /***/ break;

        }

        cout<<"Enter Your Choice\n(1) Add New Book\n(2) Add New Author\n(3) Delete Book(ID)\n(4) Delete Author(ID)\n"
        <<"(5) Print Book(ID)\n(6) Print Book(Author_ID)\n(7) Print Author (ID)\n(8) Print Author (Author_Name)\n"
        <<"(9) Write a Query\n(10) EXIT\n";
        cin>>choice;
    }
    /*
    cout<<"Author Data:\n";
    Aobj.ReadAuthor();
    cout<<"\nBook Data:\n";
    Bobj.ReadBook();
*/
/*
    Bobj.savePIndex();
    Bobj.saveSIndex();
    Aobj.savePIndex();
    Aobj.saveSIndex();
*/
/*
    cout<<"\nAuthor Index Data:\n";
    Aobj.ReadPIndex();
    cout<<"\nBook Index Data\n";
    Bobj.ReadPIndex();
*/
    return 0;
}
