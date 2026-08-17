/*
    it is useful in finding the bridges in graph

    suppose we have an undirected graph

        1
        / \
        2---3
            \
            4
    
    if we remove 3-4 node 4 gets disconnected
    so 3-4 is a bridge

    The main idea
    during the dfs for every node u, we calculate two values
    tin[u] -> the time when we first visit u
    DFS order:
    1 → 2 → 3 → 4
    tin[1] = 0
    tin[2] = 1
    tin[3] = 2
    tin[4] = 3


    low[u] -> this tells us
    what is the earliest-visited vertex that u or its dfs subtree can reach using 
    -> dfs tree edges downward
    -> at most one back edge upward

    for example
        1
        / \
        2---3

    dfs might go : 1 -> 2 -> 3
    when we are at 3, there is an edge 3 -> 1, this is back edge
    and because 2 can reach 3, which can reach 1
    low[2] = 0;


    # why does this detect a bridge?

    suppose dfs has u -> v

    where v is child of u

    ask : can the subtree of v reach u or any ancestor of u without using u -> v?
    if yes, then u -> v is not a bridge
    if no, then removing u->v disconnects the graph

    mathematically :
    if(low[v] > tin[u]) then u->v is a bridge

    see carefully strictly greater

    if(low[v] == tin[u]) then v's subtree can reach u

    how do we calculate low ?

    initially : 
    tin[u] = low[u] = timer++;
    then look at every neighbour of v
    there are two cases

    case 1) v is not visited
    dfs(v, u)

    after returning :
    low[u] = min(low[u], low[v]);

    why ? because v's subtree might have found a back edges to some ancestor of u

    case 2) v is already visited
    then we have a back edge
    low[u] = min(low[u], tin[v]);
    
    but there is one important exception
    if(v == parent) continue;
    because we don't want to treat the edge back to our parent as back edge


*/

#include<bits/stdc++.h>
using namespace std;

int timer = 0;
vector<vector<int>> adj;
vector<int> tin, low;
vector<pair<int, int>> bridges;

void dfs(int u, int parent){

    // time when we first visit u
    tin[u] = low[u] = timer++;
    for(int v : adj[u]){
        if(v == parent) continue;

        // if v is not visited
        if(tin[v] == -1){
            dfs(v, u);

            // v's subtree ,ay have a back edge to an ancestor of u

            low[u] = min(low[u], low[v]);
            
            // if v cannot reach u or any ancestor without using
            // u -> v then u -> v is bridge

            if(low[v] > tin[u]){
                bridges.push_back({u, v});
            }
        }
            // v is already visited
        else{
            // u -> v is a back edge
            low[u] = min(low[u], tin[v]);
            
        }
    }
}
int main(){
    int n, m;
    cin >> n >> m;

    adj.resize(n);
    tin.assign(n, -1);
    low.resize(n);

    for (int i = 0; i < m; i++) {

        int u, v;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    for(int i = 0; i < n; i++){
        if(tin[i] == -1){
            dfs(i, -1);
        }
    }

    // print the bridges
}