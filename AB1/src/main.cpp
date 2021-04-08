#include <iostream>
#include <fstream>
#include <regex>
#include <ctype.h>
#include <regex>

#include "category.h"

using namespace std;

typedef struct Token Token;
typedef struct State State;

struct Token {
    Category cat;
    string lex;
    int col, line;
};

struct State {
    Category cat;
    string actual;//expressao regular para continuar no estado atual
    string next;//expressaoregular para ir pro proximo estado
    State_types state_type;
    State* next_state;
};

int current = 0;

State *state_0;


string get_lex(Category c) {
    string lex = "";
    
    switch(c) {
        case  Category::OpMult:
            lex = "*";
            break;
        case Category::OpAdd:
            lex = "+";
            break;
        case Category::OpMinus:
            lex = "-";
            break;
        case Category::OpConcat:
            lex = "++";
            break;
        case Category::OpDiv:
            lex = "/";
            break;
        case  Category::OpRem:
            lex = "%";
            break;
        case Category::OpBinXor:
            lex = "^";
            break;
        case Category::OpLesser:
            lex = "<";
            break;
        case Category::OpLEqual:
            lex = "<=";
            break;   
        case Category::OpGreater:
            lex = ">";
            break;
        case Category::OpGEqual:
            lex = ">=";
            break; 
        case Category::Assign:
            lex = "=";
            break;
        case Category::OpEqual:
            lex = "==";
            break; 
        case Category::OpNot:
            lex = "!";
            break;
        case Category::OpDiff:
            lex = "!=";
            break;
        case Category::Braces1:
            lex = "{";
            break;
        case Category::Braces2:
            lex = "}";
            break;
        case Category::Parenth1:
            lex = "(";
            break;
        case Category::Parenth2:
            lex = ")";
            break;
        case Category::Bracket1:
            lex = "[";
            break;
        case Category::Bracket2:
            lex = "]";
            break;
        case Category::Terminator:
            lex = ";";
            break;
        default:
            //Caso a categoria seja uma CteChar, CteString, CteInt, CteFloat ou ID
            lex = "";
            break;
    }  
    return lex;
}

State* op_div_state() {

    //Nesse estado ele leu / e gera os estados de comentários com várias linhas

    State *op_div = new State;
    State *comment_init = new State;
    State *comment_end = new State;

    op_div->actual = "";
    op_div->next = "[\\*]";
    op_div->state_type = State_types::End;
    op_div->next_state = comment_init;
    op_div->cat = Category::OpDiv;

    comment_init->actual = "[^\\*]";
    comment_init->next = "[\\*]";
    comment_init->next_state = comment_end;
    comment_init->state_type = State_types::Inter;

    comment_end->actual = "";
    comment_end->next = "/";
    comment_end->state_type = State_types::Inter;
    comment_end->next_state = state_0;
    
    return op_div;
    
}

State* op_add_state() {
    State *op_add = new State;
    State *concat = new State;

    op_add->actual = "";
    op_add->next = "[\\+]";
    op_add->state_type = State_types::End;
    op_add->cat = Category::OpAdd;
    op_add->next_state = concat;

    concat->actual = "";
    concat->next = "";
    concat->state_type = State_types::End;
    concat->cat = Category::OpConcat;

    return op_add;
}

State* comp_equal() {
    //Para operadores compostos
    State *s_me = new State;
    s_me->actual = "";
    s_me->next = "";
    s_me->next_state = NULL;
    s_me->state_type = State_types::End;
    return s_me;
}

State* id_state() {
    State* id = new State;

    id->next_state = NULL;
    id->actual = "[_a-zA-Z0-9]*";
    id->next = "";
    id->state_type = State_types::End;
    id->cat = Category::Id;
    return id;

}

State* number_state() {
    State* cte_int = new State;
    State* cte_float = new State;

    cte_int->next_state = cte_float;
    cte_int->actual = "[0-9]*";
    cte_int->next = "\\.";//caracter ponto
    cte_int->state_type = State_types::End;
    cte_int->cat = Category::CteInt;

    cte_float->next_state = NULL;
    cte_float->actual = "[0-9]*";
    cte_float->next = "";
    cte_float->state_type = State_types::End;
    cte_float->cat = Category::CteFloat;

    return cte_int;
}

State* string_state() {
    State* cte_string = new State;
    State* interm = new State;

    interm->actual = "[^\"]";
    interm->next = "\"";
    interm->next_state = cte_string;
    interm->state_type = State_types::Inter;

    cte_string->actual = "";
    cte_string->next = "";
    cte_string->next_state = NULL;
    cte_string->state_type = State_types::End;
    cte_string->cat = Category::CteString;

    return interm;

}

