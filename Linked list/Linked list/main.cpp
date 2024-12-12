#include <iostream>

using namespace std;

struct Node {
	int data;
	Node* next;

	Node(int value) : data(value), next(nullptr) {}
};

class Stack {
private:
	Node* top;
public:
	Stack() : top(nullptr) {}

	~Stack() {
		while (!isEmpty()) {
			pop();
		}
	}

	bool isEmpty() const {
		return top == nullptr;
	}

	void push(int value) {
		Node* newNode = new Node(value);
		newNode->next = top;
		top = newNode;

	}
	
	void pop() {
		if (isEmpty()) {
			cout << "Stack is empty" << endl;
			return;
		}

		Node* temp = top;
		top = top->next;
		delete temp;
	}

	int peek() {
		if (isEmpty()) {
			cout << "Stack is empty" << endl;
			return -1;
		}

		return top->data;
	}

	Node* clone() const {
		if (isEmpty()) return nullptr;

		Node* newHead = new Node(top->data);
		Node* current = top->next;
		Node* newCurrent = newHead;

		while (current) {
			newCurrent->next = new Node(current->data);  
			newCurrent = newCurrent->next;
			current = current->next;
		}

		return newHead;
	}

	Node* operator+(const Stack& other) {
		Node* newHead = clone();

		if (!newHead) return other.clone();

		Node* tail = newHead;
		while (tail->next) {
			tail = tail->next;
		}

		for (Node* current = other.top; current; current = current->next) {
			tail->next = new Node(current->data);
			tail = tail->next;
		}

		return newHead;
	}

	Node* operator*(const Stack& other) {
		Node* newHead = nullptr;
		Node* tail = nullptr;

		for (Node* currentA = top; currentA; currentA = currentA->next) {
			for (Node* currentB = other.top; currentB; currentB = currentB->next) {
				if (currentA->data == currentB->data) {
					if (!newHead) {
						Node* newHead = new Node(currentA->data); 
						Node* tail = newHead;
					}
					else {
						
						tail->next = new Node(currentA->data);
						tail = tail->next;
					}
					break;
				}
			}
		}
		return newHead;
	}


};


int main() {
	Stack stack1;
	stack1.push(10);
	stack1.push(20);
	stack1.push(30);
	cout << "Stack 1 (Peek): " << stack1.peek() << endl;

	Stack stack2;
	stack2.push(15);
	stack2.push(20);
	stack2.push(30);

	cout << "Stack 2 (Peek): " << stack2.peek() << endl;

	Node* clonedStack = stack1.clone();
	cout << "Cloned Stack 1: ";
	for (Node* current = clonedStack; current; current = current->next) {
		cout << current->data << " ";
	}
	cout << endl;

	Node* mergedStack = stack1 + stack2;
	cout << "Merged Stack (Stack1 + Stack2): ";
	for (Node* current = mergedStack; current; current = current->next) {
		cout << current->data << " ";
	}
	cout << endl;

	Node* commonStack = stack1 * stack2;
	cout << "Common elements (Stack1 * Stack2): ";
	for (Node* current = commonStack; current; current = current->next) {
		cout << current->data << " ";
	}
	cout << endl;

	stack1.pop();
	cout << "Stack 1 after pop: " << stack1.peek() << endl;

	stack1.pop();
	stack1.pop();
	stack1.pop();  
	cout << "Stack 1 after popping all elements: " << stack1.peek() << endl;


}