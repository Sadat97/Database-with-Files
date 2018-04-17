#ifndef BOOKS_H
#define BOOKS_H

#include <bits/stdc++.h>
#include <strstream>

using namespace std;

class Books
{

    private:
        int next,snext;
        const int MaxBuffS = 200;
        struct Book
        {
            char Book_ID [13];   //primary key
            char Author_ID [30]; //sec. key
            char Book_Title [50];
            char Book_Price [50];
        };
        struct PIndex
        {
            char PK [13];
            int offset;
        };
        const static int indexSize = 100;
        PIndex index[indexSize];

        struct SIndex
        {
            char SK[30];
            char PK [13];
            int offset;

        };
        SIndex sindex[indexSize];

    public:
        Books();
        ~Books();
        void AddBook();
        void DeleteBook(char ID []);
        void ReadBook(int,Book&);
        void ReadBook(int,Book&,int);
        void ReadBook(int att );
        void sortPIndex();
        int PIndexBinarySearch(char[]);
        void constructPIndex();
        void savePIndex();
        void LoadIndex();
        bool exists(char []);
        void ReadPIndex();
        void constructSIndex();
        int SIndexBinarySearch(char[]);
        void sortSIndex();
        void saveSIndex();
        void PrintBookBID();
        void PrintBookAID();
        void PrintBookAID(int,Book &);
        Book PrintBookAID(int);
        void Queryexcuter(string * part1 , string * part2,int index);
        int ReadBookByOffset(int offset);

};

#endif // BOOKS_H
