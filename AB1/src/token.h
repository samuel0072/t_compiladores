#include <iostream>
#include <fstream>
#include <regex>

#include "category.h"


typedef struct Token Token;
typedef struct State State;
typedef struct StructAux StructAux;

Token nextToken();

int is_digit(char dig);
int is_Digit(char dig);
int is_letter(char dig);
int is__(char symbol);

class Tokenizer {
    private:
        
        Token tk{};
        ifstream program_file;
        string buffer;//linha atual sendo linda de program_file
        int position; //posição na linha

        const vector<string> lexemes = {
            "if","else", "while","for","in","step","break","return","input","output",
            "int","float","char","void","string","bool","(",")","{","}","[","]","+","-","/","*","%",
            "++",">","<",">=","<=","==","!=","^","!","and","or",
            "=", ",", ";","[_a-zA-Z][_a-zA-Z0-9]*", "[0-9][0-9]*", "([1-9])([0-9]*)\\.([0-9]*)",
            "\\’.\\’","\\”(.*)\\”","(true)|(false)"
        };
    
   


    public:
    explicit Tokenizer(string& file);
    

};