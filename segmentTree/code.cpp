#include<bits/stdc++.h>
using namespace std;

// range sum query
vector<int> seg;

void build(int i, int l, int r, vector<int>& arr){
    if(l == r){
        seg[i] = arr[l];
        return;
    }

    int mid = l + (r - l)/2;
    build(2*i + 1, l, mid, arr);
    build(2*i + 2, mid+1, r, arr);

    seg[i] = seg[2*i + 1] + seg[2*i + 2];
}

int sum_query(int a, int b, int i, int l, int r){
    if(a > r || b < l){
        return 0;
    }

    if(a <= l && r <= b) return seg[i];

    int mid = l + (r - l)/2;
    return sum_query(a, b, 2*i + 1, l, mid) + sum_query(a, b, 2*i + 2, mid + 1, r);
}
// point update....  not the range update that will lazy propagation
void update_query(int i, int l, int r, int pos, int val){
    if(l == r){
        seg[i] = val;
        return;
    }
    int mid = l + (r - l)/2;
    if(pos <= mid){
        update_query(2*i + 1, l, mid, pos, val);
    }
    else{
        update_query(2*i + 2, mid + 1, r, pos, val);
    }

    seg[i] = seg[2*i + 1] + seg[2*i + 2];
}


/* lazy propagation -> range update
    in lazy propagation when we find a node who represent the interval which lies 
    inside the desired interval then we count the number of ele represented by that
    node and instead of propagating all those child of that node we simply add the 
    val * (number of node ) and then update the lazy array set index of left child 
    and right child with val

    why we have done this?
    because updating all the element in that interval is too slow
    so instead we add the effect after adding the value in that interval
    and st the left and right child idx with value to process in future 
*/

vector<int> lazy1;
void update_range_sum(int a, int b, int val, int i, int l, int r){
    if(lazy1[i] != 0){
        seg[i] += (r - l + 1) * lazy1[i];
        if(l != r){
            lazy1[2*i + 1] = lazy1[i];
            lazy1[2*i + 2] = lazy1[i];
        }
        lazy1[i] = 0;
    }

    if(r < a || b < l || r > l){
        return;
    }

    if(a <= l && r <= b){
        seg[i] += (r - l + 1) * val;
        if(l != r){
            lazy1[2*i + 1] += val;
            lazy1[2*i + 2] += val;
        }
        return;
    }

    int mid = l + (r - l)/2;
    update_range_sum(a, b, val, 2*i + 1, l, mid);
    update_range_sum(a, b, 2*i + 2, val, mid + 1, r);
    seg[i] = seg[2*i + 1] + seg[2*i + 2];
}

vector<int> lazy2;

void update_range_min(int a, int b, int val, int i, int l, int r){
    if(lazy1[i] != 0){
        seg[i] = seg[i] + lazy1[i];
        if(l != r){
            lazy1[2*i + 1] = lazy1[i];
            lazy1[2*i + 2] = lazy2[i];
        }
        lazy1[i] = 0;
    }
    if(r < a || b < l || r > l){
        return;
    }

    if(a <= l && r <= b){
        seg[i] +=  val;
        if(l != r){
            lazy1[2*i + 1] += val;
            lazy1[2*i + 2] += val;
        }
        return;
    }

    int mid = l + (r - l)/2;
    update_range_min(a, b, val, 2*i + 1, l, mid);
    update_range_min(a, b, 2*i + 2, val, mid+1, r);
    seg[i] = min(seg[2*i + 1], seg[2*i + 2]);
}




/*
    why the size of segment tree array is 4 * n;

    when n is power of 2
    suppose n = 8
    so total node is 1 + 2 + 4 + 8 = 15 = 2*n -1
    in general for n = 2 ^ k -> only about 2 *n nodes are there so 2n space is required

    if n is not a power of 2

    ltt n = 5;
    then seg tree usually implemented as if the array were padded to next power of 2
    let m = 8;

    now the tree behaves like a complete tree with 8 leaves

    2 * m - 1 = 15 nodes
    while n = 5, so node count is much larger than 2n - 1

    general proof 
    m = next power of 2 >= n;
    then m < 2*n
    
    why? if m is the next power of two 
    then 
        m/2 < n <= m => m  < 2n

        2m - 1 = 4n - 1 => ~ 4n
        


*/