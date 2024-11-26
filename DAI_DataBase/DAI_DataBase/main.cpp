#include <iostream>
#include <string>
using namespace std;

struct ViolationNode {
    string violation;
    ViolationNode* next;

    ViolationNode(const string& v) : violation(v), next(nullptr) {}
};

struct Node {
    string carNumber;
    ViolationNode* violations;
    Node* left;
    Node* right;

    Node(const string& c) : carNumber(c), violations(nullptr), left(nullptr), right(nullptr) {}
};

class TrafficDatabase {
private:
    Node* root;

    Node* insert(Node* node, const string& carNumber, const string& violation) {
        if (node == nullptr) {
            Node* newNode = new Node(carNumber);
            newNode->violations = new ViolationNode(violation);
            return newNode;
        }
        if (carNumber < node->carNumber) {
            node->left = insert(node->left, carNumber, violation);
        }
        else if (carNumber > node->carNumber) {
            node->right = insert(node->right, carNumber, violation);
        }
        else {
            addViolation(node->violations, violation);
        }
        return node;
    }


    void addViolation(ViolationNode*& head, const string& violation) {
        if (head == nullptr) {
            head = new ViolationNode(violation);
            return;
        }

        ViolationNode* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new ViolationNode(violation);
    }

    void printTree(Node* node) {
        if (node == nullptr)
            return;
        printTree(node->left);
        cout << "Car Number: " << node->carNumber << "\nViolations:\n";
        printViolations(node->violations);
        printTree(node->right);
    }

    void printViolations(ViolationNode* head) {
        ViolationNode* current = head;
        while (current != nullptr) {
            cout << "  - " << current->violation << endl;
            current = current->next;
        }
    }

    Node* search(Node* node, const string& carNumber) {
        if (node == nullptr || node->carNumber == carNumber) {
            return node;
        }
        if (carNumber < node->carNumber) {
            return search(node->left, carNumber);
        }
        return search(node->right, carNumber);
    }

    void deleteTree(Node* node) {
        if (node == nullptr)
            return;
        deleteTree(node->left);
        deleteTree(node->right);
        deleteViolations(node->violations);
        delete node;
    }

    void deleteViolations(ViolationNode* head) {
        while (head != nullptr) {
            ViolationNode* temp = head;
            head = head->next;
            delete temp;
        }
    }
public:
    TrafficDatabase() : root(nullptr) {}

    ~TrafficDatabase() {
        deleteTree(root);
    }

    void addTicket(const string& carNumber, const string& violation) {
        root = insert(root, carNumber, violation);  
    }


    void printDatabase() {
        printTree(root);
    }

    void printCarData(const string& carNumber) {
        Node* result = search(root, carNumber);
        if (result == nullptr) {
            cout << "Car number " << carNumber << " not found.\n";
        }
        else {
            cout << "Car Number: " << result->carNumber << "\nViolations:\n";
            printViolations(result->violations);
        }
    }
};

int main() {
    TrafficDatabase db;

    db.addTicket("AB123CD", "Speeding");
    db.addTicket("AB123CD", "Illegal parking");
    db.addTicket("XY987ZT", "Running a red light");
    db.addTicket("LM456OP", "No seatbelt");

    cout << "Full database:\n";
    db.printDatabase();

    cout << "\nSearch for car AB123CD:\n";
    db.printCarData("AB123CD");

    cout << "\nSearch for car XY987ZT:\n";
    db.printCarData("XY987ZT");

    return 0;
}
