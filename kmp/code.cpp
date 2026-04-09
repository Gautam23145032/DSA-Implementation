#include<bits/stdc++.h>
using namespace std;

int main(){
    string s, p;
    int n = s.size();
    int m = p.size();

    vector<int> lps(m); // largest prefix which is also a suffix at idx i;
    lps[0] = 0;
    int i = 1;
    int len = 0;
    while(i < m){
        if(p[i] == p[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if(len != 0){
                len = lps[len-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}
