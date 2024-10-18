#include <iostream>
#include <string>

using namespace std;

class People {
private:
    string name;
    string surname;
    int age;
public:
    People() {
        name = "Bob"; 
        surname = "Cukerberg";
        age = 19;
    }
    People(const string& name, const string& surname, int age) : name(name), surname(surname), age(age) {}

    People(const People& other_people) : name(other_people.name), surname(other_people.surname), age(other_people.age) {}

    void PrintPeople() const {
        cout << "Name: " << name << ", Surname: " << surname << ", Age: " << age << endl;
    }
};

class Flat {
private:
    People* residents;
    int numResidents;
    int capacity;
public:
    Flat() : numResidents(0), capacity(2) {
        residents = new People[capacity];
    }


    Flat(const Flat& other_residents)
        : numResidents(other_residents.numResidents), capacity(other_residents.capacity) {
        residents = new People[capacity];
        for (int i = 0; i < numResidents; i++) {
            residents[i] = other_residents.residents[i];
        }
    }

    void addPeople(const People& people) {
        if (numResidents >= capacity) {
            capacity *= 2;
            People* newresidents = new People[capacity];
            for (int i = 0; i < numResidents; i++) {
                newresidents[i] = residents[i];
            }
            delete[] residents;
            residents = newresidents;
        }
        residents[numResidents++] = people;
    }

    void PrintResidents() const {
        cout << "Residents of the flat:" << endl;
        for (int i = 0; i < numResidents; ++i) {
            residents[i].PrintPeople();
        }
    }
};

class House {
private:
    Flat* flats;
    int numFlats;
    int capacity;
public:
    House() : numFlats(0), capacity(2) {
        flats = new Flat[capacity];
    }

    House(const House& other_flats)
        : numFlats(other_flats.numFlats), capacity(other_flats.capacity) {
        flats = new Flat[capacity];
        for (int i = 0; i < numFlats; i++) {
            flats[i] = other_flats.flats[i];
        }
    }

    void addFlat(const Flat& other_flat) {
        if (numFlats >= capacity) {
            capacity *= 2;
            Flat* newflats = new Flat[capacity];
            for (int i = 0; i < numFlats; i++) {
                newflats[i] = flats[i];
            }
            delete[] flats;
            flats = newflats;
        }
        flats[numFlats++] = other_flat;
    }

    ~House() {
        delete[] flats; 
    }

    void PrintFlats() const {
        cout << "Flats in the house:" << endl;
        for (int i = 0; i < numFlats; i++) {
            flats[i].PrintResidents();
        }
    }
};

int main() {
    Flat flat1;
    flat1.addPeople(People("Maks", "Jonson", 25));
    flat1.addPeople(People("John", "Smith", 30));

    Flat flat2;
    flat2.addPeople(People("Bob", "Brown", 22));

    House house;
    house.addFlat(flat1);
    house.addFlat(flat2);

    house.PrintFlats();
}
