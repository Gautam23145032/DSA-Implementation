/*
    The only extra complexity is that we need one DLL for each frequency.
    LFUCache
    │
    ├── keyToNode
    │      key → Node*
    │
    ├── freqToList
    │      frequency → DoublyLinkedList
    │
    └── minFreq
        minimum frequency currently present

*/


#include<bits/stdc++.h>
using namespace std;

struct Node{
    int key;
    int value;
    int freq;

    Node* prev;
    Node* next;
    
    Node(int key, int value){
        this->key = key;
        this->value = value;
        freq = 1;
        prev = nullptr;
        next = nullptr;
    }
};

class DLL{
public:

    Node* head;
    Node* tail;
    int size;

    DLL(){
        head = new Node(-1, -1);
        tail = new Node(-1, -1);
        head->next = tail;
        tail->prev = head;

        size = 0;
    }

    void insertFront(Node* node){
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
        size++;
    }

    void remove(Node* node){
        node->next->prev = node->prev;
        node->prev->next = node->next;
        size--;
    }

    Node* getLRU(){
        if(size == 0){
            if(size == 0) return nullptr;
        }
        return tail->prev;
    }

};

class LFUCache{
private:

    int cap;
    int minFreq;

    unordered_map<int, Node*> keyToNode;

    unordered_map<int, DLL*> freqToList;
    // here this store DLL corresponding to a freq;

public:

    LFUCache(int cap){
        this->cap = cap;
        minFreq = 0;
    }

    void increaseFrequency(Node* node){
        int oldFreq = node->freq;
        freqToList[oldFreq]->remove(node);

        if(oldFreq == minFreq && freqToList[oldFreq]->size == 0){
            minFreq++;
        }
        
        node->freq++;
        int newFreq = node->freq;

        // if DLL for new freq doesn't exist. create it

        if(!freqToList.count(newFreq)){
            freqToList[newFreq] = new DLL();
        }
        freqToList[node->freq]->insertFront(node);
    }

    int get(int key){
        if(!keyToNode.count(key)){
            return -1;
        }

        Node* node = keyToNode[key];
        increaseFrequency(node);
        return node->value;
    }

    int put(int key, int value){
        
        if(keyToNode.count(key)){
            Node* node = keyToNode[key];
            node->value = value;
            increaseFrequency(node);
            return;
        }

        if(keyToNode.size() == cap){
            DLL* list = freqToList[minFreq];
            Node* lfu = list->getLRU();
            keyToNode.erase(lfu->key);
            list->remove(lfu);

            delete lfu;
        }

        Node* node = new Node(key, value);
        keyToNode[key] = node;
        minFreq = 1;

        if(freqToList.find(1) == freqToList.end()){
            freqToList[1] = new DLL();
        }
        freqToList[1]->insertFront(node);
    }

};