#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#define QUIT 0
#define SAVE 1
#define REMOVE 2
#define DISPLAY 3
#define SEARCH 4
#define GETGROUP 5
#define PASSWORD "12345678"

struct Info{
private:
    string name;
    string number;
    string group;
    string id;
public:
    Info(){}

    Info(string name, string number){
        this->setName(name);
        this->setNumber(number);
        this->setGroup("NULL");
    }

    Info(string name, string number, string group){
        this->name = name;
        this->number = number;
        this->group = group;
    }

    Info(string name, string number, string group, string id){
        this->name = name;
        this->number = number;
        this->group = group;
        this->id = id;
    }

    string getName(){
        return name;
    }

    string getNumber(){
        return number;
    }

    string getGroup(){
        return group;
    }

    void setName(string name){
        this->name = name;
    }

    void setNumber(string number){
        this->number = number;
    }

    void setGroup(string group){
        this->group = group;
    }

    void printInfo(){
        cout << "Name:\t" << getName() << endl << "Number:\t" << getNumber() << endl << "Group:\t" << getGroup() << endl << endl;
    }
};

    //define vector here
    vector<Info> allRecords;

bool checkPassword(){
    string password;
    cout << "Password: ";
    cin >> password;
    if(password == PASSWORD)
        return true;
    return false;
}

void printIntruction(){
    cout << "Press 1 to save a new contacts\n";
    cout << "Press 2 to remove a old contacts\n";
    cout << "Press 3 to show all contacts\n";
    cout << "Press 4 to search contacts\n";
    cout << "Press 5 to get group of contacts\n";
    cout << "Press 0 to stop the application\n\n";
}

void display(){
    for(auto record_item: allRecords){
        record_item.printInfo();
    }
}

void removeRecord(){
    if(checkPassword()){
        cout << "Insert ID of the Contact you want to remove: ";
        int id = 0;
        cin >> id;
        allRecords.erase(allRecords.begin() + id - 1);
        cout << "Done!" << endl;
    }
    else{
        cout << "Wrong password! Please try again later" << endl;
    }
}

void loadToVector(){
    ifstream file("data.txt");
    string token;
    string line;
    if(file.is_open()){
        getline(file, line);
        while(!file.eof()){
            getline(file, line);
            vector<string> items;
            stringstream ss(line);
            while (getline(ss, token, '\t')) {
                items.push_back(token);
            }
            Info newInfo = Info(items[0], items[1], items[2]);
            allRecords.push_back(newInfo);
        }
    }
    file.close();
}

void saveNewContact(){
    string newName;
    string newNumber;
    fflush(stdin);
    cout << "Contact name: ";
    getline(cin, newName);
    cout << "Contact number: ";
    getline(cin, newNumber);
    Info newContact(newName, newNumber);
    allRecords.push_back(newContact);
}

void storeData(){
    ofstream outfile;
    outfile.open("data.txt");
    outfile.clear();
    if(outfile.is_open()){
        outfile << "Name\tNumber\tGroup";
        for(auto item: allRecords){
            outfile << "\n" << item.getName() << "\t" << item.getNumber() << "\t" << item.getGroup();
        }
    }
    outfile.close();
}

void searchContact(){
    string information;
    cout << "Insert information of contact: ";
    cin >> information;
    for(auto record_item: allRecords){
        if (record_item.getName().find(information) != string::npos || record_item.getNumber().find(information) != string::npos) {
            record_item.printInfo();
        }
    }
}

void getGroup(){
    string groupToGet;
    cout << "Insert name of the group: ";
    cin >> groupToGet;
    int temp = 0;
    for(auto record_item:allRecords){
        if(record_item.getGroup() == groupToGet){
            record_item.printInfo();
            temp = 1;
        }
    }
    if(temp == 0)
        cout << "Can't find any record!";
}

int main()
{
    printIntruction();
    loadToVector();
    int op;
    while(true){
        cin >> op;
        if(op == QUIT){
            break;
        }
        switch(op){
            case SAVE:
                {
                    saveNewContact();
                    break;
                }
            case REMOVE:
                {
                    removeRecord();
                    break;
                }
            case DISPLAY:
                {
                    display();
                    break;
                }
            case SEARCH:
                {
                    searchContact();
                    break;
                }
            case GETGROUP:
                {
                    getGroup();
                    break;
                }
            default:
                {
                    cout << "Something went wrong" << endl;
                    break;
                }
        }
    }
    storeData();
    return 0;
}
