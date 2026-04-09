#include<bits/stdc++.h>
using namespace std;
int findMaxXor(vector<int>& nums){
    int ans = 0;  // stores the max xor we are building
    int mask = 0; // used to extract the prefix (MSB art of numbers)

    // iterate form msb to lsb

    for(int bit = 31; bit >= 0; bit--){
        //include current bit in mask
        // this means we are now considering one more bit from left
        mask = mask | (1 << bit);

        // store all prefixes of numbers using current mask
        // prefix = left part of number till current bit;

        unordered_set<int> st;
        for(int num : nums){
            st.insert(num & mask);
        }

        // try to set this bit in ans (greedy attempt)
        // assume current bit can be 1
        int candidate =  ans | (1 << bit);
        // now check if there exist two prefixes such that
        // p1 ^ p2 = candidate

        for(int pref : st){
            // if p1 ^ p2 = candidate 
            // then p2 = p1 ^ candidate
            // so we check if pref ^ candidate exist in set
            if(st.count(pref ^ candidate)){
                ans = candidate;
                break;
            }
        }
        // if not found -> this bit remains 0; (do nothing)
    }
    return ans;
}
int main(){
    int n;
    cin >> n;

    vector<int> arr(n);
    for(int i = 0; i < n; i++){
        cin >> arr[i];
    }
    cout << findMaxXor(arr);
    
}

/*
    build ans bit by bit from MSB -> LSB;

    at each step we check
    -> is it possible to make this bit = 1 in the final xor

    key property of xor
    a ^ b = c <=> a = b ^ c
    

*/