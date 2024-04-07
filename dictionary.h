#include<bits/stdc++.h>
#include"HIGHLIGHT.h"
using namespace std;


//declare function for calculation edit distance of two string
int Distance(const string& str1 , const string& str2);


//class definition for spellchecker
class spellchecker{
    unordered_map<string,bool> dictionary; // diclare unorder map to store dictionary
    unordered_map<string,string> short_cut; // diclare unorder map to store short cut

    string main_dictionary = "dictionary.txt";  // main dictionary name/location
    string shortcut_location = "shortcut.txt";  // shortcut file name/location
    public:

    spellchecker(); //constructor

    //    --- spell checker ---

    void insert_spell(const string& word);  //function to add word to store in dictionary

    void insert_spell_to_dictionary(const string& word);  // add following word to our main dictionary

    void insert_dictionary(const string& dictionary_name);  // function to add whole dictionary

    bool is_in_dictionary(const string& word); // function to check that given word is in dictionary

    int checking_file(const string& filename); // function to check whole file

    void replace_spell(const string& file_name); // funtion to replace wrong and short cut word

    vector<string> suggestion(const string& MisSpellWord); // function to get nearest word


    //    --- short cut ---

    void insert_shortcut_word(const string& key , const string& ans); // function to insert one word to short cut list

    void insert_shortcut_file(const string& shortcut_filename); // function to insert whole short cut file

    bool is_in_shortcut(const string& word); // function to check shortcut is in list

    string replace_shortcut(const string& word); // function to give full form of short cut word

};

// constructor definition
spellchecker :: spellchecker(){

    insert_dictionary(main_dictionary); // call insert dictionary function to insert main dictionay

    insert_shortcut_file(shortcut_location); // call insert short cut function to add all short cuts

}


//function definition of insert spell
void spellchecker :: insert_spell(const string& word){
    dictionary[word] = true;
} 

//function definition of insert our new spell to dictionary
void spellchecker :: insert_spell_to_dictionary(const string& word){
    ofstream fout(main_dictionary , ios :: app); // open file with append mode
    fout << word << endl;
    fout.close(); // close file
}

//function definition of insert dictionary
void spellchecker :: insert_dictionary(const string& dictionary_name){
    ifstream input_word; // ifstream class variable for read dictionary

    input_word.open(dictionary_name);// open dictionary

    if(input_word.is_open()){
        
        cout << greenlineON <<" - dictionary open successfully\n" << greenlineOFF;
        string word;

        while (getline(input_word,word)){
            insert_spell(word); // insert every spell one by one
        }
        
        input_word.close();
        cout << greenlineON <<" - dictionary added successfully\n" << greenlineOFF;
        return;
    }

    cout << redlineON <<" - dictionary is not found\n" << redlineOFF;
}

//function definition of is_in_dictionary
bool spellchecker :: is_in_dictionary(const string& word){
    return dictionary[word];
}

//function definition of suggestion
vector<string> spellchecker::suggestion(const string &MisSpellWord) {

  vector<pair<int, string>> suggestion_word; // make pair variable for to store priorty and word

  ifstream input_word; // ifstream class variable for read dictionary

  input_word.open(main_dictionary); // open main dictionary

  vector<string> final_suggestion; // vector variable to store final suggested words 

  if (input_word.is_open()) {
    cout << greenlineON <<" - dictionary open successfully\n" << greenlineOFF;
    string word;

    while (getline(input_word, word)) {
      int distance = Distance(word, MisSpellWord); // call distance function to calculate edit distance of misspellword and dictionary word
      int matching_chars = 0;

      for (int i = 0; i < min(2, (int)word.size()) && i < min(2, (int)MisSpellWord.size()); ++i) {
        if (isupper(word[i]) && word[i] == MisSpellWord[i]) {
          matching_chars++;
        }
      }

      int priority = distance * 10 - matching_chars; // give priorty to every word
      suggestion_word.push_back({priority, word}); // push priorty and word in suggestion pair
    }

    input_word.close(); // close main dictionary

    sort(suggestion_word.begin(), suggestion_word.end()); // sort acrroding to priority

    cout << " - suggestion sorted properly\n";

    for (int i = 0; i < min(5, (int)suggestion_word.size()); ++i) {
      final_suggestion.push_back(suggestion_word[i].second);
    }

    if (suggestion_word.empty()) {
      cout << " - zero suggestion\n"; 
    }
  } else {
    cout << redlineON <<" - dictionary is not open\n" << redlineOFF; // if dictionary not open
  }

  return final_suggestion; // return final suggestion words
}


