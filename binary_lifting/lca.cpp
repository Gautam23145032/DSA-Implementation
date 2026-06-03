#include <bits/stdc++.h>
using namespace std;
class LCA {
public:
    static const int LOG = 20;

    int n;
    vector<int> depth, parent;
    vector<vector<int>> adj, up;

    LCA(int n, vector<vector<int>>& adj) {
        this->n = n;
        this->adj = adj;

        depth.resize(n);
        parent.resize(n, -1);
        up.assign(n, vector<int>(LOG, -1));
    }

    void dfs(int node, int par) {

        parent[node] = par;

        for (int child : adj[node]) {
            if (child == par) continue;

            depth[child] = depth[node] + 1;
            dfs(child, node);
        }
    }

    void build(int root = 0) {

        dfs(root, -1);

        for (int i = 0; i < n; i++) {
            up[i][0] = parent[i];
        }

        for (int j = 1; j < LOG; j++) {
            for (int i = 0; i < n; i++) {

                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
    }

    int lca(int u, int v) {

        if (depth[u] < depth[v])
            swap(u, v);

        int diff = depth[u] - depth[v];

        for (int i = 0; i < LOG; i++) {
            if (diff & (1 << i))
                u = up[u][i];
        }

        if (u == v)
            return u;

        for (int i = LOG - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }

        return up[u][0];
    }
};

/*

    for finding the lca of u, v

    find the depth of u, v from the root and make both node
    at equal level by uplifting the deeper node using binary lifting for kth ancestor

    then again use binary lifting to find the lca of those node
    Idea

    We want to move both nodes upward.

    But we must not jump over the LCA.

    So we try the largest jumps first.

    Suppose:

    up[x][k]

    means the 2^k-th ancestor of x.

    We check:

    if(up[u][i] != up[v][i])

    Why?

    Because if their 2^i ancestors are different, then the LCA is still above those ancestors.

    So it's safe to move both nodes up by 2^i.

    u = up[u][i];
    v = up[v][i];



*/