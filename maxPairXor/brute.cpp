#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
    vector<int> arr(n);
    int ans = 0;
    // try all possible pair;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            ans = max(ans, arr[i] ^ arr[j]);
        }
    }
}