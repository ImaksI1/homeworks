#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;
class Car {
private:
    string mark;
    string model;
    string carNumber;
    int year;
    double engineVolume;
    double price;
public:
    Car(string mark, string model, string carNumber, int year, double engineVolume, double price) : mark(mark), model(model), carNumber(carNumber), year(year), engineVolume(engineVolume), price(price) {};
    string getMark() { return mark; }
    string getModel() { return model; }
    string getCarNumber() { return carNumber; }
    int getYear() { return year; }
    double getEngineVolume() { return engineVolume; }
    double getPrice() { return price; }
};

class CarDealership {
private:
    vector<Car> cars;
public:
    CarDealership(vector<Car> cars) : cars(cars) {};

    void addCar(const Car& car) {
        cars.push_back(car);
    }
    void removeCar(string carNumber) {
        cout << "After removing car with number: " << carNumber << endl;
        cars.erase(remove_if(cars.begin(), cars.end(), [carNumber](Car& car) { return car.getCarNumber() == carNumber; }), cars.end());
    }
    void printCar(Car car) {
        cout << car.getMark() << " " << car.getModel() << " " << car.getCarNumber() << " " << car.getYear() << " " << car.getEngineVolume() << " " << car.getPrice() << endl;
    }
    void printCars() {
        for (Car car : cars) {
            printCar(car);
        }
        cout << endl;
    }



    void sortCars(const string& parameter) {
        if (parameter == "mark") { //хотів зробити через switch, але він не приймає string
            sort(cars.begin(), cars.end(), [](Car& a, Car& b) { return a.getMark() < b.getMark(); });
        }
        else if (parameter == "model") {
            sort(cars.begin(), cars.end(), [](Car& a, Car& b) { return a.getModel() < b.getModel(); });
        }
        else if (parameter == "year") {
            sort(cars.begin(), cars.end(), [](Car& a, Car& b) { return a.getYear() < b.getYear(); });
        }
        else if (parameter == "engineVolume") {
            sort(cars.begin(), cars.end(), [](Car& a, Car& b) { return a.getEngineVolume() < b.getEngineVolume(); });
        }
        else if (parameter == "price") {
            sort(cars.begin(), cars.end(), [](Car& a, Car& b) { return a.getPrice() < b.getPrice(); });
        }
    }

    void searchCars(const string& parameter, const string& value) {
        for (Car car : cars) {
            if (parameter == "mark" && car.getMark() == value) {
                printCar(car);
            }
            else if (parameter == "model" && car.getModel() == value) {
                printCar(car);
            }
            else if (parameter == "carNumber" && car.getCarNumber() == value) {
                printCar(car);
            }
            else if (parameter == "year" && car.getYear() == stoi(value)) {
                printCar(car);
            }
            else if (parameter == "engineVolume" && car.getEngineVolume() == stod(value)) {
                printCar(car);
            }
            else if (parameter == "price" && car.getPrice() == stod(value)) {
                printCar(car);
            }
        }
        cout << endl;
    }
};

int main() {
    Car car1("Toyota", "Camry", "AA4321AA", 2005, 2.0, 15000);
    Car car2("Toyota", "Corolla", "AA1234AA", 2000, 1.6, 10000);
    Car car3("Toyota", "Land Cruiser", "AA1111AA", 2010, 4.0, 30000);
    CarDealership dealership({ car1, car2, car3 });
    int choice = 0;
    while (choice != 6) {
        cout << "Car Dealership Menu:" << endl;
        cout << "1. Add Car" << endl;
        cout << "2. Remove Car" << endl;
        cout << "3. Print Cars" << endl;
        cout << "4. Sort Cars" << endl;
        cout << "5. Search Cars" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string mark, model, carNumber;
            int year;
            double engineVolume, price;
            cout << "Enter mark: ";
            cin >> mark;
            cout << "Enter model: ";
            cin >> model;
            cout << "Enter car number: ";
            cin >> carNumber;
            cout << "Enter year: ";
            cin >> year;
            cout << "Enter engine volume: ";
            cin >> engineVolume;
            cout << "Enter price: ";
            cin >> price;
            Car newCar(mark, model, carNumber, year, engineVolume, price);
            dealership.addCar(newCar);
            break;
        }
        case 2: {
            string carNumber;
            cout << "Enter car number to remove: ";
            cin >> carNumber;
            dealership.removeCar(carNumber);
            break;
        }
        case 3: {
            dealership.printCars();
            break;
        }
        case 4: {
            string parameter;
            cout << "Enter parameter to sort by (mark, model, year, engineVolume, price): ";
            cin >> parameter;
            dealership.sortCars(parameter);
            break;
        }
        case 5: {
            string parameter, value;
            cout << "Enter parameter to search by (mark, model, carNumber, year, engineVolume, price): ";
            cin >> parameter;
            cout << "Enter value to search for: ";
            cin >> value;
            dealership.searchCars(parameter, value);
            break;
        }
        case 6: {
            cout << "Exiting" << endl;
            break;
        }
        default: {
            cout << "Invalid choice" << endl;
            break;
        }
        }
    }
}