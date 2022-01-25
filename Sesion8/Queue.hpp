#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__
#include <iostream>
#include <functional>

using std::cout;
using std::cin;
using std::function;


namespace myCode {

    template<class T>
    class MyQueue{

        template<class V>
        class Node {
        public:
            V value;
            Node<V>* next;
            Node<V>* back;
            Node(V value, Node<V>* next = nullptr, Node<V>* back = nullptr): value(value), next(next), back(back){}
        };

        Node<T>* head; // Inicia de la lista;
        Node<T>* top; // Fin de la lista;
        size_t size;
        function<void(T)> show;
        Node<T>* aux;
    public:
        MyQueue(function<void(T)> show): show(show) {
            head = top = aux = nullptr;
            size = 0;
        }
        ~MyQueue(){
            while(size > 0)
                pop();
        }
        void push(T value){
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
        void pop(){
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
        T Head(){
            return (size > 0)?this->head->value:T();
        }
         Top(){
            return (size > 0)?this->top->value:T();
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
};

#endif