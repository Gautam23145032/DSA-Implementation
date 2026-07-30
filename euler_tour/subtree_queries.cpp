#include<bits/stdc++.h>
using namespace std;



/*

    Euler tour is a way of recording the order in which a dfs enters and leaves nodes of a tree
    -> useful for subtree queries, lca

    the core idea
    During DFS we can record 
    -> when we first enter a node
    -> when we exit a node after processing all its children

    this sequence has length 2*n because each node appears twice(enter and exit)

    we maintain two arrays tin, tout
    tin[u] = times when DFS enters u
    tout[u] = times when DFS exit u

    important property
    a node u is an ancestor of v iff
    tin[u] <= tin[v] extand tout[v] <= tout[u]


    # using euler tour to finding subtrees sum

    -> for a static tree, in one dfs we could calculate the sum but 
    -> when there is update appear in tree, we need to do euler tour and apply segment tree to ans the queries

    key observation

    -> during DFS, all nodes of a subtree appear consecutively in euler order

    suppose a tree
          1
        / | \
       2  3  4
      / \
     5   6

    suppose every node has a value
    1 -> 10
    2 -> 20
    3 -> 30
    4 -> 40
    5 -> 50
    6 -> 60

    and we want queries like sum of subtree 2 = {2, 5, 6} -> 20 + 50 + 60 = 130

    when we do euler tour

    DFS entry order
    1
    |
    +--2
    |   +--5
    |   +--6
    |
    +--3
    |
    +--4

    DFS visits
    1 2 5 6 3 4 -> store this array,
    euler = [1, 2, 5, 6, 3, 4]

    computing tin[]

*/

int timer = 0;
vector<int> tin, euler, sz;
vector<vector<int>> adj;
void dfs(int u, int par){
    tin[u] = timer++;
    euler.push_back(u);

    sz[u] = 1;
    for(auto& it : adj[u]){
        if(it == par) continue;
        dfs(it, u);

        sz[u] += sz[it];
    }

}

/*

    Magical property

    for every node,
    subtree(u) = [tin[u], tin[u] + sz[u] - 1] inside euler array

    Building flattened tree array
    node:  1  2  3  4  5  6
    value:10 20 30 40 50 60

    euler order
    1 2 5 6 3 4

    flattened array -> flat[tin[node]] = value[node];

    for query subtree sum
    find the range-> L = tin[u], R = tin[u] + sz[u] - 1;
    now it becomes a normal range query

    you can apply segtree on this array for different type of query like sum, max, min, etc

    in case updating a node value
    we run segtree query -> update(tin[u], val) -> tin[u] is the actual idx of node u in flat array
    

    if we do post order tree flattening then we use tout
    tout[u] = out time 

    dfs(x){
        for(child)
            dfs(child);
        tout[x] = timer++;
    }

    the range for subtree at node u -> [tout[u] - sz[x] + 1, tout[u]];

    in standard euler tour we use tin
    and range is -> [tin[u], tin[u] + sz[u] - 1];

*/

