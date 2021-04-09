#include <iostream>
#include <string>
#include <fstream>
#include "lexicalanalyzer.h"

int main(int argc, char * argv[]) {

    if(argc < 2) {
        std::cout << "O nome do arquivo não foi especificado";
        exit(EXIT_FAILURE);
    }
    std::string file(argv[1]);
    LexicalAnalyzer lex(file);
    Token *tk;

    while(tk->cat != Category::Eof && tk->cat != Category::Error) {
        tk = lex.nextToken();
        printf("          [%04d, %04d] (%04d, %20s) ",
         tk->line, tk->col, tk->cat, lex.get_cat_name(tk->cat));
        std::cout << "{" + tk->lex + "}\n";
    };
    
    

    
    return 0;

}