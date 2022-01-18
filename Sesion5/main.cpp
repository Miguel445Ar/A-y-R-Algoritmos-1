#include <iostream>
#include <string>
#include <vector>
#include <functional>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::function;

typedef unsigned int us;


template<class T>
class Node {
public:
    T value;
    Node<T>* next;
    Node(T value, Node<T>* next = nullptr): value(value), next(next) {}
};

template<class T>
class LinkedList {
    Node<T>* head;
    Node<T>* top;
    us size;
public:
    LinkedList(){
        head = nullptr;
        top = nullptr;
        size = 0;
    }
    ~LinkedList(){
        while(size > 0)
            popFront();
    }
    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
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
    void pushBack(T value){
        Node<T>* newNode = new Node<T>(value);
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
    void print(function<void(T)> show){
        Node<T>* aux = head;
        while (aux != nullptr) {
            show(aux->value);
            aux = aux->next;
        }
        cout << "nullptr\n";
    }
    void insertInPos(T value,us pos) {
        if(pos <= 0){
            pushFront(value);
            return;
        }
        if(pos >= size){
            pushBack(value);
            return;
        }
        Node<T>* aux = head;
        for(us i = 0; i<pos-1;++i)
            aux = aux->next;
        Node<T>* newNode = new Node<T>(value);
        newNode->next = aux->next;
        aux->next = newNode;
        ++size;
    }
    void popBack(){
        if(size == 1){
            delete head;
            head = nullptr;
            top = nullptr;
            --size;
            return;
        }
        Node<T>* aux = head;
        for(size_t i = 0; i<size-2;++i)
            aux = aux->next;
        top = aux;
        aux = aux->next;
        top->next = nullptr;
        delete aux;
        --size;
    }
    void popFront(){
        Node<T>* aux = head;
        head = head->next;
        aux->next = nullptr;
        if(size == 1)
            top = nullptr;
        delete aux;
        --size;
    }
    void eraseInPos(us pos){
        if (pos <= 0) {
            popFront();
            return;
        }
        if (pos >= size - 1){
            popBack();
            return;
        }
        Node<T>* aux = head;
        for(us i = 0; i<pos-1;++i)
            aux = aux->next;
        Node<T>* nodeToErase  = aux->next;
        aux->next = nodeToErase->next;
        nodeToErase->next = nullptr;
        delete nodeToErase;
        --size;


    }
    void invertir(){
        Node<T>* res = _invertir(head);
        head->next = nullptr;
        head = top;
        top = res;
    }
private:
    Node<T>*& _invertir(Node<T>*& n){
        if (n->next == nullptr)
            return n;
        Node<T>* node = _invertir(n->next);
        node->next = n;
        return n;
    }
public:
    void invertir2(){
        Node<T>* aux1 = nullptr;
        Node<T>* aux2 = head;
        Node<T>* aux3 = head->next;
        while(true){
            aux2->next = aux1;
            if(aux3 == nullptr)
                break;
            aux1 = aux2;
            aux2 = aux3;
            aux3 = aux3->next;
        }
        top = head;
        head = aux2;
    }
};

class Persona {
    unsigned int dni;
    string nombre;
public:
    Persona(unsigned int dni, string nombre): dni(dni), nombre(nombre) {}
    string mostrar(){
        return std::to_string(dni) + " " + nombre;
    }
};

int main() {
    LinkedList<Persona>* lista = new LinkedList<Persona>;
    auto show = [](Persona a) -> void {
        cout << a.mostrar() << "\n";
    };
    lista->pushFront(Persona(556656,"Miguel"));
    lista->pushFront(Persona(23434,"Daniel"));
    lista->pushFront(Persona(234234,"Alonso"));
    lista->pushBack(Persona(13123,"Maria"));
    lista->print(show);
    cout << "\n";
    lista->insertInPos(Persona(45562321,"Juan"),3);
    lista->print(show);

    // Invertir Lista Simplemente Enlazada Recursivamente

    /*lista->invertir();
    cout << "\n";
    lista->print(show);
    lista->invertir();
    cout << "\n";
    lista->print(show);*/

    // Invertir Lista Simplemente Enlazada Iterativamente
    lista->invertir2();
    cout << "\n";
    lista->print(show);
    /*lista->popFront();
    cout << "\n";
    lista->print(show);
    lista->popBack();
    cout << "\n";
    lista->print(show);*/
    lista->eraseInPos(2);
    cout << "\n";
    lista->print(show);
    delete lista;
    return 0;
}