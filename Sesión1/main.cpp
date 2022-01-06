/*#include <iostream>

// Genéricos en C
using std::cout;
#define DEF(type, name, val) type name = val
#define FOREACH(type, start, end, fn) for (type _foreach_var = start; _foreach_var != end; _foreach_var++) {fn(_foreach_var);}

void show(int n) {
    cout << n << "\n";
}

#define TYPE_CAST double*
void show2(void* a, void* b){
    
}
// Es algo complicado pero es lo que C te puede permitir ¯\_(ツ)_/¯

int main(){
    int number = 5;
    DEF(int*,var,&number);
    cout << "\n";
    void (*ptr)(int) = &show;
    FOREACH(int,0,10,ptr);
    
    return 0;
}
*/

// Templates en C++

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::ostream;
using std::endl;
using std::istream;
using std::cin;
using std::system;

template<class T>
struct Elem {
    T value;
};

template<class T>
class MyVector {
    Elem<T>** arreglo;
    size_t size;
public:
    MyVector(){
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
};

class Persona {
    int dni;
    string nombre;
public:
    Persona(int dni = 0, string nombre = ""): dni(dni), nombre(nombre){}
    friend ostream& operator<<(ostream& os, Persona p){
        os << p.dni << " " << p.nombre;
        return os;
    }
    friend istream& operator>>(istream& is, Persona& p){
        is >> p.dni >> p.nombre;
        return is;
    }
};

int main(){
    MyVector<int> v;
    v.pushBack(5);
    v.pushBack(9);
    v.pushBack(2);
    v.pushBack(8);
    v.pushBack(4);
    for(size_t i = 0; i<v.Size();++i)
        cout << v[i] << " ";
    cout << "\n";
    v[4] = 20;
    for(size_t i = 0; i<v.Size();++i)
        cout << v[i] << " ";
    cout << "\n";
    Persona aux;
    cout << "\nIngrese una persona";
    cin >> aux;
    cout << aux << endl;
    Persona a = Persona(5748484,"Miguel");
    cout << a << endl;
    system("pause");
    return 0;
}