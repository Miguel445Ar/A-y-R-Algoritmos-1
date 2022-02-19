#include <iostream>
#include <functional>
#include <string>
#include <list>
#include <fstream>
#include <string.h>
#include <sstream>
#include "dll.hpp"

using std::cout;
using std::list;
using std::string;
using std::ostream;
using std::getline;
using std::ifstream;
using std::stringstream;

class Virus {
    char c;
    string name, type;
public:
    Virus(char c = '.', string name = "", string type = ""): c(c), name(name), type(type){}
    char getCaracter(){
        return this->c;
    }
    friend ostream& operator<<(ostream& os, Virus v) {
        os << v.c << " " << v.name << " " << v.type;
        return os;
    }
    string getName(){
        return this->name;
    }
    string getType(){
        return this->type;
    }
};

class Node {
    Virus v;
    DoubleLinkedList<Node*>* childs;
public:
    Node(Virus v = Virus()): v(v) {
        childs = new DoubleLinkedList<Node*>;
    }
    ~Node(){
        delete childs;
    }
    Virus getVirus(){
        return this->v;
    }
    DoubleLinkedList<Node*>* getChilds(){
        return this->childs;
    }
    void insertChild(Node* n){
        childs->pushBack(n);
    }
};

class Trie {
    Node* root;
    size_t size;
public:
    Trie(){
        root = new Node;
        size = 1;
    }
    void insert(const string& cad, const string& name, const string& type){
        _insert(root,cad,0,name,type);
    }
    void print(){
        _print(root);
    }
    string findByName(const string& name){
        return _find(root,name);
    }
    void searchByCad(const string& cad){
        _searchByCad(root,cad,0);
    }
    void erase(const string& cad){
        _erase(root,nullptr,cad,0,-1);
    }
private:
    void _insert(Node* n ,const string& cad, size_t i, const string& name, const string& type){
        if(i == cad.size())
            return;
        for(auto ch: *n->getChilds()){
            if (ch->getVirus().getCaracter() == cad[i]){
                _insert(ch,cad,i+1,name,type);
                return;
            }
        }
        for(size_t k = i; k < cad.size(); ++k){
            Node* newNode = (k == cad.size() - 1)? new Node(Virus(cad[k],name,type)):new Node(Virus(cad[k]));
            n->insertChild(newNode);
            n = newNode;
        }
    }
    string _find(Node* n, const string& name){
        if(!n)
            return "";
        if(n->getVirus().getName() == name)
            return n->getVirus().getType();
        if(n->getChilds()->Size()  > 0){
            for(auto n: *n->getChilds()) {
                string res = _find(n,name);
                if(res != "")
                    return res;
            }
        }
        return "";
    }
    void _print(Node* n){
        cout << n->getVirus() << "\n";
        if(n->getChilds()->Size()  == 0)
            return;
        for(auto n: *n->getChilds()) {
            _print(n);
        }
    }
    void _searchByCad(Node* n, const string& cad, size_t i){
        for(auto ch: *n->getChilds()){
            if(ch->getVirus().getCaracter() == cad[i]){
                _searchByCad(ch,cad,i+1);
                return;
            }
        }
        if( i < cad.size())
            return;
        _print2(n);
    }
    void _print2(Node* n){
        if (n->getVirus().getName() != "")
            cout << n->getVirus().getName() << "\n";
        if(n->getChilds()->Size()  == 0)
            return;
        for(auto n: *n->getChilds()) {
            _print2(n);
        }
    }
    void _erase(Node* n, Node* parent, const string& cad, size_t i, size_t p){
        size_t pos = 0;
        for(auto ch: *n->getChilds()){
            if(ch->getVirus().getCaracter() == cad[i]){
                _erase(ch,n, cad,i+1,pos);
                if(n->getChilds()->Size() == 0 && parent != nullptr)
                    parent->getChilds()->eraseInPos(p);
                return;
            }
            ++pos;
        }
        if(i < cad.size())
            return;
        if(n->getChilds()->Size() == 0)
            parent->getChilds()->eraseInPos(p);
    }
};

class Solution {
    Trie* t;
public:
    Solution(){
        t = new Trie;
        read();
    }
    ~Solution(){
        delete t;
    }
private:
    void read(){
        ifstream arch("input.txt");
        string line;
        while(getline(arch,line)){
            stringstream s(line);
            string aux,cad,name,type;
            getline(s,aux,' ');
            cad = aux;
            getline(s,aux,' ');
            name = aux;
            getline(s,aux,' ');
            type = aux;
            t->insert(cad,name,type);
        }
        arch.close();
    }
public:
    void print(){
        t->print();
    }
    void findByName(string name){
        cout << "\nThe type which corresponds to " << name << " is " << t->findByName(name) << "\n"; 
    }
    void searchByCad(string cad){
        cout << "\nThese are the diseases which character string starts with " << cad << "\n";
        t->searchByCad(cad);
    }
    void eraseCharacterString(string cad){
        cout << "\nErasing the character string " << cad << "...\n";
        t->erase(cad);
    }
};

int main() {
    Solution s;
    s.print();
    s.findByName("sars");
    s.searchByCad("CTUTCT");
    s.eraseCharacterString("UTTCUCT");
    s.print();
    return 0;
}