#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Item {
private:
	string name;
	string category;
	double price;
	int amount;
public:
	Item(string Name, string Category, double Price, int Amount) :
		name(Name), category(Category), price(Price), amount(Amount) {
	}

	string getName() { return name; }
	string getCategory() { return category; }
	double getPrice() { return price; }
	int getAmount() { return amount; }

	void setPrice(double Price) { price = Price; }
	void setAmount(int Amount) { amount = Amount; }
};

class Store {
private:
	vector<Item> items;
	string path;
public:
	Store(const string& Path) {
		path = Path;
		ifstream file(path);
		string line;
		while (getline(file, line)) {
			string name = line.substr(0, line.find(';'));
			line = line.substr(line.find(';') + 1);
			string category = line.substr(0, line.find(';'));
			line = line.substr(line.find(';') + 1);
			double price = stod(line.substr(0, line.find(';')));
			line = line.substr(line.find(';') + 1);
			int amount = stoi(line);
			items.push_back(Item(name, category, price, amount));
		}
		file.close();
	}

	void saveItems() {
		ofstream file(path);
		for (Item item : items) {
			file << item.getName() << ";" << item.getCategory() << ";" << item.getPrice() << ";" << item.getAmount() << endl;
		}
		file.close();
	}
	void addItem(const string& name, const string& category, double price, int amount) {
		items.push_back(Item(name, category, price, amount));
		saveItems();
	}

	void printItems() {
		for (Item item : items) {
			cout << item.getName() << " " << item.getCategory() << " " << item.getPrice() << " " << item.getAmount() << endl;
		}
	}

	void printItemByName(const string& name) {
		for (Item item : items) {
			if (item.getName() == name) {
				cout << item.getName() << " " << item.getCategory() << " " << item.getPrice() << " " << item.getAmount() << endl;
			}
		}
	}

	void updateItem(const string& name, double price, int amount) {
		for (Item& item : items) {
			if (item.getName() == name) {
				item.setPrice(price);
				item.setAmount(amount);
				saveItems();
				break;
			}
		}
	}

	void deleteItem(const string& name) {
		for (int i = 0; i < items.size(); i++) {
			if (items[i].getName() == name) {
				items.erase(items.begin() + i);
				saveItems();
			}
		}
	}


};


int main() {
	Store store("items.txt");
	store.addItem("Iphone", "smartphone", 1000.0, 5);
	store.addItem("Msi", "laptop", 1300.0, 10);
	store.addItem("Samsung", "TV", 800.0, 7);
	store.printItems();
	cout << endl;
	store.printItemByName("Iphone");
	cout << endl;
	store.updateItem("Iphone", 1200.0, 6);
	store.printItems();
	cout << endl;
	store.deleteItem("Msi");
	store.printItems();
	cout << endl;
}