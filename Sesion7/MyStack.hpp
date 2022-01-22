#ifndef __MYSTACK_HPP__
#define __MYSTACK_HPP__

#include <iostream>
#include <functional>

using std::cout;
using std::function;


namespace MyCode {
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
        ~DoubleLinkedList(){
            while(size > 0){
                popBack();
            }
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
        size_t Size(){
            return this->size;
        }
        T Top(){
            return this->top->value;
        }
    };
    template<class T>
    class Stack {
        DoubleLinkedList<T>* principal;
        DoubleLinkedList<T>* secondary;
        function<bool(T,T)> comp;
        public:
            Stack(function<void(T)> show,function<bool(T,T)> comp): comp(comp) {
                principal = new DoubleLinkedList<T>(show);
                secondary = new DoubleLinkedList<T>(show);
            }
            ~Stack(){
                delete principal;
                delete secondary;
            }
            void push(T value){
                principal->pushBack(value);
                if(secondary->Size() == 0){
                    secondary->pushBack(value);
                    return;
                }
                T v = secondary->Top();
                if(comp(value,v))
                    secondary->pushBack(value);
                else
                    secondary->pushBack(v);
            }
            void pop(){
                principal->popBack();
                secondary->popBack();
            }
            void print(){
                principal->print();
            }
            T getMin(){
                return (secondary->Size() > 0)? secondary->Top(): T();
            }
    };
};

#endif