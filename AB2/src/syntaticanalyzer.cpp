#include "syntaticanalyzer.h"
#include "lexicalanalyzer.h"
#include <stdlib.h>
#include <iostream>

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
    Production** Decls = make_prod(1, N_Term::Decls, 2);
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
    Production** Init = make_prod( 30, N_Term::NInit, 2);
    Production** InitAux = make_prod( 32, N_Term::InitAux, 2);
    Production** Array = make_prod( 34, N_Term::Array, 2);
    Production** ArrayAux = make_prod( 36, N_Term::ArrayAux, 2);
    Production** OpConc = make_prod( 38, N_Term::OpConc, 2);
    Production** OpCoAux = make_prod( 40, N_Term::OpCoAux, 3);
    Production** OpCoBux = make_prod( 43, N_Term::OpCoBux, 3);
    Production** OpOr = make_prod(46, N_Term::NOpOr, 1);
    Production** OpOrAux = make_prod( 47, N_Term::OpOrAux, 2);
    Production** OpAndXor = make_prod( 49, N_Term::OpAndXor, 1);
    Production** OpAXAux = make_prod( 50, N_Term::OpAXAux, 3);
    Production** OpEquate = make_prod( 53, N_Term::OpEquate, 1);
    Production** OpEAux = make_prod(54, N_Term::OpEAux, 3);
    Production** OpCompare = make_prod(57, N_Term::OpCompare, 1);
    Production** OpCAux = make_prod(58, N_Term::OpCAux, 5);
    Production** OpAdd = make_prod(63, N_Term::NOpAdd, 1);
    Production** OpAddAux = make_prod(64, N_Term::OpAddAux, 3);
    Production** OpMult = make_prod(67, N_Term::NOpMult, 1);
    Production** OpMAux = make_prod(68, N_Term::OpMAux, 4);
    Production** OpUnary = make_prod(72, N_Term::OpUnary, 4);
    Production** Value = make_prod(76, N_Term::Value, 6);
    Production** ValueAux = make_prod(82, N_Term::ValueAux, 2);
    Production** ParamList = make_prod(84, N_Term::ParamList, 2);
    Production** ParamLAux = make_prod(86, N_Term::ParamLAux, 2);
    Production** OpCList = make_prod(88, N_Term::OpCList, 2);
    Production** Type = make_prod(90, N_Term::Type, 6);

    /*Regras de produção*/
    
    Decls[0]->handle.insert(Decls[0]->handle.end(), {N_Term::Decl, N_Term::Decls});
    Decls[1]->handle.insert(Decls[1]->handle.end(), { N_Term::Empty });

    Decl[0]->handle.insert(Decl[0]->handle.end(), { N_Term::Type, N_Term::DeclAux});
    
    DeclAux[0]->handle.insert(DeclAux[0]->handle.end(), {N_Term::TId, N_Term::DeclBux});
    DeclAux[1]->handle.insert(DeclAux[1]->handle.end(), {N_Term::TBracket1, N_Term::TBracket2, N_Term::TId, 
    N_Term::TParenth1, N_Term::ParamDef, N_Term::TParenth2, 
    N_Term::TBraces1, N_Term::StmList, N_Term::TBraces2});

    DeclBux[0]->handle.insert(DeclBux[0]->handle.end(), {N_Term::Array, N_Term::NInit, N_Term::VarList, N_Term::TTerminator});
    DeclBux[1]->handle.insert(DeclBux[1]->handle.end(), {N_Term::TParenth1, N_Term::ParamDef, N_Term::TParenth2, 
    N_Term::TBraces1, N_Term::StmList, N_Term::TBraces2});

    ParamDef[0]->handle.insert(ParamDef[0]->handle.end(), { N_Term::Type, N_Term::Array, N_Term::TId, N_Term::ParamDAux});
    ParamDef[1]->handle.insert(ParamDef[1]->handle.end(), { N_Term::Empty });

    ParamDAux[0]->handle.insert(ParamDAux[0]->handle.end(), {N_Term::TComma, N_Term::Type, N_Term::Array, N_Term::TId,N_Term::ParamDAux});
    ParamDAux[1]->handle.insert(ParamDAux[1]->handle.end(), {N_Term::Empty});

    StmList[0]->handle.insert(StmList[0]->handle.end(), {N_Term::Stm, N_Term::StmList});
    StmList[1]->handle.insert(StmList[1]->handle.end(), {N_Term::Empty});

    Stm[0]->handle.insert(Stm[0]->handle.end(), {N_Term::VarDecl});
    Stm[1]->handle.insert(Stm[1]->handle.end(), {N_Term::TCtrlIf, N_Term::TParenth1, N_Term::OpConc, N_Term::TParenth2,N_Term::TBraces1, N_Term::StmList, N_Term::TBraces2});
    Stm[2]->handle.insert(Stm[2]->handle.end(), {N_Term::TLoopWhile, N_Term::TParenth1, N_Term::OpConc, N_Term::TParenth2,N_Term::TBraces1, N_Term::StmList, N_Term::TBraces2});
    Stm[3]->handle.insert(Stm[3]->handle.end(), {N_Term::TLoopFor, N_Term::TParenth1,
        N_Term::TId,N_Term::TTerminator,
        N_Term::TId,N_Term::TTerminator,
        N_Term::TId,N_Term::TTerminator,
        N_Term::TId,N_Term::TTerminator ,N_Term::TParenth2,N_Term::TBraces1, N_Term::StmList, N_Term::TBraces2});
    Stm[4]->handle.insert(Stm[4]->handle.end(), {N_Term::NormalStm});
    
    ElseStm[0]->handle.insert(ElseStm[0]->handle.end(), {N_Term::TCtrlElse, N_Term::TBraces1, N_Term::StmList, N_Term::TBraces2});
    ElseStm[1]->handle.insert(ElseStm[1]->handle.end(), {N_Term::Empty});

    NormalStm[0]->handle.insert(NormalStm[0]->handle.end(), {N_Term::OpConc, N_Term::TTerminator});
    NormalStm[1]->handle.insert(NormalStm[1]->handle.end(), {N_Term::TBreak, N_Term::TTerminator});
    NormalStm[2]->handle.insert(NormalStm[2]->handle.end(), {N_Term::TReturn,N_Term::OpConc, N_Term::TTerminator});
    NormalStm[3]->handle.insert(NormalStm[3]->handle.end(), { N_Term::TTerminator});
    NormalStm[4]->handle.insert(NormalStm[4]->handle.end(), {N_Term::TInput, N_Term::TParenth1, N_Term::ParamList, N_Term::TParenth2,N_Term::TTerminator});
    NormalStm[5]->handle.insert(NormalStm[5]->handle.end(), {N_Term::TOutput, N_Term::TParenth1, 
    N_Term::TCteString, N_Term::TComma, N_Term::ParamList,
    N_Term::TParenth2,N_Term::TTerminator});

    VarDecl[0]->handle.insert(VarDecl[0]->handle.end(), { N_Term::Type,  N_Term::TId,N_Term::Array, N_Term::NInit, N_Term::VarList, N_Term::TTerminator});

    VarList[0]->handle.insert(VarList[0]->handle.end(), {N_Term::TComma,N_Term::TId,N_Term::Array,N_Term::NInit, N_Term::VarList});
    VarList[1]->handle.insert(VarList[1]->handle.end(), {N_Term::Empty});

    Init[0]->handle.insert(Init[0]->handle.end(), {N_Term::TAssign, N_Term::InitAux});
    Init[1]->handle.insert(Init[1]->handle.end(), {N_Term::Empty});

    InitAux[0]->handle.insert(InitAux[0]->handle.end(), {N_Term::OpConc});
    InitAux[1]->handle.insert(InitAux[1]->handle.end(), {N_Term::TBraces1, N_Term::OpConc, N_Term::OpCList, N_Term::TBraces2});

    Array[0]->handle.insert(Array[0]->handle.end(), {N_Term::TBracket1, N_Term::ArrayAux});
    Array[1]->handle.insert(Array[1]->handle.end(), {N_Term::Empty});

    ArrayAux[0]->handle.insert(ArrayAux[0]->handle.end(), {N_Term::OpConc, N_Term::TBracket2});
    ArrayAux[1]->handle.insert(ArrayAux[1]->handle.end(), {N_Term::TBracket2});
    
    OpConc[0]->handle.insert(OpConc[0]->handle.end(), {N_Term::NOpOr, N_Term::OpCoAux});
    OpConc[1]->handle.insert(OpConc[1]->handle.end(), {N_Term::TParenth1, N_Term::OpCoBux});

    OpCoAux[0]->handle.insert(OpCoAux[0]->handle.end(), {N_Term::TOpConcat, N_Term::NOpOr, N_Term::OpCoAux});
    OpCoAux[1]->handle.insert(OpCoAux[1]->handle.end(), {N_Term::TAssign,  N_Term::NOpOr, N_Term::OpCoAux});
    OpCoAux[2]->handle.insert(OpCoAux[2]->handle.end(), {N_Term::Empty});

    OpCoBux[0]->handle.insert(OpCoBux[0]->handle.end(), {N_Term::Type, N_Term::TParenth2, N_Term::TId});
    OpCoBux[1]->handle.insert(OpCoBux[1]->handle.end(), {N_Term::NOpOr,  N_Term::OpCoAux, N_Term::TParenth2});
    OpCoBux[2]->handle.insert(OpCoBux[2]->handle.end(), {N_Term::TParenth1,  N_Term::OpCoBux, N_Term::TParenth2});

    OpOr[0]->handle.insert(OpOr[0]->handle.end(), {N_Term::OpAndXor, N_Term::OpOrAux});

    OpOrAux[0]->handle.insert(OpOrAux[0]->handle.end(), {N_Term::TOpOr, N_Term::OpAndXor, N_Term::OpOrAux});
    OpOrAux[1]->handle.insert(OpOrAux[1]->handle.end(), {N_Term::Empty});

    OpAndXor[0]->handle.insert(OpAndXor[0]->handle.end(), {N_Term::OpEquate, N_Term::OpAXAux});

    OpAXAux[0]->handle.insert(OpAXAux[0]->handle.end(), {N_Term::TOpAnd, N_Term::OpEquate, N_Term::OpAXAux});
    OpAXAux[1]->handle.insert(OpAXAux[1]->handle.end(), {N_Term::TOpBinXor,  N_Term::OpEquate, N_Term::OpAXAux});
    OpAXAux[2]->handle.insert(OpAXAux[2]->handle.end(), {N_Term::Empty});

    OpEquate[0]->handle.insert(OpEquate[0]->handle.end(), {N_Term::OpCompare, N_Term::OpEAux});

    OpEAux[0]->handle.insert(OpEAux[0]->handle.end(), {N_Term::TOpEqual, N_Term::OpCompare, N_Term::OpEAux});
    OpEAux[1]->handle.insert(OpEAux[1]->handle.end(), {N_Term::TOpDiff,  N_Term::OpCompare, N_Term::OpEAux});
    OpEAux[2]->handle.insert(OpEAux[2]->handle.end(), {N_Term::Empty});

    OpCompare[0]->handle.insert(OpCompare[0]->handle.end(), {N_Term::NOpAdd, N_Term::OpCAux});
    
    OpCAux[0]->handle.insert(OpCAux[0]->handle.end(), {N_Term::TOpLesser, N_Term::NOpAdd, N_Term::OpCAux});
    OpCAux[1]->handle.insert(OpCAux[1]->handle.end(), {N_Term::TOpGreater,  N_Term::NOpAdd, N_Term::OpCAux});
    OpCAux[2]->handle.insert(OpCAux[2]->handle.end(), {N_Term::TOpLEqual,  N_Term::NOpAdd, N_Term::OpCAux});
    OpCAux[3]->handle.insert(OpCAux[3]->handle.end(), {N_Term::TOpGEqual,  N_Term::NOpAdd, N_Term::OpCAux});
    OpCAux[4]->handle.insert(OpCAux[4]->handle.end(), {N_Term::Empty});

    OpAdd[0]->handle.insert(OpAdd[0]->handle.end(), {N_Term::NOpMult, N_Term::OpAddAux});

    OpAddAux[0]->handle.insert(OpAddAux[0]->handle.end(), {N_Term::TOpAdd, N_Term::NOpMult, N_Term::OpAddAux});
    OpAddAux[1]->handle.insert(OpAddAux[1]->handle.end(), {N_Term::TOpMult,  N_Term::NOpMult, N_Term::OpAddAux});
    OpAddAux[2]->handle.insert(OpAddAux[2]->handle.end(), {N_Term::Empty});

    OpMult[0]->handle.insert(OpMult[0]->handle.end(), {N_Term::OpUnary, N_Term::OpMAux});
    
    OpMAux[0]->handle.insert(OpMAux[0]->handle.end(), {N_Term::TOpMult, N_Term::OpUnary, N_Term::OpMAux});
    OpMAux[1]->handle.insert(OpMAux[1]->handle.end(), {N_Term::TOpDiv,  N_Term::OpUnary, N_Term::OpMAux});
    OpMAux[2]->handle.insert(OpMAux[2]->handle.end(), {N_Term::TOpRem,  N_Term::OpUnary, N_Term::OpMAux});
    OpMAux[3]->handle.insert(OpMAux[3]->handle.end(), {N_Term::Empty});

    OpUnary[0]->handle.insert( OpUnary[0]->handle.end(), {N_Term::TOpNot, N_Term::OpUnary});
    OpUnary[1]->handle.insert( OpUnary[1]->handle.end(), {N_Term::TOpMinus, N_Term::OpUnary});
    OpUnary[2]->handle.insert( OpUnary[2]->handle.end(), {N_Term::TOpAdd, N_Term::OpUnary});
    OpUnary[3]->handle.insert( OpUnary[3]->handle.end(), {N_Term::Value});
    
    Value[0]->handle.insert(Value[0]->handle.end(), {N_Term::TCteInt});
    Value[1]->handle.insert(Value[1]->handle.end(), {N_Term::TCteString});
    Value[2]->handle.insert(Value[2]->handle.end(), {N_Term::TCteChar});
    Value[3]->handle.insert(Value[3]->handle.end(), {N_Term::TCteFloat});
    Value[4]->handle.insert(Value[4]->handle.end(), {N_Term::TCteBool});
    Value[5]->handle.insert(Value[5]->handle.end(), {N_Term::TId, N_Term::ValueAux});
    
    ValueAux[0]->handle.insert(ValueAux[0]->handle.end(), {N_Term::TParenth1, N_Term::ParamList, N_Term::TParenth2});
    ValueAux[1]->handle.insert(ValueAux[1]->handle.end(), {N_Term::Empty});

    ParamList[0]->handle.insert(ParamList[0]->handle.end(), {N_Term::TId, N_Term::ParamLAux});
    ParamList[1]->handle.insert(ParamList[1]->handle.end(), {N_Term::Empty});

    ParamLAux[0]->handle.insert(ParamLAux[0]->handle.end(), {N_Term::TComma,N_Term::TId, N_Term::ParamLAux});
    ParamLAux[1]->handle.insert(ParamLAux[1]->handle.end(), {N_Term::Empty});

    OpCList[0]->handle.insert(OpCList[0]->handle.end(), {N_Term::TComma,N_Term::OpConc, N_Term::OpCList});
    OpCList[1]->handle.insert(OpCList[1]->handle.end(), {N_Term::Empty});

    Type[0]->handle.insert(Type[0]->handle.end(), {N_Term::TChar});
    Type[1]->handle.insert(Type[1]->handle.end(), {N_Term::TInteger});
    Type[2]->handle.insert(Type[2]->handle.end(), {N_Term::TFloat});
    Type[3]->handle.insert(Type[3]->handle.end(), {N_Term::TString});
    Type[4]->handle.insert(Type[4]->handle.end(), {N_Term::TVoid});
    Type[5]->handle.insert(Type[5]->handle.end(), {N_Term::TBoolean});
    

    
    /*inserindo n vector de produções*/
    
    productions.push_back(Decls[0]);
    productions.push_back(Decls[1]);

    productions.push_back(Decl[0]);

    productions.push_back(DeclAux[0]);
    productions.push_back(DeclAux[1]);

    productions.push_back(DeclBux[0]);
    productions.push_back(DeclBux[1]);

    productions.push_back(ParamDef[0]);
    productions.push_back(ParamDef[1]);

    productions.push_back(ParamDAux[0]);
    productions.push_back(ParamDAux[1]);

    productions.push_back(StmList[0]);
    productions.push_back(StmList[1]);

    productions.push_back(Stm[0]);
    productions.push_back(Stm[1]);
    productions.push_back(Stm[2]);
    productions.push_back(Stm[3]);
    productions.push_back(Stm[4]);

    productions.push_back(ElseStm[0]);
    productions.push_back(ElseStm[1]);

    productions.push_back(NormalStm[0]);
    productions.push_back(NormalStm[1]);
    productions.push_back(NormalStm[2]);
    productions.push_back(NormalStm[3]);
    productions.push_back(NormalStm[4]);
    productions.push_back(NormalStm[5]);

    productions.push_back(VarDecl[0]);

    productions.push_back(VarList[0]);
    productions.push_back(VarList[1]);

    productions.push_back(Init[0]);
    productions.push_back(Init[1]);

    productions.push_back(InitAux[0]);
    productions.push_back(InitAux[1]);

    productions.push_back(Array[0]);
    productions.push_back(Array[1]);

    productions.push_back(ArrayAux[0]);
    productions.push_back(ArrayAux[1]);

    productions.push_back(OpConc[0]);
    productions.push_back(OpConc[1]);

    productions.push_back(OpCoAux[0]);
    productions.push_back(OpCoAux[1]);
    productions.push_back(OpCoAux[2]);

    productions.push_back(OpCoBux[0]);
    productions.push_back(OpCoBux[1]);
    productions.push_back(OpCoBux[2]);

    productions.push_back(OpOr[0]);

    productions.push_back(OpOrAux[0]);
    productions.push_back(OpOrAux[1]);

    productions.push_back(OpAndXor[0]);

    productions.push_back(OpAXAux[0]);
    productions.push_back(OpAXAux[1]);
    productions.push_back(OpAXAux[2]);

    productions.push_back(OpEquate[0]);

    productions.push_back(OpEAux[0]);
    productions.push_back(OpEAux[1]);
    productions.push_back(OpEAux[2]);

    productions.push_back(OpCompare[0]);

    productions.push_back(OpCAux[0]);
    productions.push_back(OpCAux[1]);
    productions.push_back(OpCAux[2]);
    productions.push_back(OpCAux[3]);
    productions.push_back(OpCAux[4]);

    productions.push_back(OpAdd[0]);

    productions.push_back(OpAddAux[0]);
    productions.push_back(OpAddAux[1]);
    productions.push_back(OpAddAux[2]);

    productions.push_back(OpMult[0]);

    productions.push_back(OpMAux[0]);
    productions.push_back(OpMAux[1]);
    productions.push_back(OpMAux[2]);
    productions.push_back(OpMAux[4]);

    productions.push_back(OpUnary[0]);
    productions.push_back(OpUnary[1]);
    productions.push_back(OpUnary[2]);
    productions.push_back(OpUnary[3]);

    productions.push_back(Value[0]);
    productions.push_back(Value[1]);
    productions.push_back(Value[2]);
    productions.push_back(Value[3]);
    productions.push_back(Value[4]);
    productions.push_back(Value[5]);

    productions.push_back(ValueAux[0]);
    productions.push_back(ValueAux[1]);

    productions.push_back(ParamList[0]);
    productions.push_back(ParamList[1]);

    productions.push_back(ParamLAux[0]);
    productions.push_back(ParamLAux[1]);

    productions.push_back(OpCList[0]);
    productions.push_back(OpCList[1]);

    productions.push_back(Type[0]);
    productions.push_back(Type[1]);
    productions.push_back(Type[2]);
    productions.push_back(Type[3]);
    productions.push_back(Type[4]);
    productions.push_back(Type[5]);

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