State* char_state(char c) {
    State* cte_char = new State;

    cte_char->actual = "";
    cte_char->next = "";
    cte_char->state_type = State_types::End;
    cte_char->cat = Category::CteChar;

    string reg(1, c);

    if(regex_match(reg, regex("[^\']"))) {
        State* interm  = new State;

        interm->actual = "";
        interm->next = "\'";
        interm->state_type = State_types::Inter;
        interm->next_state = cte_char;

        return interm;
    }

    return cte_char;
}

State* get_next_state(char c) {
    /*
    Essa é a função de transição do state_0 para outro estado
    */

    State *t = new State;//estado que vai ser retornado
    State *next;// proximo estado caso haja proximo

    //settando alguns valores padrões
    t->next_state = NULL;
    t->actual = "";
    t->next = "";
    t->state_type = State_types::End;

    switch (c) {
        case '*':
            t->cat = Category::OpMult;
            break;
        case '+':
            t = op_add_state();
            break;
        case '-':
            t->cat = Category::OpMinus;
            break;
        case '/':
            t = op_div_state();
            break;
        case '%':
            t->cat = Category::OpRem;
            break;
        case '^':
            t->cat = Category::OpBinXor;
            break;
        case '<':
            next = comp_equal();
            next->cat = Category::OpLEqual;
            t->next = "=";
            t->next_state = next;
            t->cat = Category::OpLesser;   
            break;
        case '>':
            next = comp_equal();
            next->cat = Category::OpGEqual;
            t->next = "=";
            t->next_state = next;
            t->cat = Category::OpGreater;   
            break;
        case '=':
            next = comp_equal();
            next->cat = Category::OpEqual;
            t->next = "=";
            t->next_state = next;
            t->cat = Category::Assign;  
            break; 
        case '!':
            next = comp_equal();
            next->cat = Category::OpDiff;
            t->next = "=";
            t->next_state = next;
            t->cat = Category::OpNot;   
            break;
        case '{':
            t->cat = Category::Braces1;
            break;
        case '}':
            t->cat = Category::Braces2;
            break;
        case '(':
            t->cat = Category::Parenth1;
            break;
        case ')':
            t->cat = Category::Parenth2;
            break;
        case '[':
            t->cat = Category::Bracket1;
            break;
        case ']':
            t->cat = Category::Bracket2;
            break;
        case ';':
            t->cat = Category::Terminator;
            break;
        case '\'':
            t->state_type = State_types::Caracter;
            break;
        case '\"':
            t = string_state();
            break;
        
        case '_':
            t = id_state();
            break;
        case ',':;
            t->cat = Category::Comma;
            break;
        default:
            if(isdigit(c)) {
                t = number_state();
            }
            else if(isalpha(c)) {
                t = id_state();
            }
            else {
                //Caractere nao aceito pela linguagem
                t->state_type = State_types::State_Error;
            }
            break;
    }

    return t;
}

Category reserved_word(string word) {
    Category cat = Category::Id;
    
    if(word.compare("int") == 0) {
        cat = Category::Integer;
    }
    if(word.compare("float")== 0) {
        cat = Category::Float;
    }
    if(word.compare("char")== 0) {
        cat = Category::Char;
    }
    if(word.compare("string")== 0) {
        cat = Category::String;
    }
    if(word.compare("bool")== 0) {
        cat = Category::Boolean;
    }
    if(word.compare("if")== 0) {
        cat = Category::CtrlIf;
    }
    if(word.compare("else")== 0) {
        cat = Category::CtrlElse;
    }
    if(word.compare("while")== 0) {
        cat = Category::LoopWhile;
    }
    if(word.compare("for")== 0) {
        cat = Category::LoopFor;
    }
    if(word.compare("in")== 0) {
        cat = Category::In;
    }
    if(word.compare("step")== 0) {
        cat = Category::Step;
    }
    if(word.compare("break")== 0) {
        cat = Category::Break;
    }
    if(word.compare("return")== 0) {
        cat = Category::Return;
    }
    if(word.compare("input")== 0) {
        cat = Category::Input;
    }
    if(word.compare("output")== 0) {
        cat = Category::Output;
    }
    if(word.compare("void")== 0) {
        cat = Category::Void;
    }
    if(word.compare("and")== 0) {
        cat = Category::OpAnd;
    }
    if(word.compare("or")== 0) {
        cat = Category::OpOr;
    }
    if(word.compare("true")== 0) {
        cat = Category::CteBool;
    }
    if(word.compare("false")== 0) {
        cat = Category::CteBool;
    }
    return cat;

}

