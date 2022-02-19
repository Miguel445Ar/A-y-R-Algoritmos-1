#include <iostream>
#include <functional>
#include <vector>

using std::cin;
using std::cout;
using std::function;
using std::vector;

template<class T>
class Sorting {
    T* arr;
    size_t size;
    function<bool(T,T)> comp;
    function<void(T)>show;
public:
    Sorting(T* arr, size_t size, function<bool(T,T)> comp, function<void(T)>show): arr(arr), size(size), comp(comp), show(show){}
    ~Sorting(){ arr = nullptr;}
    void print(){
        for(size_t i = 0; i<size; ++i)
            show(arr[i]);
        cout << "\n";
    }
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
    // Tarea
    void exchangeSort(){

    }
    void InsertionSort(){

    }
    void MergeSort(){
        _MergeSort(0,size - 1);
    }
    void HeapSort(){
        size_t n = size - 1;
        size_t LastParent, leftChild, rightChild, rChild;
        while (n > 0){ // n
            LastParent = (n - 1) / 2;
            for (short i = LastParent; i >= 0; --i){ // log(n)
                leftChild = 2 * i + 1;
                rightChild = 2 * i + 2;
                if (leftChild > n)
                    rChild = rightChild;
                else if (rightChild > n)
                    rChild = leftChild;
                else
                    rChild = (comp(arr[leftChild],arr[rightChild]))?leftChild:rightChild;
                if(comp(arr[rChild],arr[i]))
                    swap(arr[rChild],arr[i]);
            }
            swap(arr[0],arr[n]);
            --n;
        }
        // TimeComplexity = O(nlog(n))
        // Space Complexity = O(1)
    }
    void RecursiveHeapSort(){
        size_t lastParent = (size - 2) / 2;
        for (int i = lastParent; i >= 0; --i) {
            _heapify(i,size);
        }
        for(int i = size - 1; i > 0; --i){
            swap(arr[0],arr[i]);
            _heapify(0,i);
        }
    }
private:
    void _heapify(size_t i, size_t n){
        size_t maxChild = i;
        size_t leftChild = 2 * i + 1;
        size_t rightChild = 2 * i + 2;
        if (leftChild > (n - 1) && rightChild > (n - 1))
            return;
        if (leftChild > (n - 1))
            maxChild = rightChild;
        else if (rightChild > (n - 1))
            maxChild = leftChild;
        else
            maxChild = (arr[leftChild] > arr[rightChild]) ? leftChild : rightChild;
        if (arr[i] < arr[maxChild]){
            swap(arr[i], arr[maxChild]);
            _heapify(maxChild,n);
        }
    }
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
    int arr[] = {8,7,5,4,9,1,3,2};
    Sorting<int> s(arr,8,[](int a, int b) -> bool { return a > b;},[](int a) -> void { cout << a << " "; });
    s.print();
    s.HeapSort();
    s.print();
    return 0;
}
