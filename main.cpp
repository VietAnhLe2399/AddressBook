#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

struct Info{
private:
    string name;
    string number;
public:
    Info(){}

    Info(string name, string number){
        this->setName(name);
        this->setNumber(number);
    }

    string getName(){
        return name;
    }

    string getNumber(){
        return number;
    }

    void setName(string name){
        this->name = name;
    }

    void setNumber(string number){
        this->number = number;
    }

    void printInfo(){
        cout << "Name:\t" << getName() << endl << "Number:\t" << getNumber() << endl << endl;
    }
};

void printIntruction(){
    cout << "Press 1 to save a new contact\n";
    cout << "Press 2 to remove a old contact\n";
    cout << "Press 3 to show all contact\n";
    cout << "Press 4 to search contact by name\n";
    cout << "Press 5 to search contact by number\n";
    cout << "Press 0 to stop the app\n\n";
}

    //define vector here
    vector<Info> allRecords;

void loadToVector(){
    ifstream file("data.txt");
    string token;
    string line;
    if(file.is_open()){
        while(!file.eof()){
            getline(file, line);
            vector<string> items;
            stringstream ss(line);
            while (getline(ss, token, '\t')) {
                items.push_back(token);
            }
            Info newInfo = Info(items[0], items[1]);
            newInfo.printInfo();
        }
    }
}


int main()
{
    printIntruction();

    int op;
    while(true){
        cin >> op;
        if(op == 0){
            break;
        }
        switch(op){
            case 1:
                string newName;
                string newNumber;
                fflush(stdin);
                cout << "Contact name: ";
                cin >> newName;
                cout << "Contact number: ";
                cin >> newNumber;
                Info newContact(newName, newNumber);
                allRecords.push_back(newContact);
                break;
        }
    }

    cout << "Load to vector" << endl;
    loadToVector();


//    for(int it = 0; it < allRecords.size(); ++it){
//        cout << allRecords[it].getName() << "\t" << allRecords[it].getNumber() << endl;
//    }

    return 0;
}
