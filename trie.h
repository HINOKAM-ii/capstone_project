// #include<bits/stdc++.h>
using namespace std;

struct trieNode{
    bool terminating = false;
    struct trieNode* children[26] = {NULL};
};

class trie{
    trieNode* root;
    public:
    trie();
    
    void insertWord(string word);
    bool searchWord(string word);
    bool deleteWord(string word);
    bool updateWord(string oldWord, string newWord);
};
