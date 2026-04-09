#include<bits/stdc++.h>
using namespace std;

class TrieNode{
public :
    bool isEnd;
    vector<TrieNode*> children;

    TrieNode(){
        isEnd =  false;
        children = vector<TrieNode*>(26, nullptr);
    }
};

class Trie{
public:
    TrieNode* root;

    Trie(){
        root = new TrieNode();
    }

    void insert(string word){
        TrieNode* node = root;

        for(char& ch : word){
            int ind = ch - 'a';
            if(node->children[ind] == nullptr){
                node->children[ind] = new TrieNode();
            }
            node = node->children[ind];
        }
        node->isEnd = true;
    }
    TrieNode* searchPrefix(string prefix){
        TrieNode* node = root;
        for(char& ch : prefix){
            int ind = ch - 'a';
            if(node->children[ind] == nullptr) return nullptr;
            node = node->children[ind];
        }
        return node;
    }

    void collect(TrieNode* node, string pref, vector<string>& result){
        if(result.size() >= 5) return ;
        if(node->isEnd == true) result.push_back(pref);

        for(int i = 0; i < 26; i++){
           if(node->children[i])
                collect(node->children[i], pref + char('a' + i), result);
            
        }
    }
    vector<string> suggest(string prefix){
        TrieNode* node = searchPrefix(prefix);
        vector<string> result;
        if(node) collect(node, prefix, result);
        return result;
    }
};

int main(){
    // run your code
}