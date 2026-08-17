#include<bits/stdc++.h>
using namespace std;

 int n, m;
vector<vector<long long>> pref, arr;

void build(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            pref[i][j] = arr[i][j];
            if(i > 0){
                pref[i][j] += pref[i-1][j];
            }
            if(j > 0){
                pref[i][j] += pref[i][j-1];
            }

            if(i > 0 && j > 0){
                pref[i][j] -= pref[i-1][j-1];
            }
        }
    }
}
long long getSum(int r1, int c1, int r2, int c2, vector<vector<long long>>& pref) {

    long long ans = pref[r2][c2];

    if(r1 > 0) ans -= pref[r1 - 1][c2];
    if(c1 > 0) ans -= pref[r2][c1 - 1];
    if(r1 > 0 && c1 > 0) ans += pref[r1 - 1][c1 - 1];

    return ans;
}
int main(){
    cin >> n >> m;
}