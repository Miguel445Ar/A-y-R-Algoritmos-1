#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <string>

using std::cout;
using std::cin;
using std::function;
using std::vector;
using std::sort;
using std::string;

// Functores en C++ (Los de verdad)

class Inc
{
    int num;
public:
    Inc(int n) : num(n) {  }
  
    // This operator overloading enables calling
    // operator function () on objects of increment
    int operator () (int arr_num) const {
        return num + arr_num;
    }
    int getNum(){
        return num;
    }
};

int sumar(int a, int b) {
    int r = a + b;
    return r;
}

void exec(int (*func)(int,int), int a, int b){
    cout << func(a,b);
}

int sumar2(int a, int b) {
    int r = a + b;
    return r;
}

void exec2(function<int(int,int)> func, int a, int b){
    cout << func(a,b);
}

template<class T>
struct Elem {
    T value;
};

template<class T>
class MyVector {
    Elem<T>** arreglo;
    size_t size;
    function<void(T)> show;
public:
    MyVector(function<void(T)> show): show(show){
        size = 0;
        arreglo = nullptr;
    }
    void pushBack(T v){
        Elem<T>* newValue = new Elem<T>;
        newValue->value = v;
        Elem<T>** aux = new Elem<T>*[size+1];
        for(size_t i = 0; i<size;++i){
            aux[i] = arreglo[i];
        }
        aux[size] = newValue;
        if(!arreglo)
            delete[] arreglo;
        arreglo = aux;
        ++size;
    }
    T& operator[](size_t i){
        return arreglo[i]->value;
    }
    size_t Size(){
        return this->size;
    }
    void print(){
        for(size_t i = 0; i<size;++i)
            show(arreglo[i]->value);
    }
};



class Persona {
    int dni;
    string nombre;
public:
    Persona(int dni = 0, string nombre = ""): dni(dni), nombre(nombre){}
    string mostrar(){
        return std::to_string(dni) + " " + nombre;
    }
};


int f(int n){
    if (n == 1)
        return 1;
    return n * f(n-1);
}

// Serie de Fibonacci Recursiva
// Imprimir un triángulo rectángulo de * de forma recursiva
// Imprimir un triángulo equilátero de * de forma recursiva


int main(){
    int a = 10;
    int b = 8;

    vector<int> numeros = {1,4,7,2,8,4,9};

    auto comp = [](int a, int b) -> bool { return a < b;};
    sort(numeros.begin(),numeros.end(), comp);
    for (size_t i = 0;i <numeros.size();++i)
        cout << numeros[i] << "\n";
    
    auto show = [](Persona p) -> void {
        cout << p.mostrar() << "\n";
    };
    MyVector<Persona> v(show);
    v.pushBack(Persona(12134,"Miguel"));
    v.pushBack(Persona(132454356,"Ana"));
    v.print();
    v.print();
    v.print();
    cout << "\n";

    cout << f(5) << "\n";

    //C++

    // auto aux = sumar;
    // auto aux = [](int a, int b) -> int {
        //return a + b;
    //};
    //function<int(int,int)> aux = sumar;
    //vector<function<int(int,int)>> funciones;
    //function<int(int,int)> aux = [](int a, int b) -> int {
        //return a + b;
    //};
    //exec2(aux,a,b);
    //exec2([](int a, int b) -> int {return a + b; },a,b);

    // C
    //int (*ptr)(int,int);
    //int (*ptr[2])(int,int);
    //ptr[0] = sumar;
    //ptr[1] = sumar2;
    //ptr = &sumar;
    //exec(sumar,a,b);
    return 0;
}