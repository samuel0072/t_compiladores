#include <iostream>
#include <string>
#include <fstream>
#include "lexicalanalyzer.h"




int main(int argc, char * argv[]) {

    std::string file(argv[1]);
    LexicalAnalyzer lex(file);
    Token *tk;

    while(tk->cat != Category::Eof && tk->cat != Category::Error) {
        tk = lex.nextToken();
        std::string tk_format = "          [" + std::to_string(tk->line)
                                +", " + std::to_string(tk->col) + "] ("
                                +std::to_string(tk->cat)+", "+lex.get_cat_name(tk->cat)
                                +") {"+ tk->lex +"}\n";
        //std::cout << tk_format;
        printf("         [%04d, %04d] (%04d, %20s) ",
         tk->line, tk->col, tk->cat, lex.get_cat_name(tk->cat));
        std::cout << "{" + tk->lex + "}\n";
    };
    
    

    
    return 0;

}