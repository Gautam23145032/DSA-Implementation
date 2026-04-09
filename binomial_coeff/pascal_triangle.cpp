/*
    nCr = (n-1)Cr + (n-1)C(r-1);

    nCr = n! / (r! * (n-r)!)
    (n-1)Cr = (n-1)! / (r! * (n - 1 - r)!) --- 1
    (n-1)C(r-1) = (n-1)! / ((r-1)! * (n - r)!); ---2

    adding 1 and 2;
    it will result in nCr;
    also nC0 = 1 and nCn = 1 for all n -> base case

    so we take 2d table

*/
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n = 10;              // example
    int mod = 1e9 + 7;

    vector<vector<long long>> table(n+1, vector<long long>(n+1, 0));

    // base cases
    for(int i = 0; i <= n; i++){
        table[i][0] = 1;
        table[i][i] = 1;
    }

    // fill DP table
    for(int i = 1; i <= n; i++){
        for(int j = 1; j < i; j++){
            table[i][j] = (table[i-1][j] + table[i-1][j-1]) % mod;
        }
    }

    // print example
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= i; j++){
            cout << table[i][j] << " ";
        }
        cout << "\n";
    }
}