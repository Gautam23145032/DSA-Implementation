/*
    also called as Binary Indexed Tree (BIT)

    it is kind of seg_tree but much simpler than seg_tree


    problem:

    suppose you have
    Index : 1 2 3 4 5 6 7 8
    Value : 2 1 4 5 3 6 7 8

    you need to support
    update -> a[i] += x
    query -> sum(l, r)

    naively,
    updating is O(1), query O(n)
    
    using pref sum
    updating is O(n), querying O(1)

    we want update -> O(log n), query -> O(log n)
    this is where Fenwick tree comes in

    Basic Idea 
    instead of storing every prefix,
    store some carefully chosen ranges

    for example n = 8;

    BIT[1] -> [1]

    BIT[2] -> [1..2]

    BIT[3] -> [3]

    BIT[4] -> [1..4]

    BIT[5] -> [5]

    BIT[6] -> [5..6]

    BIT[7] -> [7]

    BIT[8] -> [1..8]

    each node stores a block whose size equals
    lowest set bit(index)

    ***Lowest set bit :- this is the heart of fenwick tree
    x & (-x)

    6 =110
        010 =2

    7 =111
        001 =1

    8 =1000
        1000 =8

    lowbit(i) = i & (-i)

    ***Meaning of BIT[i]

    BIT[i] stores [i - lowbit(i) + 1, i];

    eg. BIT[6] -> lowbit(6) = 2;
    it store [5, 6];

    *** pref query
    suppose we want sum(13)
    meaning (1...13)
    start 13 -> take BIT[13];
    suppose lowbit = 1 -> covers 13
    move to 13 - 1 = 12 -> take BIT[12]
    covers (9....12);
    move 12 - 4 = 8 -> take BIT[8]
    covers (1...8) 
    done

    so 13 -> 12 -> 8 -> 0;
    answer BIT13 + BIT12 + BIT8   exactly covers 1....13 no overlap

    algorithm

    int query(int idx){
        int sum = 0;

        while(idx > 0){
            sum += BIT[idx];
            idx -= idx&(-idx);
        }
        
        return sum;
    }

    *** Update

    suppose a[5] += 3;
    who contain index 5?
    BIT5, BIT6, BIT8, BIT9 .. so update all of them
    start = 5 -> move to 5 + 1 = 6 -> move to 6 + 2 = 8 -> move to 8 + 8 = 16

    algorithm

    void update(int idx, int val){
        while(idx <= n){
            BIT[idx] += val;
            idx += idx&(-idx);
        }
    }
*/

#include<bits/stdc++.h>
using namespace std;

struct Fenwick{
    int n;
    vector<long long> bit;

    Fenwick(int sz){
        n=sz;
        bit.assign(n+1,0);
    }

    void update(int idx,long long val){
        while(idx<=n){
            bit[idx]+=val;
            idx+=idx&-idx;
        }
    }

    long long query(int idx){
        long long ans=0;
        while(idx>0){
            ans+=bit[idx];
            idx-=idx&-idx;
        }
        return ans;
    }

    long long rangeQuery(int l,int r){
        return query(r)-query(l-1);
    }
};

int main(){

    int n=8;

    Fenwick ft(n);

    vector<int>a={0,2,1,4,5,3,6,7,8};

    for(int i=1;i<=n;i++)
        ft.update(i,a[i]);

    cout<<ft.rangeQuery(3,7);
}

/*
    Instead of

    n updates

    O(n log n)

    we can build in O(n).

    for(int i=1;i<=n;i++)
        bit[i]+=a[i];

    for(int i=1;i<=n;i++){
        int j=i+(i&-i);
        if(j<=n)
            bit[j]+=bit[i];
    }

    Many people don't know this optimization.


    Applications for Fenwick tree

    pref sum
    range sum query
    point updates
    inversion count
    counting element less than x (with coordinate compression)
    order statistics (find the k-th smallest)
    dynamic frequency arrays
    offline query processing


*/