void SyntaticAnalyzer::init_stack() {
    prod_stack.push(N_Term::Decls);
}

void SyntaticAnalyzer::push_prod(Production* p) {
    int quant = p->handle.size();
    int i;

    for(i = quant-1; i >= 0; i--) {
        prod_stack.push(p->handle[i]);
    }
}

void SyntaticAnalyzer::print_prod(Production* p) {
    std::cout << get_readable(p->n_category) << " = ";
    
    int quant = p->handle.size();
    int i;
    
    for(i = 0; i < quant; i++) {
        if(p->handle[i] > N_Term::Empty) {
            std::cout << get_cat_readable(n_term_to_cat(p->handle[i])) << " ";
        }
        else {
            std::cout << get_readable(p->handle[i]) << " ";
        }
    }
    std::cout << "\n";
}

void SyntaticAnalyzer::init_table() {
    analysis_table[N_Term::Decls][Category::Char] = 0;
    analysis_table[N_Term::Decls][Category::Integer] = 0;
    analysis_table[N_Term::Decls][Category::Float] = 0;
    analysis_table[N_Term::Decls][Category::String] = 0;
    analysis_table[N_Term::Decls][Category::Void] = 0;
    analysis_table[N_Term::Decls][Category::Boolean] = 0;
    analysis_table[N_Term::Decls][Category::Eof] = 1;

    analysis_table[N_Term::Decl][Category::Char] = 2;
    analysis_table[N_Term::Decl][Category::Integer] = 2;
    analysis_table[N_Term::Decl][Category::Float] = 2;
    analysis_table[N_Term::Decl][Category::String] = 2;
    analysis_table[N_Term::Decl][Category::Void] = 2;
    analysis_table[N_Term::Decl][Category::Boolean] = 2;

    
    analysis_table[N_Term::DeclAux][Category::Bracket1] = 4;
    analysis_table[N_Term::DeclAux][Category::Id] = 3;

    analysis_table[N_Term::DeclBux][Category::Parenth1] = 6;
    analysis_table[N_Term::DeclBux][Category::Bracket1] = 5;
    analysis_table[N_Term::DeclBux][Category::Assign] = 6;
    analysis_table[N_Term::DeclBux][Category::Comma] = 6;
    
    analysis_table[N_Term::ParamDef][Category::Char] = 7;
    analysis_table[N_Term::ParamDef][Category::Integer] = 7;
    analysis_table[N_Term::ParamDef][Category::Float] = 7;
    analysis_table[N_Term::ParamDef][Category::String] = 7;
    analysis_table[N_Term::ParamDef][Category::Void] = 7;
    analysis_table[N_Term::ParamDef][Category::Boolean] = 7;
    analysis_table[N_Term::ParamDef][Category::Parenth2] = 8;

    analysis_table[N_Term::ParamDAux][Category::Parenth2] = 10;
    analysis_table[N_Term::ParamDAux][Category::Comma] = 9;

    analysis_table[N_Term::StmList][Category::CtrlIf] = 11;
    analysis_table[N_Term::StmList][Category::LoopWhile] = 11;
    analysis_table[N_Term::StmList][Category::LoopFor] = 11;
    analysis_table[N_Term::StmList][Category::Break] = 11;
    analysis_table[N_Term::StmList][Category::Return] = 11;
    analysis_table[N_Term::StmList][Category::Input] = 11;
    analysis_table[N_Term::StmList][Category::Output] = 11;
    analysis_table[N_Term::StmList][Category::Char] = 11;
    analysis_table[N_Term::StmList][Category::Integer] = 11;
    analysis_table[N_Term::StmList][Category::Float] = 11;
    analysis_table[N_Term::StmList][Category::String] = 11;
    analysis_table[N_Term::StmList][Category::Void] = 11;
    analysis_table[N_Term::StmList][Category::Boolean] = 11;
    analysis_table[N_Term::StmList][Category::Parenth1] = 11;
    analysis_table[N_Term::StmList][Category::Braces2] = 12;
    analysis_table[N_Term::StmList][Category::OpAdd] = 11;
    analysis_table[N_Term::StmList][Category::OpMinus] = 11;
    analysis_table[N_Term::StmList][Category::OpNot] = 11;
    analysis_table[N_Term::StmList][Category::Terminator] = 11;
    analysis_table[N_Term::StmList][Category::CteInt] = 11;
    analysis_table[N_Term::StmList][Category::CteString] = 11;
    analysis_table[N_Term::StmList][Category::CteChar] = 11;
    analysis_table[N_Term::StmList][Category::CteFloat] = 11;
    analysis_table[N_Term::StmList][Category::CteBool] = 11;
    analysis_table[N_Term::StmList][Category::Id] = 11;

    analysis_table[N_Term::Stm][Category::CtrlIf] = 14;
    analysis_table[N_Term::Stm][Category::LoopWhile] = 15;
    analysis_table[N_Term::Stm][Category::LoopFor] = 16;
    analysis_table[N_Term::Stm][Category::Break] = 17;
    analysis_table[N_Term::Stm][Category::Return] = 17;
    analysis_table[N_Term::Stm][Category::Input] = 17;
    analysis_table[N_Term::Stm][Category::Output] = 17;
    analysis_table[N_Term::Stm][Category::Char] = 13;
    analysis_table[N_Term::Stm][Category::Integer] = 13;
    analysis_table[N_Term::Stm][Category::Float] = 13;
    analysis_table[N_Term::Stm][Category::String] = 13;
    analysis_table[N_Term::Stm][Category::Void] = 13;
    analysis_table[N_Term::Stm][Category::Boolean] = 13;
    analysis_table[N_Term::Stm][Category::Parenth1] = 17;
    analysis_table[N_Term::Stm][Category::OpAdd] = 17;
    analysis_table[N_Term::Stm][Category::OpMinus] = 17;
    analysis_table[N_Term::Stm][Category::OpNot] = 17;
    analysis_table[N_Term::Stm][Category::Terminator] = 17;
    analysis_table[N_Term::Stm][Category::CteInt] = 17;
    analysis_table[N_Term::Stm][Category::CteString] = 17;
    analysis_table[N_Term::Stm][Category::CteChar] = 17;
    analysis_table[N_Term::Stm][Category::CteFloat] = 17;
    analysis_table[N_Term::Stm][Category::CteBool] = 17;
    analysis_table[N_Term::Stm][Category::Id] = 17;

    analysis_table[N_Term::ElseStm][Category::CtrlIf] = 19;
    analysis_table[N_Term::ElseStm][Category::CtrlElse] = 18;
    analysis_table[N_Term::ElseStm][Category::LoopWhile] = 19;
    analysis_table[N_Term::ElseStm][Category::LoopFor] = 19;
    analysis_table[N_Term::ElseStm][Category::Break] = 19;
    analysis_table[N_Term::ElseStm][Category::Return] = 19;
    analysis_table[N_Term::ElseStm][Category::Input] = 19;
    analysis_table[N_Term::ElseStm][Category::Output] = 19;
    analysis_table[N_Term::ElseStm][Category::Char] = 19;
    analysis_table[N_Term::ElseStm][Category::Integer] = 19;
    analysis_table[N_Term::ElseStm][Category::Float] = 19;
    analysis_table[N_Term::ElseStm][Category::String] = 19;
    analysis_table[N_Term::ElseStm][Category::Void] = 19;
    analysis_table[N_Term::ElseStm][Category::Boolean] = 19;
    analysis_table[N_Term::ElseStm][Category::Parenth1] = 19;
    analysis_table[N_Term::ElseStm][Category::Braces2] = 19;
    analysis_table[N_Term::ElseStm][Category::OpAdd] = 19;
    analysis_table[N_Term::ElseStm][Category::OpMinus] = 19;
    analysis_table[N_Term::ElseStm][Category::OpNot] = 19;
    analysis_table[N_Term::ElseStm][Category::Terminator] = 19;
    analysis_table[N_Term::ElseStm][Category::CteInt] = 19;
    analysis_table[N_Term::ElseStm][Category::CteString] = 19;
    analysis_table[N_Term::ElseStm][Category::CteChar] = 19;
    analysis_table[N_Term::ElseStm][Category::CteFloat] = 19;
    analysis_table[N_Term::ElseStm][Category::CteBool] = 19;
    analysis_table[N_Term::ElseStm][Category::Id] = 19;

    analysis_table[N_Term::NormalStm][Category::Break] = 21;
    analysis_table[N_Term::NormalStm][Category::Return] = 22;
    analysis_table[N_Term::NormalStm][Category::Input] = 24;
    analysis_table[N_Term::NormalStm][Category::Output] = 25;
    analysis_table[N_Term::NormalStm][Category::Parenth1] = 20;
    analysis_table[N_Term::NormalStm][Category::OpAdd] = 20;
    analysis_table[N_Term::NormalStm][Category::OpMinus] = 20;
    analysis_table[N_Term::NormalStm][Category::OpNot] = 20;
    analysis_table[N_Term::NormalStm][Category::Terminator] = 23;
    analysis_table[N_Term::NormalStm][Category::CteInt] = 20;
    analysis_table[N_Term::NormalStm][Category::CteString] = 20;
    analysis_table[N_Term::NormalStm][Category::CteChar] = 20;
    analysis_table[N_Term::NormalStm][Category::CteFloat] = 20;
    analysis_table[N_Term::NormalStm][Category::CteBool] = 20;
    analysis_table[N_Term::NormalStm][Category::Id] = 20;

    
    analysis_table[N_Term::VarDecl][Category::Char] = 26;
    analysis_table[N_Term::VarDecl][Category::Integer] = 26;
    analysis_table[N_Term::VarDecl][Category::Float] = 26;
    analysis_table[N_Term::VarDecl][Category::String] = 26;
    analysis_table[N_Term::VarDecl][Category::Void] = 26;
    analysis_table[N_Term::VarDecl][Category::Boolean] = 26;

    
    analysis_table[N_Term::VarList][Category::Comma] = 27;
    analysis_table[N_Term::VarList][Category::Terminator] = 28;

    analysis_table[N_Term::NInit][Category::Assign] = 29;
    analysis_table[N_Term::NInit][Category::Comma] = 30;
    analysis_table[N_Term::NInit][Category::Terminator] = 30;
    
    analysis_table[N_Term::InitAux][Category::Parenth1] = 31;
    analysis_table[N_Term::InitAux][Category::Braces1] = 32;
    analysis_table[N_Term::InitAux][Category::OpAdd] = 31;
    analysis_table[N_Term::InitAux][Category::OpMinus] = 31;
    analysis_table[N_Term::InitAux][Category::OpNot] = 31;
    analysis_table[N_Term::InitAux][Category::CteInt] = 31;
    analysis_table[N_Term::InitAux][Category::CteString] = 31;
    analysis_table[N_Term::InitAux][Category::CteChar] = 31;
    analysis_table[N_Term::InitAux][Category::CteFloat] = 31;
    analysis_table[N_Term::InitAux][Category::CteBool] = 31;
    analysis_table[N_Term::InitAux][Category::Id] = 31;

    analysis_table[N_Term::Array][Category::Bracket1] = 33;
    analysis_table[N_Term::Array][Category::Assign] = 34;
    analysis_table[N_Term::Array][Category::Comma] = 34;
    analysis_table[N_Term::Array][Category::Terminator] = 34;
    
    analysis_table[N_Term::ArrayAux][Category::Parenth1] = 35;
    analysis_table[N_Term::ArrayAux][Category::Bracket2] = 36;
    analysis_table[N_Term::ArrayAux][Category::OpAdd] = 35;
    analysis_table[N_Term::ArrayAux][Category::OpMinus] = 35;
    analysis_table[N_Term::ArrayAux][Category::OpNot] = 35;
    analysis_table[N_Term::ArrayAux][Category::CteInt] = 35;
    analysis_table[N_Term::ArrayAux][Category::CteString] = 35;
    analysis_table[N_Term::ArrayAux][Category::CteChar] = 35;
    analysis_table[N_Term::ArrayAux][Category::CteFloat] = 35;
    analysis_table[N_Term::ArrayAux][Category::CteBool] = 35;
    analysis_table[N_Term::ArrayAux][Category::Id] = 35;

    analysis_table[N_Term::OpConc][Category::Parenth1] = 38;
    analysis_table[N_Term::OpConc][Category::OpAdd] = 37;
    analysis_table[N_Term::OpConc][Category::OpMinus] = 37;
    analysis_table[N_Term::OpConc][Category::OpNot] = 37;
    analysis_table[N_Term::OpConc][Category::CteInt] = 37;
    analysis_table[N_Term::OpConc][Category::CteString] = 37;
    analysis_table[N_Term::OpConc][Category::CteChar] = 37;
    analysis_table[N_Term::OpConc][Category::CteFloat] = 37;
    analysis_table[N_Term::OpConc][Category::CteBool] = 37;
    analysis_table[N_Term::OpConc][Category::Id] = 37;

    analysis_table[N_Term::OpCoAux][Category::Parenth2] = 41;
    analysis_table[N_Term::OpCoAux][Category::Braces2] = 41;
    analysis_table[N_Term::OpCoAux][Category::Bracket2] = 41;
    analysis_table[N_Term::OpCoAux][Category::OpConcat] = 39;
    analysis_table[N_Term::OpCoAux][Category::Assign] = 40;
    analysis_table[N_Term::OpCoAux][Category::Comma] = 41;
    analysis_table[N_Term::OpCoAux][Category::Terminator] = 41;

    analysis_table[N_Term::OpCoBux][Category::Char] = 42;
    analysis_table[N_Term::OpCoBux][Category::Integer] = 42;
    analysis_table[N_Term::OpCoBux][Category::Float] = 42;
    analysis_table[N_Term::OpCoBux][Category::String] = 42;
    analysis_table[N_Term::OpCoBux][Category::Void] = 42;
    analysis_table[N_Term::OpCoBux][Category::Boolean] = 42;
    analysis_table[N_Term::OpCoBux][Category::Parenth1] = 44;
    analysis_table[N_Term::OpCoBux][Category::OpAdd] = 43;
    analysis_table[N_Term::OpCoBux][Category::OpMinus] = 43;
    analysis_table[N_Term::OpCoBux][Category::OpNot] = 43;
    analysis_table[N_Term::OpCoBux][Category::CteInt] = 43;
    analysis_table[N_Term::OpCoBux][Category::CteString] = 43;
    analysis_table[N_Term::OpCoBux][Category::CteChar] = 43;
    analysis_table[N_Term::OpCoBux][Category::CteFloat] = 43;
    analysis_table[N_Term::OpCoBux][Category::CteBool] = 43;
    analysis_table[N_Term::OpCoBux][Category::Id] = 43;

    analysis_table[N_Term::NOpOr][Category::OpAdd] = 45;
    analysis_table[N_Term::NOpOr][Category::OpMinus] = 45;
    analysis_table[N_Term::NOpOr][Category::OpNot] = 45;
    analysis_table[N_Term::NOpOr][Category::CteInt] = 45;
    analysis_table[N_Term::NOpOr][Category::CteString] = 45;
    analysis_table[N_Term::NOpOr][Category::CteChar] = 45;
    analysis_table[N_Term::NOpOr][Category::CteFloat] = 45;
    analysis_table[N_Term::NOpOr][Category::CteBool] = 45;
    analysis_table[N_Term::NOpOr][Category::Id] = 45;

    analysis_table[N_Term::OpOrAux][Category::Parenth2] = 47;
    analysis_table[N_Term::OpOrAux][Category::Braces2] = 47;
    analysis_table[N_Term::OpOrAux][Category::Bracket2] = 47;
    analysis_table[N_Term::OpOrAux][Category::OpConcat] = 47;
    analysis_table[N_Term::OpOrAux][Category::OpOr] = 46;
    analysis_table[N_Term::OpOrAux][Category::Assign] = 47;
    analysis_table[N_Term::OpOrAux][Category::Comma] = 47;
    analysis_table[N_Term::OpOrAux][Category::Terminator] = 47;

    analysis_table[N_Term::OpAndXor][Category::OpAdd] = 48;
    analysis_table[N_Term::OpAndXor][Category::OpMinus] = 48;
    analysis_table[N_Term::OpAndXor][Category::OpNot] = 48;
    analysis_table[N_Term::OpAndXor][Category::CteInt] = 48;
    analysis_table[N_Term::OpAndXor][Category::CteString] = 48;
    analysis_table[N_Term::OpAndXor][Category::CteChar] = 48;
    analysis_table[N_Term::OpAndXor][Category::CteFloat] = 48;
    analysis_table[N_Term::OpAndXor][Category::CteBool] = 48;
    analysis_table[N_Term::OpAndXor][Category::Id] = 48;

    analysis_table[N_Term::OpAXAux][Category::Parenth2] = 51;
    analysis_table[N_Term::OpAXAux][Category::Braces2] = 51;
    analysis_table[N_Term::OpAXAux][Category::Bracket2] = 51;
    analysis_table[N_Term::OpAXAux][Category::OpConcat] = 51;
    analysis_table[N_Term::OpAXAux][Category::OpBinXor] = 51;
    analysis_table[N_Term::OpAXAux][Category::OpAnd] = 49;
    analysis_table[N_Term::OpAXAux][Category::OpOr] = 51;
    analysis_table[N_Term::OpAXAux][Category::Assign] = 51;
    analysis_table[N_Term::OpAXAux][Category::Comma] = 51;
    analysis_table[N_Term::OpAXAux][Category::Terminator] = 51;

    analysis_table[N_Term::OpEquate][Category::OpAdd] = 52;
    analysis_table[N_Term::OpEquate][Category::OpMinus] = 52;
    analysis_table[N_Term::OpEquate][Category::OpNot] = 52;
    analysis_table[N_Term::OpEquate][Category::CteInt] = 52;
    analysis_table[N_Term::OpEquate][Category::CteString] = 52;
    analysis_table[N_Term::OpEquate][Category::CteChar] = 52;
    analysis_table[N_Term::OpEquate][Category::CteFloat] = 52;
    analysis_table[N_Term::OpEquate][Category::CteBool] = 52;
    analysis_table[N_Term::OpEquate][Category::Id] = 52;

    
    analysis_table[N_Term::OpEAux][Category::Parenth2] = 55;
    analysis_table[N_Term::OpEAux][Category::Braces2] = 55;
    analysis_table[N_Term::OpEAux][Category::Bracket2] = 55;
    analysis_table[N_Term::OpEAux][Category::OpConcat] = 55;
    analysis_table[N_Term::OpEAux][Category::OpEqual] = 53;
    analysis_table[N_Term::OpEAux][Category::OpDiff] = 54;
    analysis_table[N_Term::OpEAux][Category::OpBinXor] = 55;
    analysis_table[N_Term::OpEAux][Category::OpAnd] = 55;
    analysis_table[N_Term::OpEAux][Category::OpOr] = 55;
    analysis_table[N_Term::OpEAux][Category::Assign] = 55;
    analysis_table[N_Term::OpEAux][Category::Comma] = 55;
    analysis_table[N_Term::OpEAux][Category::Terminator] = 55;

    analysis_table[N_Term::OpCompare][Category::OpAdd] = 56;
    analysis_table[N_Term::OpCompare][Category::OpMinus] = 56;
    analysis_table[N_Term::OpCompare][Category::OpNot] = 56;
    analysis_table[N_Term::OpCompare][Category::CteInt] = 56;
    analysis_table[N_Term::OpCompare][Category::CteString] = 56;
    analysis_table[N_Term::OpCompare][Category::CteChar] = 56;
    analysis_table[N_Term::OpCompare][Category::CteFloat] = 56;
    analysis_table[N_Term::OpCompare][Category::CteBool] = 56;
    analysis_table[N_Term::OpCompare][Category::Id] = 56;

    analysis_table[N_Term::OpCAux][Category::Parenth2] = 61;
    analysis_table[N_Term::OpCAux][Category::Braces2] = 61;
    analysis_table[N_Term::OpCAux][Category::Bracket2] = 61;
    analysis_table[N_Term::OpCAux][Category::OpConcat] = 61;
    analysis_table[N_Term::OpCAux][Category::OpLesser] = 57;
    analysis_table[N_Term::OpCAux][Category::OpGreater] = 58;
    analysis_table[N_Term::OpCAux][Category::OpLEqual] = 59;
    analysis_table[N_Term::OpCAux][Category::OpGEqual] = 60;
    analysis_table[N_Term::OpCAux][Category::OpEqual] = 61;
    analysis_table[N_Term::OpCAux][Category::OpDiff] = 61;
    analysis_table[N_Term::OpCAux][Category::OpBinXor] = 61;
    analysis_table[N_Term::OpCAux][Category::OpAnd] = 61;
    analysis_table[N_Term::OpCAux][Category::OpOr] = 61;
    analysis_table[N_Term::OpCAux][Category::Assign] = 61;
    analysis_table[N_Term::OpCAux][Category::Comma] = 61;
    analysis_table[N_Term::OpCAux][Category::Terminator] = 61;

    analysis_table[N_Term::NOpAdd][Category::OpAdd] = 62;
    analysis_table[N_Term::NOpAdd][Category::OpMinus] = 62;
    analysis_table[N_Term::NOpAdd][Category::OpNot] = 62;
    analysis_table[N_Term::NOpAdd][Category::CteInt] = 62;
    analysis_table[N_Term::NOpAdd][Category::CteString] = 62;
    analysis_table[N_Term::NOpAdd][Category::CteChar] = 62;
    analysis_table[N_Term::NOpAdd][Category::CteFloat] = 62;
    analysis_table[N_Term::NOpAdd][Category::CteBool] = 62;
    analysis_table[N_Term::NOpAdd][Category::Id] = 62;

    analysis_table[N_Term::OpAddAux][Category::Parenth2] = 65;
    analysis_table[N_Term::OpAddAux][Category::Braces2] = 65;
    analysis_table[N_Term::OpAddAux][Category::Bracket2] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpAdd] = 63;
    analysis_table[N_Term::OpAddAux][Category::OpMinus] = 64;
    analysis_table[N_Term::OpAddAux][Category::OpConcat] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpLesser] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpGreater] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpLEqual] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpGEqual] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpEqual] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpDiff] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpBinXor] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpAnd] = 65;
    analysis_table[N_Term::OpAddAux][Category::OpOr] = 65;
    analysis_table[N_Term::OpAddAux][Category::Assign] = 65;
    analysis_table[N_Term::OpAddAux][Category::Comma] = 65;
    analysis_table[N_Term::OpAddAux][Category::Terminator] = 65;

    analysis_table[N_Term::NOpMult][Category::OpAdd] = 66;
    analysis_table[N_Term::NOpMult][Category::OpMinus] = 66;
    analysis_table[N_Term::NOpMult][Category::OpNot] = 66;
    analysis_table[N_Term::NOpMult][Category::CteInt] = 66;
    analysis_table[N_Term::NOpMult][Category::CteString] = 66;
    analysis_table[N_Term::NOpMult][Category::CteChar] = 66;
    analysis_table[N_Term::NOpMult][Category::CteFloat] = 66;
    analysis_table[N_Term::NOpMult][Category::CteBool] = 66;
    analysis_table[N_Term::NOpMult][Category::Id] = 66;
    
    analysis_table[N_Term::OpMAux][Category::Parenth2] = 70;
    analysis_table[N_Term::OpMAux][Category::Braces2] = 70;
    analysis_table[N_Term::OpMAux][Category::Bracket2] = 70;
    analysis_table[N_Term::OpMAux][Category::OpAdd] = 70;
    analysis_table[N_Term::OpMAux][Category::OpMinus] = 70;
    analysis_table[N_Term::OpMAux][Category::OpMult] = 67;
    analysis_table[N_Term::OpMAux][Category::OpDiv] = 68;
    analysis_table[N_Term::OpMAux][Category::OpRem] = 69;
    analysis_table[N_Term::OpMAux][Category::OpConcat] = 70;
    analysis_table[N_Term::OpMAux][Category::OpLesser] = 70;
    analysis_table[N_Term::OpMAux][Category::OpGreater] = 70;
    analysis_table[N_Term::OpMAux][Category::OpLEqual] = 70;
    analysis_table[N_Term::OpMAux][Category::OpGEqual] = 70;
    analysis_table[N_Term::OpMAux][Category::OpEqual] = 70;
    analysis_table[N_Term::OpMAux][Category::OpDiff] = 70;
    analysis_table[N_Term::OpMAux][Category::OpBinXor] = 70;
    analysis_table[N_Term::OpMAux][Category::OpAnd] = 70;
    analysis_table[N_Term::OpMAux][Category::OpOr] = 70;
    analysis_table[N_Term::OpMAux][Category::Assign] = 70;
    analysis_table[N_Term::OpMAux][Category::Comma] = 70;
    analysis_table[N_Term::OpMAux][Category::Terminator] = 70;

    analysis_table[N_Term::OpUnary][Category::OpAdd] = 73;
    analysis_table[N_Term::OpUnary][Category::OpMinus] = 72;
    analysis_table[N_Term::OpUnary][Category::OpNot] = 71;
    analysis_table[N_Term::OpUnary][Category::CteInt] = 74;
    analysis_table[N_Term::OpUnary][Category::CteString] = 74;
    analysis_table[N_Term::OpUnary][Category::CteChar] = 74;
    analysis_table[N_Term::OpUnary][Category::CteFloat] = 74;
    analysis_table[N_Term::OpUnary][Category::CteBool] = 74;
    analysis_table[N_Term::OpUnary][Category::Id] = 74;

    analysis_table[N_Term::Value][Category::CteInt] = 75;
    analysis_table[N_Term::Value][Category::CteString] = 76;
    analysis_table[N_Term::Value][Category::CteChar] = 77;
    analysis_table[N_Term::Value][Category::CteFloat] = 78;
    analysis_table[N_Term::Value][Category::CteBool] = 79;
    analysis_table[N_Term::Value][Category::Id] = 80;

    analysis_table[N_Term::ValueAux][Category::Parenth1] = 81;
    analysis_table[N_Term::ValueAux][Category::Parenth2] = 82;
    analysis_table[N_Term::ValueAux][Category::Braces2] = 82;
    analysis_table[N_Term::ValueAux][Category::Bracket2] = 82;
    analysis_table[N_Term::ValueAux][Category::OpAdd] = 82;
    analysis_table[N_Term::ValueAux][Category::OpMinus] = 82;
    analysis_table[N_Term::ValueAux][Category::OpMult] = 82;
    analysis_table[N_Term::ValueAux][Category::OpDiv] = 82;
    analysis_table[N_Term::ValueAux][Category::OpRem] = 82;
    analysis_table[N_Term::ValueAux][Category::OpConcat] = 82;
    analysis_table[N_Term::ValueAux][Category::OpLesser] = 82;
    analysis_table[N_Term::ValueAux][Category::OpGreater] = 82;
    analysis_table[N_Term::ValueAux][Category::OpLEqual] = 82;
    analysis_table[N_Term::ValueAux][Category::OpGEqual] = 82;
    analysis_table[N_Term::ValueAux][Category::OpEqual] = 82;
    analysis_table[N_Term::ValueAux][Category::OpDiff] = 82;
    analysis_table[N_Term::ValueAux][Category::OpBinXor] = 82;
    analysis_table[N_Term::ValueAux][Category::OpAnd] = 82;
    analysis_table[N_Term::ValueAux][Category::OpOr] = 82;
    analysis_table[N_Term::ValueAux][Category::Assign] = 82;
    analysis_table[N_Term::ValueAux][Category::Comma] = 82;
    analysis_table[N_Term::ValueAux][Category::Terminator] = 82;

    analysis_table[N_Term::ParamList][Category::Parenth2] = 84;
    analysis_table[N_Term::ParamList][Category::Id] = 83;

    analysis_table[N_Term::ParamLAux][Category::Parenth2] = 86;
    analysis_table[N_Term::ParamLAux][Category::Comma] = 85;

    analysis_table[N_Term::OpCList][Category::Braces2] = 88;
    analysis_table[N_Term::OpCList][Category::Comma] = 87;

    analysis_table[N_Term::Type][Category::Char] = 89;
    analysis_table[N_Term::Type][Category::Integer] = 90;
    analysis_table[N_Term::Type][Category::Float] = 91;
    analysis_table[N_Term::Type][Category::String] = 92;
    analysis_table[N_Term::Type][Category::Void] = 93;
    analysis_table[N_Term::Type][Category::Boolean] = 94;
}

