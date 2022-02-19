#ifndef __DLL_HPP__
#define __DLL_HPP__

#include <iostream>
#include <functional>

using std::function;


template<class T>
class DoubleLinkedList {
    template<class V>
    class Node {
        public:
        V value;
        Node<V>* next;
        Node<V>* back;
        Node(V value, Node<V>* next = nullptr, Node<V>* back = nullptr) : value(value), next(next), back(back) {}
    };
    Node<T>* head; // Inicia de la lista;
    Node<T>* top; // Fin de la lista;
    size_t size;
    Node<T>* aux;
public:
    DoubleLinkedList(){
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
    size_t Size(){
        return this->size;
    }
    class Iterator {
        Node<T>* it;
        int pos;
    public:
        Iterator(Node<T>* it, int pos): it(it), pos(pos){}
        void operator++(){
            (it)? it = it->next: NULL;
            ++pos;
        }
        void operator--(){
            (it)? it = it->back: NULL;
            --pos;
        }
        T& operator*(){
            return it->value;
        }
        bool operator!=(Iterator i){
            return this->pos != i.pos;
        }
    };
    Iterator begin(){
        return Iterator(this->head,0);
    }
    Iterator end(){
        return Iterator(nullptr,size);
    }
    Iterator rbegin(){
        return Iterator(this->top,size - 1);
    }
    Iterator rend(){
        return Iterator(nullptr,-1);
    }
};

#endif