#ifndef AUTHORS_H
#define AUTHORS_H


#include <bits/stdc++.h>
#include <strstream>
using namespace std;

class Authors
{
    public:
        Authors();
        ~Authors();
        void AddAuthor();
        void ReadAuthor();
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


};

#endif // AUTHORS_H
