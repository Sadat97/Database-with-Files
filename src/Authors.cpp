#include "Authors.h"

Authors::Authors()
{
}

void Authors:: AddAuthor()
{
    ofstream AOfile ("Authors.txt",ios::app);
    Author A;
    cout << "\nThe ID of the Author: ";
	cin.getline(A.Author_ID, 29);
	cout << "\nEnter the Name of the Author: ";
	cin.getline(A.Author_Name, 49);
	cout << "\nEnter The Address of the Author: ";
	cin.getline(A.Author_Address, 49);
	cout << "\nEnter the Author's Mobile: ";
	cin>>A.Author_Mobile;

    char Buffer [MaxBuffS];

    strcpy(Buffer,A.Author_ID);strcat(Buffer,"|");
    strcat(Buffer,A.Author_Name);strcat(Buffer,"|");
    strcat(Buffer,A.Author_Address);strcat(Buffer,"|");
    strcat(Buffer,A.Author_Mobile);strcat(Buffer,"|");

    short size = strlen(Buffer);
    int address = AOfile.tellp();

    AOfile.write((char*)&size,sizeof(size));
    AOfile.write(Buffer,size);

    PIndex temp;
    strcpy(temp.PK, A.Author_ID);
    temp.offset = address;
    index[next] = temp;
    next++;
    sortPIndex();

    SIndex Stemp;
    strcpy(Stemp.SK,A.Author_Name);
    strcpy(Stemp.PK,A.Author_ID);
    sindex[snext] = Stemp;
    snext++;
    sortSIndex();

    AOfile.close();
}

void Authors::DeleteAuthor(char ID []){
    int offset = PIndexBinarySearch(ID);
    if (offset != -1){
      fstream bookFile ("Authors.txt",ios::in | ios::out);
      bookFile.seekp(offset +2,ios::beg);
      bookFile << "*";
      bookFile.close();
      LoadIndex();

    } else {
        cout << "This Author is not Available ! \n";
    }


}



void Authors:: ReadAuthor(int offset,Author& A)
{
    ifstream AIfile("Authors.txt");

    AIfile.seekg(offset,ios::beg);

    short length;
    AIfile.read((char*)&length,sizeof(length));
    char* buffer = new char[length];
    AIfile.read(buffer, length);

    istrstream strbuf(buffer);
    if (A.Author_ID[0] != '*')
    {
        strbuf.getline(A.Author_ID, 29, '|');
        strbuf.getline(A.Author_Name, 49, '|');
        strbuf.getline(A.Author_Address, 49, '|');
        strbuf.getline(A.Author_Mobile,10,'|');
    }
    delete buffer;
    AIfile.close();
}


void Authors:: ReadAuthor(int offset,Author& A,int dummy)
{
    ifstream AIfile("Authors.txt");

    AIfile.seekg(offset,ios::beg);

    short length;
    AIfile.read((char*)&length,sizeof(length));
    char* buffer = new char[length];
    AIfile.read(buffer, length);

    istrstream strbuf(buffer);

    strbuf.getline(A.Author_ID, 29, '|');
    strbuf.getline(A.Author_Name, 49, '|');
    strbuf.getline(A.Author_Address, 49, '|');
    strbuf.getline(A.Author_Mobile,10,'|');


    delete buffer;
    AIfile.close();
}


void Authors:: ReadAuthor(int offset,Author& A,int dummy)
{
    ifstream AIfile("Authors.txt");

    AIfile.seekg(offset,ios::beg);

    short length;
    AIfile.read((char*)&length,sizeof(length));
    char* buffer = new char[length];
    AIfile.read(buffer, length);

    istrstream strbuf(buffer);

    strbuf.getline(A.Author_ID, 29, '|');
    strbuf.getline(A.Author_Name, 49, '|');
    strbuf.getline(A.Author_Address, 49, '|');
    strbuf.getline(A.Author_Mobile,10,'|');

    cout <<"\nAuthor ID: "<< A.Author_ID << endl;
    cout <<"Author Name: "<< A.Author_Name << endl;
    cout <<"Author Address: "<< A.Author_Address<< endl;
    cout <<"Author Mobile: " <<A.Author_Mobile<< endl<< endl;

    if (A.Author_ID[0] != '*')
    {
        cout <<"\nAuthor ID: "<< A.Author_ID << endl;
        cout <<"Author Name: "<< A.Author_Name << endl;
        cout <<"Author Address: "<< A.Author_Address<< endl;
        cout <<"Author Mobile: " <<A.Author_Mobile<< endl<< endl;
    }
    delete buffer;
    AIfile.close();
}


