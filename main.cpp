#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct stClient{
    
    string NumberOfAccount;
    string PinCode;
    string Name;
    string Phone;
    double Balance;
    bool Delete=true;
    bool Change=true;
};

vector<string> detleDalim(string FullName,string delim){
    
    short pos=0;
    vector<string> After;
    string Temp;
    while ((pos=FullName.find(delim))!=string::npos) {
        
        Temp=FullName.substr(0,pos);
        
        if (Temp!="") {
            After.push_back(Temp);
        }
        FullName.erase(0,delim.length()+pos);
        Temp="";
    }
    
    if (FullName!="") {
        After.push_back(FullName);
    }
    
    return After;
}

stClient LoadFromVectorFile(string delim,string FulName){
    
    vector<string> Temp=detleDalim(FulName, delim);
    stClient cls;
    
    cls.NumberOfAccount=Temp.at(0);
    cls.PinCode=Temp.at(1);
    cls.Name=Temp.at(2);
    cls.Phone=Temp.at(3);
    cls.Balance=stod(Temp.at(4));
    
    return cls;
}

vector<stClient> LoadFromFile(string Name){
    
    fstream MyFile;
    stClient cls;
    vector<stClient> vcls;
    MyFile.open(Name,ios::in);
    
    while (MyFile.is_open()) {
     
        string Line;
        
        while (getline(MyFile,Line)){
            if (Line!="") {
                cls=LoadFromVectorFile("#//#", Line);
                vcls.push_back(cls);
            }
        }
        MyFile.close();
    }
    return vcls;
}

void HeaderClient(){
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    
    cout<<left<<"| "<<setw(15)<<"Account Number ";
    cout<<left<<"| "<<setw(14)<<"Pin Code ";
    cout<<left<<"| "<<setw(20)<<"Client Name ";
    cout<<left<<"| "<<setw(14)<<"Phone ";
    cout<<left<<"| "<<setw(14)<<"Balance ";
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    
}

void PrintOneClient(stClient cls){
    
    cout<<left<<"| "<<setw(15)<<cls.NumberOfAccount;
    cout<<left<<"| "<<setw(14)<<cls.PinCode;
    cout<<left<<"| "<<setw(20)<<cls.Name;
    cout<<left<<"| "<<setw(14)<<cls.Phone;
    cout<<left<<"| "<<setw(14)<<cls.Balance;

}

void _1_PrintAllClient(){
    
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
    cout<<endl<<setw(40)<<"Client List "<<vcls.size()<<" Client(s)."<<endl;
    
    HeaderClient();
    for (stClient &c : vcls) {
        
        PrintOneClient(c);
        cout<<endl;
    
    }
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    cout<<endl;
    
}

string SaveToFile(stClient cls,string delim){
    
    string newclient;
    
    newclient=cls.NumberOfAccount+delim;
    newclient+=cls.PinCode+delim;
    newclient+=cls.Name+delim;
    newclient+=cls.Phone+delim;
    newclient+=to_string(cls.Balance);
    
    return newclient;
}

stClient ReadUserCLient(){
    
    stClient cls;
    cout<<"please enter the Pin Code of Client       : ";cin>>cls.PinCode;
    cin.ignore(1,'\n');
    cout<<"please enter the Name Of CLient           : ";getline(cin, cls.Name);
    cout<<"please enter the Phone Of Client          : ";cin>>cls.Phone;
    cout<<"please enter the Balance of Client        : ";cin>>cls.Balance;
    cls.Delete=false;
    return cls;
}

void AddNewClinet(string AcountNumber){
    
    fstream MyFile;
    stClient cls=ReadUserCLient();
    
    string Line=AcountNumber+SaveToFile(cls, "#//#");
    MyFile.open("MyFile.txt",ios::out|ios::app);
    
    while (MyFile.is_open()) {
    
        MyFile<<Line<<endl;
        MyFile.close();
    }
}

bool CheckClient(string AccountNumber){
    
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
    for (stClient & C : vcls) {
        
        if (C.NumberOfAccount==AccountNumber) {
            return 0;
        }
    }
    return 1;
}



