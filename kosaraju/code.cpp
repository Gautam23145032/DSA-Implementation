/*
    it is used to find the strongly connected component

    an SSC is a maximal set of vertices where every vertex can 
    reach every other vertices

    1 → 2
    ↑   ↓
    4 ← 3

    |
    v

    5 → 6
    ↑   ↓
    └───┘

    here there is 2 SSC

    compress every SSC imagine replacing every SSC with a single node
    this is called condensation graph and 
    it is always a DAG because suppose there is 
    A -> B -> C -> A, every SSC  could reach every other SSC
    so they weren't separate SSC, they should have been one SSC

    kosaraju uses two DFS traversals

    First DFS
    we run DFS on the original graph
    whenever DFS finishes a node -> push it into an array

    eg. 1 -> 2 -> 3
    DFS: visit 1 visit 2 visit 3, 3 has no children
    finish order = 3;
    backtrack order = [3, 2]
    backtrack order = [3, 2, 1] -> notice children finishes before parents

    why store finishing order?

    let's use the SSC graph
    A -> B
    imagine DFS start from A
    A goes to B ; B finishes first then A finishes

    finish order = B A
    so source SSCs finish last

    DFS enters A 
    it cannot finish A until everything reachable from A is finished
    finish(A) > finish(B);

    What happens if DFS start from B
    then B finishes Later A finishes
    still finish(A) > finish(B) -> the property always holds

    Therefore

    Largest finishing time belongs to a source SCC.
    But There Is A Problem

    Suppose we start DFS from A.
    A → B
    If we now run DFS again on the original graph,

    starting from A,
    we'll visit
    A then B
    We'll incorrectly merge them.

    Need some trick.

    Reverse Every Edge
    Original

    A -----> B

    Reverse

    A <----- B

    Now start DFS from A.
    Can A go to B?

    No. Perfect. A remains isolated.

    Why Reverse Works
    Remember Original
    A → B

    Reverse

    A ← B

    Since we process A first (largest finish time),
    DFS cannot escape A.
    So we recover exactly one SCC.

    Then remove it.
    Repeat.

    Entire Algorithm 

    step1)
    run dfs on original graph
    store tfinishing order
    dfs1(u)
    {
        vis[u]=1;

        for(v:g[u])
            if(!vis[v])
                dfs1(v);

        order.push_back(u);
    }

    step 2)
    reverse graph
    u->v becomes v -> u

    strp 3)
    reverse finishing order
    reverse(order.begin(), order.end());

    step 4)
    run dfs on reversed graph

    every dfs gives exactly one SSC

*/

#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> graph, revGraph;
vector<bool> vis;
vector<int> order, kingdom;

void dfs1(int u) {
    vis[u] = true;
    for (int v : graph[u]) {
        if (!vis[v])
            dfs1(v);
    }
    order.push_back(u);
}

void dfs2(int u, int id) {
    vis[u] = true;
    kingdom[u] = id;

    for (int v : revGraph[u]) {
        if (!vis[v])
            dfs2(v, id);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    graph.resize(n + 1);
    revGraph.resize(n + 1);

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        graph[a].push_back(b);
        revGraph[b].push_back(a);   // reverse edge
    }

    vis.assign(n + 1, false);

    // First DFS: store finishing order
    for (int i = 1; i <= n; i++) {
        if (!vis[i])
            dfs1(i);
    }

    reverse(order.begin(), order.end());

    vis.assign(n + 1, false);
    kingdom.assign(n + 1, 0);

    int cnt = 0;

    // Second DFS on reversed graph
    for (int u : order) {
        if (!vis[u]) {
            cnt++;
            dfs2(u, cnt);
        }
    }

    cout << cnt << "\n";
    for (int i = 1; i <= n; i++)
        cout << kingdom[i] << " ";
    cout << "\n";

    return 0;
}