bool SyntaticAnalyzer::Parse() {

    Production* p = productions[25];
    print_prod(p);
    return true;
}

std::string SyntaticAnalyzer::get_readable(N_Term t) {
    
    switch(t) {
        case N_Term::Decls :
            return "Decls";
        case N_Term::Decl:
            return "Decl";
        case N_Term::DeclAux:
            return "DeclAux";
        case N_Term::DeclBux:
            return "DeclBux";
        case N_Term::ParamDef:
            return "ParamDef";
        case N_Term::ParamDAux:
            return "ParamDAux";
        case N_Term::StmList:
            return "StmList";
        case N_Term::Stm:
            return "Stm";
        case N_Term::ElseStm:
            return "ElseStm";
        case N_Term::NormalStm:
            return "NormalStm";
        case N_Term::VarDecl:
            return "VarDecl";
        case N_Term::VarList:
            return "VarList";
        case N_Term::NInit:
            return "Init";
        case N_Term::InitAux:
            return "InitAux";
        case N_Term::Array:
            return "Array";
        case N_Term::ArrayAux:
            return "ArrayAux";
        case N_Term::OpConc:
            return "OpConc";
        case N_Term::OpCoAux:
            return "OpCoAux";
        case N_Term::NOpOr:
            return "OpOr";
        case N_Term::OpAndXor:
            return "OpAndXor";
        case N_Term::OpOrAux:
            return "OpOrAux";
        case N_Term::OpAXAux:
            return "OpAXAux";
        case N_Term::OpEquate:
            return "OpEquate";
        case N_Term::OpEAux:
            return "OpEAux";
        case N_Term::OpCompare:
            return "OpCompare";
        case N_Term::NOpAdd:
            return "OpAdd";
        case N_Term::NOpMult:
            return "OpMult";
        case N_Term::OpMAux:
            return "OpMAux";
        case N_Term::OpUnary:
            return "OpUnary";
        case N_Term::Value:
            return "Value";
        case N_Term::ValueAux:
            return "ValueAux";
        case N_Term::ParamList:
            return "ParamList";
        case N_Term::ParamLAux:
            return "ParamLAux";
        case N_Term::OpCList:
            return "OpCList";
        case N_Term::Type:
            return "Type";
        case N_Term::Empty:
            return "épsilon";
        default:
            return "";
    }
}

