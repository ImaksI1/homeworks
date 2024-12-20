#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Firm {
	string name;
	string owner;
	string number;
	string address;
	string activity;
};

class Directory {
private:
	vector<Firm> firms;
	string path;

	void loadFirms() {
		ifstream file(path);
		if (!file) {
			cout << "File isn't open" << endl;
		}
		Firm firm;
		while (getline(file, firm.name)) {
			getline(file, firm.owner);
			getline(file, firm.number);
			getline(file, firm.address);
			getline(file, firm.activity);
			firms.push_back(firm);
		}
		file.close();
	}

	void saveFirms() {
		ofstream file(path);
		if (!file) {
			cout << "File isn't open" << endl;
		}
		for (const auto& firm : firms) {
			file << firm.name << "\n"
				<< firm.owner << "\n"
				<< firm.number << "\n"
				<< firm.address << "\n"
				<< firm.activity << "\n";
		}
		file.close();
	}

public:
	Directory(const string& path) : path(path) {
		loadFirms();  
	}

	void addFirm(const string& name, const string& owner, const string& number, const string& address, const string& activity) {
		firms.push_back({ name, owner, number, address, activity });
		saveFirms();  
	}

	vector<Firm> searchByName(const string& name) {
		vector<Firm> result;
		for (const auto& firm : firms) {
			if (firm.name == name)
				result.push_back(firm);
		}
		return result;
	}

	vector<Firm> searchByOwner(const string& owner) {
		vector<Firm> result;
		for (const auto& firm : firms) {
			if (firm.owner == owner)
				result.push_back(firm);
		}
		return result;
	}

	vector<Firm> searchByNumber(const string& number) {
		vector<Firm> result;
		for (const auto& firm : firms) {
			if (firm.number == number)
				result.push_back(firm);
		}
		return result;
	}

	vector<Firm> searchByActivity(const string& activity) {
		vector<Firm> result;
		for (const auto& firm : firms) {
			if (firm.activity == activity)
				result.push_back(firm);
		}
		return result;
	}

	void displayAll() {
		for (const auto& firm : firms) {
			cout << "Name: " << firm.name << "\n"
				<< "Owner: " << firm.owner << "\n"
				<< "Phone: " << firm.number << "\n"
				<< "Address: " << firm.address << "\n"
				<< "Activity: " << firm.activity << "\n\n";
		}
	}
};

int main() {
	Directory directory("text.txt");

	directory.addFirm("Tesla", "Elon Musk", "123456789", "Wall street", "Cars");
	directory.addFirm("Microsoft", "Bill Gates", "987654321", "Grove street", "IT products");

	auto nameResults = directory.searchByName("Tesla");
	cout << "Search by name:\n";
	for (const auto& firm : nameResults) {
		cout << "Name: " << firm.name << "\n"
			<< "Owner: " << firm.owner << "\n"
			<< "Phone: " << firm.number << "\n"
			<< "Address: " << firm.address << "\n"
			<< "Activity: " << firm.activity << "\n\n";
	}

	auto ownerResults = directory.searchByOwner("Bill Gates");
	cout << "Search by owner:\n";
	for (const auto& firm : ownerResults) {
		cout << "Name: " << firm.name << "\n"
			<< "Owner: " << firm.owner << "\n"
			<< "Phone: " << firm.number << "\n"
			<< "Address: " << firm.address << "\n"
			<< "Activity: " << firm.activity << "\n\n";
	}

	auto phoneResults = directory.searchByNumber("123456789");
	cout << "Search by phone:\n";
	for (const auto& firm : phoneResults) {
		cout << "Name: " << firm.name << "\n"
			<< "Owner: " << firm.owner << "\n"
			<< "Phone: " << firm.number << "\n"
			<< "Address: " << firm.address << "\n"
			<< "Activity: " << firm.activity << "\n\n";
	}

	auto activityResults = directory.searchByActivity("Bakery");
	cout << "Search by activity:\n";
	for (const auto& firm : activityResults) {
		cout << "Name: " << firm.name << "\n"
			<< "Owner: " << firm.owner << "\n"
			<< "Phone: " << firm.number << "\n"
			<< "Address: " << firm.address << "\n"
			<< "Activity: " << firm.activity << "\n\n";
	}

	cout << "\nAll entries:\n";
	directory.displayAll();
}
