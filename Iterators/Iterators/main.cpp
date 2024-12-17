#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node() : data(0), left(nullptr), right(nullptr) {}

    Node(int data, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    void Add(int elem) {
        if (elem < data) {
            if (this->left == nullptr) {
                left = new Node(elem);
            }
            else {
                this->left->Add(elem);
            }
        }
        else {
            if (this->right == nullptr) {
                right = new Node(elem);
            }
            else {
                this->right->Add(elem);
            }
        }
    }
};

class Tree {
private:
    Node* root;
public:
    Tree() : root(nullptr) {}

    void Add(int elem) {
        if (root == nullptr) {
            root = new Node(elem);
        }
        else {
            root->Add(elem);
        }
    }

    Node* getRoot() {
        return root;
    }
    void inDepth(Node* root) {
        if (root == nullptr) return;

        cout << root->data << " ";  
        inDepth(root->left);        
        inDepth(root->right);       
    }

    void inBreadth(Node* root) {
        if (root == nullptr) return;

        vector<Node*> queue;
        queue.push_back(root);  

        while (!queue.empty()) {
            Node* current = queue[0];  
            queue.erase(queue.begin());  

            cout << current->data << " ";  

            if (current->left) queue.push_back(current->left);
            if (current->right) queue.push_back(current->right);
        }
    }
};

int main() {
    Tree a;
    a.Add(10);
    a.Add(5);
    a.Add(20);
    a.Add(3);
    a.Add(15);

    cout << "Depth: ";
    a.inDepth(a.getRoot());  
    cout << endl;

    cout << "Breadth: ";
    a.inBreadth(a.getRoot());  
    cout << endl;

    return 0;
}
