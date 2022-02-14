#include <iostream>
#include <vector>
#include <functional>
#include <stack>

using std::cout;
using std::vector;
using std::function;
using std::stack;
using std::max;
using std::cin;


template<class T>
class Node {
public:
    T value;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;
    Node(T value, Node<T>* parent = nullptr) : value(value), left(nullptr), right(nullptr), parent(parent) {}
};

template<class T>
class Tree {
    Node<T>* root;
    size_t size;
    function<void(T)> show;
    function<bool(T, T)> comp;
    function<bool(T, T)> equals;
public:
    Tree(function<void(T)> show, function<bool(T, T)> comp, function<bool(T, T)> equals) : show(show), comp(comp), equals(equals) {
        root = nullptr;
        size = 0;
    }
    void insert(T value) {
        _insert(root, value, nullptr);
    }
    void IterativeInsertion(T value) {
        if (!root) {
            root = new Node<T>(value);
            ++size;
            return;
        }
        Node<T>* current = root;
        while (true) {
            if (comp(value, current->value))
                if (!current->left) { current->left = new Node<T>(value, current); ++size; break; }
                else current = current->left;
            else
                if (!current->right) { current->right = new Node<T>(value, current); ++size; break; }
                else current = current->right;
        }
    }
    void IterativePreOrder() {
        if (!root)
            return;
        stack<Node<T>*>* s = new stack<Node<T>*>;
        Node<T>* current = root;
        s->push(current);
        while (s->size() > 0) {
            current = s->top();
            s->pop();
            show(current->value);
            if (current->right)
                s->push(current->right);
            if (current->left)
                s->push(current->left);
        }
        delete s;
    }
    void print() {
        _preOrder(root);
    }
    T lowestElement() {
        return getLowestElement(root)->value;
    }
private:
    void _insert(Node<T>*& n, T value, Node<T>* parent) {
        if (n == nullptr) {
            n = new Node<T>(value, parent);
            ++size;
            return;
        }
        if (comp(value, n->value))
            _insert(n->left, value, n);
        else
            _insert(n->right, value.n);

    }
    void _preOrder(Node<T>* n) {
        if (n == nullptr)
            return;
        show(n->value);
        _preOrder(n->left);
        _preOrder(n->right);
    }
    Node<T>* getLowestElement(Node<T>* start) {
        Node<T>* current = start;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }
    Node<T>* getNode(T value) {
        Node<T>* current = root;
        while (true) {
            if (equals(current->value, value))
                break;
            if (comp(value, current->value))
                if (!current->left) { return nullptr; }
                else current = current->left;
            else
                if (!current->right) { return nullptr; }
                else current = current->right;

        }
        return current;
    }
public:
    void IterativeErasing(T value) {
        Node<T>* nodeToErase = getNode(value);
        if (nodeToErase)
            eraseNode(nodeToErase);
        else cout << "\nThis value doesn't exists in the tree\n";
    }
    T KthElement(size_t k) {
        if (k > size || k == 0)
            return T();
        stack<Node<T>*>* s = new stack<Node<T>*>;
        Node<T>* current = root;
        size_t counter = 0;
        while (current != nullptr || s->empty() == false) {
            while (current) {
                s->push(current);
                current = current->left;
            }
            ++counter;
            current = s->top();
            s->pop();
            if (counter == k) {
                delete s;
                return current->value;
            }
            current = current->right;
        }
        return T();
    }
    int height() {
        return _height(root);
    }
    T kthElementRecursive(size_t k) {
        if (k > size || k == 0)
            return T();
        T value = T();
        size_t pos = 0;
        bool stop = false;
        _kth(root, pos, k, value, stop);
        return value;
    }

