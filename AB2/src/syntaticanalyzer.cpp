#include "syntaticanalyzer.h"
#include <stdlib.h>

SyntaticAnalyzer::SyntaticAnalyzer(std::string file) {
    lexical = new LexicalAnalyzer(file);

    init_prods();
    init_table();
    init_stack();
}

void SyntaticAnalyzer::init_prods() {

    /*
    * Não terminais
    */
    Production** Decls = make_prod( 1, Prod_types::Rule, N_Term::Decls, 2);
    Production** Decl = make_prod( 3, Prod_types::Rule, N_Term::Decl, 1);
    Production** DeclAux = make_prod( 4, Prod_types::Rule, N_Term::DeclAux, 2);
    Production** DeclBux = make_prod( 6, Prod_types::Rule, N_Term::DeclBux, 2);
    Production** ParamDef = make_prod( 8, Prod_types::Rule, N_Term::ParamDef, 2);
    Production** ParamDAux = make_prod( 10, Prod_types::Rule, N_Term::ParamDAux, 2);
    Production** StmList = make_prod( 12, Prod_types::Rule, N_Term::StmList, 2);
    Production** Stm = make_prod( 14, Prod_types::Rule, N_Term::Stm, 5);
    Production** ElseStm = make_prod(19, Prod_types::Rule, N_Term::ElseStm, 2);
    Production** NormalStm = make_prod(21, Prod_types::Rule, N_Term::NormalStm, 6);
    Production** VarDecl = make_prod(27, Prod_types::Rule, N_Term::VarDecl, 1);
    Production** VarList = make_prod(28, Prod_types::Rule, N_Term::VarList, 2);
    Production** Init = make_prod( 30, Prod_types::Rule, N_Term::Init, 2);
    Production** InitAux = make_prod( 32, Prod_types::Rule, N_Term::InitAux, 2);
    Production** Array = make_prod( 34, Prod_types::Rule, N_Term::Array, 2);
    Production** ArrayAux = make_prod( 36, Prod_types::Rule, N_Term::ArrayAux, 2);
    Production** OpConc = make_prod( 38, Prod_types::Rule, N_Term::OpConc, 2);
    Production** OpCoAux = make_prod( 40, Prod_types::Rule, N_Term::OpCoAux, 3);
    Production** OpCoBux = make_prod( 43, Prod_types::Rule, N_Term::OpCoBux, 3);
    Production** OpOr = make_prod(46, Prod_types::Rule, N_Term::OpOr, 1);
    Production** OpOrAux = make_prod( 47, Prod_types::Rule, N_Term::OpOrAux, 2);
    Production** OpAndXor = make_prod( 49, Prod_types::Rule, N_Term::OpAndXor, 1);
    Production** OpAXAux = make_prod( 50, Prod_types::Rule, N_Term::OpAXAux, 3);
    Production** OpEquate = make_prod( 53, Prod_types::Rule, N_Term::OpEquate, 1);
    Production** OpEAux = make_prod(54, Prod_types::Rule, N_Term::OpEAux, 3);
    Production** OpCompare = make_prod(57, Prod_types::Rule, N_Term::OpCompare, 1);
    Production** OpCAux = make_prod(58, Prod_types::Rule, N_Term::OpCAux, 5);
    Production** OpAdd = make_prod(63, Prod_types::Rule, N_Term::OpAdd, 1);
    Production** OpAddAux = make_prod(64, Prod_types::Rule, N_Term::OpAddAux, 3);
    Production** OpMult = make_prod(67, Prod_types::Rule, N_Term::OpMult, 1);
    Production** OpMAux = make_prod(68, Prod_types::Rule, N_Term::OpMAux, 4);
    Production** OpUnary = make_prod(72, Prod_types::Rule, N_Term::OpUnary, 4);
    Production** Value = make_prod(76, Prod_types::Rule, N_Term::Value, 6);
    Production** ValueAux = make_prod(82, Prod_types::Rule, N_Term::ValueAux, 2);
    Production** ParamList = make_prod(84, Prod_types::Rule, N_Term::ParamList, 2);
    Production** ParamLAux = make_prod(86, Prod_types::Rule, N_Term::ParamLAux, 2);
    Production** OpCList = make_prod(88, Prod_types::Rule, N_Term::OpCList, 2);
    Production** Type = make_prod(90, Prod_types::Rule, N_Term::Type, 6);

    /*
    * Terminais
    */

    /*Production* CtrlIf = make_term(Category::CtrlIf);
    Production* CtrlElse = make_term(Category::CtrlElse); 
    Production* LoopWhile = make_term(Category::LoopWhile); 
    Production* LoopFor = make_term(Category::LoopFor);  
    Production* Break = make_term(Category::Break);
    Production* Return = make_term(Category::Return); 
    Production* Input = make_term(Category::Input); 
    Production* Output = make_term(Category::Output); 
    Production* Integer = make_term(Category::Integer); 
    Production* Float = make_term(Category::Float); 
    Production* Char = make_term(Category::Char); 
    Production* Void = make_term(Category::Void);
    Production* String = make_term(Category::String); 
    Production* Boolean = make_term(Category::Boolean); 
    Production* Parenth1 = make_term(Category::Parenth1); 
    Production* Parenth2 = make_term(Category::Parenth2);
    Production* Braces1 = make_term(Category::Braces1);
    Production* Braces2 = make_term(Category::Braces2); 
    Production* Bracket1 = make_term(Category::Bracket1); 
    Production* Bracket2 = make_term(Category::Bracket2); 
    Production* OpAdd = make_term(Category::OpAdd); 
    Production* OpMinus = make_term(Category::OpMinus); 
    Production* OpDiv = make_term(Category::OpDiv); 
    Production* OpMult = make_term(Category::OpMult); 
    Production* OpRem = make_term(Category::OpRem); 
    Production* OpConcat = make_term(Category::OpConcat); 
    Production* OpGreater = make_term(Category::OpGreater);
    Production* OpLesser = make_term(Category::OpLesser); 
    Production* OpGEqual = make_term(Category::OpGEqual);
    Production* OpLEqual = make_term(Category::OpLEqual);  
    Production* OpEqual = make_term(Category::OpEqual);  
    Production* OpDiff = make_term(Category::OpDiff);  
    Production* OpBinXor = make_term(Category::OpBinXor); 
    Production* OpNot = make_term(Category::OpNot);  
    Production* OpAnd = make_term(Category::OpAnd);  
    Production* OpOr = make_term(Category::OpOr);  
    Production* Assign = make_term(Category::Assign);  
    Production* Comma = make_term(Category::Comma);  
    Production* Terminator = make_term(Category::Terminator);  
    Production* Error = make_term(Category::Error);  
    Production* Id = make_term(Category::Id);  
    Production* CteInt = make_term(Category::CteInt);  
    Production* CteFloat = make_term(Category::CteFloat);  
    Production* CteChar = make_term(Category::CteChar);  
    Production* CteString = make_term(Category::CteString); 
    Production* CteBool = make_term(Category::CteBool);  
    Production* Eof= make_term(Category::Eof); */
    
    Decls[0]->handle = { N_Term::Decl, N_Term::Decls};
    Decls[1]->handle = { N_Term::Empty };

    Decl[0]->handle = { N_Term::Type, N_Term::DeclAux};

    DeclAux[0]->handle = {N_Term::Id, N_Term::DeclBux};
    DeclAux[1]->handle = {N_Term::Bracket1, N_Term::Bracket2, N_Term::Id, 
    N_Term::Parenth1, N_Term::ParamDef, N_Term::Parenth2, 
    N_Term::Braces1, N_Term::StmList, N_Term::Braces2};

    DeclBux[0]->handle = {N_Term::Array, N_Term::Init, N_Term::VarList, N_Term::Terminator};
    DeclBux[1]->handle = {N_Term::Parenth1, N_Term::ParamDef, N_Term::Parenth2, 
    N_Term::Braces1, N_Term::StmList, N_Term::Braces2};

    ParamDef[0]->handle = { N_Term::Type, N_Term::Array, N_Term::Id, N_Term::ParamDAux};
    ParamDef[1]->handle = { N_Term::Empty };

    ParamDAux[0]->handle = {N_Term::Comma, N_Term::Type, N_Term::Array, N_Term::Id,N_Term::ParamDAux};
    ParamDAux[1]->handle = {N_Term::Empty};

    StmList[0]->handle = {N_Term::Stm, N_Term::StmList};
    StmList[1]->handle = {N_Term::Empty};

    Stm[0]->handle = {N_Term::VarDecl};
    Stm[1]->handle = {N_Term::CtrlIf, N_Term::Parenth1, N_Term::OpConc, N_Term::Parenth2,N_Term::Braces1, N_Term::StmList, N_Term::Braces2};
    Stm[2]->handle = {N_Term::LoopWhile, N_Term::Parenth1, N_Term::OpConc, N_Term::Parenth2,N_Term::Braces1, N_Term::StmList, N_Term::Braces2};
    Stm[3]->handle = {N_Term::LoopFor, N_Term::Parenth1,
        N_Term::Id,N_Term::Terminator,
        N_Term::Id,N_Term::Terminator,
        N_Term::Id,N_Term::Terminator,
        N_Term::Id,N_Term::Terminator ,N_Term::Parenth2,N_Term::Braces1, N_Term::StmList, N_Term::Braces2};
    Stm[4]->handle = {N_Term::NormalStm};

    ElseStm[0]->handle = {N_Term::CtrlElse, N_Term::Braces1, N_Term::StmList, N_Term::Braces2};
    ElseStm[1]->handle = {N_Term::Empty};

    NormalStm[0]->handle = {N_Term::OpConc, N_Term::Terminator};
    NormalStm[1]->handle = {N_Term::Break, N_Term::Terminator};
    NormalStm[2]->handle = {N_Term::Return,N_Term::OpConc, N_Term::Terminator};
    NormalStm[3]->handle = { N_Term::Terminator};
    NormalStm[4]->handle = {N_Term::Input, N_Term::Parenth1, N_Term::ParamList, N_Term::Parenth2,N_Term::Terminator};
    NormalStm[5]->handle = {N_Term::Output, N_Term::Parenth1, 
    N_Term::CteString, N_Term::Comma, N_Term::ParamList,
    N_Term::Parenth2,N_Term::Terminator};

    VarDecl[0]->handle = { N_Term::Type,  N_Term::Id,N_Term::Array, N_Term::Init, N_Term::VarList, N_Term::Terminator};

    VarList[0]->handle = {N_Term::Comma,N_Term::Id,N_Term::Array,N_Term::Init, N_Term::VarList};
    VarList[1]->handle = {N_Term::Empty};

    Init[0]->handle = {N_Term::Assign, N_Term::InitAux};
    Init[1]->handle = {N_Term::Empty};

    InitAux[0]->handle = {N_Term::OpConc};
    InitAux[1]->handle = {N_Term::Braces1, N_Term::OpConc, N_Term::OpCList, N_Term::Braces2};

    Array[0]->handle = {N_Term::Bracket1, N_Term::ArrayAux};
    Array[1]->handle = {N_Term::Empty};

    ArrayAux[0]->handle = {N_Term::OpConc, N_Term::Bracket2};
    ArrayAux[1]->handle = {N_Term::Bracket2};

    OpConc[0]->handle = {N_Term::OpOr, N_Term::OpCoAux};
    OpConc[1]->handle = {N_Term::Parenth1, N_Term::OpCoBux};

    OpCoAux[0]->handle = {N_Term::OpConcat, N_Term::OpOr, N_Term::OpCoAux};
    OpCoAux[1]->handle = {N_Term::Assign,  N_Term::OpOr, N_Term::OpCoAux};
    OpCoAux[2]->handle = {N_Term::Empty};

    OpCoBux[0]->handle = {N_Term::Type, N_Term::Parenth2, N_Term::Id};
    OpCoBux[1]->handle = {N_Term::OpOr,  N_Term::OpCoAux, N_Term::Parenth2};
    OpCoBux[2]->handle = {N_Term::Parenth1,  N_Term::OpCoBux, N_Term::Parenth2};

    OpOr[0]->handle = {N_Term::OpAndXor, N_Term::OpOrAux};

    OpOrAux[0]->handle = {N_Term::OpOrT, N_Term::OpAndXor, N_Term::OpOrAux};
    OpOrAux[1]->handle = {N_Term::Empty};

    OpAndXor[0]->handle = {N_Term::OpEquate, N_Term::OpAXAux};

    OpAXAux[0]->handle = {N_Term::OpAnd, N_Term::OpEquate, N_Term::OpAXAux};
    OpAXAux[1]->handle = {N_Term::OpBinXor,  N_Term::OpEquate, N_Term::OpAXAux};
    OpAXAux[2]->handle = {N_Term::Empty};

    OpEquate[0]->handle = {N_Term::OpCompare, N_Term::OpEAux};

    OpEAux[0]->handle = {N_Term::OpEqual, N_Term::OpCompare, N_Term::OpEAux};
    OpEAux[1]->handle = {N_Term::OpDiff,  N_Term::OpCompare, N_Term::OpEAux};
    OpEAux[2]->handle = {N_Term::Empty};

    OpCompare[0]->handle = {N_Term::OpAdd, N_Term::OpCAux};

    OpCAux[0]->handle = {N_Term::OpLesser, N_Term::OpAdd, N_Term::OpCAux};
    OpCAux[1]->handle = {N_Term::OpGreater,  N_Term::OpAdd, N_Term::OpCAux};
    OpCAux[2]->handle = {N_Term::OpLEqual,  N_Term::OpAdd, N_Term::OpCAux};
    OpCAux[3]->handle = {N_Term::OpGEqual,  N_Term::OpAdd, N_Term::OpCAux};
    OpCAux[4]->handle = {N_Term::Empty};

    OpAdd[0]->handle = {N_Term::OpMult, N_Term::OpAddAux};

    OpAddAux[0]->handle = {N_Term::OpAddT, N_Term::OpMult, N_Term::OpAddAux};
    OpAddAux[1]->handle = {N_Term::OpMultT,  N_Term::OpMult, N_Term::OpAddAux};
    OpAddAux[2]->handle = {N_Term::Empty};

    OpMult[0]->handle = {N_Term::OpUnary, N_Term::OpMAux};

    OpMAux[0]->handle = {N_Term::OpMultT, N_Term::OpUnary, N_Term::OpMAux};
    OpMAux[1]->handle = {N_Term::OpDiv,  N_Term::OpUnary, N_Term::OpMAux};
    OpMAux[2]->handle = {N_Term::OpRem,  N_Term::OpUnary, N_Term::OpMAux};
    OpMAux[4]->handle = {N_Term::Empty};

    OpUnary[0]->handle = {N_Term::OpNot, N_Term::OpUnary};
    OpUnary[1]->handle = {N_Term::OpMinus, N_Term::OpUnary};
    OpUnary[2]->handle = {N_Term::OpAddT, N_Term::OpUnary};
    OpUnary[3]->handle = {N_Term::Value};

    Value[0]->handle = {N_Term::CteInt};
    Value[1]->handle = {N_Term::CteString};
    Value[2]->handle = {N_Term::CteChar};
    Value[3]->handle = {N_Term::CteFloat};
    Value[4]->handle = {N_Term::CteBool};
    Value[5]->handle = {N_Term::Id, N_Term::ValueAux};

    ValueAux[0]->handle = {N_Term::Parenth1, N_Term::ParamList, N_Term::Parenth2};
    ValueAux[1]->handle = {N_Term::Empty};

    ParamList[0]->handle = {N_Term::Id, N_Term::ParamLAux};
    ParamList[1]->handle = {N_Term::Empty};

    ParamLAux[0]->handle = {N_Term::Comma,N_Term::Id, N_Term::ParamLAux};
    ParamLAux[1]->handle = {N_Term::Empty};

    OpCList[0]->handle = {N_Term::Comma,N_Term::OpConc, N_Term::OpCList};
    OpCList[1]->handle = {N_Term::Empty};

    Type[0]->handle = {N_Term::Char};
    Type[1]->handle = {N_Term::Integer};
    Type[2]->handle = {N_Term::Float};
    Type[3]->handle = {N_Term::String};
    Type[4]->handle = {N_Term::Void};
    Type[5]->handle = {N_Term::Boolean};

}

Production** SyntaticAnalyzer::make_prod( unsigned int id_base, 
    Prod_types prod_type, N_Term n_term, int hd_count) {
        Production** prods = (Production**) std::malloc(hd_count*sizeof(Production*));
        int i;
        for(i = 0; i < hd_count; i++) {
            prods[i] = new Production;
            prods[i]->id = i + id_base;
            prods[i]->type =  prod_type;
            prods[i]->n_category = n_term;
        }

    return prods; 
}

Production* SyntaticAnalyzer::make_term(Category lex_category) {
    Production* p = new Production;
    p->type = Prod_types::Lexeme;
    p->lex_category = lex_category;

}