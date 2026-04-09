#include<bits/stdc++.h>
using namespace std;

long long power(long long a, long long b, long long m){
    long long res = 1;
    while(b){
        if(b&1) res = (res * a) % m;
        a = (a * a) % m;
        b = b >> 1;
    }
    return res;
}
vector<long long> fact, inverse_fact;
int maxi = 1e5 + 5;
int mod = 1e9 + 7;
void func(){
    
    fact.resize(maxi);
    inverse_fact.resize(maxi);

    for(int i = 1; i <= 1e5; i++){
        fact[i] = (fact[i-1] * i) % mod;
    }
    
    inverse_fact[maxi] = power(fact[maxi], mod - 2, mod);

    for(int i = maxi - 1; i >= 0; i--){
        inverse_fact[i] = (inverse_fact[i + 1] * (i + 1)) % mod;
    }
    /*
        we do reverse loop to find inverse_fact in o(n)
        we use the identity
        i ! = (i + 1)!/ (i + 1);
        1 / i ! = 1/(i + 1)!  * (i + 1);
    
    */

}
long long nCr(long n, long r){
    return ((fact[n] * inverse_fact[r]) % mod * inverse_fact[n - r]) % mod;
}
int main(){
    int n;
}