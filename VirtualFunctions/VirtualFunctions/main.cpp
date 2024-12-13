#include <iostream>
#include <fstream>
#include <string>
#include <bitset>

using namespace std;

class DefaultFile {
public:
	DefaultFile() {}

	ifstream openFile(const string& fileName) {
		ifstream file(fileName);
		if (!file.is_open()) {
			cout << "File isn't open";
		}
		return file;
	}

	virtual void Display(const string& fileName) {
		ifstream file = openFile(fileName);
		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}
		file.close();
	}
};

class AsciiFile : public DefaultFile {
public:
	void Display(const string& fileName) override {
		ifstream file = openFile(fileName);
		char ch;
		while (file.get(ch)) {
			cout << static_cast<int>(ch) << " ";
		}
		cout << endl;
	}
};

class BinaryFile : public DefaultFile {
public:
	void Display(const string& fileName) override {
		ifstream file = openFile(fileName);
		char ch;
		while (file.get(ch)) {
			bitset<8> b(ch);
			cout << b << " ";
		}
		cout << endl;
	}
};

int main() {
	DefaultFile df;
	df.Display("text.txt");
	AsciiFile af;
	af.Display("text.txt");
	BinaryFile bf;
	bf.Display("text.txt");
}