/*
    What is an Articulation point?

    An articulation point is (also called cut vertex) is a vertex
    such that :-
    if we remove this vertex and all edges connected to it,
    then the number of connected components of the graph increases

    simple word :- A vertex whose failure can disconnect the network

        1     here is 2 fails it becomes 2 connected component
       / \
      2   3
      |
      4



    what are we really trying to detect?

    suppose DFS gives us
        u
       /
      v
     / \
    x   y

    here v is a dfs child of u

    imp. ques :-
    can the entire subtree of v reach some ancestor of u without passing through u?

    if NO, then removing u disconnect that subtree
    That's the entire idea

    ** How do we efficiently know whether a subtree can escape?
    tin[u] = the time at which we first visit u
    low[u] = what is the earliest ancestor that subtree of u can reach without going through the parent edge

*/

#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> tin, low;
vector<bool> isArticulation;
int timer;

void dfs(int u, int par){

    int children = 0;
    tin[u] = low[u] = timer++;

    for(auto& v : adj[u]){
        if(v == par) continue;

        if(tin[v] == -1){
            dfs(v, u);
            children++;
            low[u] = min(low[u], low[v]);

            if(par != -1 && low[v] >= tin[u]){
                isArticulation[u] = true;
            }
        }
        else{
            low[u] = min(low[u], tin[v]);
        }
    }
    if(par == -1 && children > 1){
        isArticulation[u] = true;
    }
}
int main(){
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        adj.resize(n);
        tin.assign(n, -1);
        low.resize(n);
        isArticulation.resize(n);

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                int x;
                cin >> x;
                if(x == 1){
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        for(int i = 0; i < n; i++){
            if(tin[i] == -1){
                dfs(i, -1);
            }
        }
        int ans = 0;
        for(int i = 0; i < n; i++){
            if(isArticulation[i]){
                ans++;
            }
        }
        cout << ans << endl;
    }
}
