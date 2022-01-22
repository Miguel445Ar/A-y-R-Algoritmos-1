#include <iostream>
#include <string>
#include <functional>

using std::cout;
using std::cin;
using std::function;

template<class T>
class Node {
public:
    T value;
    Node<T>* next;
    Node<T>* back;
    Node(T value, Node<T>* next = nullptr, Node<T>* back = nullptr): value(value), next(next), back(back){}
};

template<class T>
class DoubleLinkedList{
    Node<T>* head; // Inicia de la lista;
    Node<T>* top; // Fin de la lista;
    size_t size;
    function<void(T)> show;
    Node<T>* aux;
public:
    DoubleLinkedList(function<void(T)> show): show(show) {
        head = top = aux = nullptr;
        size = 0;
    }
    void pushFront(T value){
        Node<T>* newNode = new Node<T>(value);
        if(size == 0){
            head = top = newNode;
            ++size;
            return;
        }
        newNode->next = head;
        head->back = newNode;
        head = newNode;
        ++size;
    }
    void pushBack(T value){
        Node<T>* newNode = new Node<T>(value);
        if(size == 0){
            head = top = newNode;
            ++size;
            return;
        }
        top->next = newNode;
        newNode->back = top;
        top = newNode;
        ++size;
    }
    void popBack(){
        if(size == 0)
            return;
        if(size == 1){
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        top = top->back;
        top->next->back = nullptr;
        delete top->next;
        top->next = nullptr;
        --size;
    }
    void print(){
        aux = head;
        while(aux != nullptr){
            this->show(aux->value);
            aux = aux->next;
        }
        cout << "nullptr\n";
    }
};

int main(){
    auto show = [](int a) -> void {
        cout << a << "-->";
    };
    DoubleLinkedList<int>* lista = new DoubleLinkedList<int>(show);
    lista->pushFront(5);
    lista->pushFront(6);
    lista->pushFront(7);
    lista->pushFront(9);
    lista->pushFront(10);
    lista->pushFront(2);
    lista->pushBack(20);
    lista->print();
    lista->popBack();
    lista->print();
    delete lista;
    return 0;
}