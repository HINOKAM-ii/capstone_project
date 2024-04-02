#include"dictionary.h"

int main() {
    spellchecker f1;
    f1.checking_file("input.txt");
    f1.replace_wrong_spell("input.txt");
    
    return 0;
}
