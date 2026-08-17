#include<bits/stdc++.h>
using namespace std;

/*  
    function to build lps
    lps[i] = length of the longest proper prefix of pattern[0..i] which also a suffix

     Example:
        Pattern = "ababc"

        Index    : 0 1 2 3 4
        Pattern  : a b a b c
        LPS      : 0 0 1 2 0

*/

vector<int> buildLPS(string& p){
    int m = p.size();
    vector<int> lps(m, 0);
    //length of prev longest prefix-suffix;

    int len = 0;
    // first char has always lps = 0;
    int i = 1;
    while(i < m){
        if(p[i] == p[len]){
            len++;
            lps[i] = len;
            i++;
        }
        else{
            //try the next smaller border
            if(len != 0){
                len = lps[len-1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

/*

    KMP pattern searching

    returns starting indices where pattern occurs


*/
vector<int> KMPsearch(string & txt, string pattern){
    vector<int> ans;
    int n = txt.size(), m = pattern.size();

    if(m == 0) return ans;

    vector<int> lps = buildLPS(pattern);

    int i = 0, j = 0;
    while(i < n){
        if(txt[i] == pattern[j]){
            i++;
            j++;
        }

        if(j == m){
            ans.push_back(i - m);
            j = lps[j-1]; 
        }
        else if(i < n && txt[i] != pattern[j]){

            if(j != 0){
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }
    return ans;

}
int main(){
    string s;
    cin >> s;
    int sz = s.size();
    
    vector<int> arr = buildLPS(s);
    int len = arr[sz-1];
    vector<int> ans;
    int i = sz - 1;
    while(len > 0){
        ans.push_back(len);
        len = arr[len-1];
    }
    reverse(ans.begin(), ans.end());
    for(auto& it : ans)  cout << it << " ";
}


