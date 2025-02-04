#include <iostream>
#include <vector>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int data, Node* left = nullptr, Node* right = nullptr) {
        this->data = data;
        this->left = left;
        this->right = right;
    }

    void Add(int elem) {
        if (elem < data) {
            if (!left)
                left = new Node(elem);
            else
                left->Add(elem);
        }
        else {
            if (!right)
                right = new Node(elem);
            else
                right->Add(elem);
        }
    }
};

class Tree {
private:
    Node* root;

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    Tree() : root(nullptr) {}

    ~Tree() {
        clear(root);
    }

    void Add(int elem) {
        if (!root)
            root = new Node(elem);
        else
            root->Add(elem);
    }

    Node* getRoot() {
        return root;
    }

    vector<int> inDepth() {
        vector<int> result;
        if (!root) return result;

        vector<Node*> stack = { root }; 

        while (!stack.empty()) {
            Node* current = stack.back();
            stack.pop_back();
            result.push_back(current->data);

            if (current->right) stack.push_back(current->right);
            if (current->left) stack.push_back(current->left);
        }
        return result;
    }

    vector<int> inWidth() {
        vector<int> result;
        if (!root) return result;

        vector<Node*> queue = { root };  
        size_t head = 0; 

        while (head < queue.size()) {
            Node* current = queue[head++];
            result.push_back(current->data);

            if (current->left) queue.push_back(current->left);
            if (current->right) queue.push_back(current->right);
        }
        return result;
    }
};

int main() {
    Tree tree;
    tree.Add(10);
    tree.Add(5);
    tree.Add(20);
    tree.Add(3);
    tree.Add(15);

    cout << "in Depth: ";
    for (int val : tree.inDepth()) {
        cout << val << " ";
    }
    cout << endl;

    cout << "in Width: ";
    for (int val : tree.inWidth()) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}