void _2_PrintAddclient(){
    
    char C='Y';
    
    while (tolower(C)=='y') {
        
        string AccountNumber;
        cout<<"please enter the Account Number of Client : ";cin>>AccountNumber;
        
        while (CheckClient(AccountNumber)==0) {
            cout<<"Client with ["<<AccountNumber<< "] already exists, Enter another Account Number ? ";
            cin>>AccountNumber;
            
        }
        
        AddNewClinet(AccountNumber);
        
        cout<<"Client Added Successfully, do you want to add more clients? Y/N? ";cin>>C;
        
    }
    
}


void PrintaccountoneClient(stClient cls){
    
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Accout Number : "<<cls.NumberOfAccount<<endl;
    cout<<"Pin Code      : "<<cls.PinCode<<endl;
    cout<<"Name          : "<<cls.Name<<endl;
    cout<<"Phone         : "<<cls.Phone<<endl;
    cout<<"Balace : "<<cls.Balance<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    
}

bool CheckDeleteFromVectorClient(char C,stClient cls){
    
    if (C=='y') {
        
        return 1;
    }
    return 0;
}


bool CheckClient(vector<stClient> &vcls,string AccountOfNumber){
    
    char c;
    
    for (stClient & C : vcls) {
        
        if (C.NumberOfAccount==AccountOfNumber) {
            
            PrintaccountoneClient(C);
            cout<<"Are you sure you want delete this client? y/n"<<endl;
            cin>>c;
            if (CheckDeleteFromVectorClient(tolower(c), C)) {
                C.Delete=false;
            }
            
            return 1;
            
        }
    }
    
    return 0;
}

void SaveToFileAfterDelete(vector<stClient> vcls){
    
    fstream MyFile;
    string Line;
    
    MyFile.open("MyFile.txt",ios::out);
    
    while (MyFile.is_open()) {
        
        for (stClient & c : vcls) {
            
            if (c.Delete) {
                
            Line=SaveToFile(c, "#//#");
                MyFile<<Line<<endl;
                
            }
        }
        
        MyFile.close();
    }

}


void _3_PrintDeleteFromeFile(){
    
    string AccountNumber;
    cout<<"Please enter AccountNumber ? ";cin>>AccountNumber;
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
        
        if (CheckClient(vcls, AccountNumber)) {
            
            SaveToFileAfterDelete(vcls);
            cout<<"The Client Delete succesfully "<<endl;
            
        } else {
            cout<<"Client with Account Number (" <<AccountNumber<<") is Not Found!"<<endl;
        }
                                    
}

bool CheckFindAccount(string Account,vector<stClient> vcls,stClient &cls){
    
    for (stClient & C : vcls) {
        if (C.NumberOfAccount==Account) {
            
            return 1;
        }
    }
    return 0;
}


bool CheckUpdateClient(){
    
    char C;
    cout<<"LientAre you sure you want update this client? y/n ? ";
    cin>>C;
    
    return (tolower(C)=='y');

}

void SaveToFileAfterUpdate(vector<stClient> vcls,stClient cls){
    
    fstream MyFile;
    string Line;
    
    MyFile.open("MyFile.txt",ios::out);
    
    while (MyFile.is_open()) {
        
        for (stClient & c : vcls) {
            
            if (c.Delete) {
                
            Line=SaveToFile(c, "#//#");
                MyFile<<Line<<endl;
            }   else {
                
                Line=SaveToFile(cls, "#//#");
                    MyFile<<Line<<endl;
                
            }

        }
        
        MyFile.close();
    }

}


void _4_PrintUpadteClient(){
    
    string Account;
    cout<<"Please enter AccountNumber ? ";cin>>Account;
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    stClient cls;
    
    if (CheckFindAccount(Account, vcls,cls)) {
        
        cout<<" The following are the client details : "<<endl;
        PrintaccountoneClient(cls);
        
        if (CheckUpdateClient()) {
            
          cls=ReadUserCLient();
            
            SaveToFileAfterUpdate(vcls, cls);
            
        }
    }
    else {
        
        cout<<"Client with ["<<Account<< "] doesnt exists";

    }
}

bool CheckFindClient(string Account,stClient & cls){
    
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
    for (stClient & c : vcls) {
        
        if (c.NumberOfAccount==Account) {
            cls=c;
            return 1;
        }
    }
    
    return 0;
}

