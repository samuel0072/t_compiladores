#include "syntaticanalyzer.h"
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

    
    /*array*/

    productions[0] = Decls[0];
    productions[1] = Decls[1];

    productions[2] = Decl[0];

    productions[3] = DeclAux[0];
    productions[4] = DeclAux[1];

    productions[5] = DeclBux[0];
    productions[6] = DeclBux[1];

    productions[7] = ParamDef[0];
    productions[8] = ParamDef[1];

    productions[9] = ParamDAux[0];
    productions[10] = ParamDAux[1];

    productions[11] = StmList[0];
    productions[12] = StmList[1];

    productions[13] = Stm[0];
    productions[14] = Stm[1];
    productions[15] = Stm[2];
    productions[16] = Stm[3];
    productions[17] = Stm[4];

    productions[18] = ElseStm[0];
    productions[19] = ElseStm[1];

    productions[20] = NormalStm[0];
    productions[21] = NormalStm[1];
    productions[22] = NormalStm[2];
    productions[23] = NormalStm[3];
    productions[24] = NormalStm[4];
    productions[25] = NormalStm[5];

    productions[26] = VarDecl[0];

    productions[27] = VarList[0];
    productions[28] = VarList[1];

    productions[29] = Init[0];
    productions[30] = Init[1];

    productions[31] = InitAux[0];
    productions[32] = InitAux[1];

    productions[33] = Array[0];
    productions[34] = Array[1];

    productions[35] = ArrayAux[0];
    productions[36] = ArrayAux[1];

    productions[37] = OpConc[0];
    productions[38] = OpConc[1];

    productions[39] = OpCoAux[0];
    productions[40] = OpCoAux[1];
    productions[41] = OpCoAux[2];

    productions[42] = OpCoBux[0];
    productions[43] = OpCoBux[1];
    productions[44] = OpCoBux[2];

    productions[45] = OpOr[0];

    productions[46] = OpOrAux[0];
    productions[47] = OpOrAux[1];

    productions[48] = OpAndXor[0];

    productions[49] = OpAXAux[0];
    productions[50] = OpAXAux[1];
    productions[51] = OpAXAux[2];

    productions[52] = OpEquate[0];

    productions[53] = OpEAux[0];
    productions[54] = OpEAux[1];
    productions[55] = OpEAux[2];

    productions[56] = OpCompare[0];

    productions[57] = OpCAux[0];
    productions[58] = OpCAux[1];
    productions[59] = OpCAux[2];
    productions[60] = OpCAux[3];
    productions[61] = OpCAux[4];

    productions[62] = OpAdd[0];

    productions[63] = OpAddAux[0];
    productions[64] = OpAddAux[1];
    productions[65] = OpAddAux[2];

    productions[66] = OpMult[0];

    productions[67] = OpMAux[0];
    productions[68] = OpMAux[1];
    productions[69] = OpMAux[2];
    productions[70] = OpMAux[4];

    productions[71] = OpUnary[0];
    productions[72] = OpUnary[1];
    productions[73] = OpUnary[2];
    productions[74] = OpUnary[3];

    productions[75] = Value[0];
    productions[76] = Value[1];
    productions[77] = Value[2];
    productions[78] = Value[3];
    productions[79] = Value[4];
    productions[80] = Value[5];

    productions[81] = ValueAux[0];
    productions[82] = ValueAux[1];

    productions[83] = ParamList[0];
    productions[84] = ParamList[1];

    productions[85] = ParamLAux[0];
    productions[86] = ParamLAux[1];

    productions[87] = OpCList[0];
    productions[88] = OpCList[1];

    productions[89] = Type[0];
    productions[90] = Type[1];
    productions[91] = Type[2];
    productions[92] = Type[3];
    productions[93] = Type[4];
    productions[94] = Type[5];

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
    std::cout << p->n_category;
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
        case N_Term::Init:
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
        case N_Term::OpOr:
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
        case N_Term::OpAdd:
            return "OpAdd";
        case N_Term::OpMult:
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