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
        
    }
    void popFront(){

    }
    void eraseInPos(T value, us pos){

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
    lista->invertir();
    cout << "\n";
    lista->print(show);
    lista->invertir();
    cout << "\n";
    lista->print(show);
    return 0;
}