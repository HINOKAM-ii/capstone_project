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

void spellchecker :: insert_dictionary(string dictionary_name){
    ifstream input_word;
    input_word.open(dictionary_name);

    if(input_word.is_open()){
        
        cout << " - dictionary open successfully\n";
        string word;

        while (getline(input_word,word)){
            insert_spell(word);
        }
        
        input_word.close();
        cout << " - dictionary added successfully\n";
        return;
    }

    cout << " - dictionary is not found\n";
}


bool spellchecker :: is_in_dictionary(string word){
    return dictionary[word];
}


void spellchecker :: replace_wrong_spell(string file_name){
    
    ifstream input(file_name);

    if (!input.is_open()) {
        cerr << " -> Error: Unable to open input file: <- " << file_name << endl;
        return;
    }

    ofstream tmp("tmp.txt");
    if (!tmp.is_open()) {
        cerr << " -> Error: Unable to create temporary file. <- " << endl;
        input.close();
        return;
    }

    char c;
    string word = "";
    while (input.get(c)) {
        if(c >= 'a' && c <= 'z')
            word += c;
        else if(c >= 'A' && c <= 'Z')
            word += (c + 32);
        else if(word != ""){
            if(is_in_dictionary(word)){
                tmp << word << c;
            }
            else{
                cout << " - Mistake in the word " << underlineON << word << underlineOFF << endl;
                vector<string> suggestions = suggestion(word);
                if(suggestions.empty()){
                    cout << " - No suggestions found in dictionary." << endl;
                }
                else{
                    int i = 0;
                    cout << " - We found these suggestions for you:" << endl;
                    while(i != suggestions.size()){
                        cout << i + 1 << " " << suggestions[i] << endl;
                        i++;
                    }

                    cout << " ~> Choose any of them or enter 0 to keep the word unchanged: ";
                    cin >> i;

                    if(i == 0){
                        cout << " - no changes\n";
                        tmp << word << c;
                    }
                    else{
                        tmp << suggestions[i-1] << c;
                    }
                }
            }
            word = "";
        }
        else{
            tmp << c;
        }
    }
    
    input.close();
    tmp.close();
    remove(file_name.c_str());
    rename("tmp.txt", file_name.c_str());
    cout << "all spell corrected\n";
    return;
}
