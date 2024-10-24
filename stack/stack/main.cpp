#include <iostream>
#include <string>

using namespace std;
class Stack {
private:
	char* arr;
	int maxSize;
	int top;
public:
	Stack(int size) : maxSize(size), top(-1) {
		arr = new char[size];
	}
	~Stack() {
		delete[] arr;
	}
	void push(char value) {
		if (top < maxSize - 1) {
			arr[++top] = value;
		}
		else {
			cout << "Stack is full!" << endl;
		}
	}
	char pop() {
		if (top >= 0) {
			return arr[top--];
		}
		else {
			cout << "Stack is empty!" << endl;
			return -1;
		}
	}
	char peek() const {
		if (top >= 0) {
			return arr[top];
		}
		else {
			cout << "Stack is empty!" << endl;
			return -1;
		}
	}
	bool isEmpty() const {
		return top == -1;
	}
};

bool isMatchingPair(char opening, char closing) {
	return (opening == '(' && closing == ')') ||
		(opening == '{' && closing == '}') ||
		(opening == '[' && closing == ']');
}
int checkBrackets(const string& expression) {
	Stack s(expression.length());
	string result;
	for (size_t i = 0; i < expression.length(); i++) {
		char ch = expression[i];
		result += ch;
		if (ch == '(' || ch == '{' || ch == '[') {
			s.push(ch);
		}
		else if (ch == ')' || ch == '}' || ch == ']') {
			if (s.isEmpty() || !isMatchingPair(s.peek(), ch)) {
				cout << "error" << endl;
				cout << result << endl;
				return 0;
			}
			s.pop();
		}
	}
	cout << "expression is correct" << endl;
}

int main() {
	string expression = "({x-y-z} * [x + 2y] - (z + 4x));";
	checkBrackets(expression);

	expression = "([x-y-z} * [x + 2y) - {z + 4x)];";
	checkBrackets(expression);
}