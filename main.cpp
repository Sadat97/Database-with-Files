#include <iostream>
#include <fstream>
#include <cstring>
#include <strstream>
#include "Books.h"
#include "Authors.h"

using namespace std;


bool QueryChecker(string query){
 return (((query.find("select ") != string::npos )&&( query.find("from ")!= string::npos)) && (query.find("select ") < query.find("from ")));
}

string * AnalyizeQuery(string query){

    string line = query;
    string * arr = new string [3];
    int i = 0;
    stringstream ssin(line);
    string temp;
    bool thereisAnd = false;
    while (ssin.good() && i < 3){
        ssin >> temp;
        if (temp == "select" || temp == "from" )
            continue;
        if (temp == "and")
        {
            thereisAnd = true;
            continue;
        }

        arr[i] = temp;
        if (thereisAnd)
            break;
        ++i;
    }
//    for(i = 0; i < 4; i++){
//        cout<< endl << arr[i] ;
//    }
    return   arr;
}

string * WhereCondition(string query){

    string * wherecond = new string [2];
    int position = query.find("where ");

    if (position == string::npos){
            wherecond[0] = "NULL";
            return  wherecond ;
    }

    string temp = query.substr(position + 6);
    string right , left ;
    right = temp.substr(temp.find("=")+1);
    wherecond[1] = right;
    left  = temp.substr(0, temp.find("="));
    wherecond[0] = left;
    //cout << "this is left " << left << " And this is Right " << right << endl;
    return  wherecond;
}

void Queryexcuter(string * firstpart[],string * secondpart[]){


}

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
string query ;
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
            case 9:
            string * queryselectpart= new string [3] , * wherecond = new string[2];
            cin.ignore();
            cout << "Please Write Your query : \n" ;
            getline(cin,query);
            if (QueryChecker(query)){
                queryselectpart = AnalyizeQuery(query);
                wherecond = WhereCondition(query);
                QueryExcuter(queryselectpart,wherecond);
            }
            break;

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
