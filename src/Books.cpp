#include "Books.h"
#include <vector>
Books::Books()
{
//    char datafile [50]="Books.txt";
//    char Pindexfile [50]="BooksPIndex.txt";
//    char Sindexfile [50]="BooksSIndex.txt";
//    char LabelIDList [50]="BooksList.txt";
}


void Books:: AddBook()
{
    ofstream BOfile("Books.txt",ios::app);
    Book B;
    cout << "\nThe ID of the Book: ";
    cin.getline(B.Book_ID, 12);
    cout << "\nEnter the ID of the Author: ";
    cin.getline(B.Author_ID, 29);
    cout << "\nEnter The Book Title: ";
    cin.getline(B.Book_Title, 49);
    cout << "\nEnter the Book's price: ";
    cin>>B.Book_Price;

    char Buffer [MaxBuffS];

    strcpy(Buffer,B.Book_ID);strcat(Buffer,"|");
    strcat(Buffer,B.Author_ID);strcat(Buffer,"|");
    strcat(Buffer,B.Book_Title);strcat(Buffer,"|");
    strcat(Buffer,B.Book_Price);strcat(Buffer,"|");

    short size = strlen(Buffer);
    int address = BOfile.tellp();

    BOfile.write((char*)&size,sizeof(size));
    BOfile.write(Buffer,size);

    PIndex temp;
    strcpy(temp.PK, B.Book_ID);
    temp.offset = address;
    index[next] = temp;
    next++;
    sortPIndex();

    SIndex Stemp;
    strcpy(Stemp.SK,B.Author_ID);
    strcpy(Stemp.PK,B.Book_ID);
    sindex[snext] = Stemp;
    snext++;
    sortSIndex();

    BOfile.close();
}


void Books:: ReadBook()
{
    ifstream BIfile("Books.txt",ios::app);
    Book b;
    BIfile.seekg(0,ios::beg);
    while(!BIfile.eof())
    {
        short length;
        BIfile.read((char*)&length,sizeof(length));
        char* buffer = new char[length];
        BIfile.read(buffer, length);

        if(BIfile.eof())
            break;

        istrstream strbuf(buffer);

        strbuf.getline(b.Book_ID, 12, '|');
        strbuf.getline(b.Author_ID, 29, '|');
        strbuf.getline(b.Book_Title, 49, '|');
        strbuf.getline(b.Book_Price,49,'|');

        cout <<"\nBook ID: "<< b.Book_ID << endl;
        cout <<"Author ID: "<< b.Author_ID << endl;
        cout <<"Book Title: "<< b.Book_Title<< endl;
        cout <<"Book Price: "<< b.Book_Price<< endl;
        delete buffer;
    }
    BIfile.close();
}

void Books::sortPIndex() //bubble sort
{
    int len = next - 1;
    PIndex temp;
    for (int i = 0; i<len; i++)
        for (int j = 0; j<len - i; j++)
        {
            if (atoi(index[j].PK)>atoi(index[j + 1].PK))
            {
                temp = index[j];
                index[j] = index[j + 1];
                index[j + 1] = temp;
            }
        }
}

void Books::sortSIndex() //bubble sort
{
    int len = snext - 1;
    SIndex temp;
    for (int i = 0; i<len; i++)
        for (int j = 0; j<len - i; j++)
        {
            if (atoi(sindex[j].SK)>atoi(sindex[j + 1].SK))
            {
                temp = sindex[j];
                sindex[j] = sindex[j + 1];
                sindex[j + 1] = temp;
            }
        }
}


int Books:: PIndexBinarySearch(char key[])
{
    int size = next;
    int low = 0, high = size - 1;
    while (low <= high)
    {
    int middle = (low + high) / 2;
    if (strcmp(index[middle].PK, key) == 0)
        return middle;
    else if (atoi(index[middle].PK)<atoi(key))
        low = middle + 1;
    else
        high = middle - 1;
    }
    return -1;
}

