#include <iostream>
#include <fstream>
#include <vector>

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
        cout << getName() << endl << getNumber();
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

int main()
{
    printIntruction();

    Info temp;
    temp.setName("Viet Anh");
    temp.setNumber("0961 679 361");

    //Open file
//    ofstream file;
//    file.open("data.txt");
//    file << temp.getName() << "\t" << temp.getNumber();
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
            case 2:
                cout << "Case 2" << endl;
                break;
            case 3:
                break;
            default:
                cout << "Something went wrong" << endl;
                break;
        }
    }

    allRecords.push_back(temp);

    for(int it = 0; it < allRecords.size(); ++it){
        cout << allRecords[it].getName() << "\t" << allRecords[it].getNumber() << endl;
    }

    return 0;
}
