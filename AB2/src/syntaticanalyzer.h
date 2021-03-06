#ifndef SYNTACTIC_ANALYZER_H
#define SYNTACTIC_ANALYZER_H
#include "lexicalanalyzer.h"
#include <vector>
#include <string>
#include <stack>

#define N_TERM_COUNT 39 //Quantidade de não terminais da gramatica LL(1)
#define PROD_MAX 96//Quandtidade de produções da gramatica LL(1)
#define TOKEN_COUNT 47 //Quantidade de tokens definidos em category.h
#define ERROR_COUNT 6 //Quantidade de erros identificados na tabela de análise 
#define OFF_SET 39
#define ERROR -1
typedef struct Production Production;

/*
Essa struct representa uma regra de produção
id  é utilizado para auxiliar na tabela de analise
type é especificado em category.h
handle é o handle da produção
lex_category é a categoria associada ao lexema(se for esse o tipo da produção)
error_msg é uma mensagem de erro caso a categoria seja error
readable é o nome legível da produção
n_category é a categoria do não terminal 
*/
struct Production {
    unsigned int id;
    N_Term n_category;//categoria do não terminal
    std::vector<N_Term> handle;
};


class SyntaticAnalyzer {
    private:
        std::stack<N_Term> prod_stack;//pilha 
        int analysis_table[N_TERM_COUNT][TOKEN_COUNT];//tabela de analise
        std::vector<Production*> productions;//produções na ordem que aparecem na gramatica LL(1)
        LexicalAnalyzer* lexical;

        void init_table();
        void init_prods();
        void init_stack();
        void push_prod(Production* p);
        void print_prod(Production* p);
        Production** make_prod( unsigned int id_base,  N_Term n_term, int hd_count);
        Category n_term_to_cat(N_Term n);
        std::string get_cat_readable(Category c);
        void print_stack();

        

    public:
        /*
        * Construtor
        * file é o nome do arquivo para ser analisado
        */
        SyntaticAnalyzer(std::string file); //construtor
        
        /*
        * Executa a analise léxica + sintática. Se o código for aceito retorna true
        * caso contrário, retorna falso.
        */
        bool Parse(); 

        std::string get_readable(N_Term t);
};
#endif