int Books:: SIndexBinarySearch(char key[])
{
    int size = snext;
    int low = 0, high = size - 1;
    while (low <= high)
    {
    int middle = (low + high) / 2;
    if (strcmp(sindex[middle].SK, key) == 0)
        return middle;
    else if (atoi(sindex[middle].SK)<atoi(key))
        low = middle + 1;
    else
        high = middle - 1;
    }
    return -1;
}


void Books::constructPIndex()
{
    ifstream fin("Books.txt");  		next = 0;
    while(!fin.eof())
        {
            PIndex temp;
            int offset = fin.tellg();
            short len;
            fin.read((char*)&len, sizeof(len));

            if (fin.eof())
                break;

            char *buffer = new char [len];
            fin.read(buffer, len);
            if (buffer[0] == '*')
                continue;
            istringstream strbuf(buffer);
            strbuf.getline(temp.PK,12, '|');/****/
            temp.offset = offset;
            index[next] = temp;
            next++;
        }
        fin.close();
        sortPIndex();
}

void Books::constructSIndex()
{
    ifstream fin("Books.txt");  		snext = 0;
    while(!fin.eof())
        {
            SIndex temp;
            short len;
            fin.read((char*)&len, sizeof(len));

            if (fin.eof())
                break;

            char *buffer = new char [len];
            fin.read(buffer, len);
            if (buffer[0] == '*')
                continue;
            istringstream strbuf(buffer);
            strbuf.getline(temp.PK,12, '|');
            strbuf.getline(temp.SK,29, '|');
            sindex[snext] = temp;
            snext++;
        }
        fin.close();
        sortSIndex();
}


void Books::savePIndex()
{
    ofstream fout("BooksPIndex.txt", ios::trunc);
    for (int i = 0; i<next; i++)
    {
        PIndex temp = index[i];
        fout.write((char*)&temp, sizeof(temp));
    }
    fout.close();
}


void Books::saveSIndex()
{
    ofstream sout("BooksSIndex.txt", ios::trunc);
    ofstream lout("BooksList.txt", ios::trunc);


    vector<string>SKT;
    vector<string>PKT;
    //vector<int>Sptr;
    vector<int>Lptr;

    for (int i=0;i<snext;i++)
    {
        if (strcmp(sindex[i].SK,sindex[i+1].SK) == 0)
        {
            SKT.push_back(sindex[i].SK);
            while(strcmp(sindex[i].SK,sindex[i+1].SK) == 0)
            {
                i++;
            }
        }
        else
            SKT.push_back(sindex[i].SK);
    }

    for (int i=0;i<snext;i++)
    {
        if (strcmp(sindex[i].SK,sindex[i+1].SK) == 0)
        {
            while (strcmp(sindex[i].SK,sindex[i+1].SK) == 0)
            {
                PKT.push_back(sindex[i].PK);
                Lptr.push_back(i+1);
                i++;
            }
            PKT.push_back(sindex[i].PK);
            Lptr.push_back(-1);
        }
        else
        {
            PKT.push_back(sindex[i].PK);
            Lptr.push_back(-1);

        }

    }

    for (int i=0;i<SKT.size();i++)
        sout<<SKT[i]<<" "<<i<<endl;
    for (int i=0;i<PKT.size();i++)
        lout<<PKT[i]<<" "<<Lptr[i]<<endl;


    lout.close();
    sout.close();
}


void Books::LoadIndex()
{
    if(!exists("Books.txt"))
    {
        next = 0;
        snext = 0;
    }
    else
    {
        constructPIndex();
        constructSIndex();
    }
}


bool Books :: exists(char file [50])
{
    ifstream f(file);
    if (f.fail())
        return false;

    else
    {
        f.close();
        return true;
    }
}

void Books::ReadPIndex()
{
    ifstream fin("BooksPIndex.txt");
    while (!fin.eof())
    {
        PIndex temp;
        fin.read((char*)&temp, sizeof(temp));
        if (fin.eof())
            break;
        cout<<temp.PK<<"  "<<temp.offset<<endl;
    }
    fin.close();
}

Books::~Books()
{
}
