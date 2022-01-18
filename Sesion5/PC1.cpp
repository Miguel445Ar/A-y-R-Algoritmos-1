#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>

using std::cout;
using std::cin;
using std::string;
using std::vector;
using std::rand;
using std::srand;
using std::time;

typedef unsigned int ui;
template<class T>
class Matrix2d {
    short m,n;
    vector<T> matriz;
public:
    Matrix2d(int n){
        matriz.resize(n);
        for(size_t i = 0; i<n;++i)
            matriz[i] = 1 + rand()% 20;
    }
    void eliminacion(short m, short n, short i1, short j1){
        if(m*n != matriz.size())
            return;
        bool band = false;
        ui cont = 0;
        for(size_t i = 0; i<m;++i){
            for(size_t j = 0; j<n;++j){
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
    void print(){
        for(size_t i = 0; i<matriz.size();i++)
            cout << matriz[i] << " ";
        cout << "\n";
    }
};

int main(){
    srand(time(0));
    Matrix2d<short> m(16);
    m.print();
    m.eliminacion(4,4,2,2);
    m.print();
    return 0;
}