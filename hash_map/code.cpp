/*
    What problem we are solving ?
    -> we want a data structure that supports
    put(key, val),
    get(key), 
    remove(key)
    in approx O(1) time 

    A simple array cannot do this because keys can be very large 
    eg. put(1000000000, 1); -> we cannot create an array of size 1e9

    so we need a way to map large keys into smaller range of indices

    Core idea : Hashing
    -> we use hash function 
    for example index = key % capacity
    suppose capacity is 10
    then we assume some key, value -> (25, 0), (28, 1), (15, 9), (2, 4);

    so index for the key -> 
    25 % 10 = 5;
    28 % 10 = 8
    15 % 10 = 5
    2 % 10 = 2;
    now instead of storing values at index 25, 28, 15, 2
    we store them inside bucket number 0 - 9.

    Problem with this : Collision
    Different keys can generate the same index
    eg 25 % 10 = 5, 15 % 10 = 5 -> this is called collision

    Collision Resolution : using chaining

    for every bucket we maintain a linked list

    so bucket[5] -> (25, 0) -> (15, 9)  ==> linked list

    whenever multiple keys hash to the same bucket, we simply add them to that buckets linked list

    Data Structure Design

*/

#include <bits/stdc++.h>
using namespace std;

/*
    each node stores
    key => actual value
    value => value corresponding to key
    next => pointer that points to next node in the chain

*/

class Node{
public:
    int key;
    int value;
    Node* next;

    Node(int k, int v){
        key = k;
        value = v;
        next = nullptr;
    }
};

class MyHashMap{
public:
    //Total number of buckets. eg capacity = 10
    int capacity;

    // every bucket stores head of a linked list
    // vector<Node*> buckets;

    vector<Node*> buckets;
    /*
        Hash function converts a key into bucket index
    */

    int hashFunction(int key){
        return ((key % capacity) + capacity) % capacity;
    }

public:
    // constructor -> create 'capacity' buckets -> initially every bucket is empty

    MyHashMap(int cap = 10){
        capacity = cap;
        buckets.resize(capacity, nullptr);
    }

    /* 
        put operation
        case 1. key already exists -> update value
        case 2. key does not exist -> insert new node
    */

    void put(int key, int value){
        // find bucket index;
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        /*
            Search whether key already exists
        */

        while(curr){
            if(curr->key == key){
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // node not found => create new node

        Node* newNode = new Node(key, value);
        /*
            insert at the beginning of the chain
            before : head -> A -> B
            after : head -> newNode -> A -> B
        
        */
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
        
    }
        /*
            Get operation
            return corresponding value
            return -1 if not present;
        */

    int get(int key){
        int idx = hashFunction(key);
        Node* curr = buckets[idx];
        while(curr){
            if(curr->key == key){
                return curr->value;
            }
            curr = curr->next;
        }
        return -1;
    }

    // remove operation => delete node containing given key.

    void remove(int key){
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        Node* prev = nullptr;
        while(curr){
            if(curr->key == key){

                if(prev == nullptr){
                    buckets[idx] = curr->next;
                }
                else{
                    prev->next = curr->next;
                }
                
                delete curr;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    /*
        Utility function to visualize hashmap.
    */
    void display() {

        for (int i = 0; i < capacity; i++) {

            cout << "Bucket " << i << ": ";

            Node* curr = buckets[i];

            while (curr) {

                cout << "("
                        << curr->key
                        << ","
                        << curr->value
                        << ") -> ";

                curr = curr->next;
            }

            cout << "NULL\n";
        }
    }

};

int main(){
    MyHashMap mp(10);
    mp.put(5, 9);
    mp.put(2, 0);
    mp.put(3, 8);
    mp.display();
}


/*
    Next Improvement -> Rehashing,
    because without it your hashMap degrades badly as more elements are inserted

    why Rehashing?
    suppose capacity = 10 and we insert 100 ele
    so average chain length becomes 100/10 = 10
    so get(key) may traverse 10 nodes

    if we insert 10000 ele
    so average chain length becomes 10000/10 = 1000
    now your o(1) hashmap behaves closer to o(n)

    Load Factor -> to decide when to grow table

    Load Factor = number of ele / number of buckets
    eg. elements = 8, capacity = 10
    load factor = 0.8

    most of the implementation rehash around 0.75

*/


class Node{
public:
    int key;
    int value;
    Node* next;

    Node(int k, int v){
        key = k;
        value = v;
        next = nullptr;
    }
};

class MyHashMap{
public:
    //Total number of buckets. eg capacity = 10
    int capacity;
    int element_count;
    // every bucket stores head of a linked list
    // vector<Node*> buckets;

    vector<Node*> buckets;
    /*
        Hash function converts a key into bucket index
    */

    int hashFunction(int key){
        size_t hashValue = std::hash<int>{}(key);

        return hashValue % capacity;
    }

    double loadFactor(){
        return (double) element_count / capacity;
    }

    void rehash(){
        vector<Node*> oldBuckets = buckets;
        int oldCapacity = capacity;

        capacity *= 2;
        buckets.clear();
        buckets.resize(capacity, nullptr);

        /*
            since we are reinserting everything 
            reset size first;
        */

        element_count = 0;

        for(int i = 0; i < oldCapacity; i++){
            Node* curr = oldBuckets[i];
            while(curr){
                /*
                    reinsert into new buckets
                    new bucket index may differ because capacity changed
                */
                put(curr->key, curr->value);
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
        }
    }

public:
    // constructor -> create 'capacity' buckets -> initially every bucket is empty

    MyHashMap(int cap = 10){
        element_count = 0;
        capacity = max(1, cap);
        buckets.resize(capacity, nullptr);
    }

    /* 
        put operation
        case 1. key already exists -> update value
        case 2. key does not exist -> insert new node
    */

    void put(int key, int value){
        // find bucket index;
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        /*
            Search whether key already exists
        */

        while(curr){
            if(curr->key == key){
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // node not found => create new node

        Node* newNode = new Node(key, value);
        /*
            insert at the beginning of the chain
            before : head -> A -> B
            after : head -> newNode -> A -> B
        
        */
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
        element_count++;

        // rehash
        if(loadFactor() > 0.75){
            rehash();
        }
    }
        /*
            Get operation
            return corresponding value
            return -1 if not present;
        */

    int get(int key){
        int idx = hashFunction(key);
        Node* curr = buckets[idx];
        while(curr){
            if(curr->key == key){
                return curr->value;
            }
            curr = curr->next;
        }
        return -1;
    }

    // remove operation => delete node containing given key.

    void remove(int key){
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        Node* prev = nullptr;
        while(curr){
            if(curr->key == key){

                if(prev == nullptr){
                    buckets[idx] = curr->next;
                }
                else{
                    prev->next = curr->next;
                }
                
                delete curr;
                element_count--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    /*
        Utility function to visualize hashmap.
    */
    void display() {

        for (int i = 0; i < capacity; i++) {

            cout << "Bucket " << i << ": ";

            Node* curr = buckets[i];

            while (curr) {

                cout << "("
                        << curr->key
                        << ","
                        << curr->value
                        << ") -> ";

                curr = curr->next;
            }

            cout << "NULL\n";
        }
    }
    /*
        FIX:

        Destructor

        Free all dynamically allocated memory.
    */
    ~MyHashMap(){

        for(auto head : buckets){

            while(head){

                Node* temp = head;

                head = head->next;

                delete temp;
            }
        }
    }

};