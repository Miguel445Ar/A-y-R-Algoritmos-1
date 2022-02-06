#include <iostream>
#include <vector>
#include <functional>

using std::cout;
using std::vector;
using std::function;

/*
bool binarySearch(const vector<int>& arr, size_t i, size_t f, int value){
    if (i == f)
        return arr[i] == value;
    size_t mid = (i + f) / 2;
    if(arr[mid] == value)
        return true;
    if(value < arr[mid])
        return binarySearch(arr,i,mid-1,value);
    else
        return binarySearch(arr,mid+1,f,value);

}

int main(){
    vector<int> numeros = {1,3,5,9,10,15,20};
    if(binarySearch(numeros,0,numeros.size() - 1, 15))
        cout << "\nSe encontro :D\n";
    else
        cout << "\nNo se encontro :(\n"; 
    return 0;
}*/

template<class T>
class Node {
public:
    T value;
    Node<T>* left;
    Node<T>* right;
    Node(T value): value(value), left(nullptr), right(nullptr) {}
};

template<class T>
class Tree {
    Node<T>* root;
    size_t size;
    function<void(T)> show;
    function<bool(T,T)> comp;
public:
    Tree(function<void(T)> show, function<bool(T,T)> comp): show(show), comp(comp) {
        root = nullptr;
        size = 0;
    }
    void insert(T value){
        _insert(root,value);
    }
    void print(){
        _preOrder(root);
    }
private:
    void _insert(Node<T>*& n, T value){
        if(n == nullptr){
            n = new Node<T>(value);
            return;
        }
        if(comp(value,n->value))
            _insert(n->left,value);
        else
            _insert(n->right,value);

    }
    void _preOrder(Node<T>* n){
        if(n == nullptr)
            return;
        show(n->value);
        _preOrder(n->left);
        _preOrder(n->right);
    }
};
int main(){
    void (*show)(int) = [](int a) -> void {
        cout << a << " ";
    };
    bool (*comp)(int, int) = [](int a, int b) -> bool {
        return a < b;
    };
    Tree<int>* tree = new Tree<int>(show,comp);
    tree->insert(9);
    tree->insert(6);
    tree->insert(12);
    tree->insert(4);
    tree->insert(8);
    tree->insert(3);
    tree->insert(2);
    tree->insert(7);
    tree->insert(11);
    tree->insert(14);
    tree->insert(10);
    tree->print();
    delete tree;
    return 0;
}