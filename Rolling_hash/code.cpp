#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    string s;
    int n;
    vector<unsigned long long> pref, power;
    const unsigned long long base = 131;

    void buildHash(){
        n = s.size();
        pref.assign(n + 1, 0);
        power.assign(n + 1, 1);

        for(int i = 0; i < n; i++){
            pref[i+1] = pref[i] * base + s[i];
            power[i + 1] = power[i] * base;
        }
    }
    unsigned long long getHash(int l, int r){
        return pref[r + 1] - pref[l] * power[r - l + 1];
    }

    bool check(int len, int& start){
        unordered_set<unsigned long long> seen;

        for(int i = 0; i + len - 1 < n; i++){
            unsigned long long h = getHash(i, i + len - 1);
            if(seen.count(h)){
                start = i;
                return true;
            }
            seen.insert(h);
        }
        return false;
    }
    string longestDupSubstring(string s) {
        this->s = s;
        n = s.size();
        buildHash();

        int best_start = -1, best_len = 0;
        int low = 1, high = n-1;

        while(low <= high){
            int mid = low + (high - low) / 2;
            int pos = -1;
            if(check(mid, pos)){
                best_start = pos;
                best_len = mid;
                low = mid + 1;
            }
            else{
                high = mid - 1;
            }
        }

        if(best_start == -1) return "";
        return s.substr(best_start, best_len);
    }
};

/*
    rolling hash
    convert each substring into a number (hash)
    compare hashed numbers -> O(n);

    hash of string ->
    "abc" = 1 * base^2 + 2 * base^1 + 3 * base ^ 0;
    order matters

    problem with naive hashing
    => if we compute hash like this every time -> thats slow for sliding windows

    Rolling hash idea
    when u move window by 1 char -> you should update hash in O(1);
    so reuse previous hash -> that's why called rolling

    prefix hash
    pref[i] = hash of s[0....i-1];

    pref[i+1] = pref[i] * base + values(s[i]);

    substring s[l...r]
    formula -> hash(l, r) = pref[r+1] - pref[l] * base^(r-l+1);

    eg->
    "abcdm"

    pref[4] = hash("abcd") = 1 * b ^ 3 + 2 * b^2 + 3 * b^1 + 4 * b^0
    pref[1] = hash("ab") = 1 * b ^ 1 + 2 * b ^ 0;
                          - (1*b^3 + 2 * b^2)
    hash(2, 3) = hash("cd") = pref[4] - pref[2] * b ^ (2)




    3 * b^1 + 4 * b^0
*/