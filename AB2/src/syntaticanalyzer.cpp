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
    Production** Decls = make_prod( 1, N_Term::Decls, 2);
    Production** Decl = make_prod( 3, N_Term::Decl, 1);
    Production** DeclAux = make_prod( 4, N_Term::DeclAux, 2);
    Production** DeclBux = make_prod( 6, N_Term::DeclBux, 2);
    Production** ParamDef = make_prod( 8, N_Term::ParamDef, 2);
    Production** ParamDAux = make_prod( 10, N_Term::ParamDAux, 2);
    Production** StmList = make_prod( 12, N_Term::StmList, 2);
    Production** Stm = make_prod( 14, N_Term::Stm, 5);
    Production** ElseStm = make_prod(19, N_Term::ElseStm, 2);
    Production** NormalStm = make_prod(21, N_Term::NormalStm, 6);
    Production** VarDecl = make_prod(27, N_Term::VarDecl, 1);
    Production** VarList = make_prod(28, N_Term::VarList, 2);
    Production** Init = make_prod( 30, N_Term::Init, 2);
    Production** InitAux = make_prod( 32, N_Term::InitAux, 2);
    Production** Array = make_prod( 34, N_Term::Array, 2);
    Production** ArrayAux = make_prod( 36, N_Term::ArrayAux, 2);
    Production** OpConc = make_prod( 38, N_Term::OpConc, 2);
    Production** OpCoAux = make_prod( 40, N_Term::OpCoAux, 3);
    Production** OpCoBux = make_prod( 43, N_Term::OpCoBux, 3);
    Production** OpOr = make_prod(46, N_Term::OpOr, 1);
    Production** OpOrAux = make_prod( 47, N_Term::OpOrAux, 2);
    Production** OpAndXor = make_prod( 49, N_Term::OpAndXor, 1);
    Production** OpAXAux = make_prod( 50, N_Term::OpAXAux, 3);
    Production** OpEquate = make_prod( 53, N_Term::OpEquate, 1);
    Production** OpEAux = make_prod(54, N_Term::OpEAux, 3);
    Production** OpCompare = make_prod(57, N_Term::OpCompare, 1);
    Production** OpCAux = make_prod(58, N_Term::OpCAux, 5);
    Production** OpAdd = make_prod(63, N_Term::OpAdd, 1);
    Production** OpAddAux = make_prod(64, N_Term::OpAddAux, 3);
    Production** OpMult = make_prod(67, N_Term::OpMult, 1);
    Production** OpMAux = make_prod(68, N_Term::OpMAux, 4);
    Production** OpUnary = make_prod(72, N_Term::OpUnary, 4);
    Production** Value = make_prod(76, N_Term::Value, 6);
    Production** ValueAux = make_prod(82, N_Term::ValueAux, 2);
    Production** ParamList = make_prod(84, N_Term::ParamList, 2);
    Production** ParamLAux = make_prod(86, N_Term::ParamLAux, 2);
    Production** OpCList = make_prod(88, N_Term::OpCList, 2);
    Production** Type = make_prod(90, N_Term::Type, 6);

    /*Regras de produção*/
    
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

Production** SyntaticAnalyzer::make_prod( unsigned int id_base,  N_Term n_term, int hd_count) {
        Production** prods = (Production**) std::malloc(hd_count*sizeof(Production*));
        int i;
        for(i = 0; i < hd_count; i++) {
            prods[i] = new Production;
            prods[i]->id = i + id_base;
            prods[i]->n_category = n_term;
        }

    return prods; 
}

