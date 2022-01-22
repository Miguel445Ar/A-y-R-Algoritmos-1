#include "MyStack.hpp"

using MyCode::Stack;

int main(){
    auto show = [](int a) -> void {
        cout << a << "-->";
    };
    auto comp = [](int a, int b){
        return a > b;
    };
    Stack<int>* pila = new Stack<int>(show,comp);
    pila->push(5);
    pila->push(2);
    pila->push(7);
    pila->push(1);
    pila->push(10);
    pila->print();
    cout << "\nThe lowest value in the stack is " << pila->getMin() << "\n";
    pila->pop();
    pila->print();
    cout << "\nThe lowest value in the stack is " << pila->getMin() << "\n";
    pila->pop();
    pila->print();
    cout << "\nThe lowest value in the stack is " << pila->getMin() << "\n";
    return 0;
}