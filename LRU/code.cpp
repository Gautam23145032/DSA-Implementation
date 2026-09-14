/*
    we can implement this using map and doubly link list


*/

#include<bits/stdc++.h>
using namespace std;

struct Node{
    int key;
    int value;

    Node* prev;
    Node* next;

    Node(int key, int value){
        this->key = key;
        this->value = value;
        prev = nullptr;
        next = nullptr;
    }

};

class DLL{
public:

    Node* head;
    Node* tail;
    DLL(){
        head = new Node(-1, -1);
        tail = new Node(-1, -1);

        head->next = tail;
        tail->next = head;
    }

    void insert_front(Node* node){
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;

    }

    void remove(Node* node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    Node* getLRU(){
        return tail->prev;
    }
};

class LRUCache{
private:
    int cap;
    unordered_map<int, Node*> mp;
    DLL dll;

public:

    LRUCache(int cap){
        this->cap = cap;
    }

    int get(int key){
        if(!mp.count(key)){
            return -1;
        }
        Node* node = mp[key];
        dll.insert_front(node);
        dll.remove(node);

        return node->value;
    }

    void put(int key, int value){
        if(mp.count(key)){
            Node* node = mp[key];
            dll.insert_front(node);
            dll.remove(node);
            node->value = value;
            return;
        }

        Node* node = new Node(key, value);
        dll.insert_front(node);

        if(mp.size() > cap){
            Node* lru = dll.getLRU();
            dll.remove(lru);
            mp.erase(lru->key);
            delete lru;
        }
    }
    
};