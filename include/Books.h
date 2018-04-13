#ifndef BOOKS_H
#define BOOKS_H

#include <bits/stdc++.h>
#include <strstream>

using namespace std;

class Books
{
    public:
        Books();
        ~Books();
        void AddBook();
        void ReadBook();
        void DeleteBook(char ID []);
        void sortPIndex();
        int IndexBinarySearch(char[]);
        void constructPIndex();
        void savePIndex();
        void LoadIndex();
        bool exists(char [20]);
        void ReadPIndex();

    private:
        int next;
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




};

#endif // BOOKS_H
