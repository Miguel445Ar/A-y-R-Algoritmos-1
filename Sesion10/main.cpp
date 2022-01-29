#include <iostream>
#include <functional>
#include <string>
#include <fstream>
#include <string.h>

using std::cout;
using std::cin;
using std::function;
using std::string;
using std::ifstream;
using std::getline;
using std::ofstream;



template<class T>
class CircularDoubleLinkedList {
    template<class V>
    class Node {
    public:
        V value;
        Node<V>* next;
        Node<V>* back;
        CircularDoubleLinkedList<V>* children;
        Node(V value, function<void(T)> show) : value(value), next(nullptr), back(nullptr) {
            children = new CircularDoubleLinkedList<V>(show);
        }
        ~Node(){
            delete children;
        }
    };
    Node<T>* head; // Inicia de la lista;
    Node<T>* top; // Fin de la lista;
    size_t size;
    function<void(T)> show;
    Node<T>* aux;
public:
    CircularDoubleLinkedList(function<void(T)> show) : show(show) {
        head = top = aux = nullptr;
        size = 0;
    }
    ~CircularDoubleLinkedList(){
        while (size > 0)
            popBack();
    }
    void pushBack(T value, function<void(T)> show) {
        Node<T>* newNode = new Node<T>(value, show);
        if (size == 0) {
            head = top = newNode;
            head->back = top;
            top->next = head;
            ++size;
            return;
        }
        head->back = newNode;
        top->next = newNode;
        newNode->back = top;
        newNode->next = head;
        top = newNode;
        ++size;
    }
    void popBack() {
        if (size == 0)
            return;
        if (size == 1) {
            top->next = nullptr;
            head->back = nullptr;
            delete top;
            top = head = nullptr;
            --size;
            return;
        }
        top->next = nullptr;
        top = top->back;
        head->back = top;
        top->next->back = nullptr;
        delete top->next;
        top->next = head;
        --size;
    }
    
    CircularDoubleLinkedList<T>* getChildrenOfNode(size_t pos) {
        aux = head;
        for (size_t i = 0; i < pos; ++i)
            aux = aux->next;
        return aux->children;
    }
    class Iterator {
        Node<T>* it;
        int pos;
    public:
        Iterator(Node<T>* it, int pos) : it(it), pos(pos) {}
        void operator++() {
            (it) ? it = it->next : NULL;
            ++pos;
        }
        void operator--() {
            (it) ? it = it->back : NULL;
            --pos;
        }
        T& operator*() {
            return it->value;
        }
        bool operator!=(Iterator i) {
            return this->pos != i.pos;
        }
        Node<T>* operator+() {
            return it;
        }
    };
    Iterator begin() {
        return Iterator(this->head, 0);
    }
    Iterator end() {
        return Iterator(nullptr, size);
    }
    Iterator rbegin() {
        return Iterator(this->top, size - 1);
    }
    Iterator rend() {
        return Iterator(nullptr, -1);
    }
    void print() {
        aux = head;
        for (size_t i = 0; i < size; ++i) {
            show(aux->value);
            aux = aux->next;
        }
    }
    void result(function<void(T)>& add) {
        eraseCycle();
        _result(this->head, add);
        addCycle();
    }
private:
    void _result(Node<T>* n,function<void(T)>& add) {
        if (!n)
            return;
        add(n->value);
        if (n->children->Size() > 0) {
            CircularDoubleLinkedList<T>::Iterator it = n->children->begin();
            n->children->eraseCycle();
            _result(+it,add);
            n->children->addCycle();
        }
        _result(n->next,add);
    }
public:
    void eraseCycle() {
        head->back = nullptr;
        top->next = nullptr;
    }
    void addCycle() {
        head->back = top;
        top->next = head;
    }
    size_t Size() {
        return this->size;
    }
};

class Solution {
    CircularDoubleLinkedList<string>* lista;
    function<void(string)> show;
public:
    Solution() {
        auto show = [](string value) -> void {
            cout << value << " ";
        };
        this->show = show;
        lista = new CircularDoubleLinkedList<string>(show);
    }
    ~Solution() {
        delete lista;
    }
    void read() {
        ifstream arch("input.txt");
        string line;
        size_t nullCounter = -1;
        CircularDoubleLinkedList<string>* current = lista;
        while (getline(arch, line, ',')) {
            if (line.compare("nullptr") == 0) {
                ++nullCounter;
                continue;
            }
            if (nullCounter == -1) {
                current->pushBack(line,this->show);
                continue;
            }
            current = current->getChildrenOfNode(nullCounter);
            current->pushBack(line,this->show);
            nullCounter = -1;
        }
        arch.close();
        CircularDoubleLinkedList<string>* res = new CircularDoubleLinkedList<string>(this->show);
        function<void(string)> add = [res,this](string value) -> void {
            res->pushBack(value,show);
        };
        lista->result(add);
        res->print();
        ofstream arch2("output.txt");
        function<void(string)> save = [&arch2](string value) -> void {
            arch2 << value << ",";
        };
        res->result(save);
        arch2.close();
        delete res;
        current = nullptr;
    }
};
int main() {
    Solution* sol = new Solution;
    sol->read();
    delete sol;
    return 0;
}