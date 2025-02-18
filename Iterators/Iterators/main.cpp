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

    class DepthIterator {
    private:
        vector<Node*> nodes;

    public:
        DepthIterator(Node* root) {
            if (root) {
                nodes.push_back(root);
            }
        }

        bool hasNext() {
            return !nodes.empty();
        }

        int next() {
            if (nodes.empty()) {
                throw out_of_range("No more elements");
            }

            Node* current = nodes.back();
            nodes.pop_back();

            if (current->right) {
                nodes.push_back(current->right);
            }

            if (current->left) {
                nodes.push_back(current->left);
            }

            return current->data;
        }
    };

    class WidthIterator {
    private:
        vector<Node*> nodes;
        size_t index;

    public:
        WidthIterator(Node* root) : index(0) {
            if (root) {
                nodes.push_back(root);
            }
        }

        bool hasNext() {
            return index < nodes.size();
        }

        int next() {
            if (index >= nodes.size()) {
                throw out_of_range("No more elements");
            }

            Node* current = nodes[index++];

            if (current->left) {
                nodes.push_back(current->left);
            }

            if (current->right) {
                nodes.push_back(current->right);
            }

            return current->data;
        }
    };

    DepthIterator depthIterator() {
        return DepthIterator(root);
    }

    WidthIterator widthIterator() {
        return WidthIterator(root);
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
    Tree::DepthIterator depthIter = tree.depthIterator();
    while (depthIter.hasNext()) {
        cout << depthIter.next() << " ";
    }
    cout << endl;

    cout << "in Width: ";
    Tree::WidthIterator widthIter = tree.widthIterator();
    while (widthIter.hasNext()) {
        cout << widthIter.next() << " ";
    }
    cout << endl;

    return 0;
}
