#include<bits/stdc++.h>
#include"underline.h"

using namespace std;

class spellchecker{
    map<string,bool> dictionary;
    string main_dictionary = "dictionary.txt";

    public:

    void insert_dictionary(string dictionary_name);
    void insert_spell(string word);
    bool is_in_dictionary(string word);
    void replace_wrong_spell(string file_name);
    vector<string> suggestion(string MisSpellWord);
    int checking_file(string filename);

    spellchecker();

};