std::string SyntaticAnalyzer::get_cat_readable(Category c) {
    switch(c) {

        case Category::CtrlIf :
            return "'if'";
        case Category::CtrlElse:
            return "'else'";
        case Category::LoopWhile:
            return "'while'";
        case Category::LoopFor:
            return "'for'";
        case Category::Break:
            return "'break'";
        case Category::Return:
            return "'return'";
        case Category::Input:
            return "'input'";
        case Category::Output:
            return "'output'";
        case Category::Integer:
            return "'intr'";
        case Category::Float:
            return "'float'";
        case Category::Char:
            return "'char'";
        case Category::Void:
            return "'void'";
        case Category::String:
            return "'string'";
        case Category::Boolean:
            return "'bool'";
        case Category::Parenth1:
            return "'('";
        case Category::Parenth2:
            return "')'";
        case Category::Braces1:
            return "'{'";
        case Category::Braces2:
            return "'}'";
        case Category::Bracket1:
            return "'['";
        case Category::Bracket2:
            return "']'";
        case Category::OpAdd:
            return "'+'";
        case Category::OpMinus:
            return "'-'";
        case Category::OpDiv:
            return "'/'";
        case Category::OpMult:
            return "'*'";
        case Category::OpRem:
            return "'%'";
        case Category::OpConcat:
            return "'++'";
        case Category::OpGreater:
            return "'>'";
        case Category::OpLesser:
            return "'<'";
        case Category::OpGEqual:
            return "'>='";
        case Category::OpLEqual:
            return "'<='";
        case Category::OpDiff:
            return "'!='";
        case Category::OpEqual:
            return "'==";
        case Category::OpBinXor:
            return "'^'";
        case Category::OpNot:
            return "'!'";
        case Category::OpAnd:
            return "'and'";
        case Category::OpOr:
            return "'or'";
        case Category::Assign:
            return "'='";
        case Category::Comma:
            return "','";
        case Category::Terminator:
            return "';'";
        case Category::Error:
            return "'Error'";
        case Category::Id:
            return "'Id'";
        case Category::CteInt:
            return "'CteInt'";
        case Category::CteFloat:
            return "'CteFloat'";
        case Category::CteString:
            return "'CteString'";
        case Category::CteChar:
            return "'CteChar'";
        case Category::CteBool:
            return "'CteBool'";
        case Category::Eof:
            return "'Eof'";
        default:
            return"'Erro'";
    }
}