int Authors:: ReadBookByOffset(int offset)
{   Author A;
   ifstream BIfile("Authors.txt");
    BIfile.seekg(0,ios::end);
    int end_of_file = BIfile.tellg();

    BIfile.seekg(offset,ios::beg);

    short length;
    BIfile.read((char*)&length,sizeof(length));
    char* buffer = new char[length];
    BIfile.read(buffer, length);

    istrstream strbuf(buffer);

    strbuf.getline(A.Author_ID, 29, '|');
    strbuf.getline(A.Author_Name, 49, '|');
    strbuf.getline(A.Author_Address, 49, '|');
    strbuf.getline(A.Author_Mobile,10,'|');

    
    if (A.Author_ID[0] != '*')
    {
        cout <<"\nAuthor ID: "<< A.Author_ID << endl;
        cout <<"Author Name: "<< A.Author_Name << endl;
        cout <<"Author Address: "<< A.Author_Address<< endl;
        cout <<"Author Mobile: " <<A.Author_Mobile<< endl<< endl;
    }
    delete buffer;
    int current = BIfile.tellg();
    BIfile.close();
    if (current == end_of_file)
        return -1 ;

    return current;
}

void Authors:: ReadAuthor(int att = 0)
{
    ifstream AIfile("Authors.txt");
    Author A;
    AIfile.seekg(0,ios::beg);
    while (!AIfile.eof())
    {

        short length;
        AIfile.read((char*)&length,sizeof(length));
        char* buffer = new char[length];
        AIfile.read(buffer, length);

        if(AIfile.eof())
            break;
        istrstream strbuf(buffer);

        strbuf.getline(A.Author_ID, 29, '|');
        strbuf.getline(A.Author_Name, 49, '|');
        strbuf.getline(A.Author_Address, 49, '|');
        strbuf.getline(A.Author_Mobile,10,'|');

        if (A.Author_ID[0] == '*')
            continue;
if (att == 0){
        cout <<"\nAuthor ID: "<< A.Author_ID << endl;
        cout <<"Author Name: "<< A.Author_Name << endl;
        cout <<"Author Address: "<< A.Author_Address<< endl;
        cout <<"Author Mobile: " <<A.Author_Mobile<< endl<< endl;
        } else if (att == 1)
    cout <<"\nAuthor ID: "<< A.Author_ID << endl;
        else if (att == 2)
    cout <<"Author Name: "<< A.Author_Name << endl;
        else if (att == 3)
    cout <<"Author Address: "<< A.Author_Address<< endl;
        else if (att == 4)
    cout <<"Author Mobile: " <<A.Author_Mobile<< endl<< endl;
        delete buffer;
    }
    AIfile.close();
}


void Authors::sortPIndex() //bubble sort
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


void Authors::sortSIndex() //bubble sort
{
    int len = snext - 1;
    SIndex temp;
    for (int i = 0; i<len; i++)
        for (int j = 0; j<len - i; j++)
        {
            if (strcmp(sindex[j].SK,sindex[j + 1].SK) > 0)
            {
                temp = sindex[j];
                sindex[j] = sindex[j + 1];
                sindex[j + 1] = temp;
            }
        }
}


int Authors:: PIndexBinarySearch(char key[])
{
    int size = next;
    int low = 0, high = size - 1;
    while (low <= high)
    {
    int middle = (low + high) / 2;
    if (strcmp(index[middle].PK, key) == 0)
        return index[middle].offset;
    else if (atoi(index[middle].PK)<atoi(key))
        low = middle + 1;
    else
        high = middle - 1;
    }
    return -1;
}


int Authors:: SIndexBinarySearch(char key[])
{
    int size = snext;
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int middle = (low + high) / 2;
        if (strcmp(sindex[middle].SK, key) == 0)
            return middle;
        else if (strcmp(sindex[middle].SK,key)<0)
            low = middle + 1;
        else
            high = middle - 1;
    }
    return -1;
}


void Authors::constructPIndex()
{
    ifstream fin("Authors.txt");  		next = 0;
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
            strbuf.getline(temp.PK,29, '|');
            temp.offset = offset;
            index[next] = temp;
            next++;
        }
        fin.close();
        sortPIndex();
}


