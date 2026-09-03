#include<bits/stdc++.h>
using namespace std;

int main(){

    // vector *********************
    vector<int> v;
    sort(v.begin(), v.end());              // ascending
    sort(v.begin(), v.end(), greater<int>()); // descending
    reverse(v.begin(), v.end());            // reverse

    // custom sorting
    sort(v.begin(), v.end(), [](int a, int b) {
        return a > b;
    });
    int x;
    v.push_back(x);        // add at end
    v.pop_back();          // remove last
    v.size();              // size
    v.empty();             // check empty
    v.front();             // first
    v.back();              // last
    v.clear();             // remove all


    // ****************************
    
    binary_search(v.begin(), v.end(), x); // return true or false;

    lower_bound(v.begin(), v.end(), x); // value >= x
    int idx = lower_bound(v.begin(), v.end(), x) - v.begin();

    upper_bound(v.begin(), v.end(), x); // value > x


    // min / max

    *min_element(v.begin(), v.end());
    *max_element(v.begin(), v.end());

    // sum
    long long sum = accumulate(v.begin(), v.end(), 0LL);

    // count
    count(v.begin(), v.end(), x);

    //Count elements satisfying a condition:

    count_if(v.begin(), v.end(), [](int x) {
        return x % 2 == 0;
    });

    // remove all occurrence of x
    v.erase(remove(v.begin(), v.end(), x), v.end());

    v.erase(
        remove_if(v.begin(), v.end(), [](int x) {
            return x < 0;
        }),
        v.end()
    );

    // set

    set<int> st;

    st.insert(x);
    st.erase(x);
    st.count(x);       // 0 or 1
    st.find(x);
    st.begin();
    st.end();

    auto it = st.lower_bound(x); // first element >= x
    auto it = st.upper_bound(x); // first element > x;

    // multiset
    multiset<int> ms;

    ms.insert(x);
    ms.erase(ms.find(x));   // erase only ONE occurrence

    ms.erase(x); // removes all occurrence of x

    // map
    map<int, int> mp;
    int value;
    mp[x]++;          // frequency
    mp[x] = value;
    mp.erase(x);
    mp.count(x);
    mp.find(x);



    // Priority Queue

//Max heap

    priority_queue<int> pq;
    pq.push(x);
    pq.top();
    pq.pop();
    pq.empty();
    pq.size();


    //Min heap

    //This is extremely important:

    priority_queue<int, vector<int>, greater<int>> pq;
    
    pair<int,int> p = {10, 20};

    p.first;
    p.second;

    //Create quickly:

    auto p = make_pair(10, 20);


    //String
    string s = "";
    s.size();
    s.empty();
    s.push_back('a');
    s.pop_back();
    int pos, len;
    s.substr(pos, len);
    s.find("abc");
    s.erase(pos, len);

    //Convert:

    stoi("123");       // string -> int
    stoll("123456");   // string -> long long
    to_string(123);    // int -> string



    //Useful string / character checks
    int c;

    isdigit(c);
    isalpha(c);
    isalnum(c);
    islower(c);
    isupper(c);
    tolower(c);
    toupper(c);

    // Rotate
    int k;
    rotate(v.begin(), v.begin() + k, v.end());

    /*
        1 2 3 4 5

        with k = 2:

        3 4 5 1 2

    */

    next_permutation(v.begin(), v.end());

    // custom set
    struct cmp {
        bool operator()(const pair<int,int>& a,
                        const pair<int,int>& b) const {
            return a.second < b.second;
        }
    };

    set<pair<int,int>, cmp> s;

// Now the set orders pairs according to second



}