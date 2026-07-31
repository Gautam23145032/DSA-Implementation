#include <bits/stdc++.h>
using namespace std;
/*
Term	Visits every edge exactly once?	Starts = Ends?
Euler Trail (Euler Path)	✅ Yes	❌ Not necessarily
Euler Circuit (Euler Cycle)	✅ Yes	✅ Yes
Euler Tour	Usually means an Euler Circuit (in most CP books), but some books use it for any Euler Trail.

*/
int main() {
    int n, m;
    cin >> n >> m;

    // adj[u] = {v, edge_id}
    // We store an edge id because the same undirected edge
    // appears in both adj[u] and adj[v].
    vector<vector<pair<int, int>>> adj(n + 1);

    // Degree of every vertex.
    vector<int> deg(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;

        adj[u].push_back({v, i});
        adj[v].push_back({u, i});

        deg[u]++;
        deg[v]++;
    }

    // Eulerian Circuit exists only if every vertex has even degree.
    for (int i = 1; i <= n; i++) {
        if (deg[i] & 1) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }

    // used[id] tells whether this edge has already been traversed.
    vector<bool> used(m, false);

    // Stores Euler tour in reverse order.
    vector<int> ans;

    function<void(int)> dfs = [&](int u) {

        // Keep traversing unused edges from current vertex.
        while (!adj[u].empty()) {

            // Take one edge.
            auto [v, id] = adj[u].back();
            adj[u].pop_back();

            // This edge might already have been used from
            // the opposite endpoint, so skip it.
            if (used[id])
                continue;

            // Mark edge as used so it is never traversed again.
            used[id] = true;

            // Continue DFS.
            dfs(v);
        }

        /*
            When no unused edges remain from u,
            add u to the answer.

            This is the key idea of Hierholzer's Algorithm.

            Vertices are added during backtracking,
            so the tour is obtained in reverse order.
        */
        ans.push_back(u);
    };

    // Start DFS from any vertex having edges.
    // (For CSES Mail Delivery, starting from 1 is sufficient.)
    dfs(1);

    /*
        An Euler tour containing m edges
        must contain exactly m+1 vertices.

        If not, some edges were unreachable,
        meaning the graph is disconnected.
    */
    if ((int)ans.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return 0;
    }

    // Since vertices were collected while backtracking,
    // reverse to obtain the correct Euler circuit.
    reverse(ans.begin(), ans.end());

    for (int x : ans)
        cout << x << " ";
    cout << '\n';

    return 0;
}

/*

Graph Type	       Euler Trail (Path)	            Euler Circuit (Cycle)

Undirected	Connected + exactly 0 or 2 vertices     Connected + all vertices have even degree
            of odd degree

Directed	All relevant vertices connected +        All relevant vertices connected +
            one vertex has out = in + 1 (start),     indegree = outdegree for every vertex
            one has in = out + 1 (end),
            all others have in = out


Degree Conditions at a Glance

Type	            Start Vertex	    End Vertex	    Other Vertices

Undirected Trail	Odd degree	        Odd degree	    Even degree
Undirected Circuit	Even degree	        Even degree	    Even degree
Directed Trail	    out = in + 1	    in = out + 1	in = out
Directed Circuit	in = out	        in = out	    in = out

*/