void _5_PrintFindClient(){
    
    string Account;
    cout<<"Please enter AccountNumber ? ";cin>>Account;
    stClient cls;
    
    if (CheckFindClient(Account,cls)) {
        
        PrintaccountoneClient(cls);
        
    } else {
        cout<<"the Client ["<<Account<<"doesnt Exist"<<endl;
    }
    
}


bool CheckFindBalanceClient(vector<stClient>& vcls,string Account,stClient & cls){
    
    for (stClient & c : vcls) {
        
        if (c.NumberOfAccount==Account) {
            cls=c;
            c.Change=false;
            return 1;
        }
    }
    
    return 0;
}


void ChangeBalance(stClient &cls,long long Depost){
    
    char C;
    cout<<"Are you sure you want perfrom this transaction? y/n ? ";cin>>C;
    
    if (tolower(C)=='y') {
        
        cls.Balance+=Depost;

    }
    
}

void SaveToFileAfterChange(vector<stClient> vcls,stClient cls){
    
    fstream MyFile;
    string Line;
    
    
    MyFile.open("MyFile.txt",ios::out);
    
    while (MyFile.is_open()) {
        
        for (stClient & c : vcls) {
            
            if (c.Change) {
                
            Line=SaveToFile(c, "#//#");
            MyFile<<Line<<endl;
                
            }   else {
                
                Line=SaveToFile(cls, "#//#");
                MyFile<<Line<<endl;
                
            }

        }
        
        MyFile.close();
    }

}
    
void _6_1Diagonst(){
    
    string Account;
    cout<<"Please enter AccountNumber ? ";cin>>Account;
    stClient cls;
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
    if (CheckFindBalanceClient(vcls,Account, cls)) {
        
        cout<<" The following are the client details : "<<endl;
        
        PrintaccountoneClient(cls);
    
        long long Diag;
        cout<<"Please enter deposit amount ? ";cin>>Diag;
        
        ChangeBalance(cls, Diag);
        
        SaveToFileAfterChange(vcls,cls);
        
        cout<<"Done Deposit , you Add "<<Diag<<" for this AAcount "<<endl;
        
    } else {
        
        cout<<"Client with ["<<Account<<"] does not exist."<<endl;
    }
    
}


void _6_2Withdraw(){

    string Account;
    cout<<"Please enter AccountNumber ? ";cin>>Account;
    stClient cls;
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    
    if (CheckFindBalanceClient(vcls,Account, cls)) {
        
        cout<<" The following are the client details : "<<endl;
        PrintaccountoneClient(cls);
        
        long long Diag;
        cout<<"Please enter withdraw amount ? ";cin>>Diag;
        
        while (Diag>cls.Balance) {
            
            cout<<"Amount Exceeds the balance, you can withdraw up to : "<<cls.Balance<<endl;
            
            cout<<"Please enter another amount ? ";cin>>Diag;
        }
        
        ChangeBalance(cls,-Diag);
        cls.Change=false;
        
        
        SaveToFileAfterChange(vcls,cls);
        
        cout<<"Done withdraw , you remove "<<Diag<<" for this AAcount "<<endl;
        
    } else {
        
        cout<<"Client with ["<<Account<<"] does not exist."<<endl;
    }

}

void HeaderList(){
    
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
        
    cout<<left<<"| "<<setw(15)<<"Account Number ";
    cout<<left<<"| "<<setw(20)<<"Client Name ";
    cout<<left<<"| "<<setw(14)<<"Balance ";
        
        cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    
}


void BalanceList(stClient cls,long long &sum){
    
    cout<<left<<"| "<<setw(15)<<cls.NumberOfAccount;
    cout<<left<<"| "<<setw(20)<<cls.Name;
    cout<<left<<"| "<<setw(14)<<cls.Balance;
    sum+=cls.Balance;
    cout<<endl;
}

void _6_3ToTalBlnce(){
    
    vector<stClient> vcls=LoadFromFile("MyFile.txt");
    long long sum=0;
    
    HeaderList();
    
    for (stClient & C : vcls) {
        
        BalanceList(C,sum);
        
    }
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    
    cout<<right<<setw(40)<<"Total Balace = "<<sum<<endl<<endl;
    
}


