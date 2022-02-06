#include <iostream>

using std::cout;
using std::cin;


template<class T>
class Sorting {
    T* arr;
    size_t size;
public:
    Sorting(T* arr, size_t size): arr(arr), size(size){}
    ~Sorting(){ arr = nullptr;}
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
    void exchangeSort(){

    }
    void InsertionSort(){

    }
    void MergeSort(){
        _MergeSort(0,size - 1);
    }
private:
    void _MergeSort(size_t i, size_t f){
        if (i == f)
            return;
        size_t mid = (i + f) / 2;
        _MergeSort(i,mid); // Dividimos por la izquierda
        _MergeSort(mid+1,f); // Dividimos por la derecha
        _Merge(i,mid,f); // Combinamos resultados (Ordenamos)
    }
    void _Merge(size_t i, size_t m , size_t f){
        size_t c = f - i + 1;
        T* aux = new T[c];
        size_t k = 0, l = i, r = m + 1;
        while (l <= m && r <= f){
            if (arr[l] < arr[r])
                aux[k++] = arr[l++];
            else
                aux[k++] = arr[r++];
        }
        // Compensamos por la izquierda
        while (l <= m)
            aux[k++] = arr[l++];
        // Compensamos por la derecha
        while (r <= f)
            aux[k++] = arr[r++];
        // Actualizamos el arreglo original
        for (size_t j = 0; j < c; ++j)
            arr[i + j] = aux[j];
        delete[] aux;
    }
};

int main(){
    int arr[] = {3,6,1,7,9};
    Sorting<int> aux(arr,5);
    aux.print();
    //aux.BubleSort();
    aux.MergeSort();
    aux.print();
    return 0;
}
