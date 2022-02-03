#include <iostream>
#include <functional>
#include <vector>
#include <string>
#include <list>
#include <cmath>

using std::cout;
using std::cin;
using std::vector;
using std::function;
using std::string;
using std::pair;
using std::list;
using std::pow;

template<class T>
class Elem {
    T value;
public:
    Elem(T value): value(value) {}
    T getValue(){
        return this->value;
    }
};

template<class T>
class HashTable {
    Elem<T>** ht;
    size_t capacity;
    size_t size;
    function<void(T)> show;
    vector<list<pair<string,size_t>>*> colision; 
public:
    HashTable(size_t capacity, function<void(T)> show): capacity(capacity), show(show) {
        ht = new Elem<T>*[capacity];
        for(size_t i = 0; i < capacity; ++i)
            ht[i] = nullptr;
        size = 0;
        colision.resize(capacity,nullptr);
    }
    ~HashTable(){
        if(size == 0){
            delete[] ht;
        } else {
            for(size_t i = 0; i < capacity; ++i)
                if(ht[i] != nullptr)
                    delete ht[i];
            delete[] ht;
        }
    }
    void print(){
        for(size_t i = 0; i < capacity; ++i){
            cout << "\nPos: " << i << " --> ";
            if(ht[i] != nullptr)
                show(ht[i]->getValue());
        }
        cout << "\n";
    }
private:
    size_t HashFunction(string key){
        int s = 0;
        for(auto c: key){
            s += c;
        }
        return s % capacity;
    }
    size_t LinearProbing(size_t index){
        size_t newIndex = index;
        while(ht[newIndex] != nullptr){
            ++newIndex;
            if(newIndex > (capacity - 1))
                newIndex %= capacity;
        }
        return newIndex;
    }
    size_t CuadraticProbing(size_t index){
        size_t newIndex = index;
        size_t jump = 1;
        while(ht[newIndex] != nullptr){
            newIndex = index;
            newIndex += pow(jump,2);
            if(newIndex > (capacity - 1))
                newIndex %= capacity;
            ++jump;
        }
        return newIndex;
    }
public:
    void insert(string key, T value){
        if (size == capacity)
            return;
        size_t index = HashFunction(key);
        if(ht[index] == nullptr){
            ht[index] = new Elem<T>(value);
            colision[index] = new list<pair<string,size_t>>;
            colision[index]->push_back(pair<string,size_t>(key,index));
        } else{
            //size_t newIndex = LinearProbing(index);
            size_t newIndex = CuadraticProbing(index);
            ht[newIndex] = new Elem<T>(value);
            colision[index]->push_back(pair<string,size_t>(key,newIndex));
        }
        ++size;
    }
    T get(string key){
        size_t index = HashFunction(key);
        if(ht[index] != nullptr){
            if(colision[index]->size() > 1){
                for(auto elem: *colision[index]){
                    if(key == elem.first)
                        return ht[elem.second]->getValue();
                }
            }else{
                return ht[index]->getValue();
            }
        }
        return T();
    }
    void erase(string key){
        size_t index = HashFunction(key);
        if(ht[index] != nullptr){
            if(colision[index]->size() > 1){
                list<pair<string,size_t>>::iterator it = colision[index]->begin();
                for(it; it != colision[index]->end();++it){
                    if(key == (*it).first){
                        delete ht[(*it).second];
                        --size;
                        ht[(*it).second] = nullptr;
                        colision[index]->erase(it);
                        break;
                    }
                }
            }else{
                delete ht[index];
                ht[index] = nullptr;
                colision[index]->erase(colision[index]->begin());
                --size;
            }
        }
    }
};

int main(){
    HashTable<int>* ht = new HashTable<int>(10,[](int a) -> void {cout << a;});
    ht->insert("Hola",8);
    ht->insert("aloH",10);
    ht->print();
    cout << "\n" << ht->get("aloH") << "\n";
    ht->erase("Hola");
    ht->print();
    cout << "\n" << ht->get("Hola") << "\n";
    delete ht;
    return 0;
}