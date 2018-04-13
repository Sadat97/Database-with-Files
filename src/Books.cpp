#include "Books.h"

Books::Books()
{
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

int Books:: IndexBinarySearch(char key[])
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

void Books::LoadIndex()
{
    if(!exists("Books.txt"))
    {
        next = 0;
    }

    else
        constructPIndex();
}

bool Books ::exists(char file [20])
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
