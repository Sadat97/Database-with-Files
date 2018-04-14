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


void Authors:: ReadAuthor()
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

        cout <<"\nAuthor ID: "<< A.Author_ID << endl;
        cout <<"Author Name: "<< A.Author_Name << endl;
        cout <<"Author Address: "<< A.Author_Address<< endl;
        cout <<"Author Mobile: " <<A.Author_Mobile<< endl;

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
            if (atoi(sindex[j].SK)>atoi(sindex[j + 1].SK))
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
        return middle;
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
    else if (atoi(sindex[middle].SK)<atoi(key))
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


Authors::~Authors()
{
}
