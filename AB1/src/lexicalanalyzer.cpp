#include "lexicalanalyzer.h"

struct State {
    Category cat;
    std::string actual;//expressao regular para continuar no estado atual
    std::string next;//expressao regular para ir pro proximo estado
    State_types state_type;
    State* next_state;
};


LexicalAnalyzer::LexicalAnalyzer(std::string file){
    //Construtor
    current = 0;
    line_number = 0;
    line_len = 0;

    line.clear();
    program_file.open(file);
    init_state_0();

    actual_state = state_0;

    if(!program_file.is_open()) {
        std::cout << "Erro ao abrir o arquivo";
        exit(EXIT_FAILURE);
    }
    
}

void LexicalAnalyzer::init_state_0() {
    state_0 = new State;
    state_0->actual = "\\s";
    state_0->state_type = State_types::Init;
}

std::string LexicalAnalyzer::get_lex(Category c) {
    std::string lex = "";
    
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
        case Category::Comma:
            lex = ",";
            break;
        default:
            //Caso a categoria seja uma CteChar, CteString, CteInt, CteFloat ou ID
            lex = "";
            break;
    }  
    return lex;
}

State* LexicalAnalyzer::op_div_state() {

    //Nesse estado ele leu / e gera os estados de comentários com várias linhas

    State *op_div = new State;
    State *comment_init = new State;
    State *comment_end = new State;

    op_div->actual = "";
    op_div->next = "[\\*|/]";
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

State* LexicalAnalyzer::op_add_state() {
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

State* LexicalAnalyzer::comp_equal() {
    //Para operadores compostos
    State *s_me = new State;
    s_me->actual = "";
    s_me->next = "";
    s_me->next_state = NULL;
    s_me->state_type = State_types::End;
    return s_me;
}

State* LexicalAnalyzer::id_state() {
    State* id = new State;

    id->next_state = NULL;
    id->actual = "[_a-zA-Z0-9]*";
    id->next = "";
    id->state_type = State_types::End;
    id->cat = Category::Id;
    return id;

}

State* LexicalAnalyzer::number_state() {
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

State* LexicalAnalyzer::string_state() {
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

State* LexicalAnalyzer::char_state(char c) {
    State* cte_char = new State;

    cte_char->actual = "";
    cte_char->next = "";
    cte_char->state_type = State_types::End;
    cte_char->cat = Category::CteChar;

    std::string reg(1, c);

    if(std::regex_match(reg, std::regex("[^\']"))) {
        State* interm  = new State;

        interm->actual = "";
        interm->next = "\'";
        interm->state_type = State_types::Inter;
        interm->next_state = cte_char;

        return interm;
    }

    return cte_char;
}

State* LexicalAnalyzer::get_next_state(char c) {
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

Category LexicalAnalyzer::reserved_word(std::string word) {
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

void LexicalAnalyzer::dealoc_state(State* state) {
    State* next_state = state->next_state;

    while(next_state != NULL) {
        State* aux = next_state->next_state;
        delete next_state;
        next_state = aux;
    }
    delete state;
}

Token* LexicalAnalyzer::nextToken() {

    Token* tk = new Token;
    
    

    if(program_file.eof() && current >= line_len) {
        //Se tiver tratado a linha anterior e só resta eof 
        tk->cat = Category::Eof;
        tk->col = current;
        tk->line = line_number;
        return tk;
    }
    
    if(current >= line_len) {
        //Lê a próxima linha se tiver tratado a linha anterior ou se for a primeira linha do arquivo
        getline(program_file, line);
        current = 0;
        line_number++;
        print_line();
        //Lendo linhas vazias
        while(line.length() == 0 && !program_file.eof()) {
            getline(program_file, line);
            current = 0;
            line_number++;
            print_line();
        }
        line_len = line.length();
        line[line_len] = '\n';//a função getline retira o \n do final da linha
        
    }
    tk->col = current;
    tk->line = line_number;
    
    if(actual_state->state_type == State_types::Init) {
        //trata os espaços em branco no começo das linhas
        while(line[current] == ' '){
            current++;
        }
    }

    while(current <= line_len) {
        
        std::string char_act(1, line[current]);
        lex.append(char_act);

        if(actual_state->state_type == State_types::Inter
        && std::regex_search(lex, std::regex("//"))) {
            //Vai para a próxima linha do arquivo fonte
            actual_state = state_0;
            current = line_len + 1;
            break;

        }
        
        if( std::regex_match(char_act, std::regex(actual_state->actual)) ) {
            //continua no mesmo estado
        }
        else if( std::regex_match( char_act, std::regex(actual_state->next) ) ) {
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
        else {
            tk->cat = Category::Error;
            tk->lex.append(lex);
            actual_state->state_type = State_types::State_Error;
            break;
        }
        current++;
    }

    if(actual_state->state_type == State_types::Inter 
    || actual_state->state_type == State_types::Init) {
        //Esse if é executado quando se está lendo um comentário com mais de uma linha
        
        tk = nextToken();
    }
    actual_state = state_0;//Ocorreu o reconhecimento de um token

    return tk;
}

void LexicalAnalyzer::print_line() {
    printf("%4d  %s\n", line_number, line.c_str());
    //std::cout << std::to_string(line_number) + "  "+line + "\n";
}

char* LexicalAnalyzer::get_cat_name(Category c) {
    
    switch(c) {

        case Category::CtrlIf :
            return (char*) "CtrlIf";
        case Category::CtrlElse:
            return (char*) "CtrlElse";
        case Category::LoopWhile:
            return (char*) "LoopWhile";
        case Category::LoopFor:
            return (char*) "LoopFor";
        case Category::Break:
            return (char*) "Break";
        case Category::Return:
            return (char*) "Return";
        case Category::Input:
            return (char*) "Input";
        case Category::Output:
            return (char*) "Output";
        case Category::Integer:
            return (char*) "Integer";
        case Category::Float:
            return (char*) "Float";
        case Category::Char:
            return (char*) "Char";
        case Category::Void:
            return (char*) "Void";
        case Category::String:
            return (char*) "String";
        case Category::Boolean:
            return (char*) "Boolean";
        case Category::Parenth1:
            return (char*) "Parenth1";
        case Category::Parenth2:
            return (char*) "Parenth2";
        case Category::Braces1:
            return (char*) "Braces1";
        case Category::Braces2:
            return (char*) "Braces2";
        case Category::Bracket1:
            return (char*) "Bracket1";
        case Category::Bracket2:
            return (char*) "Bracket2";
        case Category::OpAdd:
            return (char*) "OpAdd";
        case Category::OpMinus:
            return (char*) "OpMinus";
        case Category::OpDiv:
            return (char*) "OpDiv";
        case Category::OpMult:
            return (char*) "OpMult";
        case Category::OpRem:
            return (char*) "OpRem";
        case Category::OpConcat:
            return (char*) "OpConcat";
        case Category::OpGreater:
            return (char*) "OpGreater";
        case Category::OpLesser:
            return (char*) "OpLesser";
        case Category::OpGEqual:
            return (char*) "OpGEqual";
        case Category::OpLEqual:
            return (char*) "OpLEqual";
        case Category::OpDiff:
            return (char*) "OpDiff";
        case Category::OpEqual:
            return (char*) "OpEqual";
        case Category::OpBinXor:
            return (char*) "OpBinXor";
        case Category::OpNot:
            return (char*) "OpNot";
        case Category::OpAnd:
            return (char*) "OpAnd";
        case Category::OpOr:
            return (char*) "OpGEqual";
        case Category::Assign:
            return (char*) "Assign";
        case Category::Comma:
            return (char*) "Comma";
        case Category::Terminator:
            return (char*) "Terminator";
        case Category::Error:
            return (char*) "Error";
        case Category::Id:
            return (char*) "Id";
        case Category::CteInt:
            return (char*) "CteInt";
        case Category::CteFloat:
            return (char*) "CteFloat";
        case Category::CteString:
            return (char*) "CteString";
        case Category::CteChar:
            return (char*) "CteChar";
        case Category::CteBool:
            return (char*) "CteBool";
        case Category::Eof:
            return (char*) "Eof";
        default:
            return (char*)"Erro";
    }
}

