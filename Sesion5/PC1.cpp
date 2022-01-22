#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <functional>
#include <fstream>
#include <string.h>

using std::cout;
using std::cin;
using std::rand;
using std::srand;
using std::time;
using std::string;
using std::vector;
using std::function;
using std::ifstream;
using std::getline;
using std::stoi;
using std::ofstream;
using std::to_string;

typedef unsigned int ui;
typedef unsigned int us;
template<class T>
class Matrix2d {
    short m,n;
    vector<T> matriz;
public:
    Matrix2d(int n, int m, int n1): m(m), n(n1){
        matriz.resize(n);
        for(size_t i = 0; i<n;++i)
            matriz[i] = 1 + rand()% 20;
    }
    void eliminacion(short i1, short j1){
        bool band = false;
        ui cont = 0;
        for(size_t i = 0; i<this->m;++i){
            for(size_t j = 0; j<this->n;++j){
                ++cont;
                if(i == i1 && j == j1){
                    band = true;
                    break;
                }
            }
            if(band)
                break;
        }
        cont -= 1;
        matriz.erase(matriz.begin()+cont);
    }
    void mostrarId(size_t col){
        int cont = -1;
        for(size_t i = 0; i<this->m;++i){
            for(size_t j = 0; j<this->n;++j){
                ++cont;
                if (j == col){
                    cout << matriz[cont] << " ";
                }
            }
        }
        cout << "\n";
    }
    void print(){
        int cont = -1;
        for(size_t i = 0; i<this->m;++i){
            for(size_t j = 0; j<this->n;++j){
                ++cont;
                if (cont >= matriz.size())
                    break;
                cout << matriz[cont] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }
};



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
    function<void(T)> show;
public:
    LinkedList(function<void(T)> show): show(show){
        head = nullptr;
        top = nullptr;
        size = 0;
    }
    ~LinkedList(){
        while(size > 0)
            popFront();
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
    void print(){
        Node<T>* aux = head;
        while (aux != nullptr) {
            show(aux->value);
            aux = aux->next;
        }
        cout << "nullptr\n";
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
    void intercambio(){
        if (size < 2)
            return;
        Node<T>* uno = head;
        Node<T>* dos = head->next;
        while(true){
            // Intercambio  de valores de los nodos
            T value = dos->value;
            dos->value = uno->value;
            uno->value = value;
            
            uno = uno->next->next;
            if (uno == nullptr)
                break;
            dos = dos->next->next;
            if(dos == nullptr)
                break;
        }
    }
    void intercambio2(){
        if (size < 2)
            return;
        Node<T>* uno = head;
        Node<T>* dos = head->next;
        _intercambio2(uno,dos);
    }
    void guardarEnArchivo(ofstream& arch){
        while(size > 0){
            T value = head->value;
            arch << to_string(value) << " ";
            popFront();
        }
    }
private:
    void _intercambio2(Node<T>*& uno, Node<T>*& dos){
        T value = dos->value;
        dos->value = uno->value;
        uno->value = value;
        if (uno->next->next == nullptr)
                return;
        if (dos->next->next == nullptr)
                return;
        _intercambio2(uno->next->next,dos->next->next);
    }
};

class Solution {
    LinkedList<int>* lista;
public:
    Solution(){
        auto show = [](int a) -> void {
            cout << a << "-->";
        };
        lista = new LinkedList<int>(show);
    }
    ~Solution(){
        delete lista;
    }
    // Con la versión iterativa
    void execute1(){
        ifstream arch("input.txt");
        if(arch.is_open() == false)
            return;
        string line;
        while(arch >> line)
            lista->pushBack(stoi(line));
        arch.close();
        lista->print();
        lista->intercambio();
        lista->print();
        ofstream arch2("input.txt");
        lista->guardarEnArchivo(arch2);
        arch2.close();
    }
    // Con la versión Recursiva
    void execute2(){
        ifstream arch("input.txt");
        if(arch.is_open() == false)
            return;
        string line;
        while(arch >> line)
            lista->pushBack(stoi(line));
        arch.close();
        lista->print();
        lista->intercambio2();
        lista->print();
        ofstream arch2("input.txt");
        lista->guardarEnArchivo(arch2);
        arch2.close();
    }
};

int main(){
    srand(time(0));
    Matrix2d<short> m(16,4,4);
    m.print();
    cout << "\n";
    m.mostrarId(1);
    cout << "\n";
    m.eliminacion(2,2);
    m.print();
    cout << "\nEjercicio de lista\n";
    Solution* sol = new Solution;
    sol->execute2();
    delete sol;
    return 0;
}