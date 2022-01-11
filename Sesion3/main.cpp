#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::string;

typedef unsigned short us;

class Node {
public:
    int value;
    Node* next;
    Node(int value = 0, Node* next = nullptr): value(value), next(next) {}
};

class LinkedList {
    Node* head;
    Node* top;
    us size;
public:
    LinkedList(){
        head = nullptr;
        top = nullptr;
        size = 0;
    }
    void pushFront(int value) {
        Node* newNode = new Node(value);
        if (size == 0) {
            head = newNode;
            top = newNode;
            ++size;
            return;
        }
        newNode->next = head;
        head = newNode;
        ++size;
    }
    void pushBack(int value){
        Node* newNode = new Node(value);
        if (size == 0) {
            head = newNode;
            top = newNode;
            ++size;
            return;
        }
        top->next = newNode;
        top = newNode;
        ++size;
    }
    void print(){
        Node* aux = head;
        while (aux != nullptr) {
            cout << aux->value << "-->";
            aux = aux->next;
        }
        cout << "nullptr\n";
    }
};



int main() {
    int arr[] = { 10,2,6,7,8,4 };
    // Implementación con programación funcional de una lista simplemente enlazada

    /*int size = 0;
    Node* head = nullptr; // Puntero al inicio de la lista
    Node* top = nullptr; // Puntero al final de la lista
    pushFront(head,top, 5, size);
    pushFront(head,top, 8, size);
    pushFront(head,top, 7, size);
    pushBack(head,top,10,size);
    Node* aux = head;
    while (aux != nullptr) {
        cout << aux->value << "-->";
        aux = aux->next;
    }
    cout << "nullptr\n";*/

    // Implementación con programación orientada a objetos de una lista simplemente enlazada

    LinkedList* lista = new LinkedList;
    lista->pushFront(5);
    lista->pushFront(8);
    lista->pushFront(7);
    lista->pushBack(10);
    lista->print();
    
    return 0;
}