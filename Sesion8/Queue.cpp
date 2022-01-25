#include "Queue.hpp"
#include <string>

using myCode::MyQueue;
using std::string;
using std::to_string;

class Persona {
    unsigned int dni;
    string nombre;
public:
    Persona(unsigned int dni = 0, string nombre = ""): dni(dni), nombre(nombre) {}
    string mostrar(){
        return to_string(dni) + " " + nombre;
    }
};

// Tareas :D
// Implementar el ordenamiento burbuja para una lista doblemente enlazada tratar de utilizar solo un bucle
// Intentar resolver el ejercicio llamado Linked List.pdf

int main(){
    auto show = [](Persona a) -> void {
        cout << a.mostrar() << "-->";
    };
    MyQueue<Persona>* cola = new MyQueue<Persona>(show);
    cola->push(Persona(12345,"Miguel"));
    cola->push(Persona(12345,"Maria"));
    cola->push(Persona(12345,"Daniel"));
    cola->push(Persona(12345,"Alonsso"));
    cola->push(Persona(12345,"José"));
    cola->print();
    cola->pop();
    cola->print();
    return 0;
}