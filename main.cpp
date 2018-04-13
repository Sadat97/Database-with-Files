#include <iostream>
#include <fstream>
#include <cstring>
#include <strstream>
#include "Books.h"
#include "Authors.h"



/* to work on codeblocks enable this
#include "../Books.h"
#include "Authors.h"
*/
using namespace std;

int main()
{
    Books Bobj;
    Authors Aobj;
    int choice;
    Bobj.LoadIndex();
    Aobj.LoadIndex();

    //Test Char obj
    char test[7] = "123456";

    cout<<"Enter Your Choice\n(1) Add New Book\n(2) Add New Author\n(3) Delete Book(ID)\n(4) Delete Author(ID)\n"
        <<"(5) Print Book(ID)\n(6) Print Book(Author_ID)\n(7) Print Author (ID)\n(8) Print Author (Author_Name)\n"
        <<"(9) Write a Query\n(10) EXIT\n";
    cin>>choice;
    while (choice!=10)
    {
        switch (choice)
        {
            case 1: cin.ignore();Bobj.AddBook();break;
            case 2: cin.ignore();Aobj.AddAuthor();break;
            case 3: cin.ignore();cout << Bobj.PIndexBinarySearch(test);
        }

        cout<<"Enter Your Choice\n(1) Add New Book\n(2) Add New Author\n(3) Delete Book(ID)\n(4) Delete Author(ID)\n"
        <<"(5) Print Book(ID)\n(6) Print Book(Author_ID)\n(7) Print Author (ID)\n(8) Print Author (Author_Name)\n"
        <<"(9) Write a Query\n(10) EXIT\n";
        cin>>choice;
    }
    cout<<"Author Data:\n";
    Aobj.ReadAuthor();
    cout<<"\nBook Data:\n";
    Bobj.ReadBook();

    Bobj.savePIndex();
    Aobj.savePIndex();

    cout<<"\nAuthor Index Data:\n";
    Aobj.ReadPIndex();
    cout<<"\nBook Index Data\n";
    Bobj.ReadPIndex();

    return 0;
}