//function definition of checking file
int spellchecker :: checking_file(const string& filename){

    int count = 0; // declare count variable to count wronge spell

    ifstream input; // ifstream class variable for read input file
    input.open(filename); // open input file

    if(!input.is_open()){
        cerr << redlineON <<" -> Error: Unable to open input file: <- " << filename << redlineOFF <<endl;
        return -1; // if not open then give error and return -1
    }

    char c;
    string word = ""; // declare necessary variable

    while (input.get(c))
    {
        if(c == EOF) // loop break at END OF FILE 
        break;

        if(c >= 'a' && c <= 'z')
            word += c;
        else if(c >= 'A' && c <= 'Z') // convert upper case to lower
            word += (c + 32);
        else if(word != ""){
            if(is_in_dictionary(word)) // check if word is in dectionary or not
                cout << word << c;
            else{
                cout << underlineON << word << underlineOFF << c;   
                count++;
            }
            word = "";
        }
        else
            cout << c;
        
    }
    cout << endl;
    return count; // return count of misspelled word
}


//function definition of replace wrong and short cut spell
void spellchecker :: replace_spell(const string& file_name){
    
    ifstream input(file_name);
    // if file does not exist
    if (!input.is_open()) {
        cerr << redlineON <<" -> Error: Unable to open input file: <- " << file_name << redlineOFF << endl;
        return;
    }

    ofstream tmp("tmp.txt");
    if (!tmp.is_open()) {
        cerr << redlineON <<" -> Error: Unable to create temporary file. <- "<< redlineOFF << endl;
        input.close();
        return;
    }

    char c;    // declare character and string
    string word = "";
    while (input.get(c)) {
        if(c >= 'a' && c <= 'z')
            word += c;
        else if(c >= 'A' && c <= 'Z')
            word += (c + 32);
        else if(word != ""){
            if(is_in_shortcut(word)){
                string stword = replace_shortcut(word);
                cout << " - Do you want to replace " << word << " with " << stword << "?" << endl;
                int ch;
                cout << " ~> if yes then press 1 or press 0\n";
                cin >> ch;
                if(ch == 1){
                    tmp << stword << c;
                    cout << " - change sucseffuly\n";
                }else if(ch == 0){
                    tmp << word << c;
                    cout << " - no change happen\n";
                }else{
                    cout << redlineON << " ~> somthing wrong no change happen. " << redlineOFF << endl;
                    tmp << word << c;
                }
            }
            else if(is_in_dictionary(word)){
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

void spellchecker :: insert_shortcut_word(const string& key , const string& ans){
    ofstream file(shortcut_location, ios::app);

    if (file.is_open()) {
        file << key << endl;
        file << ans << endl;

        if(short_cut[key] == "")
            short_cut[key] = ans;
        // Close the file
        file.close();

        cout << greenlineON <<" ~> shortcut added successfully." << greenlineOFF << endl;
    } else {
        cout << redlineON <<"Unable to add shortcut" << redlineOFF << endl;
    }
}

void spellchecker :: insert_shortcut_file(const string& shortcut_filename){
    ifstream shortcutfile;
    shortcutfile.open(shortcut_filename);

    string key_word,ans_word;

    while (getline(shortcutfile,key_word)){
        getline(shortcutfile,ans_word);
        short_cut[key_word] = ans_word;
    }
    
    shortcutfile.close();
    return;
}

string spellchecker :: replace_shortcut(const string& word){
    return short_cut[word];
}

bool spellchecker :: is_in_shortcut(const string& word){
    if(short_cut[word] != ""){
        return true;
    }

    return false;
}


//write definition of distance based of Levenshtein algorithm
int Distance(const string& str1 , const string& str2){
    // Get the lengths of the input strings
    int n = str1.size();
    int m = str2.size();

    // Declare array for dynamic programming
    int dis[n+1][m+1];

    // Initialize the first row of the array
    for(int i = 0 ; i <= n ; i++) 
        dis[i][0] = i;   
       
    // Initialize the first column of the array
    for(int i = 0 ; i <= m ; i++) 
        dis[0][i] = i;

    // Iterate through each character of both strings
    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++){
            // If the characters at the current positions are the same
            if(str1[i - 1] == str2[j - 1]) 
                dis[i][j] = dis[i-1][j-1]; // No additional edit needed
            else {
                // If characters are different, find the minimum of the three neighboring cells
                // and add one to represent the minimum edit distance required
                dis[i][j] = 1 + min({ dis[i-1][j], dis[i][j-1], dis[i-1][j-1] });
            }
        }
    }
    
    // Return the Levenshtein distance between the two strings
    return dis[n][m];
}