Category SyntaticAnalyzer::n_term_to_cat(N_Term n) {

    Category c;
    switch(n) {
        case  N_Term::TOpMult:
            c = Category::OpMult;
            break;
        case N_Term::TOpAdd:
            c = Category::OpAdd;
            break;
        case N_Term::TOpMinus:
            c = Category::OpMinus;
            break;
        case N_Term::TOpConcat:
            c = Category::OpConcat;
            break;
        case N_Term::TOpDiv:
            c = Category::OpDiv;
            break;
        case  N_Term::TOpRem:
            c = Category::OpRem;
            break;
        case N_Term::TOpBinXor:
            c = Category::OpBinXor;
            break;
        case N_Term::TOpLesser:
            c = Category::OpLesser;
            break;
        case N_Term::TOpLEqual:
            c = Category::OpLEqual;
            break;   
        case N_Term::TOpGreater:
            c = Category::OpGreater;
            break;
        case N_Term::TOpGEqual:
            c = Category::OpGEqual;
            break; 
        case N_Term::TAssign:
            c = Category::Assign;
            break;
        case N_Term::TOpEqual:
            c = Category::OpEqual;
            break; 
        case N_Term::TOpNot:
            c = Category::OpNot;
            break;
        case N_Term::TOpDiff:
            c = Category::OpDiff;
            break;
        case N_Term::TBraces1:
            c = Category::Braces1;
            break;
        case N_Term::TBraces2:
            c = Category::Braces2;
            break;
        case N_Term::TParenth1:
            c = Category::Parenth1;
            break;
        case N_Term::TParenth2:
            c = Category::Parenth2;
            break;
        case N_Term::TBracket1:
            c = Category::Bracket1;
            break;
        case N_Term::TBracket2:
            c = Category::Bracket2;
            break;
        case N_Term::TTerminator:
            c = Category::Terminator;
            break;
        case N_Term::TComma:
            c = Category::Comma;
            break;
        case N_Term::TCtrlIf :
            c = Category::CtrlIf;
            break;
        case N_Term::TCtrlElse:
            c = Category::CtrlElse;
            break;
        case N_Term::TLoopWhile:
            c = Category::LoopWhile;
            break;
        case N_Term::TLoopFor:
            c = Category::LoopFor;
            break;
        case N_Term::TBreak:
            c = Category::Break;
            break;
        case N_Term::TReturn:
            c = Category::Return;
            break;
        case N_Term::TInput:
            c = Category::Input;
            break;
        case N_Term::TOutput:
            c = Category::Output;
            break;
        case N_Term::TInteger:
            c = Category::Integer;
            break;
        case N_Term::TFloat:
            c = Category::Float;
            break;
        case N_Term::TChar:
            c = Category::Char;
            break;
        case N_Term::TVoid:
            c = Category::Void;
            break;
        case N_Term::TString:
            c = Category::String;
            break;
        case N_Term::TBoolean:
            c = Category::Boolean;
            break;
        case N_Term::TOpAnd:
            c = Category::OpAnd;
            break;
        case N_Term::TOpOr:
            c = Category::OpGEqual;
            break;
        case N_Term::TId:
            c = Category::Id;
            break;
        case N_Term::TCteInt:
            c = Category::CteInt;
            break;
        case N_Term::TCteFloat:
            c = Category::CteFloat;
            break;
        case N_Term::TCteString:
            c = Category::CteString;
            break;
        case N_Term::TCteChar:
            c = Category::CteChar;
            break;
        case N_Term::TCteBool:
            c = Category::CteBool;
            break;
        default:
            //Caso a categoria seja uma CteChar, CteString, CteInt, CteFloat ou ID
            c = Category::Error;
            break;
    }
    return c;
}