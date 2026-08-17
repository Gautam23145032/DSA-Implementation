
#include <bits/stdc++.h>
using namespace std;

string manacher(string s){
    string t = "#";
    for(char c : s){
        t += c;
        t += '#';
    }

    int n = t.size();
    vector<int> p(n, 0);

    int c = 0; // center of right most palindrome
    int r = 0; // right boundary

    int bestCenter = 0;
    int bestRadius = 0;

    for(int i = 0; i < n; i++){
        // mirror of i around c
        /*
            ...i...c...mirror...
            the distance from i to c is c-i;
            mirror should also be same distance
            mirror - c = c - i
        
        */
        int mirror = 2*c - i;


        //reuse prev info
        if(i < r){
            p[i] = min(r-i, p[mirror]);
        }

        // expand around i

        while(i + p[i] + 1 < n && i - p[i] - 1 >= 0 &&
            t[i + p[i] + 1] == t[i - p[i] - 1]){
                p[i]++;
            }

        // update the rightmost palindrome

        if(i + p[i] > r){
            c = i;
            r = i + p[i];
        }

        // store the longest
        if(p[i] > bestRadius){
            bestRadius = p[i];
            bestCenter = i;
        }

        // convert transformed indices back to original string

        

    }
    int start = (bestCenter - bestRadius)/2;

    return s.substr(start, bestRadius);
}

