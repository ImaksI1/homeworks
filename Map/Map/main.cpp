#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

class Dictionary {
private:
	map<string, int> words;
	int max;
	string word;
public:
	void readFile(const string& path) {
		ifstream file(path);
		if (!file) {
			cout << "the file isn't open" << endl;
		}
		string line;
		while (getline(file, line)) {
			cout << line << endl;
		}
		cout << endl;
		file.close();
	}

	void wordFrequency(const string& path) {
		ifstream file(path);
		if (!file) {
			cout << "the file isn't open" << endl;
		}
		string rawWord, word;
		char ch;
		while (file >> rawWord) {
			for (int i = 0; i < rawWord.size(); i++) {
				ch = rawWord[i];
				if (isalpha(ch)) {
					word += (char)tolower(ch);
				}
			}
			auto it = words.find(word);
			if (it == words.end()) {
				words.insert({ word, 1 });
			}
			else {
				words[word]++;
			}
			word = "";
		}	
		for (const auto& pair : words) {
			cout << pair.first << ": " << pair.second << endl;
		}
		cout << endl;
		file.close();
	}

	void maxFrequency() {
		for (const auto& pair : words) {
			if (pair.second > max) {
				word = pair.first;
				max = pair.second;
			}
		}
		cout << word << ": " << max << endl << endl;
	}

	void outputToFile(const string& path) {
		ofstream file(path);
		if (!file) {
			cout << "the file isn't open" << endl;
		}
		for (const auto& pair : words) {
			file << pair.first << ": " << pair.second << endl;
		}
		file << endl << "max frequency - " << word << ": " << max;
		file.close();
	}

};

int main() {
	Dictionary a;
	a.readFile("input.txt");
	a.wordFrequency("input.txt");
	a.maxFrequency();
	a.outputToFile("output.txt");
}