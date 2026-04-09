#include<bits/stdc++.h>
using namespace std;


class Priority_q{
public:
    vector<int> arr;
    Priority_q() {};

    void push(int v){
        arr.push_back(v);

        int i = arr.size() - 1;

        // heapify up
        while(i > 0){
            int parent = (i - 1)/2;

            if(arr[parent] < arr[i]){
                swap(arr[parent], arr[i]);
                i = parent;
            }
            else{
                break;
            }
        }
    }

    // remove max element
    void pop(){
        if(arr.empty()) return;
        if(arr.size() == 1){
            arr.pop_back();
            return;
        }
        // replace root with last element
        arr[0] = arr.back();
        arr.pop_back();
        // heapify down
        heapify(arr.size(), 0);
    }
    int top(){
        if(arr.empty()) throw runtime_error("Heap is empty");
        return arr[0];
    }

    // iterative
    // heapify down
    void heapify(int n, int i){

        while(true){
            int left = 2 * i + 1;
            int right = 2 * i + 2;

            int largest = i;

            if(left < n && arr[left] > arr[largest]){
                largest = left;
            }

            if(right < n && arr[right] > arr[largest]){
                largest = right;
            }

            if(largest == i){
                break;
            }
            swap(arr[largest], arr[i]);
            i = largest;
        }
    }
    
    // recursive
    // void heapify(int n, int i){
    //     int parent = i;
    //     int left = 2*i + 1;
    //     int right = 2*i + 2;
    //     int largest = parent;
    //     if(left < n && arr[left] > arr[largest]){
    //         largest = left;
    //     }
    //     if(right < n && arr[right] > arr[largest]){
    //         largest = right;
    //     }

    //     if(largest != i){
    //         swap(arr[largest], arr[i]);
    //         heapify(n, largest);
    //     }
    // }
};


int main(){
    Priority_q pq;
    vector<int> arr = {2, 3, 4, 5, 2, 9};
    for(auto& it : arr) pq.push(it);

    cout << pq.top() << endl;
    pq.pop();
    cout << pq.top();
}

/*
    when we push an element in arr at back
        -> we do heapify up
        -> because element is added at last then it find their correct position

    when we pop the top (max element) -> root of the tree
        -> we do heapify down
        -> because heap data structure is maintained such that the root value is always
           greater than its children in case of max heap 
        -> so when we pop() then the main root is removed means whole ordering is dis balanced
           thats why we take the back element and replace the max element then we do heapify down

        


*/