void _6_Transactions(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(40)<<"Transactions Menue Screen"<<endl;
    cout<<"=================================================="<<endl;
    
    cout<<right<<setw(25)<<"[1] Deposit."<<endl;
    cout<<right<<setw(26)<<"[2] Withdraw."<<endl;
    cout<<right<<setw(32)<<"[3] Total Balances."<<endl;
    
    int num;
    cout<<"Choose what do you want to do? [1 to 3] ? ";cin>>num;
    
    while (num>3) {
        
        cout<<"you enter the ivalid number "<<endl;
        
        cout<<"please enter the anothe choise : ";
        cin>>num;
    }
    
    switch (num) {
        case 1:_6_1Diagonst();break;
        case 2:_6_2Withdraw();break;
        default:_6_3ToTalBlnce();break;
            
    }
}
    

int ReadNumberChoise(){
    int num;
    cout<<"Choose what do you want to do? [1 to 6] ? : ";cin>>num;
    
    while (num>6) {
        
        cout<<"the number doesnt exist in Range ";
        cout<<"please Choose what do you want to do? [1 to 6] ? : ";
        cin>>num;
    }
    cout<<endl;
    
    return num;
}

void HeaderOFMenuClient(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(40)<<"Main Menue Screen"<<endl;
    cout<<"=================================================="<<endl;
    
    cout<<right<<setw(30)<<"[1] Show Client List."<<endl;
    cout<<right<<setw(27)<<"[2]Add New Client."<<endl;
    cout<<right<<setw(26)<<"[3]Delete Client."<<endl;
    cout<<right<<setw(32)<<"[4] Update Client Info."<<endl;
    cout<<right<<setw(24)<<"[5]Find Client."<<endl;
    cout<<right<<setw(24)<<"[6]Transactions"<<endl<<endl;
    
}

void PrintChoise(int num){
    
    switch (num) {
            
        case 1:_1_PrintAllClient();break;
        case 2:_2_PrintAddclient();break;
        case 3:_3_PrintDeleteFromeFile();break;
        case 4:_4_PrintUpadteClient();break;
        case 5:_5_PrintFindClient();break;
        default:_6_Transactions();break;
    }
}

void PrintAllFunction(){
    
    char Reb='y';
    
    while (tolower(Reb)=='y') {
    
        HeaderOFMenuClient();
        
        PrintChoise(ReadNumberChoise());
        
        cout<<"if you Want to complete y/n : ";
        cin>>Reb;
        
    }
}


int ReadChoiseUser(){
    int num;
    cout<<"Choose what do you want to do? [1 to 5] ? : ";cin>>num;
    
    while (num>5) {
        
        cout<<"the number doesnt exist in Range ";
        cout<<"please Choose what do you want to do? [1 to 5] ? : ";
        cin>>num;
    }
    cout<<endl;
    
    return num;
}

struct stUser{
    
    string Name;
    string Pasword;
    int Acces;
    bool Delete=true;
    
};

vector<string> delteDalim(string FullName,string delim){
    
    short pos=0;
    vector<string> After;
    string Temp;
    while ((pos=FullName.find(delim))!=string::npos) {
        
        Temp=FullName.substr(0,pos);
        
        if (Temp!="") {
            After.push_back(Temp);
        }
        FullName.erase(0,delim.length()+pos);
        Temp="";
    }
    
    if (FullName!="") {
        After.push_back(FullName);
    }
    
    return After;
}

stUser LoadFromVectorofUserFile(string delim,string FulName){
    
    vector<string> Temp=delteDalim(FulName, delim);
    stUser cls;
    
    cls.Name=Temp.at(0);
    cls.Pasword=Temp.at(1);
    cls.Acces=stoi(Temp.at(2));
    
    return cls;
}


vector<stUser> LoadFromUserFile(string Name){
    
    fstream MyFile;
    stUser cls;
    vector<stUser> vcls;
    MyFile.open(Name,ios::in);
    
    while (MyFile.is_open()) {
        string Line;
        
        while (getline(MyFile,Line)){
            if (Line!="") {
                cls=LoadFromVectorofUserFile("#//#", Line);
                vcls.push_back(cls);
            }
        }
        
        MyFile.close();
    }
    return vcls;
}

void HeaderUser(){
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    
    cout<<left<<"| "<<setw(20)<<"User Name ";
    cout<<left<<"| "<<setw(14)<<"Pin Code ";
    cout<<left<<"| "<<setw(14)<<"Access ";
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    
}

