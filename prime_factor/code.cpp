/*
    if you want the unique prime factors of a number x,
    the standard trivial division algorithm is 
    time complexity O(root x)

*/

#include<bits/stdc++.h>
using namespace std;

vector<int> solve(int x){
    vector<int> fact;

    for(int i = 2; i * i <= x; i++){
        if(x % i == 0){
            fact.push_back(i);
            // remove all occurrences of i
            while(x % i == 0){
                x = x/i;
            }
        }
    }
    if(x > 1) fact.push_back(x);
    return fact;
}

/*
    if we want to find for many number then spf method is
    more feasible
    time complexity
    preprocessing O(N log log N)
    Unique prime factors of each number O(log x);


*/

const int maxi = 1e6;
vector<int> spf(maxi + 1);

// build spf array
void buildSpf(){
    for(int i = 0; i <= maxi; i++){
        spf[i] = i;
    }

    spf[0] = 0;
    spf[1] = 1;

    for(int i = 2; i * i <= maxi; i++){
        if(spf[i] == i){
            for(int j = i * i; j <= maxi; j += i){
                if(spf[j] == j){
                    spf[j] = i;
                }
            }
        }
    }
}

vector<int> cnt_p(int x){
    vector<int> fact;
    while(x > 1){
        int p = spf[x];
        fact.push_back(p);

        while(x % p == 0){
            x /= p;
        }
    }
    return fact;
}

int main(){

}