#include <iostream>
#include <string>

using namespace std;

enum Gender {
    male, female
};

class Pet {
protected:
    string name;
    int age;
    int weight;
    Gender gender;
    string colour;
    string breed;
public:
    Pet(const string& name, int age, int weight, Gender gender, const string& colour, const string& breed) :
        name(name), age(age), weight(weight), gender(gender), colour(colour), breed(breed) {
    }

    virtual void showInfo() const {
        cout << "Name: " << name << ", Age: " << age << ", Weight: " << weight
            << ", Gender: " << (gender == male ? "Male" : "Female")
            << ", Colour: " << colour << ", Breed: " << breed;
    }
};

class Dog : public Pet { 
private:
    bool isKnowCommands;
public:
    Dog(const string& name, int age, int weight, Gender gender, const string& colour, const string& breed, bool isKnowCommands) :
        Pet(name, age, weight, gender, colour, breed), isKnowCommands(isKnowCommands) {
    }

    void showInfo() const override {
        Pet::showInfo();
        cout << ", Knows commands: " << (isKnowCommands ? "Yes" : "No") << endl;
    }
};

class Cat : public Pet { 
private:
    int sleepTime;
public:
    Cat(const string& name, int age, int weight, Gender gender, const string& colour, const string& breed, int sleepTime) :
        Pet(name, age, weight, gender, colour, breed), sleepTime(sleepTime) {
    }

    void showInfo() const override {
        Pet::showInfo();
        cout << ", Sleeping time: " << sleepTime << endl;
    }
};

class Parrot : public Pet { 
private:
    bool isCanTalk;
public:
    Parrot(const string& name, int age, int weight, Gender gender, const string& colour, const string& breed, bool isCanTalk) :
        Pet(name, age, weight, gender, colour, breed), isCanTalk(isCanTalk) {
    }

    void showInfo() const override {
        Pet::showInfo();
        cout << ", Can talk: " << (isCanTalk ? "Yes" : "No") << endl;
    }
};

int main() {
    string name1 = "Buddy", name2 = "Kitty", name3 = "Polly";
    string colour1 = "Brown", colour2 = "White", colour3 = "Green";
    string breed1 = "Labrador", breed2 = "Persian", breed3 = "Macaw";

    Dog dog(name1, 5, 20, male, colour1, breed1, true);
    Cat cat(name2, 3, 4, female, colour2, breed2, 15);
    Parrot parrot(name3, 2, 1, male, colour3, breed3, true);


    dog.showInfo();
    cat.showInfo();
    parrot.showInfo();

    return 0;
}
