#include <bits/stdc++.h>
using namespace std;

// struct TrieNode{
//     TrieNode* children[26];
//     bool isEnd;
//     TrieNode(){
//         isEnd = false;
//         for(int i =0; i<26; i++){
//             children[i] = NULL;
//         }
//     }
// };

// class Trie{
//     private:
//         TrieNode* root;
//     public:
//         Trie() {root = new TrieNode();}

//         // chen
//         void insert(const string &word){
//             TrieNode* node = root;
//             for(char c : word){
//                 int index = c- 'a';
//                 if(!node->children[index]){
//                     node->children[index] = new TrieNode();
//                 }
//                 node = node->children[index];
//             }
//             node->isEnd = true;
//         }

//         // tra tu
//         bool search(const string &word){
//             TrieNode* node = root;
//             for(char c :word){
//                 int index = c - 'a';
//                 if(!node->children[index]) return false;
//                 node = node->children[index];
//             }
//             return node->isEnd;
//         }

// };

struct trienode{
    int children[26];
    bool isend;
    trienode() {
        memset(children, 0, sizeof(children));
        isend = false;
    }
};

const int maxNode = 6000000;
trienode *trie = new trienode[maxNode];
int nodecount = 1;

void insert(const string &s){
    int cur = 0;
    for(char c : s){
        int idx = c - 'a';
        if(trie[cur].children[idx] == 0) 
            trie[cur].children[idx] = nodecount++;
        cur = trie[cur].children[idx];
    }
    trie[cur].isend = true;
}

bool search(const string &s){
    int cur = 0;
    for(char c : s){
        int idx = c - 'a';
        if(trie[cur].children[idx] == 0) return false;
        cur = trie[cur].children[idx];
    }
    return trie[cur].isend;
}


int main(){
    //
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; cin >> n;
    string s;
    
    for(int i =0 ; i< n; i++){
        cin >> s;
        insert(s);
    }

    int q; cin >> q;
    string m;
    for(int i = 0; i< q; i++){
        cin >> m;
        if(search(m)){
            cout << "YES" <<endl;
        }
        else cout <<"NO" << endl;
    }

    return 0;
}