void PrintOneUser(stUser cls){
    
    cout<<left<<"| "<<setw(20)<<cls.Name;
    cout<<left<<"| "<<setw(14)<<cls.Pasword;
    cout<<left<<"| "<<setw(20)<<cls.Acces;

}

void _1_PrintAllUser(){
    
    vector<stUser> vcls=LoadFromUserFile("UserFile.txt");
    
    cout<<endl<<setw(40)<<"User List "<<vcls.size()<<" User(s)."<<endl;
    
    HeaderUser();
    for (stUser &c : vcls) {
        
        PrintOneUser(c);
        cout<<endl;
    
    }
    
    cout<<"–––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––––"<<endl;
    cout<<endl;
    
}

string SaveToUSerFile(stUser cls,string delim){
    
    string newclient=delim;
    
    newclient+=cls.Pasword+delim;
    newclient+=to_string(cls.Acces);
    
    return newclient;
}

bool CheckTheAcces(char X){
    
    return (tolower(X)=='y');
}

stUser ReadUser(){
    
    stUser us;
    cout<<"pLease enter the Password of The User : ";cin>>us.Pasword;
    
    char X;
    cout<<"Do you want to give full access? y/n? ";cin>>X;
    
    if (CheckTheAcces(X)) {
        us.Acces=-1;
        return us;
        
    }
    
    int Arr[7];
    cout<<"Show Client List? y/n?  :  ";cin>>X;(CheckTheAcces(X))?Arr[0]=pow(2,(1-1)):Arr[0]=0;
    cout<<"Add New Client? y/n?    :  ";cin>>X;(CheckTheAcces(X))?Arr[1]=pow(2,(2-1)):Arr[1]=0;
    cout<<"Delete Client? y/n?     :  ";cin>>X;(CheckTheAcces(X))?Arr[2]=pow(2,(3-1)):Arr[2]=0;
    cout<<"Update Client? y/n?     :  ";cin>>X;(CheckTheAcces(X))?Arr[3]=pow(2,(4-1)):Arr[3]=0;
    cout<<"Find Client? y/n?       :  ";cin>>X;(CheckTheAcces(X))?Arr[4]=pow(2,(5-1)):Arr[4]=0;
    cout<<"Transactions? y/n?      :  ";cin>>X;(CheckTheAcces(X))?Arr[5]=pow(2,(6-1)):Arr[5]=0;
    cout<<"Manage Users? y/n?      :  ";cin>>X;(CheckTheAcces(X))?Arr[6]=pow(2,(7-1)):Arr[6]=0;
    
    us.Acces=(Arr[0]|Arr[1]|Arr[2]|Arr[3]|Arr[4]|Arr[5]|Arr[6]);
    
    return us;
}

void AddNewUser(string Name){
    
    fstream MyFile;
    stUser cls=ReadUser();
    
    string Line=Name+SaveToUSerFile(cls, "#//#");
    MyFile.open("UserFile.txt",ios::out|ios::app);
    
    while (MyFile.is_open()) {
    
        MyFile<<Line<<endl;
        MyFile.close();
    }
}

bool CheckUser(string Name){
    
    vector<stUser> vcls=LoadFromUserFile("UserFile.txt");
    
    for (stUser & C : vcls) {
        
        if (C.Name==Name) {
            return 0;
        }
    }
    return 1;
}



void _2_PrintAddUser(){
    
    char C='Y';
    
    while (tolower(C)=='y') {
        
        string Name;
        cout<<"please enter the Name of The User : ";cin>>Name;
        
        while (CheckUser(Name)==0) {
            cout<<"Users with ["<<Name<< "] already exists, Enter another Name? ";
            cin>>Name;
            
        }
        
        AddNewUser(Name);
        
        cout<<"User Added Successfully, do you want to add more User? Y/N? ";cin>>C;
        
    }
    
}


void PrintaccountoneUser(stUser cls){
    
    cout<<"------------------------------------------------------------"<<endl;
    cout<<"Name          : "<<cls.Name<<endl;
    cout<<"Pin Code      : "<<cls.Pasword<<endl;
    cout<<"Pin Code      : "<<cls.Acces<<endl;
    cout<<"------------------------------------------------------------"<<endl;
    
}

bool CheckDeleteFromVectorUser(char C,stUser cls){
    
    if (C=='y') {
        
        return 1;
    }
    return 0;
}


