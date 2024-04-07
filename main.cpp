#include <iostream>
#include <string>
#include "dictionary2.h"

#ifdef _WIN32
#include <conio.h>
#define CLEAR_SCREEN "cls"
#else
#include <unistd.h>
#define CLEAR_SCREEN "clear"
#endif

using namespace std;

int main() {
    spellchecker f1;
    int choice;

    do {
        cout << "\033[2J\033[H"; // ANSI escape sequence to clear screen
        cout << bluelineON <<"\n** Spellchecker Menu **\n" << bluelineOFF;
        cout << "1. Check Spelling in a File and replace wrong words\n";
        cout << "2. Add your word in dictonary\n";
        cout << "3. Add a Shortcut\n";
        cout << redlineON << "4. Exit\n" << redlineOFF;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Clear input buffer

        switch (choice) {
            case 1: {
                cout << "Enter File Name to check spelling: ";
                string file_name;
                cout << yellowlineON ;
                getline(cin, file_name);
                cout << yellowlineOFF;

                cout << redlineON << " ~> Following underlined words are wrong words\n" << redlineOFF;
                int errors = f1.checking_file(file_name);
                if (errors == -1) {
                    cerr << redlineON << "Error opening file.\n" << redlineOFF;
                } else {
                    cout << errors << " Misspelled words found.\n";
                }
                cout << " ~> wrong words have been corrected in the " << file_name << " you can check in the file\n";
                f1.replace_spell(file_name);
                break;
            }
            case 2: {
                // take word from user to add in dictonary
                string word;
                cout << "ENTER WORD YOU WANTED TO INSERT - " << endl;
                cout << yellowlineON ;
                cin>>word;
                cout << yellowlineOFF;
                // call function to add word in dictonary
                f1.insert_spell(word);
                f1.insert_spell_to_dictionary(word);
                cout << greenlineON << "ENTERED WORD ADDED SUCCESSFULLY !!" << greenlineOFF << endl;
                break;
            }
            // case 3 for add short cut word for some word..
            case 3: {
                cout << "Enter the short cut key: ";
                string shortcut_key, full_form;
                cout << yellowlineON ;
                getline(cin, shortcut_key);
                cout << yellowlineOFF;
                cout << "Enter full form: ";
                cout << yellowlineON ;
                getline(cin, full_form);
                cout << yellowlineOFF;
                f1.insert_shortcut_word(shortcut_key, full_form);
                break;
            }
            // case for left menu.
            case 4: {
                cout << yellowlineON << "Exiting this menu\n" << yellowlineOFF;
                break;
            }
            // default case for invalid choice...
            default: {
                cout << redlineON << "Invalid choice. Please try again.\n" << redlineOFF;
            }
        }
        if(choice != 4){
            cout << "Press Enter to continue...";
            cin.ignore(); // Clear input buffer
            cin.get();
        }
    } while (choice != 4);

    return 0;
}

