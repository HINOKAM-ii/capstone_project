#include<bits/stdc++.h>
#include <fstream>

using namespace std;

#include "trie.cpp"


int main() {
    ifstream inputfile("words_alpha.txt");
    trie strie;

    if(inputfile.is_open()){
        cout << "File opened successfully.\n";

        string word;

        while( getline(inputfile , word) )
            strie.insertWord(word);

    }

    cout << ( strie.searchWord("a") ? "FOUND" : "NOT FOUND" ) << endl;

    return 0;
}