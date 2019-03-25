#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

/**
* CONST HERE
*/

const char S_Mode = 's';
const char R_Mode = 'r';
const char QUIT = 'q';
const char SAVE = 'a';
const char REMOVE = 'm';
const char DISPLAY = 'd';
const char SEARCH = 'f';
const char GETGROUP = 'g';
const char YES = 'y';
const char NO = 'n';
#define PASSWORD "12345678"

/**
* DEFINE STRUCT INFORMATION
*/

struct Information {
private:
    string name;
    string number;
    string group;
    string id;

public:
    Information() {}

    Information(string name, string number) {
        this->setName(name);
        this->setNumber(number);
        this->setGroup("None");
    }

    Information(string name, string number, string group) {
        this->name = name;
        this->number = number;
        this->group = group;
    }

    string getName() {
        return name;
    }

    string getNumber() {
        return number;
    }

    string getGroup() {
        return group;
    }

    void setName(string name) {
        this->name = name;
    }

    void setNumber(string number) {
        this->number = number;
    }

    void setGroup(string group) {
        this->group = group;
    }

    void printInfo(int id) {
        cout << "ID:\t" << id + 1 << endl
             << "Name:\t" << getName() << endl
             << "Number:\t" << getNumber() << endl
             << "Group:\t" << getGroup() << endl
             << endl;
    }
};

/**
* DEFINE VECTOR HERE
*/
vector<Information> allRecords;

/**
* DEFINE FUNCTION HERE
*/

void printIntruction();

int loadToVector();

void storeDataToFile();

/**
* R_MODE
*/

void saveNewContact();

bool checkPassword();

void removeRecord();

/**
* S_MODE
*/

void display();

void searchContact();

void getGroupOfContacts();

int main()
{
    printIntruction();
    char flag = R_Mode;
    int idMax = loadToVector();
    char FuncKey;
    cout << "CHOOSE FUNCTION TO START: ";
    while (true) {
        cin >> FuncKey;
        if (FuncKey == QUIT) {
            break;
        }
        if (FuncKey == S_Mode) {
            flag = S_Mode;
            cout << "YOU'RE IN S_MODE" << endl;
            continue;
        }
        if (FuncKey == R_Mode) {
            flag = R_Mode;
            cout << "YOU'RE IN R_MODE" << endl;
            continue;
        }
        switch (flag) {
        case R_Mode: {
            switch (FuncKey) {
            case SAVE: {
                saveNewContact();
                idMax++;
                break;
            }
            case REMOVE: {
                removeRecord();
                idMax--;
                break;
            }
            default: {
                cout << "Something went wrong in R_MODE" << endl;
                break;
            }
            }
            break;
        }
        case S_Mode: {
            switch (FuncKey) {
            case DISPLAY: {
                display();
                break;
            }
            case SEARCH: {
                searchContact();
                break;
            }
            case GETGROUP: {
                getGroupOfContacts();
                break;
            }
            default: {
                cout << "Something went wrong in S_MODE" << endl;
            }
            }
            break;
        }
        default: {
            cout << "Something went wrong" << endl;
            break;
        }
        }
    }
    storeDataToFile();
    return 0;
}

/**
* IMPLEMENT FUNCTION HERE
*/

bool checkPassword() {
    string password;
    cout << "Password: ";
    cin >> password;
    if (password == PASSWORD)
        return true;
    return false;
}

void printIntruction() {
    cout << "**** ADDRESS BOOK APPLICATION ****\n\n";
    cout << "- PRESS S TO ACCESS TO S_MODE\n";
    cout << "- PRESS R TO ACCESS TO R_MODE\n\n";
    cout << "- PRESS A TO SAVE A NEW CONTACT\n";
    cout << "- PRESS M TO REMOVE OLD CONTACT\n";
    cout << "- PRESS D TO SHOW ALL CONTACTS\n";
    cout << "- PRESS F TO SEARCH FOR A CONTACT\n";
    cout << "- PRESS G TO GET GROUP OF CONTACTS\n";
    cout << "- PRESS Q TO QUIT THE APPLICATION\n\n";
}

void display() {
    for (int i = 0; i < (int)allRecords.size(); i++) {
        allRecords[i].printInfo(i);
    }
}

void removeRecord() {
    if (checkPassword()) {
        cout << "Insert ID of the Contact you want to remove: ";
        int id = 0;
        cin >> id;
        allRecords.erase(allRecords.begin() + id - 1);
        cout << "Done!" << endl;
    }
    else {
        cout << "Wrong password! Please try again later" << endl;
    }
}

int loadToVector() {
    ifstream file("data.txt");
    string token;
    string line;
    int id = 0;
    if (file.is_open()) {
        getline(file, line);
        while (!file.eof()) {
            getline(file, line);
            vector<string> items;
            stringstream ss(line);
            while (getline(ss, token, '\t')) {
                items.push_back(token);
            }
            Information newInfo = Information(items[0], items[1], items[2]);
            allRecords.push_back(newInfo);
            id++;
        }
    }
    if (id == 0) {
        cout << "Data file is empty. Please add new contacts" << endl;
    }
    file.close();
    return id;
}

void saveNewContact() {
    string newName;
    string newNumber;
    string group;
    Information newContact;
    char isContinue;
    fflush(stdin);
    cout << "Contact name: ";
    getline(cin, newName);
    cout << "Contact number: ";
    getline(cin, newNumber);
    cout << "Group? Press y for yes, n for no" << endl;
    cin >> isContinue;
    if (isContinue == YES) {
        cout << "Contact's group: ";
        cin >> group;
        newContact = Information(newName, newName, group);
    }
    if (isContinue == NO)
        newContact = Information(newName, newNumber);
    allRecords.push_back(newContact);
}

void storeDataToFile() {
    ofstream outfile;
    outfile.open("data.txt");
    outfile.clear();
    if (outfile.is_open()) {
        outfile << "Name\tNumber\tGroup";
        for (int i = 0; i < (int)allRecords.size(); i++) {
            outfile << "\n" << allRecords[i].getName() << "\t" << allRecords[i].getNumber() << "\t" << allRecords[i].getGroup() << "\t" << i + 1;
        }
    }
    outfile.close();
}

void searchContact() {
    string information;
    cout << "Insert information of contact: ";
    cin >> information;
    for (int i = 0; i < (int)allRecords.size(); i++) {
        if (allRecords[i].getName().find(information) != string::npos || allRecords[i].getNumber().find(information) != string::npos) {
            allRecords[i].printInfo(i);
        }
    }
}

void getGroupOfContacts() {
    string groupToGet;
    cout << "Insert name of the group: ";
    cin >> groupToGet;
    int temp = 0;
    for (int i = 0; i < (int)allRecords.size(); i++) {
        if (allRecords[i].getGroup() == groupToGet) {
            allRecords[i].printInfo(i);
            temp = 1;
        }
    }
    if (temp == 0)
        cout << "Can't find any record!" << endl;
}
