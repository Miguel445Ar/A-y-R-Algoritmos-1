#include <iostream>

using std::cout;
using std::cin;


template<class T>
class Sorting {
    T* arr;
    size_t size;
public:
    Sorting(T* arr, size_t size): arr(arr), size(size){}
    ~Sorting(){ delete[] arr;}
    void print(){
        for(size_t i = 0; i<size; ++i)
            cout << arr[i] << " ";
        cout << "\n";
    }
    /*void swap(T* a, T*b){
        T c = *b;
        *b = *a;
        *a = c;
    }*/
    void swap(T& a, T& b){
        T c = b;
        b = a;
        a = c;
    }
    void BubleSort(){
        for(size_t i = 0; i < size - 1; ++i){
            if(arr[i] > arr[i + 1]){
                this->swap(arr[i],arr[i+1]);
                (i == 0)? --i : i -= 2;
            }
        }
    }
};

int main(){
    int arr[] = {3,6,1,7,9};
    Sorting<int> aux(arr,5);
    aux.print();
    aux.BubleSort();
    aux.print();
    return 0;
}