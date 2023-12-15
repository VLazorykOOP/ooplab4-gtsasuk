#include <iostream>
#include <map>

using namespace std;

class CountryCapitalAssociation {
private:
    map<string, string> association; // Associative array for storing "country - capital" pairs
    int errorCode; // Variable to store error code

public:
    CountryCapitalAssociation() : errorCode(0) {}

    // Function to add associative entities (country - capital)
    void addAssociation(const string& country, const string& capital) {
        association[country] = capital;
    }

    // Overloading the indexing operator []
    string& operator[](const string& country) {
        auto it = association.find(country);
        if (it != association.end()) {
            errorCode = 0; // Entity exists, error code - 0
            return it->second;
        }
        else {
            errorCode = 1; // Entity does not exist, error code - 1
            // No need for static string here
            return association[country]; // Adds an empty string to the map
        }
    }

    // Overloading the output operator <<
    friend ostream& operator<<(ostream& os, const CountryCapitalAssociation& obj) {
        for (const auto& pair : obj.association) {
            os << "Country: " << pair.first << ", Capital: " << pair.second << endl;
        }
        return os;
    }

    // Overloading the input operator >>
    friend istream& operator>>(istream& is, CountryCapitalAssociation& obj) {
        string country, capital;
        cout << "Enter country: ";
        is >> country;
        cout << "Enter capital: ";
        is >> capital;
        obj.addAssociation(country, capital);
        return is;
    }

    // Function to get the error code
    int getErrorCode() const {
        return errorCode;
    }
};

int main() {
    CountryCapitalAssociation countries;

    // Adding associative entities
    countries.addAssociation("Ukraine", "Kyiv");
    countries.addAssociation("USA", "Washington");
    countries.addAssociation("France", "Paris");
    // Outputting associative entities
    cout << "Associative array:" << endl;
    cout << countries;
    // Using the indexing operator []
    cout << "Capital of Ukraine: " << countries["Ukraine"] << endl;
    if (countries["Germany"].empty()) {
        cout << "Error: Country not found." << endl;
    }
    else {
        cout << "Capital of Germany: " << countries["Germany"] << endl;
    }
    // Введення нової асоціативної сутності
    cout << "Enter a new associative entity:" << endl;
    cin >> countries;
    // Перевірка наявності помилки під час введення
    if (countries.getErrorCode() == 1) {
        cout << "Error: Country not found." << endl;
    }
    return 0;
}