Token* nextToken(string line, int line_number) {

    Token* tk = new Token;
    State* actual_state = state_0;

    int line_len = line.length();
    string lex = "";

    tk->col = current;
    tk->line = line_number;

    while(current < line_len) {
        string char_act(1, line[current]);
        lex.append(char_act);

        if( regex_match(char_act, regex(actual_state->actual)) ) {
            //continua no mesmo estado
        }
        else if( regex_match( char_act, regex(actual_state->next) ) ) {
            //muda de estado
            actual_state = actual_state->next_state;   
        }
        else if( actual_state->state_type == State_types::Init ) {
            //Verifica se está no estado inicial
            actual_state = get_next_state(line[current]);
            lex = char_act;
            
            //Verifica se fez uma transição válida
            tk->col = current+1;//comecou a formar o token;
            if(actual_state->state_type == State_types::State_Error) {
                tk->lex.append(lex);
                tk->cat = Category::Error;
                break;
            }
        }
        else if( actual_state->state_type == State_types::End ) {
            //Verifica se está em um estado final
            //cout << " ->Saiu do estado final\n";
            tk->cat = actual_state->cat;
            tk->lex.clear();
            
            if(actual_state->cat == Category::CteFloat||
            actual_state->cat == Category::CteInt||
            actual_state->cat == Category::CteString||
            actual_state->cat == Category::CteChar) {
                lex.pop_back();
                tk->lex.append(lex);
            }
            else if(actual_state->cat == Category::Id) {
                lex.pop_back();
                tk->cat = reserved_word(lex);
                tk->lex.append(lex);
            }
            else {
                tk->lex.append(get_lex(tk->cat));//Obtem o lexema da categoria
            }
            break;
        }
        else if(actual_state->state_type == State_types::Caracter) {
            actual_state = char_state(line[current]);
        }
        else if(actual_state->state_type == State_types::Inter) {
            tk->cat = Category::Error;
            tk->lex.append(char_act);
            break;
        }
        current++;
    }
    
    //Esse if é pra reconhecer o ultimo caractere da linha
    if( actual_state->state_type == State_types::End ) {
            //Verifica se está em um estado final
            //cout << " ->Saiu do estado final\n";
            tk->cat = actual_state->cat;
            tk->lex.clear();
            if(actual_state->cat == Category::CteFloat||
            actual_state->cat == Category::CteInt||
            actual_state->cat == Category::CteString||
            actual_state->cat == Category::CteChar) {
                tk->lex.append(lex);
            }
            else if(actual_state->cat == Category::Id) {
                tk->cat = reserved_word(lex);
                tk->lex.append(lex);
            }
            else {
                tk->lex.append(get_lex(tk->cat));//Obtem o lexema da categoria
            }
        }
    
    return tk;
}

void init_state_0() {
    state_0 = new State;
    state_0->actual = "\\s";
    state_0->state_type = State_types::Init;
}

void dealoc_state(State* state) {
    State* next_state = state->next_state;

    while(next_state != NULL) {
        State* aux = next_state->next_state;
        delete next_state;
        next_state = aux;
    }
    delete state;
}

int main(int argc, char * argv[]) {
    
    ifstream program_file(argv[1]);
    string line;
    int line_len;
    int line_number = 1;
    Token *tk;
    
    

    while(getline(program_file, line)) {
        line_len =  line.length();
        cout << to_string(line_number) + "  "+line + "\n";
        for(current = 0; current < line_len; ) {
            init_state_0();
            tk = nextToken(line, line_number);
            if(tk->cat == Category::Error) {
                cout << "erro no analisador léxico\n";
                cout << "Inesperado " + tk->lex + " na linha "+ to_string(tk->line) +" coluna " + to_string(tk->col)+ "\n";
                return 0;
            }
            string tk_format = "          [" + to_string(tk->line)
                                +", " + to_string(tk->col) + "] ("
                                +to_string(tk->cat)+", "+to_string(tk->cat)
                                +") {"+ tk->lex +"}\n";
            cout << tk_format;
            //cout << "Token " + tk->lex + "-> ("+ to_string(tk->line) +", "+  +")\n" ;
            //printf("token %s -> (%4d, %4d)\n", tk->lex, tk->line, tk->col);
        }
        line_number++;
    }

    program_file.close();
    return 0;
}