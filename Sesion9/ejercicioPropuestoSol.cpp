#include <iostream>
#include <functional>
#include <string>

using std::cout;
using std::cin;
using std::function;
using std::string;


template<class T>
class Node {
public:
    T value;
    Node<T>* next;
    Node<T>* back;
    Node(T value, Node<T>* next = nullptr, Node<T>* back = nullptr) : value(value), next(next), back(back) {}
};

template<class T>
class DoubleLinkedList {
    Node<T>* head; // Inicia de la lista;
    Node<T>* top; // Fin de la lista;
    size_t size;
    function<void(T)> show;
    Node<T>* aux;
public:
    DoubleLinkedList(function<void(T)> show) : show(show) {
        head = top = aux = nullptr;
        size = 0;
    }
    ~DoubleLinkedList() {
        while (size > 0)
            popBack();
    }
    void pushFront(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (size == 0) {
            head = top = newNode;
            ++size;
            return;
        }
        newNode->next = head;
        head->back = newNode;
        head = newNode;
        ++size;
    }
    void pushBack(T value) {
        Node<T>* newNode = new Node<T>(value);
        if (size == 0) {
            head = top = newNode;
            ++size;
            return;
        }
        top->next = newNode;
        newNode->back = top;
        top = newNode;
        ++size;
    }
    void popBack() {
        if (size == 0)
            return;
        if (size == 1) {
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
    void popFront() {
        if (size == 0)
            return;
        if (size == 1) {
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
    void insertInPos(T value, size_t pos) {
        if (pos <= 0) {
            pushFront(value);
            return;
        }
        if (pos >= size) {
            pushBack(value);
            return;
        }
        aux = head;
        for (size_t i = 0; i < pos - 1; ++i)
            aux = aux->next;
        Node<T>* newNode = new Node<T>(value);
        newNode->back = aux;
        newNode->next = aux->next;
        aux->next = newNode;
        newNode->next->back = newNode;
        ++size;
    }
    void eraseInPos(int pos) {
        if (pos == 0) {
            popFront();
            return;
        }
        if (pos == size - 1) {
            popBack();
            return;
        }
        if (pos >= size || pos < 0)
            throw "This is not possible";
        aux = head;
        for (size_t i = 0; i < pos - 1; ++i)
            aux = aux->next;
        Node<T>* nodeToErase = aux->next;
        // Preparamos a la lista
        aux->next = nodeToErase->next;
        nodeToErase->next->back = aux;
        // Desconectamos el nodo
        nodeToErase->next = nodeToErase->back = nullptr;
        delete nodeToErase;
        --size;
    }
    void print() {
        aux = head;
        while (aux != nullptr) {
            this->show(aux->value);
            aux = aux->next;
        }
        // cout << "nullptr\n";
    }
    Node<T>*& Top() {
        return this->top;
    }
    Node<T>*& Head() {
        return this->head;
    }
    void setTop(Node<T>*& n){
        this->top = n;
        this->size++;
    }
};

class Solution {
    function<void(char)> show;
public:
    Solution() {
        auto show = [](char a) -> void {
            cout << a;
        };
        this->show = show;
    }
    Node<char>*& _read(size_t& i, size_t& f, size_t& it, const string& line) {
        DoubleLinkedList<char>* lista = new DoubleLinkedList<char>(this->show);
        for (it = i; it <= f; ++it) {
            if (line[it] == '[') {
                i = it + 1;
                Node<char>* aux = _read(i, f, it, line);
                if (aux){
                    aux->next = lista->Head();
                } 
                if (lista->Head()) {
                    lista->Head()->back = aux;
                } else {
                    lista->setTop(aux);
                }
                if(it + 1 > f)
                    break;
                ++it;
            }
            if (line[it] == ']') {
                return lista->Top();
            }
            lista->pushBack(line[it]);
        }
        return lista->Top();
    }
    void read(const string& line) {
        size_t init = 0, end = line.size() - 1, it = 0;
        Node<char>* ends = _read(init, end, it, line);
        DoubleLinkedList<char>* res = new DoubleLinkedList<char>(this->show);
        while (ends != nullptr) {
            res->pushFront(ends->value);
            ends = ends->back;
        }
        res->print();
        delete res;
        while (ends != nullptr) {
            Node<char>* aux = ends;
            ends = ends->back;
            delete aux;
        }
    }
};

// Solución de LinkedList.pdf

int main() {
    Solution* aux = new Solution;
    aux->read("[Miguel]XD");
    delete aux;
    return 0;
}