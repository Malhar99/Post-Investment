#include<iostream>
#include<fstream>
#include<Windows.h>
#include<string>
#include<conio.h>
#include<stdlib.h>
using namespace std;
void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
class Post
{
    char name[30];///enter the name
    char no_name[30];/// enter the name of nomination
    char toi[6]; ///type of investments
    long long int cif; ///enter the CIF no.
    int pno; ///enter the passbook no.
    int dd,mm,yy; ///enter the date of purchase
    int d,m,y; ///enter the date of maturity
    long double amt;/// enter the amount
    double com; ///enter the commission
    int tds; ///enter  TDS
    double ncom; ///enter the net commission
    char poname[30]; ///enter the name of post office
public:
    Post()
    {
        strcpy(name,"no name");///enter the name
        strcpy(no_name,"no name");/// enter the name of nomination
        strcpy(toi,"no name"); ///type of investments
        cif=0; ///enter the CIF no.
        pno=0; ///enter the passbook no.
        dd=0,mm=0,yy=0; ///enter the date of purchase
        d=0,m=0,y=0; ///enter the date of maturity
        amt=0;/// enter the amount
        com=0; ///enter the commission
        tds=0; ///enter  TDS
        ncom=0; ///enter the net commission
        strcpy(poname,"no name"); ///enter the name of post office
    }
    void getData();
    void displayData();
    void storeData();
    void displayAllData();
    void searchDate(char *);
    void updateData(char *);
    void deleteData(char *);
};
void Post :: getData()
{
    cout<<"\nEnter name of candidate="<<flush;
    cin>>name;
    cout<<"Enter name of nomination ="<<flush;
    cin>>no_name;
    cout<<"Enter the type of investment (NSC,KVP,MIS,TD-1,TD-2,TD-3,TD-5)="<<flush;
    cin>>toi;
    cout<<"Enter the CIF (costumer information file number no) ="<<flush;
    cin>>cif;
    cout<<"Enter the passbook no ="<<flush;
    cin>>pno;
    cout<<"Enter the date of purchase (dd/mm/yyyy) ="<<flush;
    cin>>dd>>mm>>yy;
    cout<<"Enter the date of maturity (dd/mm/yyyy) ="<<flush;
    cin>>d>>m>>y;
    cout<<"Enter the amount ="<<flush;
    cin>>amt;
    com=amt*0.005;
    cout<<"The commission ="<<com<<endl;
    tds=com*0.05+1;
    cout<<"The TDS (Tax Deducted at Source) ="<<tds<<endl;
    ncom=com-tds;
    cout<<"The  net commission ="<<ncom<<endl;
    cout<<"Enter the PostOffice name ="<<flush;
    cin>>poname;
}
void Post :: displayData()
{
    cout<<"The entered details are as follows: \n\n"<<endl;
    cout<<"The name of candidate ="<<name<<endl;
    cout<<"The name of nomination ="<<no_name<<endl;
    cout<<"The type of investment (NSC,KVP,MIS,TD-1,TD-2,TD-3,TD-5)="<<toi<<endl;
    cout<<"The CIF (costumer information file number number) ="<<cif<<endl;
    cout<<"The passbook no ="<<pno<<endl;
    cout<<"The date of purchase ="<<dd<<"/"<<mm<<"/"<<yy<<endl;
    cout<<"The date of maturity  ="<<d<<"/"<<m<<"/"<<y<<endl;
    cout<<"The amount = "<<amt<<endl;
    cout<<"The commission ="<<com<<endl;
    cout<<"The TDS (Tax Deducted at Source)="<<tds<<endl;
    cout<<"The net commission ="<<ncom<<endl;
    cout<<"The PostOffice ="<<poname<<endl;
}
void Post :: storeData() ///function to store data in the file
{
    ofstream fp;
    fp.open("post.dat",ios::binary|ios::app);
    fp.write((char*)this,sizeof(*this));
    fp.close();
}
void Post :: displayAllData()
{
    ifstream fp;
    fp.open("post.dat",ios::binary|ios::in);
    if(!fp)
    {
        cout<<"File Not Found...";
    }
    else
    {
        fp.read((char*)this,sizeof(*this)); ///here *this represents the size of caller object
        while(!fp.eof())
        {
        displayData();
        cout<<endl;
        fp.read((char*)this,sizeof(*this));
        }
    }
    fp.close();
}
void Post :: searchDate(char *mo) /// function to search data from the file
{
    int c=0;
    ifstream fp;
    fp.open("post.dat",ios::binary|ios::in);
    if(!fp)
    {
        cout<<"File Not Found...";
    }
    else
    {
        fp.read((char*)this,sizeof(*this));
        while(!fp.eof())
        {
            if(!strcmp(mo,name))
            {
                displayData();
                c++;
            }
            fp.read((char*)this,sizeof(*this));
        }
        if(c==0)
        {
            cout<<"Record Not found... ";
        }

    }
    fp.close();
}
void Post :: deleteData(char *t)
{
    ifstream fin;
    ofstream fout;
    fin.open("Post.dat",ios::in |ios::binary);
    if(!fin)
    {
        cout<<"File Not Found...";
    }
    else
    {
        fout.open("tempfile.dat", ios::out | ios::binary);
        fin.read((char*)this,sizeof(*this));
        while(!fin.eof())
        {
            if(strcmp(name,t))
            {
                fout.write((char*)this,sizeof(*this));
            }
            fin.read((char*)this,sizeof(*this));
        }
        fin.close();
        fout.close();
        remove("Post.dat");
        rename("tempfile.dat","Post.dat");
        cout<<"record deleted";
    }
}
void Post :: updateData(char *t)
{
    fstream fp;
    fp.open("Post.dat",ios::in | ios::out | ios::ate | ios::binary);
    if(!fp)
    {
        cout<<"File Not Found...";
    }
    fp.seekg(0);
    fp.read((char*)this,sizeof(*this));
    while(!fp.eof())
    {
        if(!strcmp(t,name))
        {
            getData();
            fp.seekp(fp.tellp()-sizeof(*this));
            fp.write((char*)this,sizeof(*this));
        }
        fp.read((char*)this,sizeof(*this));
    }
}
main()
{
     Post p;
     int a;
     while(1)
     {
     system("cls");
     system("color F0");
     gotoxy(30,6);
     cout<<"POST INVESTMENTS";
     gotoxy(30,7);
     cout<<"________________";
     gotoxy(30,10);
     cout<<"1 - Create New Entry";
     gotoxy(30,11);
     cout<<"2 - Display all Entry";
     gotoxy(30,12);
     cout<<"3 - Search Old Entry";
     gotoxy(30,13);
     cout<<"4 - Update Entry";
     gotoxy(30,14);
     cout<<"5 - Delete Entry";
     gotoxy(30,15);
     cout<<"6 - Exit";
     cout<<"\n\nEnter your option here by typing the numeric code:";
     cin>>a;
        switch(a)  /// switch case
     {
        case 1:///enter the data
                {
                    p.getData();
                    p.storeData();
                    getch();
                }
                break;
        case 2:///display all data
                {
                    system("color 70");
                    p.displayAllData();
                    getch();
                    break;
                }
        case 3: ///search data
                {
                    system("color 70");
                    char a[30];
                    cout<<"Enter the name to search :";
                    cin>>a;
                    p.searchDate(a);
                    getch();
                    break;
                }
        case 4: ///update data
                {
                system("color 70");
                char a[30];
                cout<<"Enter the name to update :";
                cin>>a;
                p.updateData(a);
                getch();
                break;
                }
        case 5:///delete data
            {
                system("color 7C");
                char a[30];
                cout<<"Enter the name to delete :";
                cin>>a;
                p.deleteData(a);
                getch();
                break;
            }
        case 6:///exit
                system("color 7C");
                cout<<"successfully exited \n";
                cout<<"Press any key to exit.";
                getch();
                exit(0);
                break;
        default:
                gotoxy(29,16);
                cout<<"Please Enter valid number !";
                break;
     }
     getch();
   }
}
