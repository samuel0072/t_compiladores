#ifndef LEXICAL_ANALYZER_H
#define LEXICAL_ANALYZER_H

#include <iostream>
#include <fstream>
#include <regex>
#include <ctype.h>
#include <regex>

#include "category.h"


typedef struct State State;

typedef struct Token Token;

struct Token {
    Category cat;
    std::string lex;
    int col, line;
};


class LexicalAnalyzer {
    private:
        
        /* Váriaveis */
        std::ifstream program_file;
        std::string line;//linha atual sendo linda de program_file
        int current; //posição na linha
        int line_number;//número da linha
        int line_len;//Comprimento da linha
        std::string lex;
        State* state_0;
        State* actual_state;


        /*Funções e procedimentos*/
        std::string get_lex(Category c);
        State* op_div_state();
        State* op_add_state();
        State* comp_equal();
        State* id_state();
        State* number_state();
        State* string_state();
        State* char_state(char c);
        State* get_next_state(char c);
        Category reserved_word(std::string word);
        void init_state_0();
        void dealoc_state(State* state);
        std::string cat_name(Category cat);
        void print_line();
        State* CommentEnd(char c);
        State* get_ctrl_string_state(char c);
    

    public:
        /*Funções e procedimentos*/
        LexicalAnalyzer(std::string file);
        Token* nextToken();
        char* get_cat_name(Category c);
        
};

#endif