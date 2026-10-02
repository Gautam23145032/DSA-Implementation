#include<bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> par;
int mst(int n, vector<vector<int>>& edges){

    adj.resize(n);
    for(auto& it : edges){
        adj[it[0]].push_back({it[1], it[2]});
        adj[it[1]].push_back({it[0], it[2]});

    }
    par.assign(n, -1);
    using T = tuple<long long, int, int>;

    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, 0, -1});
    vector<bool> inMst(n, false);

    int tot_weight = 0;
    int included_vert = 0;

    while(!pq.empty()){
        auto[wt, u, p] = pq.top();
        pq.pop();

        if(inMst[u]) continue;

        inMst[u] = true;
        par[u] = p;

        tot_weight += wt;

        for(auto& [v, w] : adj[u]){
            if(inMst[v]) continue;
            pq.push({w, v, u});
        }
    }
    return tot_weight;
}


int main(){

}