void Authors::constructSIndex()
{
    ifstream fin("Authors.txt");  		snext = 0;
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




void Authors::savePIndex()
{
    ofstream fout("AuthorsPIndex.txt", ios::trunc);
    for (int i = 0; i<next; i++)
    {
        PIndex temp = index[i];
        fout.write((char*)&temp, sizeof(temp));
    }
    fout.close();
}



void Authors::saveSIndex()
{
    ofstream sout("AuthorsSIndex.txt", ios::trunc);
    ofstream lout("AuthorsList.txt", ios::trunc);

    vector<string>SKT;
    vector<string>PKT;
    vector<int>Lptr;
    vector<int>ptr;

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

    for (int i=0;i<PKT.size();i++)
    {
        int c = 0;
        while (Lptr[i] != -1)
        {
            if (c == 0)
                ptr.push_back(lout.tellp());
                lout<<PKT[i]<<' '<<Lptr[i]<<endl;
                i++;
                c++;
        }
        if (c > 0 )
        {
            lout<<PKT[i]<<' '<<Lptr[i]<<endl;
            continue;
        }

        else
        {
            ptr.push_back(lout.tellp());
            lout<<PKT[i]<<' '<<Lptr[i]<<endl;
        }
    }
    for (int i=0;i<SKT.size();i++)
    {
        if (SKT.size()<snext)
        {
            for (int x = 0;x<SKT.size();x++)
            {
                strcpy(sindex[x].SK ,SKT[x].c_str());
            }
            snext = SKT.size();
        }
        sindex[i].offset = sout.tellp();
        sout<<SKT[i]<<' '<<ptr[i]<<endl;
    }
    lout.close();
    sout.close();

}




void Authors::ReadPIndex()
{
    ifstream fin("AuthorsPIndex.txt");
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


void Authors::LoadIndex()
{
    if(!exists("Authors.txt"))
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


bool Authors ::exists(char file [20])
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


void Authors::PrintAuthorAID()
{
    cout<<"Enter the Author's ID: ";
    Author A;
    cin.getline(A.Author_ID,29);
    int offset = PIndexBinarySearch(A.Author_ID);
    if (offset == -1)
        cout<<"Invalid ID\n";
    else
    {
        ReadAuthor(offset,A);
    }
}


void Authors::PrintAuthorAName()
{
    cout<<"Enter the Author's Name: ";
    Author A;
    cin.getline(A.Author_Name,49);
    int Idx = SIndexBinarySearch(A.Author_Name);
    if (Idx == -1)
    {
        cout<<"Invalid Name\n\n";
    }

    else
    {
        cout<<Idx<<endl;
        ifstream listfile ("AuthorsSIndex.txt");
        listfile.seekg(sindex[Idx].offset,ios::beg);

        vector<string>PK;
        string t;
        int RRN;

        listfile>>t>>RRN;
        listfile.close();

        listfile.open("AuthorsList.txt");
        listfile.seekg(RRN,ios::beg);

        listfile>>t>>RRN;
        while (RRN != -1)
        {
            PK.push_back(t);
            if (!listfile.eof())
            {
                listfile>>t>>RRN;
            }
        }

        PK.push_back(t);

        for (int i = 0;i<PK.size();i++)
        {
            char arr [PK.size()];
            strcpy(arr,PK[i].c_str());
            int offset = PIndexBinarySearch(arr);
            ReadAuthor(offset,A);
        }

        listfile.close();
    }
}



void Authors::Queryexcuter(string * part1 , string * part2,int index){

char key[part2[1].size()];
    char attr[part1[0].size()];
    strcpy(key,part2[1].c_str());
    strcpy(attr,part1[0].c_str());


if (index == 1){

    int offset = PIndexBinarySearch(key);
     if (offset != -1){
         Author a;
        ReadAuthor(offset,a);
       if (strcmp(attr,"all")==0)
            cout <<"Author_ID: "<<a.Author_ID<<endl<<"Author_Name: "<<a.Author_Name<<endl
            << "Author_Address: " << a.Author_Address<<endl << "Author_Mobile: " <<a.Author_Mobile <<endl;
        else if (strcmp(attr,"Author_Address") == 0)
            cout << "Author_Address: "<< a.Author_Address<<endl;
        else if (strcmp(attr,"Author_Mobile") == 0)
             cout << "Author_Mobile: "<< a.Author_Mobile<<endl;
        else if ((strcmp(attr,"Author_Name") == 0))
              cout << "Author_Name: " << a.Author_Name<<endl;
       else if ((strcmp(attr,"Author_ID") == 0))
              cout << "Author_ID: " << a.Author_ID<<endl;
        else
            cout << "Wrong Query! \n";


    }
}else if (index == 2){
int offset = SIndexBinarySearch(key);
     if (offset != -1){
         Author a;
        ReadAuthor(offset,a);
        if (strcmp(attr,"all")==0)
            cout <<"Author_ID: "<<a.Author_ID<<endl<<"Author_Name: "<<a.Author_Name<<endl
            << "Author_Address: " << a.Author_Address<<endl << "Author_Mobile: " <<a.Author_Mobile <<endl;
        else if (strcmp(attr,"Author_Address") == 0)
            cout << "Author_Address: "<< a.Author_Address<<endl;
        else if (strcmp(attr,"Author_Mobile") == 0)
             cout << "Author_Mobile: "<< a.Author_Mobile<<endl;
        else if ((strcmp(attr,"Author_Name") == 0))
              cout << "Author_Name: " << a.Author_Name<<endl;
       else if ((strcmp(attr,"Author_ID") == 0))
              cout << "Author_ID: " << a.Author_ID<<endl;
        else
            cout << "Wrong Query! \n";
     }
    }
}


Authors::~Authors()
{
}
