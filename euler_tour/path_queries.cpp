#include<bits/stdc++.h>
using namespace std;

/*
    this is interesting case

    for a path -> answer depend on nodes from multiple subtrees
    so subtree sum is not beneficial here

    for path sum ->
    first important concept -> LCA
    -> every path between u and v goes through their LCA

    so for static queries (without update)

    we calculate the pref[u] -> sum of values from root to u

    void dfs(int u, int par){

        for(auto v : tree[u]){

            if(v == par) continue;

            pref[v] = pref[u] + value[v];

            dfs(v,u);
        }
    }

    and let lca(u, v) = w; -> can be calculate using binary lifting o(log n)

    so path sum = pref[u] + pref[v] - 2 * pref[w] + val[w];

    we have to add val[w] -> because removing 2*pref[w] remove the lca contribution in path, so we add

    this above technique is useful only when there is no any update query

    what if updates exist

    now all affected pref[] values become wrong
    -> recomputing o(n) per update -> not accepted

    # Dynamic path queries
    this is where Heavy-Light Decomposition (HLD) comes in

    why euler order alone fails?
    for subtree queries -> euler array is contiguous ranges after euler flattening

    but path path is not contiguous in euler order 

    so one segment tree query cannot answer path sums


    Main idea of HLD 
    we want any path to become few contiguous ranges in an array then
    segment tree can answer it

    Heavy Edge and Light Edges

    for every node:-> choose the child having maxm subtree size -> that edge become heavy and all other child edges become light

    


*/