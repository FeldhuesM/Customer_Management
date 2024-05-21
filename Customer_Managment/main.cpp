#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
using namespace std;

const int Data_Size_Per_Customer = 3;


void Save_Vector_To_File(const vector<std::string>& vec, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const string& data : vec) {
            file << data << endl;
        }
        file.close();
        cout << "Vector erfolgreich gespeichert." << std::endl;
    } else {
        cerr << "Fehler beim Öffnen der Datei zum Speichern des Vektors." << endl;
    }
}

vector<std::string> Load_Vector_From_File(const string& filename) {
    vector<string> vec;
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            vec.push_back(line);
        }
        file.close();
        cout << "Vector erfolgreich geladen." << endl;
    } else {
        cerr << "Fehler beim oeffnen der Datei zum Laden des Vektors." << endl;
    }
    return vec;
}


void Print_Vector(const vector<string>& vec) {
    string labels[Data_Size_Per_Customer] = {"Name: ", "Email: ", "Telefonnummer: "};

    for(size_t i=0; i < vec.size(); i += Data_Size_Per_Customer){
        cout << "\n" << (i / Data_Size_Per_Customer + 1) << ". Kunde:\n";
        for (size_t j = 0; j < Data_Size_Per_Customer; ++j) {
            if (i + j < vec.size()) {
                cout << labels[j] << vec[i + j] << "\n";
            }
        }
    }
}


void Del_Customer(vector<string>& vec, int to_del) {
    int start_pos = (to_del - 1) * Data_Size_Per_Customer;
    if (start_pos >= 0 && start_pos + Data_Size_Per_Customer <= vec.size()) {
        vec.erase(vec.begin() + start_pos, vec.begin() + start_pos + Data_Size_Per_Customer);
        cout << "Kunde wurde gelöscht." << endl;
    } else {
        cerr << "Fehler beim Löschen des Kunden." << endl;
    }
}

void Edit_Customer(int customer_choice, vector<string>& vec){

    int start_pos = (customer_choice - 1) * Data_Size_Per_Customer;

    if (start_pos >= 0 && start_pos + Data_Size_Per_Customer < vec.size()) {
        int Choice;
        cout << "1. Gesamten Kunden? \n 2. Einzelne angabe bearbeiten" << endl;
        cin  >> Choice;
        switch (Choice) {
            case 1:
                cout << "Name angeben:" << endl;
                cin >> vec[start_pos];
                cout << "Email angeben:" << endl;
                cin >> vec[start_pos +1];
                cout << "Nummer angeben:" << endl;
                cin >> vec[start_pos + 2];
                break;
            case 2:
                cout << "1. Name:\n2. Email\n 3. Nummer\n" << endl;
                cin >> Choice;
                switch (Choice) {
                    case 1:
                        cout << "Name angeben:" << endl;
                        cin >> vec[start_pos];
                        break;
                    case 2:
                        cout << "Email angeben:" << endl;
                        cin >> vec[start_pos + 1];
                        break;
                    case 3:
                        cout << "Nummer angeben:" << endl;
                        cin >> vec[start_pos + 2];
                        break;
                    default:
                        cerr << "Falsche Eingabe" << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                }
                break;
            default:
                cerr << "Falsche Eingabe" << std::endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;

        }
    }
    else {
        cerr << "Fehler beim bearbeiten des Kunden." << endl;
    }
}


int main() {

    string  Email, Name, Nummer ;

    int choice, customer_choice, del_choice;
    bool ablauf = true;

    const string filename = "C:/EigeneDaten/Jetbrains/C++/Customer_Managment/customer.txt";

    vector<string> namesVec;

    namesVec = Load_Vector_From_File(filename);


    while(ablauf){
        cout << "Was möchten Sie machen?\n1. Kunden eingeben\n2. Kunden anzeigen\n3. Kunden löschen\n4. Programm beenden\n5. Kunden bearbeiten\n";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Kunden eingeben" << endl;
                cout << "Name angeben:" << endl;
                cin >> Name;
                cout << "Email eingeben:" << endl;
                cin >> Email;
                cout << "Nummer eingeben:" << endl;
                cin >> Nummer;
                namesVec.push_back(Name);
                namesVec.push_back(Email);
                namesVec.push_back(Nummer);
                break;

            case 2:
                cout << "Kunden anzeigen" << endl;
                Print_Vector(namesVec);
                cout << endl;
                break;

            case 3:
                cout << "Welchen Kunden moechten sie loeschen?" << endl;
                Print_Vector(namesVec);
                cin >> del_choice;
                Del_Customer(namesVec, del_choice);
                break;

            case 4:
                Save_Vector_To_File(namesVec, filename);
                cout << "Programm wird beendet." << endl;
                ablauf = false;
                break;
            case 5:
                cout << "Welchen Kunden moechten sie bearbeiten?" << endl;
                cin >> customer_choice;
                Edit_Customer(customer_choice, namesVec);
                break;

            default:
                cerr << "Falsche Eingabe" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;

        }
    }

    return 0;
}

