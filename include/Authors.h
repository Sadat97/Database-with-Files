#ifndef AUTHORS_H
#define AUTHORS_H


#include <bits/stdc++.h>
#include <strstream>
using namespace std;

class Authors
{

    private:
        int next,snext;
        const int MaxBuffS = 200;
        struct Author
        {
                char Author_ID [30];    //primary key
                char Author_Name [50];  //sec. key
                char Author_Address[50];
                char Author_Mobile [11];
        };
        struct PIndex
        {
            char PK [30];
            int offset;
        };
        const static int indexSize = 100;
        PIndex index[indexSize];

        struct SIndex
        {
            char SK[50];
            char PK [30];
            int offset;

        };
        SIndex sindex[indexSize];

    public:
        Authors();
        ~Authors();
        void AddAuthor();
        void DeleteAuthor(char[]);
        void ReadAuthor(int,Author&);
        int ReadBookByOffset(int offset);
        void ReadAuthor(int,Author&,int);
        void ReadAuthor(int att );
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
        void PrintAuthorAID();
        void PrintAuthorAName();
        void Queryexcuter(string * part1 , string * part2,int index);
};

#endif // AUTHORS_H
