#include "syntaticanalyzer.h"
#include "lexicalanalyzer.h"
#include <stdlib.h>
#include <iostream>

SyntaticAnalyzer::SyntaticAnalyzer(std::string file) {
    lexical = new LexicalAnalyzer(file);
    init_prods();
    //init_table();
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
            std::cout << lexical->get_lex(n_term_to_cat(p->handle[i])) << " ";
        }
        else {
            std::cout << get_readable(p->handle[i]) << " ";
        }
    }
    std::cout << "\n";
}

bool SyntaticAnalyzer::Parse() {

    Production* p = productions[9];
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
        default:
            return "";
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