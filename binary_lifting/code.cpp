#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    cin >> n;
    vector<int> parent(n); // parent of node i is parent[i];
    for(int i = 0; i < n; i++) cin >> parent[i];

    // for n upto 1e5 LOG = 20 is enough;
    int LOG = 20;
    vector<vector<int>> up(n, vector<int>(LOG, -1));
    // up[i][j] = 2^j the ancestor of node i;
    // base case
    for(int i = 0; i < n; i++){
        up[i][0] = parent[i]; // 1st ancestor of node i is the parent of i
    }

    for(int j = 0; j < LOG; j++){
        for(int i = 0; i < n; i++){
            if(up[i][j-1] != -1){
                up[i][j] = up[up[i][j-1]][j-1];
                // 2^j th ancestor of node i is 2^(j-1) the ancestor of 2^(j-1) the ancestor;

            }
        }
    }

    // finding the k'th ancestor of node node n1;
    int k, n1;
    int node = 0;
    for(int j = 0; j < LOG; j++){
        if(k & (1 << j)){
            node = up[node][j];
            if(node == -1) return -1;
        }
    }
    // for find the ancestor we traverse up according to the binary representation of k
    // if the bth bit is set in binary representation k then go 2^b up if not then skip
    // during this if node value become -1 then ans is -1 because k is more than the length of path
    // else return final node after processing
    return node;
    
}

/* 
    ans buildup...
    
    if you have to find the k'th ancestor of a node 
    ->  the naive approach is from that node traverse back to toward the root
        till you find the k'th node from the node
        ->  time complexity is O(k) so for n queries -> O(n*k);

    instead of going one step up, go in power of 2 steps up
    like -> 1, 2, 4, 8, ....
    that's why name binary lifting

*/