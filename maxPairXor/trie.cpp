#include<bits/stdc++.h>
using namespace std;

class TrieNode{
public:
    TrieNode* child[2];
    TrieNode(){
        child[0] = child[1] = nullptr;
    }

};
class Trie{
public:
    TrieNode* root;
    Trie(){
        root = new TrieNode();
    }

    void insert(int num){
        TrieNode* node = root;
        for(int i = 31; i >= 0; i--){
            int bit = (num >> i) & 1;

            if(node->child[bit] == nullptr){
                node->child[bit] = new TrieNode();
            }
            node = node->child[bit];

        }
    }

};

int getMaxXor(int num, TrieNode* node){
    int ans = 0;

    for(int i = 31; i >= 0; i--){
        int bit = (num >> i) & 1;
        int des_bit = 1 - bit;
        if(node->child[des_bit]){
            ans = ans | (1 << i);
            node = node->child[des_bit];
        }
        else{
            node = node->child[bit];
        }
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
    int ans = 0;
    Trie trie;
    for(int num : arr){
        trie.insert(num);
    }
    for(int num : arr){
        TrieNode* node = trie.root;
        ans = max(ans, getMaxXor(num, node));
    }
    cout << ans;
}

/*
    we store binary form of all number in a trie from msb to lsb

    and for each number in array we try to find a number in trie to maximize it greedily
    so walk over trie bit by bit of current number and try to go to that child which is
    opposite of current bit because

    why? because opposite bit xor will be 1 and also we are going from msb to lsb so setting the current bit 1 if the child is
    present corresponding to des_bit is always beneficial

*/