    int HeightWithoutRecursion() {
        stack<Node<T>*>* s = new stack<Node<T>*>;
        vector<int> s2;
        Node<T>* current = root;
        while (current != nullptr || s->empty() == false) {
            for (int i = 0; i < s2.size(); ++i) {
                if (s2[i] == -2) {
                    if (i - 1 >= 0 && i - 2 >= 0) {
                        if (s2[i - 1] != -2 && s2[i - 2] != -2) {
                            int first = i - 1;
                            int second = i - 2;
                            s2[i] = max(s2[first], s2[second]) + 1;
                            s2.erase(s2.begin() + first);
                            s2.erase(s2.begin() + second);
                            break;
                        }
                    }
                    break;
                }
            }
            while (current != nullptr) {
                s->push(current);
                s2.insert(s2.begin(), -2);
                current = current->left;
            }
            current = s->top();
            if (current->left == nullptr && current->right == nullptr) {
                s2[0] = 0;
            }
            else if (current->left == nullptr || current->right == nullptr) {
                s2.insert(s2.begin(), -1);
            }
            s->pop();
            current = current->right;
        }
        while (s2.size() > 1) {
            for (int i = 0; i < s2.size(); ++i) {
                if (s2[i] == -2) {
                    if (i - 1 >= 0 && i - 2 >= 0) {
                        if (s2[i - 1] != -2 && s2[i - 2] != -2) {
                            int first = i - 1;
                            int second = i - 2;
                            s2[i] = max(s2[first], s2[second]) + 1;
                            s2.erase(s2.begin() + first);
                            s2.erase(s2.begin() + second);
                            break;
                        }
                    }
                    break;
                }
            }
        }
        int h = s2[0];
        s2.clear();
        delete s;
        return s2[0];
    }
private:
    void eraseNode(Node<T>* e) {
        Node<T>* n = e;
        while (n) {
            if (n->left == nullptr && n->right == nullptr) {
                if (n == root) {
                    delete root;
                    root = nullptr;
                    --size;
                }
                else if (n->parent->left == n) {
                    Node<T>* nodeToErase = n;
                    n->parent->left = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                else if (n->parent->right == n) {
                    Node<T>* nodeToErase = n;
                    n->parent->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                n = nullptr;
            }
            else if (n->left == nullptr && n->right != nullptr) {
                if (n == root) {
                    Node<T>* nodeToErase = root;
                    n->right->parent = nullptr;
                    root = n->right;
                    nodeToErase->right = nullptr;
                    delete nodeToErase;
                    --size;
                }
                else if (n->parent->left == n) {
                    n->parent->left = n->right;
                    n->right->parent = n->parent;
                    n->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                else if (n->parent->right == n) {
                    n->parent->right = n->right;
                    n->right->parent = n->parent;
                    n->right = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                n = nullptr;
            }
            else if (n->left != nullptr && n->right == nullptr) {
                if (n == root) {
                    Node<T>* nodeToErase = root;
                    n->left->parent = nullptr;
                    root = n->left;
                    nodeToErase->left = nullptr;
                    delete nodeToErase;
                    --size;
                }
                else if (n->parent->left == n) {
                    n->parent->left = n->left;
                    n->left->parent = n->parent;
                    n->left = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                else if (n->parent->right == n) {
                    n->parent->right = n->left;
                    n->left->parent = n->parent;
                    n->left = nullptr;
                    n->parent = nullptr;
                    delete n;
                    --size;
                }
                n = nullptr;
            }
            else {
                Node<T>* aux = getLowestElement(n->right);
                n->value = aux->value;
                n = aux;
            }
        }
    }
    int _height(Node<T>* node) {
        if (!node)
            return -1;
        return max(_height(node->left), _height(node->right)) + 1;
    }
    void _kth(Node<T>* n, size_t& pos, const size_t& k, T& value, bool& stop) {
        if (!n || stop == true)
            return;
        _kth(n->left, pos, k, value, stop);
        ++pos;
        if (pos == k) {
            value = n->value;
            stop = true;
            return;
        }
        _kth(n->right, pos, k, value, stop);
    }
};


// Implementar un método para hallar la altura del arbol

int main() {

    auto equals = [](int a, int b) -> bool {
        return a == b;
    };

    void (*show)(int) = [](int a) -> void {
        cout << a << " ";
    };

    bool (*comp)(int, int) = [](int a, int b) -> bool {
        return a < b;
    };

    Tree<int>* tree = new Tree<int>(show, comp, equals);
    tree->IterativeInsertion(9);
    tree->IterativeInsertion(5);
    tree->IterativeInsertion(12);
    tree->IterativeInsertion(3);
    tree->IterativeInsertion(7);
    tree->IterativeInsertion(10);
    tree->IterativeInsertion(14);
    tree->IterativeInsertion(2);
    tree->IterativeInsertion(6);
    tree->IterativeInsertion(8);
    cout << "\n";
    tree->IterativePreOrder();
    cout << "\nThe 7th element in the tree is " << tree->KthElement(7) << "\n";
    cout << "\nThe 7th element in the tree is (with recursion) " << tree->kthElementRecursive(7) << "\n";
    tree->IterativeErasing(5);
    cout << "\n";
    tree->IterativePreOrder();
    cout << "\nThe height of the tree is " << tree->height() << "\n";
    cout << "\nThe height of the tree (without recursion) is " << tree->HeightWithoutRecursion() << "\n";
    delete tree;
    return 0;
}