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
    if (query.find("and ") == string::npos)
      arr[2]="";

    stringstream ssin(line);
    string temp;
    bool thereisAnd = false;
    while (ssin.good() && i < 2){
        ssin >> temp;
        if (temp == "select" || temp == "from" )
            continue;
        if (temp == "where ")
        {
            break;
        }

        arr[i] = temp;
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
    right = temp.substr(temp.find("=")+2);
    wherecond[1] = right;
    left  = temp.substr(0, temp.find("=") -1);
    wherecond[0] = left;
    //cout << "this is left " << left << " And this is Right " << right << endl;
    return  wherecond;
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
                string *firstpart = queryselectpart;
                string *secondpart = wherecond;
             int index = 1;
             if ((firstpart[2] == "")){
                 if (secondpart[0] != "NULL") {
                    if (firstpart[1] == "Books"){
                            if (secondpart[0] == "Author_ID")
                                    index = 2;
                    Bobj.Queryexcuter(queryselectpart,wherecond,index);
                    } else if (firstpart[1] == "Authors") {

                     if (secondpart[0] == "Author_ID")
                                    index = 1;
                     else if (secondpart[0] == "Author_name")
                                    index = 2;

                    Aobj.Queryexcuter(queryselectpart,wherecond,index);
                    }
                 }else{
                     int attribute;
                     if (firstpart[0]=="all"){attribute = 0;}

                     if (firstpart[1] == "books"){
                            if (firstpart[0]=="all")            {attribute = 0;}
                            else if (firstpart[0]=="Book_ID")   {attribute = 1;}
                            else if (firstpart[0]=="Author_ID") {attribute = 2;}
                            else if (firstpart[0]=="Book_Title"){attribute = 3;}
                            else if (firstpart[0]=="Book_Price"){attribute = 4;}
                            else {cout <<"wrong attribue !";break;}
                            Bobj.ReadBook(attribute);

                     }
                     else if  (firstpart[1] == "authors"){
                            if      (firstpart[0]=="all")            {attribute = 0;}
                            else if (firstpart[0]=="Author_ID")      {attribute = 1;}
                            else if (firstpart[0]=="Author_Name")    {attribute = 2;}
                            else if (firstpart[0]=="Author_Address") {attribute = 3;}
                            else if (firstpart[0]=="Author_Mobile")  {attribute = 4;}
                            else {cout <<"wrong attribue !";break;}
                            Aobj.ReadAuthor(attribute);

                     }
                     else {cout << "Not A Table !"<<endl;}
                 }
             } else {int tempA = Aobj.ReadBookByOffset(0);
                   int tempB = Bobj.ReadBookByOffset(0);
                    while ((tempA != -1) && (tempB != -1)){
                              tempA = Aobj.ReadBookByOffset(tempA);
                              tempB = Bobj.ReadBookByOffset(tempB);
                    }


             }


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
