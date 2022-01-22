#include <iostream>
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
    void popFront(){
        if(size == 0)
            return;
        if(size == 1){
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        // Nos movemos al siguiente del inicio
        head = head->next;
        // Desconectamos el nodo a eliminar
        head->back->next = nullptr;
        // Eliminamos el nodo
        delete head->back;
        // Seteamos a nullptr el puntero back del head
        head->back = nullptr;
        --size;
    }
    void insertInPos(T value, size_t pos){
        if(pos <= 0){
            pushFront(value);
            return;
        }
        if (pos >= size){
            pushBack(value);
            return;
        }
        aux = head;
        for(size_t i = 0; i<pos-1;++i)
            aux = aux->next;
        Node<T>* newNode = new Node<T>(value);
        newNode->back = aux;
        newNode->next = aux->next;
        aux->next = newNode;
        newNode->next->back = newNode;
        ++size;
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
    lista->popFront();
    lista->print();
    lista->insertInPos(4,2);
    lista->print();
    delete lista;
    return 0;
}