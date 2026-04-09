/*
    modular arithmetic of division

    a * x = 1 (mod M);

    x is called the modular inverse of a modulo M
    so, x = a^-1 (mod M);

    *** Inverse exist only when gcd(a, M) = 1;
        a and M must be co-prime

    Fermat's little theorem
    when M is prime like (1e9 + 7) -> gcd(a, M) = 1

    then a^(M-1) = 1 (mod M)

    divid by a both side

    => a^(M - 2) = a^-1 (mod M);
    => a^-1 = a^(M-2);

    so modular inverse of a id a^-1 = a^(M-2) = power(a, M-2);

    we find  power(a, M-2) by binary exponentiation

*/

#include<bits/stdc++.h>
using namespace std;

long long power(long long a, long b, int mod){
    long long res = 1;
    while(b){
        if(b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b = b >> 1;
    }
    return res;
}

long long mod_inverse(long long a, int m){
    return power(a, m-2, m);
}
int main(){

}