bool CheckUSer(vector<stUser> &vcls,string Name){
    
    char c;
    
    for (stUser & C : vcls) {
        
        if (C.Name==Name) {
            
            PrintaccountoneUser(C);
            cout<<endl<<"Are you sure you want delete this User ? y/n : ";
            cin>>c;
            if (CheckDeleteFromVectorUser(tolower(c), C)) {
                C.Delete=false;
            }
            
            return 1;
            
        }
    }
    
    return 0;
}

void  SaveToFileAfterDeleteUser(vector<stUser> vcls){
    
    fstream MyFile;
    string Line;
    
    MyFile.open("UserFile.txt",ios::out);
    
    while (MyFile.is_open()) {
        
        for (stUser & c : vcls) {
            
            if (c.Delete) {
                
            Line=c.Name+SaveToUSerFile(c, "#//#");
                MyFile<<Line<<endl;
                
            }
        }
        
        MyFile.close();
    }

}


void _3_PrintDeleteFromUserFile(){
    
    string Name;
    cout<<"Please enter Name ? ";cin>>Name;
    vector<stUser> vcls=LoadFromUserFile("UserFile.txt");
    
    if (CheckUSer(vcls, Name)) {
              
            SaveToFileAfterDeleteUser(vcls);
            cout<<endl<<"The User Delete succesfully "<<endl;
            
        } else {
            cout<<endl<<"User with Name Number (" <<Name<<") is Not Found!"<<endl;
        }
                                    
}

bool CheckFindAccountUser(string Name,vector<stUser> vcls,stUser &cls){
    
    for (stUser & C : vcls) {
        if (C.Name==Name) {
            cls=C;
            return 1;
        }
    }
    return 0;
}


bool CheckUpdateUser(){
    
    char C;
    cout<<"Are you sure you want update this User? y/n ? ";
    cin>>C;

    return (tolower(C)=='y');
}

void SaveToFileAfterUpdateUser(vector<stUser> vcls,stUser cls){
    
    fstream MyFile;
    string Line;
    
    MyFile.open("UserFile.txt",ios::out);
    
    while (MyFile.is_open()) {
        
        for (stUser & c : vcls) {
            
            if (c.Name!=cls.Name) {
                
            Line=c.Name+SaveToUSerFile(c, "#//#");
                MyFile<<Line<<endl;
            }   else {
                
                Line=cls.Name+SaveToUSerFile(cls, "#//#");
                    MyFile<<Line<<endl;
                
            }

        }
        
        MyFile.close();
    }

}


void _4_PrintUpadteUser(){
    
    string Name;
    cout<<"Please enter Name ? ";cin>>Name;
    vector<stUser> vcls=LoadFromUserFile("UserFile.txt");
    stUser cls;
    
    if (CheckFindAccountUser(Name,vcls,cls)) {
        
        cout<<" The following are the User details : "<<endl;
        PrintaccountoneUser(cls);
        
        if (CheckUpdateUser()) {
            
          cls=ReadUser();
            cls.Delete=false;
            cls.Name=Name;
            SaveToFileAfterUpdateUser(vcls,cls);
            
        }
    }
    else {
        
        cout<<"User with ["<<Name<< "] doesnt exists"<<endl<<endl;

    }
}

bool CheckFindUser(string Name,stUser & cls){
    
    vector<stUser> vcls=LoadFromUserFile("UserFile.txt");
    
    for (stUser & c : vcls) {
        
        if (c.Name==Name) {
            cls=c;
            return 1;
        }
    }
    
    return 0;
}

void _5_PrintFindUser(){
    
    string Name;
    cout<<"Please enter Name ? ";cin>>Name;
    stUser cls;
    
    if (CheckFindUser(Name,cls)) {
        
        PrintaccountoneUser(cls);
        
    } else {
        cout<<"the User ["<<Name<<"doesnt Exist"<<endl;
    }
}

void PrintChoiseUSer(int num){
    
    switch (num) {
            
        case 1:_1_PrintAllUser();break;
        case 2:_2_PrintAddUser();break;
        case 3:_3_PrintDeleteFromUserFile();break;
        case 4:_4_PrintUpadteUser();break;
        
        default:_5_PrintFindUser();break;
    }
}

