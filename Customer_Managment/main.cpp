#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <fstream>

// Funktion zum Speichern des Vektors in eine Datei
void Save_Vector_To_File(const std::vector<std::string>& vec, const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const std::string& data : vec) {
            file << data << std::endl;
        }
        file.close();
        std::cout << "Vector erfolgreich gespeichert." << std::endl;
    } else {
        std::cerr << "Fehler beim Öffnen der Datei zum Speichern des Vektors." << std::endl;
    }
}

// Funktion zum Laden des Vektors aus einer Datei
std::vector<std::string> Load_Vector_From_File(const std::string& filename) {
    std::vector<std::string> vec;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            vec.push_back(line);
        }
        file.close();
        std::cout << "Vector erfolgreich geladen." << std::endl;
    } else {
        std::cerr << "Fehler beim Öffnen der Datei zum Laden des Vektors." << std::endl;
    }
    return vec;
}

void Print_Vector(std::vector<std::string>& vec) {
    int iter ;
    int customer_count;
    customer_count = 1;

    for (const std::string& str : vec){
        if (iter % 3 == 0){
            std::cout << std::endl;
            std::cout << customer_count << ". Kunde:";
            customer_count++;
        }
        std::cout << std::endl;
        std::cout << str << " ";
        iter++;
    }
    std::cout << std::endl;
}


void Del_Customer(std::vector<std::string>& vec, int to_del){
    int pos1 = to_del * 3 -1 ;
    int pos2 = to_del * 3 -2 ;
    int pos3 = to_del * 3 -3 ;
    if (pos1 >= 0 && pos1 < vec.size() && pos2 >= 0 && pos2 < vec.size() && pos3 >= 0 && pos3 < vec.size()) {
        vec.erase(vec.begin() + pos1);
        vec.erase(vec.begin() + pos2);
        vec.erase(vec.begin() + pos3);
        std::cout << "Kunde wurde geloescht." << std::endl;

    }
    else {
        std::cerr << "Fehler beim loeschen des Kunden." << std::endl;
    }
}

void Edit_Customer(int customer_choice, std::vector<std::string>& vec){
    int Choice;

    int pos1 = customer_choice * 3 -1 ;
    int pos2 = customer_choice * 3 -2 ;
    int pos3 = customer_choice * 3 -3 ;
    if (pos1 >= 0 && pos1 < vec.size() && pos2 >= 0 && pos2 < vec.size() && pos3 >= 0 && pos3 < vec.size()) {
        std::cout << "1. Gesamten Kunden?" << std::endl;
        std::cout << "2. Einzelne angabe bearbeiten" << std::endl;
        std::cin  >> Choice;
        switch (Choice) {
            case 1:
                std::cout << "Name angeben:" << std::endl;
                std::cin >> vec[customer_choice * 3 - 3];
                std::cout << "Email angeben:" << std::endl;
                std::cin >> vec[customer_choice * 3 - 2];
                std::cout << "Nummer angeben:" << std::endl;
                std::cin >> vec[customer_choice * 3 - 1];
                break;
            case 2:
                std::cout << "1. Name" << std::endl;
                std::cout << "2. Email" << std::endl;
                std::cout << "3. Nummer" << std::endl;
                std::cin >> Choice;
                switch (Choice) {
                    case 1:
                        std::cout << "Name angeben:" << std::endl;
                        std::cin >> vec[customer_choice * 3 - 3];
                        break;
                    case 2:
                        std::cout << "Email angeben:" << std::endl;
                        std::cin >> vec[customer_choice * 3 - 2];
                        break;
                    case 3:
                        std::cout << "Nummer angeben:" << std::endl;
                        std::cin >> vec[customer_choice * 3 - 1];
                        break;
                    default:
                        std::cerr << "Falsche Eingabe" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        break;
                }
                break;
            default:
                std::cerr << "Falsche Eingabe" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;

        }
    }
    else {
        std::cerr << "Fehler beim bearbeiten des Kunden." << std::endl;
    }
}



int main() {

    std::string  Email;
    std::string  Name;
    std::string Nummer;
    int choice;
    int customer_choice;
    bool ablauf;
    int del_choice;
    ablauf = true;


    const std::string filename = "vector_data.txt";

    std::vector<std::string> namesVec;

    namesVec = Load_Vector_From_File(filename);


    while(ablauf){
        std::cout << "Was moechten sie manchen?" << std::endl;
        std::cout << "1. Kunden eingeben" << std::endl;
        std::cout << "2. Kunden anzeigen" << std::endl;
        std::cout << "3. Kunden loeschen" << std::endl;
        std::cout << "4. Programm beenden" << std::endl;
        std::cout << "5. Kunden bearbeiten" << std::endl;
        std::cin >> choice;

        switch(choice) {
            case 1:
                std::cout << "Kunden eingeben" << std::endl;
                std::cout << "Name angeben:" << std::endl;
                std::cin >> Name;
                std::cout << "Email eingeben:" << std::endl;
                std::cin >> Email;
                std::cout << "Nummer eingeben:" << std::endl;
                std::cin >> Nummer;
                namesVec.push_back(Name);
                namesVec.push_back(Email);
                namesVec.push_back(Nummer);
                break;

            case 2:
                std::cout << "Kunden anzeigen" << std::endl;
                Print_Vector(namesVec);
                std::cout << std::endl;
                break;

            case 3:
                std::cout << "Kunden loeschen" << std::endl;
                std::cout << "Welchen Kunden moechten sie loeschen?" << std::endl;
                Print_Vector(namesVec);
                std::cin >> del_choice;
                Del_Customer(namesVec, del_choice);
                break;

            case 4:
                std::cout << "Programm beenden" << std::endl;
                Save_Vector_To_File(namesVec, filename);
                std::cout << "Programm wird beendet." << std::endl;
                ablauf = false;
                break;
            case 5:
                std::cout << "Welchen Kunden bearbeiten?" << std::endl;
                std::cin >> customer_choice;
                Edit_Customer(customer_choice, namesVec);
                break;

            default:
                std::cerr << "Falsche Eingabe" << std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                break;

        }
    }

    return 0;
}

