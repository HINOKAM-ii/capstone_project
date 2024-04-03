#include "dictionary.h"
#include <string>

int main()
{
    // create object of class and call constructor
    spellchecker f1;

    // take shortcut and full form string from user...
    string shortcut_key;
    string full_form;
    getline(cin, shortcut_key);
    getline(full_form);
    f1.insert_shortcut_word("shortcut_key","full_form");
    
    // Get input file name from user
    cout << "Enter File Name to check spelling\n";
    string file_name;
    getline(cin, file_name);
    cout << " ~> Following underlined words are wrong words\n";
    f1.checking_file("input.txt");
    cout << " ~> wrong words have been corrected in the " << file_name << " yon can check in the file \n";
    f1.replace_wrong_spell("input.txt");

    return 0;
}