void HeaderOFManuUser(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(40)<<"Main Menue Screen"<<endl;
    cout<<"=================================================="<<endl;
    
    cout<<right<<setw(30)<<"[1] Show User List."<<endl;
    cout<<right<<setw(27)<<"[2]Add New User."<<endl;
    cout<<right<<setw(26)<<"[3]Delete User."<<endl;
    cout<<right<<setw(32)<<"[4] Update User Info."<<endl;
    cout<<right<<setw(24)<<"[5]Find User."<<endl;

}

void PrintAllFunctionUser(){
    
        HeaderOFManuUser();
        PrintChoiseUSer(ReadChoiseUser());
        
}

bool CheckFindUser(string Name,string Password,stUser & cls){
    
    vector<stUser> vcls=LoadFromUserFile("UserFile.txt");
    
    for (stUser & c : vcls) {
        
        if (c.Name==Name&&c.Pasword==Password) {
            cls=c;
            return 1;
        }
    }
    
    return 0;
}


bool FindUserByNameAndPassword(string Name,string Password,stUser &cls){
    
        if (CheckFindUser(Name,Password,cls)) {
        
        return 1;
    }
    
    return 0;
}

void HeaderForLogin(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(20)<<"Login Screen"<<endl;
    cout<<"=================================================="<<endl;

}

void MenuScreen(){
    
    cout<<"=================================================="<<endl;
    cout<<right<<setw(40)<<"Main Menue Screen"<<endl;
    cout<<"=================================================="<<endl;

    cout<<right<<setw(30)<<"[1] Show Client List."<<endl;
    cout<<right<<setw(27)<<"[2]Add New Client."<<endl;
    cout<<right<<setw(26)<<"[3]Delete Client."<<endl;
    cout<<right<<setw(32)<<"[4] Update Client Info."<<endl;
    cout<<right<<setw(24)<<"[5]Find Client."<<endl;
    cout<<right<<setw(24)<<"[6]Transactions"<<endl;
    cout<<right<<setw(25)<<"[7]Manage Users."<<endl<<endl;
    cout<<"=================================================="<<endl;

}

int ReadAccess(){
    
    int num;
    cout<<"Choose what do you want to do? [1 to 7] ? : ";cin>>num;
    
    while (num>7) {
        
        cout<<"the number doesnt exist in Range ";
        cout<<"please Choose what do you want to do? [1 to 7] ? : ";
        cin>>num;
    }
    cout<<endl;
    
    return num;
}

void NotAcess(){
    
    cout<<"Access Denied,\n You dont Have Permission To Do this,\n Please Conact Your Admin.\n";
    
}

void Aceess(stUser cls){
        
    char Rep='y';

    while (tolower(Rep)=='y') {
        
        int Choice=ReadAccess();

        int X=pow(2,Choice-1);

        switch (Choice) {
            case 1: (cls.Acces&X)?_1_PrintAllClient():NotAcess();break;
            case 2: (cls.Acces&X)?_2_PrintAddclient():NotAcess();break;
            case 3: (cls.Acces&X)?_3_PrintDeleteFromeFile():NotAcess();break;
            case 4: (cls.Acces&X)?_4_PrintUpadteClient():NotAcess();break;
            case 5: (cls.Acces&X)?_5_PrintFindClient():NotAcess();break;
            case 6: (cls.Acces&X)?_6_Transactions():NotAcess();break;

            default:(cls.Acces&X)?PrintAllFunctionUser():NotAcess();break;
                
        }

        cout<<endl<<"If You Want To Copmlete ["<<cls.Name<<"] : y/n ";cin>>Rep;
        cout<<endl;

    }
    
    
}

void Login(){
    
    stUser cls;
    string Name;
    char Rep='y';
    
    while (tolower(Rep)=='y') {
        
        HeaderForLogin();
        cout<<"Please enter Name of The User ?  : ";cin>>Name;
        string Password;cout<<"please enter the number of The User ? : ";cin>>Password;
        
        if (FindUserByNameAndPassword(Name,Password, cls)) {
        
            MenuScreen();
            Aceess(cls);
            
        } else {
            
            cout<<endl<<"Invlaid Username/Password! "<<endl;
            
        }
        
        cout<<endl<<"If You Want To Copmlete : y/n ";cin>>Rep;
        cout<<endl;
        
    }
    
}


int main(){
    
    Login();
    
    return 0;
}
