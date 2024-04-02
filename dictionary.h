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


spellchecker :: spellchecker(){
    insert_dictionary("dictionary.txt");
}

void spellchecker :: insert_spell(string word){
    dictionary[word] = true;
} 

int Distance(const string& str1 , const string& str2){
    int n = str1.size();
    int m = str2.size();

    int dis[n+1][m+1];

    for(int i = 0 ; i <= n ; i++) dis[i][0] = i;   
       
    for(int i = 0 ; i <= m ; i++) dis[0][i] = i;

    for (int i = 1; i <= n; i++){

        for (int j = 1; j <= m; j++){
            if(str1[i] == str2[j])
                dis[i][j] = dis[i-1][j-1];
            else{
                dis[i][j] = 1 + min( { dis[i-1][j] ,
                                       dis[i][j-1] ,
                                       dis[i-1][j-1] } );
            }
        }
    }
    
    return dis[n][m];
}
