/*
    when edge vector is given

*/

#include<bits/stdc++.h>
using namespace std;

struct edge{
    int u, v;
    long long wt;
};
class DSU{
public:
    vector<int> par, sz;
    DSU(int n){
        par.resize(n);
        sz.assign(n, 1);
        for(int i = 0; i < n; i++){
            par[i] = i;
        }
    }

    int find(int u){
        if(par[u] == u) return u;
        return par[u] = find(par[u]);
    }

    bool unite(int u, int v){
        int pu = find(u), pv = find(v);
        if(pu == pv) return false;

        if(sz[pu] < sz[pv]) swap(pu, pv);

        par[pv] = pu;
        sz[pu] += sz[pv];

        return true;
    }
};
vector<edge> edges;
int mst(int n){

    sort(edges.begin(), edges.end(), [&](edge& a, edge b){
        return a.wt < b.wt;
    });

    DSU dsu(n);
    long long tot = 0;
    int edge_cnt = 0;
    vector<vector<pair<int, int>>> mst_adj(n);
    for(auto& e : edges){
        if(dsu.unite(e.u, e.v)){
            tot += e.wt;
            edge_cnt++;
            mst_adj[e.u].push_back({e.v, e.wt});
            mst_adj[e.v].push_back({e.u, e.wt});
            if(edge_cnt == n-1) break;
        }
    }

    if(edge_cnt != n-1) return -1;

    return tot;
}
int main(){

}