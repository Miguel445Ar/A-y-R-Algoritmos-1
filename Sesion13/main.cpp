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
using std::list;
using std::pow;

template<class T>
class Elem {
    T value;
    string key;
public:
    Elem(T value, string key): value(value), key(key) {}
    T getValue(){
        return this->value;
    }
    string getKey(){
        return this->key;
    }
};

template<class T>
class HashTable {
    list<Elem<T>*>** ht;
    size_t capacity;
    size_t size;
    function<void(T)> show;
    function<T(void)> defaultValue;
public:
    HashTable(size_t capacity, function<void(T)> show, function<T(void)> defaultValue): capacity(capacity), show(show), defaultValue(defaultValue) {
        ht = new list<Elem<T>*>*[capacity];
        for(size_t i = 0; i < capacity; ++i)
            ht[i] = nullptr;
        size = 0;
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
            if(ht[i] != nullptr){
                for(auto elem: *(ht[i])){
                    show(elem->getValue()); cout << "-->";
                }
                cout << "nullptr\n";
            }
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
public:
    void insert(string key, T value){
        size_t index = HashFunction(key);
        if(ht[index] == nullptr){
            ht[index] = new list<Elem<T>*>;
            ht[index]->push_back(new Elem<T>(value,key));
            ++size;
            return;
        }
        ht[index]->push_back(new Elem<T>(value,key));
        ++size;
    }
    T get(string key){
        size_t index = HashFunction(key);
        if(ht[index] != nullptr)
            for(auto elem: *(ht[index])){
                if(elem->getKey() == key)
                    return elem->getValue();
            }
        return defaultValue();
    }
    void erase(string key){
        size_t index = HashFunction(key);
        if(ht[index] != nullptr){
            auto it = ht[index]->begin();
            for(it; it != ht[index]->end(); ++it){
                if((*it)->getKey() == key){
                    ht[index]->erase(it);
                    break;
                }
            }
        }
    }
};


int main(){
    HashTable<int>* ht = new HashTable<int>(10,[](int a) -> void {cout << a;},[]()-> int { return -10000;});
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