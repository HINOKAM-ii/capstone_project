// #include<bits/stdc++.h>
// using namespace std;
#include "trie.h"

trie :: trie(){
    root = new trieNode();
}

void trie :: insertWord(string word){
    trieNode* curr = root;

    for (char c : word)   
    {
        if(curr->children[c - 'a'] == NULL){
            curr->children[c - 'a'] = new trieNode();
        }
        curr = curr->children[c - 'a'];
    }
    curr->terminating = true;
}

bool trie :: searchWord(string word){
    trieNode* curr = root;

    for(char c : word){
        if(curr->children[c - 'a'] == NULL){
            return false;
        }
        curr = curr->children[c - 'a'];
    }
    return curr->terminating;
}

bool trie :: deleteWord(string word){
    trieNode* curr = root;

    for(char c : word){
        if(curr->children[c - 'a'] == NULL){
            return false;
        }
        curr = curr->children[c - 'a'];
    }
    curr->terminating = false;
    return true;
}

bool trie :: updateWord(string oldWord , string newWord){

    bool find = deleteWord(oldWord);

    if(find)
        this->insertWord(newWord);
    
    return find;
}